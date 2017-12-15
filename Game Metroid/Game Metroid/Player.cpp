#include "Player.h"
Player::Player()
{
	Vx = 0;
	Vy = 0;

	Size = new GTexture(PLAYER_IMAGE_FILE, 29, 1, 29);
	ObjectSprite = new Sprite(Size, PLAYER_FRAME);

	this->x = PLAYER_X;
	this->y = PLAYER_Y;
	player_weight = PLAYER_WEIGHT;
	Speed = PLAYER_VX;

	a = (float)PLAYER_F_JUMP / PLAYER_WEIGHT; //F = m*a => a = F/m
	Vy = PLAYER_VY;
	Trend = PLAYER_TREND;


}

Player::~Player()
{
}


void Player::Update(Camera *camera, int t)
{
	if (isMove)
	{
		if (PLAYER_state != MOVE_JUMP)
			PLAYER_state = MOVE;
	}
	if (isJump)
	{
		if (canJump)
			PLAYER_state = JUMP;
	}
	if (isAttack)
	{
		if (canAttack)
			PLAYER_state = ATTACK;
	}
	if (isRoll)
	{
		if (canRoll)
			PLAYER_state = ROLL;

	}
	if (isLookUp)
	{
		if (canLookUp)
			PLAYER_state = LOOKUP;
	}

	if (isMove && isJump)
	{
		if (canMove && canJump)
		{
			PLAYER_state = MOVE_JUMP;
		}
	}

	if (!isMove && !isJump && !isLookUp && !isRoll && !isAttack && !isRoll)
		PLAYER_state = NONE;
	if (isFall)
		PLAYER_state = FALL;
	UpdateState(camera, t);
}

void Player::UpdateState(Camera *camera, int t)
{
	switch (PLAYER_state)
	{
	case FALL:
	{
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canAttack = true;
		canLookUp = true;

		Vy -= PLAYER_GRAVITY;
		y += Vy;
	}
	case NONE:
	{
		//in this state, player can do following actions.
		canMove = true;
		canJump = true;
		canFall = true;
		canRoll = true;
		canAttack = true;
		canLookUp = true;

		ObjectSprite->_index = 4;
		break;
	}
	case MOVE:
	{
		//in this state, player can do following actions.
		canMove = true;
		canJump = true;
		canFall = true;
		canRoll = true;
		canAttack = true;
		canLookUp = true;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;


		ObjectSprite->_start = 5;
		ObjectSprite->_end = 7;
		ObjectSprite->Update(t);
		break;
	}
	case JUMP:
	{
		//in this state, player can do following actions.
		canRoll = false;

		canMove = true;
		canFall = true;
		canAttack = true;
		canLookUp = true;


		if (Vy > 0)
			Vy -= (a - PLAYER_GRAVITY); //gia tốc thực = gia tốc của player - gia tốc trái đất.
		else {
			isFall = true;
		}

		y += Vy;
		ObjectSprite->_index = 8;
		break;
	}
	case ROLL:
	{
		//in this state, player can do following actions.
		canJump = false;
		canAttack = false;
		canLookUp = false;

		canMove = true;
		canFall = true;

		ObjectSprite->_start = 13;
		ObjectSprite->_end = 16;
		ObjectSprite->Update(t);
		break;
	}
	case LOOKUP:
	{
		// after looking, state become NONE.
		isLookUp = false;
		//in this state, player can do following actions.
		canMove = true;
		canJump = true;
		canFall = true;
		canRoll = true;
		canAttack = true;

		ObjectSprite->SelectIndex(28);
		break;
	}
	case ATTACK:
	{
		// after attacking, state become NONE.
		isAttack = false;
		//in this state, player can do following actions.
		canMove = true;
		canJump = true;
		canFall = true;
		canRoll = true;
		canLookUp = true;

		Vx = 0;
		ObjectSprite->SelectIndex(4);
		break;
	}

	//case MOVE_JUMP:
	{
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canFall = true;
		canAttack = true;
		canLookUp = true;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		//Jump
		if (Vy > 0)
			Vy -= (a - PLAYER_GRAVITY); //gia tốc thực = gia tốc của player - gia tốc trái đất.
		else {
			isFall = true;
		}

		y += Vy;
		ObjectSprite->_index = 8;
		break;
	}
	}
}


void Player::DrawObject(Camera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == -1) ObjectSprite->DrawFlipX(pos.x, pos.y);
	else ObjectSprite->Draw(pos.x, pos.y);
}
