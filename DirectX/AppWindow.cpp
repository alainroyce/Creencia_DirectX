#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <cmath>
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
	
	Cube* cube = new Cube();
	cube->SetScale(Vector3D(1.0f, 1.0f, 1.0f));
	cube->SetPosition(Vector3D(-1.5f, 1.0f, -3.0f));
	cube->SetRotation(Vector3D(0, 0, 0));
	cube->SetAnimSpeed(0.0f);

	CubeList.push_back(cube);
	
	Cube* cube2 = new Cube();
	cube2->SetScale(Vector3D(1.0f, 1.0f, 1.0f));
	cube2->SetPosition(Vector3D(0, 1.0f, 0));
	cube2->SetAnimSpeed(0.0f);


	Cube* cube3 = new Cube();
	cube3->SetScale(Vector3D(1.0f, 1.0f, 1.0f));
	cube3->SetPosition(Vector3D(2.6f, 1.0f, 2.0));
	cube3->SetAnimSpeed(0.0f);


	Cube* cube4 = new Cube();
	cube4->SetScale(Vector3D(5.0f, 0.05f, 5.0f));
	cube4->SetPosition(Vector3D(0, -0.5f, 0));
	cube4->SetAnimSpeed(0.0f);

	/*
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
	*/

	
	
	
	CubeList.push_back(cube2);
	CubeList.push_back(cube3);
	CubeList.push_back(cube4);
	/*
	CubeList.push_back(cube5);
	CubeList.push_back(cube6);
	CubeList.push_back(cube7);
	CubeList.push_back(cube8);
	CubeList.push_back(cube9);
	CubeList.push_back(cube10);
	
	*/

	/*
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// Create and add 50 cubes to the CubeList
	for (int i = 0; i < 50; i++) {
		Cube* cube = new Cube();

		// Randomly set the position within the range [-0.5, 0.5] for x, y, and z axes
		float randomX = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 0.5f;
		float randomY = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 0.5f;
		float randomZ = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) - 0.5f;

		cube->SetScale(Vector3D(0.2f, 0.2f, 0.2f)); // You can adjust the scale as needed.
		cube->SetPosition(Vector3D(randomX, randomY, randomZ));
		cube->SetAnimSpeed(0.0f);

		CubeList.push_back(cube);
	}*/



}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	/*
	// Update the animation time
	animationTime += m_delta_time;


	
	// Define animation parameters
	float animationDuration = 4.0f;  // Time for one full cycle (1.0 to 0.25 to 1.0)

	// Calculate t based on a sine wave within the range [0, 1]
	const float pi = 3.14;
	float t = (1.0f + sin(animationTime * 2 * pi / animationDuration)) / 2.0f;

	
	Vector3D scale = Vector3D::lerp(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(0.25f, 0.25f, 0.25f), t);

	float posX = sin(animationTime * 2 * pi / animationDuration);
	float posY = cos(animationTime * 2 * pi / animationDuration);
	Vector3D position(posX, posY, 0.0f);

	for (Cube* cube : CubeList) {
		cube->SetScale(scale);
		cube->SetPosition(position);
	}
	*/

	/*
	// Update the animation time
	animationTime += m_delta_time;


	float animationDuration = 5.0f;  


	const float pi = 3.14;
	float t = (1.0f + sin(animationTime * 2 * pi / animationDuration)) / 2.0f;
	Vector3D scale;
	Vector3D position;
	Vector3D rotation;

	
	if (t <= 0.5f) {
		scale = Vector3D::lerp(Vector3D(1.0f, 1.0f, 1.0f), Vector3D(4.0f, 0.05f, 4.0f), t * 2);
		position = Vector3D(0.0f, 0.0f, 0.0f);  
		rotation = Vector3D(0.0f, 0.0f, 0.0f);  
	}
	else {
		scale = Vector3D::lerp(Vector3D(4.0f, 0.05f, 4.0f), Vector3D(1.0f, 1.0f, 1.0f), (t - 0.5f) * 2);
		position = Vector3D(0.0f, 0.0f, 0.0f);  
		rotation = Vector3D(0.0f, 0.0f, 0.0f);  
	}

	for (Cube* cube : CubeList) {
		cube->SetScale(scale);
		cube->SetPosition(position);
		cube->SetRotation(rotation);
	}
	*/
	// run the update for the InputSystem
	InputSystem::getInstance()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	


	update();

	for (Cube* cube : CubeList)
	{
		cube->update(m_world_cam);
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
		cube->SetAnimSpeed(0.0f);
	}
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);
	CameraRot.m_x+= deltaPos.getY() * 0.1f * m_delta_time;
	CameraRot.m_y += deltaPos.getX() * 0.1f * m_delta_time;

	cout << CameraRot.m_x << " : " << CameraRot.m_y << endl;
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
}





