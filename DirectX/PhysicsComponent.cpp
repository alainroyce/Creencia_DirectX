#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{

	//whenever a new physics component is initialized. Register to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->GetLocalScale();
	Transform transform; transform.setFromOpenGL(this->getOwner()->GetPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2)); //half extent
	if (transform.isValid()) {
		this->rigidBody = physicsWorld->createRigidBody(transform);
		this->rigidBody->addCollider(boxShape, transform);
		this->rigidBody->updateMassPropertiesFromColliders();
		this->rigidBody->setMass(this->mass);
		this->rigidBody->setType(BodyType::DYNAMIC);

		transform = this->rigidBody->getTransform();
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		this->getOwner()->RecomputeMatrix(matrix);
	}
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->RecomputeMatrix(matrix);
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}