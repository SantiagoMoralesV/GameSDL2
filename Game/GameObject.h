// GameObject.h                                                                                                      
// The base class for all game object, providing position functionality to all entities.                                                                                                           
// Sets up a system to parent GameObject objects to one another                                                      
// making the child's position to the parent's instead of the world origin 
#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "MathHelper.h"

class GameObject {

public:
	//Enum to describe either world space or local space, used to get Position associated with each space
	enum SPACE { local = 0, world = 1 };

	//pos is the starting position of the new GameObject
	GameObject(Vector2 pos = VEC2_ZERO);;
	~GameObject();

	//Sets the GameObject's position, it only updates local space                               
	//If the object has a parent, its new position is relative to the parent's world position   
	//If the object has no parent, its new position is relative to the origin   
	void Pos(Vector2 pos);

	//Returns the position of the GameObject                                                                         
	//If space = world, the world position is returned (relative to the origin)                                       
	//if space = local, if the object has a parent, the local position is returned (relative to the parent position)  
	//       otherwise if the object has no parent, the world position is returned instead (relative to the origin)  
	Vector2 Pos(SPACE space = world);

	//Sets the GameObject's rotation, it only updates local space                               
	//If the object has a parent, its new rotation is relative to the parent's world rotation   
	//If the object has no parent, its new rotation is set to the given rotation 
	void Rotation(float rotation);

	//Returns the rotation of the GameObject                                                                         
	//If space = world, the world rotation is returned (total rotation of parent[if it has one] and object)            
	//if space = local, if the object has a parent, the local rotation is returned (relative to the parent's rotation) 
	//       otherwise if the object has no parent, the world rotation is returned instead (relative to the origin) 
	float Rotation(SPACE space = world);

	//Sets the GameEntity's scale, it only updates local space    
	void Scale(Vector2 scale);

	//Returns the scale of the GameObject                                                                             
	//If space = world, the world scale is returned (product of the parent and local scale)                            
	//if space = local, if the object has a parent, the local scale is returned (relative to the parent's scale)       
	//       otherwise if the object has no parent, the GameObject's scale is returned instead                         
	//-----------------------------------------------------------------------------------------------------------------
	Vector2 Scale(SPACE space = world);

	//Sets the active state of the GameObject
	void Active(bool active);

	//Returns the active state of the GameObject
	bool Active();

	//Sets the parent of the GameObject as the given GameObject                                                                
	//If the GameObject has no parent, the given GameEntity is set as its parent                                                
	//If the GameObject has a parent, the given game entity is set as the new parent,                                           
	//       and the local Position/Rotation are changed to be relative to the new parent (world values are unchanged)    
	//If NULL is passed in, the GameObject is considered without a parent,                                                      
	//       and all values are set to be relative to the origin (world values are unchanged)    
	void Parent(GameObject* parent);

	//Returns the Current parent of the GameEntity,  
	//Returns NULL if the GameEntity has no parent   
	GameObject* Parent();


	virtual void Update();
	virtual void Render();

	//Translates the GameObject's local position by the given amount
	void Translate(Vector2 vec);

	void Rotate(float amount);

private:

	// Position/Rotation/Active/Parent set to private to make they are not set directly, but the functions are 
	// used instead  
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;
	//Set to true if the object is to be updated and rendered 
	bool mActive;
	//A GameObject can only have one parent at a time, but can have many children 
	GameObject* mParent;


};

#endif 
