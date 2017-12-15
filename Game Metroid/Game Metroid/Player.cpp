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
		if (!isRoll)
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

	if (isJump && isAttack)
	{
		PLAYER_state = JUMP_ATTACK;
	}

	if (isJump && isLookUp)
	{
		PLAYER_state = JUMP_LOOKUP;
	}

	if (isMove && isAttack)
	{
		PLAYER_state = MOVE_ATTACK;
	}

	

	
	
	
	if (isMove && isRoll)
	{
			PLAYER_state = MOVE_ROLL;
	}
	

	if (isMove && isLookUp)
	{
		PLAYER_state = MOVE_LOOKUP;
	}

	if (isMove && isLookUp &&isAttack)
	{
		PLAYER_state = MOVE_LOOKUP_ATTACK;
	}

	if (isJump && isAttack && isMove)
	{
		PLAYER_state = MOVE_JUMP_ATTACK;
	}


	if (isMove && isLookUp &isJump)
	{
		PLAYER_state = MOVE_LOOKUP_JUMP;
	}


	

	if (isJump && isLookUp && isAttack)
	{
		PLAYER_state = JUMP_LOOKUP_ATTACK;
	}

	if (isMove && isLookUp &isJump && isAttack)
	{
		PLAYER_state = MOVE_LOOKUP_JUMP_ATTACK;
	}
	if (isFall)
		if (canFall) {
			PLAYER_state = FALL;
		}
	if (isFall && isAttack)
	{
		PLAYER_state = FALL_ATTACK;
	}
	if (isFall && isLookUp)
	{
		PLAYER_state = FALL_LOOKUP;
	}
	if (isFall && isLookUp && isAttack)
	{
		PLAYER_state = FALL_LOOKUP_ATTACK;
	}
	
	
	if (!isMove && !isJump && !isLookUp && !isRoll && !isAttack && !isRoll)
		PLAYER_state = NONE;
	UpdateState(camera, t);
}

void Player::UpdateState(Camera *camera, int t)
{
	switch (PLAYER_state)
	{
	case FALL: // có thể điều khiển qua trái phải khi rơi.
	{
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canAttack = true;
		canLookUp = true;

		Vy -= PLAYER_GRAVITY;
		y += Vy;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		ObjectSprite->_index = 8;
		break;
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
			isJump = false;
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
	case MOVE_JUMP:
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
			isJump = false;
		}

		y += Vy;
		ObjectSprite->_index = 8;
		break;
	}
	case MOVE_ATTACK:
	{
		isAttack = false;
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

		if (ObjectSprite->_index < 18) {
			ObjectSprite->_index = 18;
			ObjectSprite->Update(t);
		}
		else {
			ObjectSprite->_start = 19;
			ObjectSprite->_end = 20;
			ObjectSprite->Update(t);
		}
		break;
	}
	case MOVE_JUMP_ATTACK:
	{
		isAttack = false;
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

		//Jump
		if (Vy > 0)
			Vy -= (a - PLAYER_GRAVITY); //gia tốc thực = gia tốc của player - gia tốc trái đất.
		else {
			isFall = true;
			isJump = false;
		}
		y += Vy;

		ObjectSprite->_index = 21;
		break;
	}
	case MOVE_ROLL:
	{
		//in this state, player can do following actions.
		canMove = true;
		canJump = false;
		canFall = true;
		canRoll = true;
		canAttack = false;
		canLookUp = false;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		//Roll
		ObjectSprite->_start = 13;
		ObjectSprite->_end = 16;
		ObjectSprite->Update(t);
		break;
	}
	case MOVE_LOOKUP:
	{
		isLookUp = false;
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
		if (ObjectSprite->_index < 22) {
			ObjectSprite->_index = 22;
		}
		else {
			ObjectSprite->_start = 24;
			ObjectSprite->_end = 25;
			ObjectSprite->Update(t);
		}
		break;
	}
	case MOVE_LOOKUP_ATTACK:
	{
		isAttack = false;
		isLookUp = false;
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
		if (ObjectSprite->_index < 24)
			ObjectSprite->_index = 24; //note
		ObjectSprite->_start = 24;
		ObjectSprite->_end = 25;
		ObjectSprite->Update(t);
		break;
	}
	case MOVE_LOOKUP_JUMP:
	{
		isLookUp = false;
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

		//Jump
		if (Vy > 0)
			Vy -= (a - PLAYER_GRAVITY); //gia tốc thực = gia tốc của player - gia tốc trái đất.
		else {
			isFall = true;
			isJump = false;
		}
		y += Vy;

		ObjectSprite->_index = 26;
		break;
	}
	case MOVE_LOOKUP_JUMP_ATTACK:
	{
		isAttack = false;
		isLookUp = false;
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canFall = true;
		canAttack = true;
		canLookUp = true;

		isLookUp = false;
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

		//Jump
		if (Vy > 0)
			Vy -= (a - PLAYER_GRAVITY); //gia tốc thực = gia tốc của player - gia tốc trái đất.
		else {
			isFall = true;
			isJump = false;
		}

		y += Vy;


		ObjectSprite->_end = 26;
		break;
	}
	case FALL_ATTACK:
	{
		isAttack = false;
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canAttack = true;
		canLookUp = true;

		Vy -= PLAYER_GRAVITY;
		y += Vy;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		ObjectSprite->_index = 21;
		break;
	}
	case FALL_LOOKUP:
	{
		isLookUp = false;
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canAttack = true;
		canLookUp = true;

		Vy -= PLAYER_GRAVITY;
		y += Vy;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		ObjectSprite->_index = 27;
		break;
	}
	case FALL_LOOKUP_ATTACK:
	{
		isLookUp = false;
		isAttack = false;
		//in this state, player can do following actions.
		canJump = false;
		canRoll = false;

		canMove = true;
		canAttack = true;
		canLookUp = true;

		Vy -= PLAYER_GRAVITY;
		y += Vy;

		//Move
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;

		ObjectSprite->_index = 26;
		break;
	}
	case JUMP_ATTACK: 
	{
		isAttack = false;
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
			isJump = false;
		}

		y += Vy;
		ObjectSprite->_index = 21;
		break;
	}
	case JUMP_LOOKUP:
	{
		isLookUp = false;
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
			isJump = false;
		}

		y += Vy;
		ObjectSprite->_index = 26;
		break;
	}
	case JUMP_LOOKUP_ATTACK:
	{
		isLookUp = false;
		isAttack = false;
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
			isJump = false;
		}

		y += Vy;
		ObjectSprite->_index = 26;
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
