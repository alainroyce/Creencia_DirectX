#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <iostream>

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


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

void AppWindow::updateQuadPosition()
{
	constant cc;
	cc.m_time = ::GetTickCount();


	Matrix4x4 temp;


	cc.m_world.setScale(Vector3D(0.5f, 0.5f, 0.5f));

	temp.setIdentity();
	

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 300.0f,
		-4.0f,
		4.0f
	);

	

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{

	std::cout << this->getClientWindowRect().bottom - this->getClientWindowRect().top << std::endl;
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	Cube* cube = new Cube();
	cube->SetScale(Vector3D(0.01f, 0.01f, 0.01f));
	cube->SetPosition(Vector3D(0, 0, 0));
	cube->SetAnimSpeed(5);

	Cube* cube2 = new Cube();
	cube2->SetScale(Vector3D(0.02f, 0.02f, 0.02f));
	cube2->SetPosition(Vector3D(0, -0.3f, 0));
	cube2->SetAnimSpeed(3);

	Cube* cube3 = new Cube();
	cube3->SetScale(Vector3D(0.01f, 0.01f, 0.01f));
	cube3->SetPosition(Vector3D(0, 0.3f, 0));
	cube3->SetAnimSpeed(7);

	Cube* cube4 = new Cube();
	cube4->SetScale(Vector3D(0.02f, 0.02f, 0.02f));
	cube4->SetPosition(Vector3D(0.3f, 0.3f, 0));
	cube4->SetAnimSpeed(7);

	Cube* cube5 = new Cube();
	cube5->SetScale(Vector3D(0.02f, 0.02f, 0.02f));
	cube5->SetPosition(Vector3D(-0.3f, -0.3f, 0));
	cube5->SetAnimSpeed(7);

	CubeList.push_back(cube);
	CubeList.push_back(cube2);
	CubeList.push_back(cube3);
	CubeList.push_back(cube4);
	CubeList.push_back(cube5);




}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (Cube* cube : CubeList)
	{
		cube->update();
	}

	for (Cube* cube : CubeList)
	{
		cube->draw();
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