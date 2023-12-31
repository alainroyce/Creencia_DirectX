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
	Cube(std::string name);
	~Cube();
	void update(Matrix4x4 cam)override;
	void draw()override;
	void SetAnimSpeed(float speed);
	Vector3D LerpColor(float minValue, float maxValue, float yMin, float yMax, const Vector3D& startColor, const Vector3D& endColor);
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

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;

	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;

};