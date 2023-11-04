#pragma once
#include "GameObject.h"
#include "Cube.h"
#include "EngineTime.h"
#include <vector>
#include <string>
#include <unordered_map>

class GameObjectManager
{
private:

    GameObjectManager();
    ~GameObjectManager();

    GameObjectManager(GameObjectManager const&) {};
    GameObjectManager& operator =(GameObjectManager const&) {};
    static GameObjectManager* sharedInstance;


    std::vector<GameObject*> ObjectList;


public:

    static GameObjectManager* getInstance();
    static void initialize();
    static void destroy();

    enum ObjectType {
        CUBE,
        PLANE,
        SPHERE
    };

    void createGameObject(ObjectType type);
    void addGameObject(GameObject* gameObject);
    void update(Matrix4x4 cam);
    void draw();
    void setSelectGameObject(GameObject* gameObject);
    GameObject* getSelectedGameObject();
    GameObject* selectedGameObject = nullptr;
    std::vector<GameObject*> getAllGameObject();

  


  

};

