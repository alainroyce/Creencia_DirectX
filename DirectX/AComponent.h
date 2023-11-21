#pragma once
#include <string>

class GameObject;
class AComponent
{
public:
	typedef std::string String;
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	AComponent(String name, ComponentType type, GameObject* owner);
	~AComponent();

	void attachOwner(GameObject* owner);
	void detachOwner();
	GameObject* getOwner();
	ComponentType getType();
	String getName();

	virtual void perform(float deltaTime) = 0; //performs the associated action.

protected:
	GameObject* owner;
	ComponentType type;
	String name;
};