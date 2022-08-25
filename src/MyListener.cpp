#include "MyListener.h"
#include "CollisionHandler.h"
#include <iostream>

void MyListener::BeginContact(b2Contact* contact)
{
    auto objectA = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    auto objectB = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (objectA && objectB)
    {
        processCollision(objectA, objectB);
    }
}