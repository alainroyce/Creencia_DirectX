#pragma once
#include <string>

#include "Matrix4x4.h"
#include "Vector3D.h"

using namespace std;
class Matrix4x4;
class AppWindow;
class VertexShader;
class PixelShader;

class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D pos);
	Vector3D GetLocalPosition();

	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetLocalScale();

	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rot);
	Vector3D GetLocalRotation();

	virtual void update(Matrix4x4 cam);
	virtual void draw();
	std::string GetName();

	// openGL matrix to our matrix implementation
	void RecomputeMatrix(float matrix[16]);
	// our matrix implementation to openGL matrix
	float* GetPhysicsLocalMatrix();

protected:
	std::string name;
	Vector3D m_position;
	Vector3D m_scale;
	Vector3D m_rotation;
	Matrix4x4 m_matrix;

};