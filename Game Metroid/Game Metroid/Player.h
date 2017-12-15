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
#define PLAYER_VY 9
#define PLAYER_F_JUMP 10 //lực tác động khi nhảy 
#define PLAYER_WEIGHT 10
#define PLAYER_GRAVITY 0.8
#define PLAYER_FALL 180
#define PLAYER_VX_DAMAGED 150
#define PLAYER_VY_DAMAGED 450
#define MAX_JUMP 40

enum STATE
{
	NONE = 0,//
	MOVE = 1,//
	JUMP = 2,//
	FALL = 3,//
	ROLL = 4,//
	LOOKUP = 5,//
	ATTACK = 6,//
	COLLISION_ENEMY = 7,

	MOVE_JUMP = 8,//
	MOVE_JUMP_ATTACK = 10,//
	
	FALL_ATTACK = 11, //
	FALL_LOOKUP = 13, //
	FALL_LOOKUP_ATTACK = 14, //chưa đc

	MOVE_ROLL = 15, //
	MOVE_LOOKUP = 16, //
	MOVE_LOOKUP_JUMP = 17,//

	

	MOVE_LOOKUP_ATTACK = 18,//
	MOVE_LOOKUP_JUMP_ATTACK = 19,//

	

	MOVE_ATTACK = 20, //
	WEAPON_ATTACK = 21,
	DIE = 22,

	JUMP_ATTACK = 23, //
	JUMP_LOOKUP = 24,//
	JUMP_LOOKUP_ATTACK = 25 //
};

class Player : public Object
{
public:
	STATE PLAYER_state;
	Player();
	Player(float x, float y);
	~Player();
	int player_weight;
	int vjump;
	float a; //gia tốc khi nhảy
	virtual void Update(Camera *camera, int t);
	virtual void DrawObject(Camera *camera);
	void UpdateState(Camera *camera, int t);





	//check input
	bool isArrowKeyDown = false;
	bool isArrowKeyUp = false;
	bool isArrowKeyLeft = false;
	bool isArrowKeyRight = false;
	bool isKey_Z = false;
	bool isKey_X = false;
	bool isKey_C = false;

	bool canMove = false;
	bool isMoveJump = false;

	bool canJump = true;
	bool isJump = false;

	bool isFall = false;
	bool canFall = false;
	bool isMoveFall = false;

	bool isRoll = false;
	bool canRoll = false;

	bool isAttack = false;
	bool canAttack = false;

	bool isLookUp = false;
	bool canLookUp = false;
};
#endif
