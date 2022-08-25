#include "CollisionHandler.h"

#include "Object/MoveableObjects/Big.h"
#include "Object/MoveableObjects/Small.h"
#include "Object/MoveableObjects/Tall.h"
#include "Object/MoveableObjects/Box.h"
#include "Object/StaticObjects/BlockedTile.h"
#include "Object/StaticObjects/Key.h"
#include "Object/StaticObjects/Thorn.h"

namespace {
    void PlayerGate(Object* player, Object*)
    {
        player->setDisposed();
        GameManager::instance().incPlayersAtGate();
    }
    void PlayerKey(Object* player, Object* Key)
    {
        ResourcesSounds::getInstance().play(Sounds::key);
        Key->setDisposed();
        (dynamic_cast<Player*>(player))->incKeys(); 
    }
    void PlayerBlockedTile(Object* player, Object* blockedTile)
    {
        auto playerPtr = dynamic_cast<Player*>(player);
        if (playerPtr->hasKeys()) {
            blockedTile->setDisposed();
            playerPtr->decKeys();
        }
    }
    void playerThorn(Object* player, Object*)
    {
        (dynamic_cast<Player*>(player))->setAlive(false);
    }
    //======================================================================
    void GatePlayer(Object* gate, Object* player)
    {
        PlayerGate(player, gate);
    }
    void KeyPlayer(Object* key, Object* player)
    {
        PlayerKey(player, key);
    }
    void blockedTilePlayer(Object* blockedTile, Object* player)
    {
        PlayerBlockedTile(player, blockedTile);
    }
    void thornPlayer(Object* throne, Object* player)
    {
        playerThorn(player, throne);
    }
     
    HitTable initializeCollisionMap()
    {
        HitTable hmPtr;
        hmPtr[_Key(typeid(Gate),        typeid(Big))]         = &GatePlayer;
        hmPtr[_Key(typeid(Gate),        typeid(Small))]       = &GatePlayer;
        hmPtr[_Key(typeid(Gate),        typeid(Tall))]        = &GatePlayer;
        hmPtr[_Key(typeid(Big),         typeid(Gate))]        = &PlayerGate;
        hmPtr[_Key(typeid(Small),       typeid(Gate))]        = &PlayerGate;
        hmPtr[_Key(typeid(Tall),        typeid(Gate))]        = &PlayerGate;
        hmPtr[_Key(typeid(Big),         typeid(Key))]         = &PlayerKey;
        hmPtr[_Key(typeid(Small),       typeid(Key))]         = &PlayerKey;
        hmPtr[_Key(typeid(Tall),        typeid(Key))]         = &PlayerKey;
        hmPtr[_Key(typeid(Key),         typeid(Big))]         = &KeyPlayer;
        hmPtr[_Key(typeid(Key),         typeid(Small))]       = &KeyPlayer;
        hmPtr[_Key(typeid(Key),         typeid(Tall))]        = &KeyPlayer; 
        hmPtr[_Key(typeid(BlockedTile), typeid(Big))]         = &blockedTilePlayer;
        hmPtr[_Key(typeid(BlockedTile), typeid(Small))]       = &blockedTilePlayer;
        hmPtr[_Key(typeid(BlockedTile), typeid(Tall))]        = &blockedTilePlayer; 
        hmPtr[_Key(typeid(Big),         typeid(BlockedTile))] = &PlayerBlockedTile;
        hmPtr[_Key(typeid(Small),       typeid(BlockedTile))] = &PlayerBlockedTile;
        hmPtr[_Key(typeid(Tall),        typeid(BlockedTile))] = &PlayerBlockedTile;
        hmPtr[_Key(typeid(Big),         typeid(Thorn))]       = &playerThorn;
        hmPtr[_Key(typeid(Small),       typeid(Thorn))]       = &playerThorn;
        hmPtr[_Key(typeid(Tall),        typeid(Thorn))]       = &playerThorn;
        hmPtr[_Key(typeid(Thorn),       typeid(Big))]         = &thornPlayer;
        hmPtr[_Key(typeid(Thorn),       typeid(Small))]       = &thornPlayer;
        hmPtr[_Key(typeid(Thorn),       typeid(Tall))]        = &thornPlayer;

        return hmPtr;
    }

    HitFunctionPtr lookup(const std::type_index& obj_type1, const std::type_index& obj_type2)
    {
        static auto collisionTable = initializeCollisionMap();

        auto collisionTableFunc = collisionTable.find(std::make_pair(obj_type1, obj_type2));
        if (collisionTableFunc == collisionTable.end())
        {
            return nullptr;
        }
        return collisionTableFunc->second;
    }
}

void processCollision(Object* object1, Object* object2)
{
    auto hfPtr = lookup(typeid(*object1), typeid(*object2));
    if (!hfPtr)
    {
        return;
    }
    hfPtr(object1, object2);
}