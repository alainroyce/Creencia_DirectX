#include "GameObject.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <math.h>


GameObject::GameObject(string name)
{
	this->name = name;
	m_position = Vector3D::zeros();
	m_scale = Vector3D::ones();
	m_rotation = Vector3D::zeros();
}

GameObject::~GameObject()
{
}

std::string GameObject::GetName()
{
	return this->name;
}

void GameObject::SetPosition(float x, float y, float z)
{
	m_position = Vector3D{ x,y,z };
}

void GameObject::SetPosition(Vector3D pos)
{
	m_position = pos;
}

Vector3D GameObject::GetLocalPosition()
{
	return m_position;
}

void GameObject::SetScale(float x, float y, float z)
{
	m_scale = Vector3D{ x,y,z };
}

void GameObject::SetScale(Vector3D scale)
{
	m_scale = scale;
}

Vector3D GameObject::GetLocalScale()
{
	return m_scale;
}

void GameObject::SetRotation(float x, float y, float z)
{
	m_rotation = Vector3D{ x,y,z };
}

void GameObject::SetRotation(Vector3D rot)
{
	m_rotation = rot;
}

Vector3D GameObject::GetLocalRotation()
{
	return m_rotation;
}

void GameObject::update(Matrix4x4 cam)
{
}

void GameObject::draw()
{
}


