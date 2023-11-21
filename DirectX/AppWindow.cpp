#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <cmath>
#include "InputSystem.h"
#include "UIManager.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <reactphysics3d/reactphysics3d.h>
#include "PhysicsSystem.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


// constant buffer; this is updated per frame
__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


AppWindow::AppWindow()
{
}



// updating our constant buffer
void AppWindow::update()
{

	

	m_world_cam.setIdentity();
	Matrix4x4 rotX;
	rotX.setIdentity();
	rotX.setRotationX(CameraRot.m_x);
	m_world_cam *= rotX;

	Matrix4x4 rotY;
	rotY.setIdentity();
	rotY.setRotationY(CameraRot.m_y);
	m_world_cam *= rotY;

	CameraPos = CameraPos + m_world_cam.getZDirection() * (m_forward * 0.1f);
	CameraPos = CameraPos + m_world_cam.getXDirection() * (m_rightward * 0.1f);


	m_world_cam.setTranslation(CameraPos);


	m_world_cam.inverse();
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();


	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));
	
	
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	
	
	// Setup Platform/Renderer backends
	GameObjectManager::initialize();
	UIManager::initialize(this->m_hwnd);
	BaseComponentSystem::initialize();
	//ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getD3D11DeviceContext());


}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	
	// run the update for the InputSystem
	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, clear_color.x, clear_color.y, clear_color.z, 1);
	
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	
	
	GameObjectManager::getInstance()->update(m_world_cam);
	
	GameObjectManager::getInstance()->draw();
	UIManager::getInstance()->drawUI();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
	update();




	m_swap_chain->present(true);


	//for camera
	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{

	UIManager::getInstance()->destroy();
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
	BaseComponentSystem::destroy();

}

void AppWindow::onKeyDown(int key)
{
	cout << "onkeydown:\n";
	if (key == 'W')
	{
		for (Cube* cube : CubeList)
		{
			//cube->SetAnimSpeed(5.0f);
		}
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		for (Cube* cube : CubeList)
		{
			//cube->SetAnimSpeed(-5.0f);
		}
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
	}
}

void AppWindow::onKeyUp(int key)
{
	for (Cube* cube : CubeList)
	{
		
	}
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	if (isMouseLeftHold)
	{
		int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
		int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
		CameraRot.m_x += deltaPos.getY() * 0.1f * m_delta_time;
		CameraRot.m_y += deltaPos.getX() * 0.1f * m_delta_time;
	}

}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	isMouseLeftHold = true;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	isMouseLeftHold = false;
}





