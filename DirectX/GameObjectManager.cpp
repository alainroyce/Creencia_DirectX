#include "GameObjectManager.h"
#include "PhysicsComponent.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;


GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::update(Matrix4x4 cam)
{
	for (int i = 0; i < sharedInstance->ObjectList.size(); i++) {
		sharedInstance->ObjectList[i]->update(cam);
	}
}

void GameObjectManager::destroy()
{
	delete sharedInstance;
}
std::vector<GameObject*> GameObjectManager::getAllGameObject()     
{
	return sharedInstance->ObjectList;
}

void GameObjectManager::createGameObject(ObjectType type)
{
	
	GameObject* object = nullptr;
	PhysicsComponent* physicsComp = nullptr;
	switch (type)
	{
	case CUBE:
        object = new Cube("Cube");
		object->SetScale(Vector3D(0.5f, 0.5f, 0.5f));
		object->SetPosition(Vector3D(0, 3, 0));
		physicsComp = new PhysicsComponent(object->GetName(), object);
		//physicsComp->getRigidBody()->setType(BodyType::DYNAMIC);

		sharedInstance->ObjectList.push_back(object);
		break;
	case PLANE:
		object = new Cube("Plane");
		object->SetScale(Vector3D(10.0f, 0.1f, 10.0f));
		object->SetPosition(Vector3D(0, -5, 0));
		physicsComp = new PhysicsComponent(object->GetName(), object);
		physicsComp->getRigidBody()->setType(BodyType::STATIC);
		sharedInstance->ObjectList.push_back(object);
		break;
	

	default:
		object = nullptr;
		physicsComp = nullptr;
		break;
	}
	
	std::cout << ObjectList.size() << std::endl;
	
	setSelectGameObject(object);
	
}

void GameObjectManager::addGameObject(GameObject* gameObject)
{
	sharedInstance->ObjectList.push_back(gameObject);
}



void GameObjectManager::draw()
{
	for (int i = 0; i < ObjectList.size(); i++)
	{
		ObjectList[i]->draw();
	}
}


void GameObjectManager::setSelectGameObject(GameObject* gameObject)
{
	sharedInstance->selectedGameObject = gameObject;
}

GameObject* GameObjectManager::getSelectedGameObject()
{
	return sharedInstance->selectedGameObject;
}
GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
