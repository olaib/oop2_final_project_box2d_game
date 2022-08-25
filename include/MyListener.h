#pragma once
#include "Object/Object.h"

//this is a collusion class inherince from box2d b2ContactListener class
class MyListener :public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
private:
};