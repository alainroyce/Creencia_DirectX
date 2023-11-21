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

void GameObject::RecomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];


	
	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->GetLocalScale());
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->GetLocalPosition());
	this->m_matrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	
	
	
	Vector3D posMatrix;
	posMatrix.m_x = newMatrix.m_mat[3][0];
	posMatrix.m_y = newMatrix.m_mat[3][1];
	posMatrix.m_z = newMatrix.m_mat[3][2];


	SetPosition(posMatrix);
	
	
}

float* GameObject::GetPhysicsLocalMatrix()
{

	
	Matrix4x4 matrix;
	matrix.setIdentity();
	matrix.setScale(this->GetLocalScale());
	
	
	Matrix4x4 rotZ;
	rotZ.setIdentity();
	rotZ.setRotationZ(m_rotation.m_z);
	matrix = rotZ;
	

	Matrix4x4 rotY;
	rotY.setIdentity();
	rotY.setRotationY(m_rotation.m_y);
	matrix = rotY;

	Matrix4x4 rotX;
	rotX.setIdentity();
	rotX.setRotationX(m_rotation.m_x);
	matrix *= rotX;

	matrix.setTranslation(this->GetLocalPosition());

	return matrix.getMatrix();
}


void GameObject::SetPosition(float x, float y, float z)
{
	m_position = Vector3D( x,y,z );
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
	m_scale = Vector3D( x,y,z );
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
	m_rotation = Vector3D( x,y,z );
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


