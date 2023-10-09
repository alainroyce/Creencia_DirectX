#pragma once
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "EngineTime.h"


class AppWindow;
class Window;
using namespace std;


class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	void update();
	void draw();
	void SetAnimSpeed(float speed);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	PixelShader* m_ps;
	VertexShader* m_vs;
private:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;;
	float animSpeed = 1.0f;
	friend class Window;

};