#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

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

}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	// subscribe this class to the InputSystem
	InputSystem::get()->addListener(this);
	// hides the cursor
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	Cube* cube = new Cube();
	cube->SetScale(Vector3D(0.5f, 0.5f, 0.5f));
	cube->SetPosition(Vector3D(0, 0, 0));
	cube->SetRotation(Vector3D(0, 5.0f, 0));
	cube->SetAnimSpeed(0.0f);

	Cube* cube2 = new Cube();
	cube2->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube2->SetPosition(Vector3D(0, -0.3f, 0));
	cube2->SetAnimSpeed(0.0f);


	Cube* cube3 = new Cube();
	cube3->SetScale(Vector3D(0.1f, 0.1f, 0.1f));
	cube3->SetPosition(Vector3D(0, 0.3f, 0));
	cube3->SetAnimSpeed(0.0f);


	Cube* cube4 = new Cube();
	cube4->SetScale(Vector3D(0.3f, 0.3f, 0.3f));
	cube4->SetPosition(Vector3D(0.3f, 0.3f, 0));
	cube4->SetAnimSpeed(0.0f);


	Cube* cube5 = new Cube();
	cube5->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube5->SetPosition(Vector3D(-0.3f, -0.3f, 0));
	cube5->SetAnimSpeed(0.0f);

	Cube* cube6 = new Cube();
	cube6->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube6->SetPosition(Vector3D(-0.5f, -0.5f, 0));
	cube6->SetAnimSpeed(0.0f);

	Cube* cube7 = new Cube();
	cube7->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube7->SetPosition(Vector3D(0.5f, 0.5f, 0.5));
	cube7->SetAnimSpeed(0.0f);

	Cube* cube8 = new Cube();
	cube8->SetScale(Vector3D(0.3f, 0.3f, 0.3f));
	cube8->SetPosition(Vector3D(0.5f, 0.7f, 0.2));
	cube8->SetAnimSpeed(0.0f);

	Cube* cube9 = new Cube();
	cube9->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube9->SetPosition(Vector3D(0.1f, 0.1f, 0.1));
	cube9->SetAnimSpeed(0.0f);

	Cube* cube10 = new Cube();
	cube10->SetScale(Vector3D(0.2f, 0.2f, 0.2f));
	cube10->SetPosition(Vector3D(0.8f, 0.2f, 0.2));
	cube10->SetAnimSpeed(0.0f);


	CubeList.push_back(cube);
	CubeList.push_back(cube2);
	CubeList.push_back(cube3);
	CubeList.push_back(cube4);
	CubeList.push_back(cube5);
	CubeList.push_back(cube6);
	CubeList.push_back(cube7);
	CubeList.push_back(cube8);
	CubeList.push_back(cube9);
	CubeList.push_back(cube10);
	


}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// run the update for the InputSystem
	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	


	//update();

	for (Cube* cube : CubeList)
	{
		cube->draw();
		cube->update();

	}
	
	
	m_swap_chain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	// subscribe this class to the InputSystem
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

// InputListener virtual method definitions
void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		for (Cube* cube : CubeList)
		{
			cube->SetAnimSpeed(1.0f);

		}
		cout << "W Pressed" << endl;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		for (Cube* cube : CubeList)
		{
			cube->SetAnimSpeed(-1.0f);

		}
		cout << "S Pressed" << endl;
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
	if (key == 'W')
	{
		for (Cube* cube : CubeList)
		{
			cube->SetAnimSpeed(0.0f);

		}
	}
	if (key == 'S')
	{
		for (Cube* cube : CubeList)
		{
			cube->SetAnimSpeed(0.0f);

		}
	}
	// stops the camera
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	// width and height of the screen
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;

	//InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));
}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_pos)
{
	
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_pos)
{
	
}