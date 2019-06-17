#ifndef _PHYSICSMANAGER_H
#define _PHYSICSMANAGER_H

#include "PhysEntity.h"
#include <bitset>

class PhysicsManager
{
public:

	enum class CollisionLayers {

		Friendly = 0,
		MaxLayers
		
	};

	enum class CollisionFlags {

		None = 0x00,
		Friendly = 0x01

	};
private:

	static PhysicsManager* sInstance;

	// for now one layer will contain all the entities
	std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	// sets a unique physics entity id
	unsigned long mLastId;
public:

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);

	void UnregisterEntity(unsigned long id);

	void Update();

private:

	PhysicsManager();
	~PhysicsManager();
};

#endif 