/*#include "QuadRenderer.h"

QuadRenderer::QuadRenderer(vec3 a, vec3 b, vec3 c, vec3 d)
{
	this->vectorList[0].position = a;
	this->vectorList[1].position = b;
	this->vectorList[2].position = c;
	this->vectorList[3].position = d;

	initialize();
}

QuadRenderer::~QuadRenderer()
{
}

void QuadRenderer::initialize()
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(this->vectorList);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	//GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(this->vectorList, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void QuadRenderer::render()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::get();
	if (graphicsEngine)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	}
}

void QuadRenderer::release()
{
	if(m_vb)
	{
		m_vb->release();
		m_vb = nullptr;
	}
}
*/