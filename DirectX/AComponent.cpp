#include "AComponent.h"
#include <iostream>

AComponent::AComponent(String name, ComponentType type, GameObject* owner)
{
    this->name = name;
    this->owner = owner;
    this->type = type;
}

AComponent::~AComponent()
{
    this->owner = NULL;
    this->type = NotSet;
}

void AComponent::attachOwner(GameObject* owner)
{
    this->owner = owner;
}

void AComponent::detachOwner()
{
    //if object owner gets detached. then component must also be deleted.
    this->owner = NULL;
}

GameObject* AComponent::getOwner()
{
    return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
    return this->type;
}

AComponent::String AComponent::getName()
{
    if (this == NULL) {
       
    }
    return this->name;
}

void AComponent::perform(float deltaTime)
{
}