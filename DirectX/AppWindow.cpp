#include "AppWindow.h"


AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	QuadRenderer quad1
	(
		{ 0.80f,0.30f,0.0f },        // INDEX 0
		{ 0.30f,0.30f,0.0f },        // INDEX 1
		{ 0.80f,0.80f,0.0f },        // INDEX 2
		{ 0.30f,0.80f,0.0f }       // INDEX 3
	);

	QuadRenderer quad2
	(
		{ 0.25f,-0.25f,0.0f },    // INDEX 4
		{ -0.25f,-0.25f,0.0f },    // INDEX 5
		{ 0.25f,0.25f,0.0f },        // INDEX 6
		{ -0.25f,0.25f,0.0f }    // INDEX 7
	);

	QuadRenderer quad3
	(
		{ -0.30f,-0.80f,0.0f },    // INDEX 8
		{ -0.80f,-0.80f,0.0f },    // INDEX 9
		{ -0.30f,-0.30f,0.0f },    // INDEX 10
		{ -0.80f,-0.30f,0.0f }    // INDEX 11
	);

	quadList.push_back(quad1);
	quadList.push_back(quad2);
	quadList.push_back(quad3);

	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();


	for (QuadRenderer quad : quadList)
	{
		quad.render();
	}


	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	for (QuadRenderer quad : quadList)
	{
		quad.release();
	}
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}