#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <d3dx9.h>
#include "Sprite.h"
#include "Object.h"
	
#define PLAYER_IMAGE_FILE "Resources/player.png"
#define PLAYER_TREND 0
#define PLAYER_FRAME 30
#define PLAYER_STOP_IMAGE 0

#define PLAYER_STOP_IMAGE 4

#define PLAYER_X 910
#define PLAYER_Y 128

#define PLAYER_VX 5.0f
#define PLAYER_VX_STAIR 43	
#define PLAYER_VY_STAIR 43
#define PLAYER_VJUMP 20.0f
#define PLAYER_GRAVITY 11
#define PLAYER_FALL 180
#define PLAYER_VX_DAMAGED 150
#define PLAYER_VY_DAMAGED 450
#define MAX_JUMP 40

class Player : public Object
{
	
public:
	Player();
	Player(float x, float y);
	~Player();
	int vjump;
	int IsJumping;
	int IsFalling;
	int IsLookUp;
	void Jump();
	void LookUp();
	virtual void Update(Camera *camera,int t);
	virtual void DrawObject(Camera *camera);
};
#endif
