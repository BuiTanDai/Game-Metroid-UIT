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
	NONE = 0,
	MOVE = 1,
	JUMP = 2,
	FALL = 3,
	ROLL = 4,
	LOOKUP = 5,
	ATTACK = 6,
	COLLISION_ENEMY = 7,

	MOVE_JUMP = 8,
	MOVE_JUMP_ATTACK = 10,
	MOVE_FALL = 10,
	MOVE_FALL_ATTACK = 11,

	MOVE_ROLL = 12,
	MOVE_LOOPUP = 12,
	MOVE_LOOPUP_JUMP = 12,
	MOVE_LOOPUP_FALL = 12,
	MOVE_LOOPUP_ATTACK = 12,
	MOVE_LOOKUP_JUMP_ATTACK = 12,
	MOVE_LOOKUP_FALL_ATTACK = 12,

	MOVE_ATTACK = 12,
	WEAPON_ATTACK = 12,
	DIE = 13
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

	bool canJump = false;
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
