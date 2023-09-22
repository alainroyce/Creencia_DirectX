#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"


struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};
class QuadRenderer
{
public:
	QuadRenderer(vec3 a, vec3 b, vec3 c, vec3 d);
	~QuadRenderer();

	void initialize();
	void render();
	void release();

	vertex vectorList[4];
	VertexBuffer* m_vb;
};