#include "Player.h"

Player::Player()
{
	Vx = 0;
	Vy = 0;
	
	Size = new GTexture(PLAYER_IMAGE_FILE, 29, 1, 29);
	ObjectSprite = new Sprite(Size, PLAYER_FRAME);

	this->x = PLAYER_X;
	this->y = PLAYER_Y;

	Speed = PLAYER_VX;
	Vy = PLAYER_VJUMP;
	IsMoving = 0;
	IsAttacking = 0;
	IsJumping = 0;
	IsFalling = 0;
	IsLookUp = 0;
	vjump = PLAYER_VJUMP;
	Trend = PLAYER_TREND;
}

void Player::Jump()
{
	IsJumping = 1;
}

void Player::LookUp()
{
	IsLookUp = 1;
}

void Player::Update(Camera *camera, int t)
{
	if (IsJumping == 1 && IsMoving == 0) { //Nhảy tại chỗ.
		IsJumping = 0;
		IsFalling = 1;
		
		if (vjump > 0)
			vjump -= 0.05;
		else
		{
			// Hàm rơi xuống và moving
			if (IsFalling == 1 && IsMoving == 1)
			{
				//Falling.
				IsMoving = 0;
				y -= PLAYER_GRAVITY;
				ObjectSprite->_index = 8;

				//Moving.
				x += Vx;
				D3DXVECTOR2 pos = camera->Transform(x, y);
				if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
					x -= Vx;
				return;
			}
			//Hàm đứng yên rơi xuống 
			if (IsFalling == 1 && IsMoving == 0)
			{
				y -= PLAYER_GRAVITY;
				ObjectSprite->_index = 8;
				return;
			}
		}
		y += vjump;
		ObjectSprite->_index = 8;
		return;
	}

	if (IsJumping == 1 && IsMoving == 1) { //Nhảy và di chuyển.
		//Jumping.
		IsJumping = 0;
		IsFalling = 1;
		if (vjump > 0)
			vjump -= 0.05;
		else {
			// Hàm rơi xuống và moving
			if (IsFalling == 1 && IsMoving == 1)
			{
				//Falling.
				IsMoving = 0;
				y -= PLAYER_GRAVITY;
				ObjectSprite->_index = 8;

				//Moving.
				x += Vx;
				D3DXVECTOR2 pos = camera->Transform(x, y);
				if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
					x -= Vx;
				return;
			}
			//Hàm đứng yên rơi xuống 
			if (IsFalling == 1 && IsMoving == 0)
			{
				y -= PLAYER_GRAVITY;
				ObjectSprite->_index = 8;
				return;
			}

		}
		y += vjump;
		ObjectSprite->_index = 8;
		//Di chuyển
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;
		return;
	}
	vjump = PLAYER_VJUMP;

	if (IsLookUp == 1 && IsMoving == 0) // Đứng yên và hướng lên trên
	{
		IsLookUp = 0;
		ObjectSprite->_index = 28;
		return;
	}

	if (IsLookUp == 1 && IsMoving == 1) // Di chuyển và hướng lên trên
	{
		//Hướng lên trên.
		IsLookUp = 0;
		ObjectSprite->_index = 24;
		if (ObjectSprite->_index > 25) ObjectSprite->_index = 24;
		ObjectSprite->Update(t);
		//Di chuyển.
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;
		return;
	}

	
	if (IsFalling == 1 && IsMoving == 0)
	{
		y -= PLAYER_GRAVITY;
		ObjectSprite->_index = 8;
		return;
	}

	if (IsFalling == 1 && IsMoving == 1)
	{
		//Falling.
		IsMoving = 0;
		y -= PLAYER_GRAVITY;
		ObjectSprite->_index = 8;

		//Moving.
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4)
			x -= Vx;
		return;
	}

	if (IsAttacking == 1 && IsMoving == 0) //Trạng thái đứng yên tấn công trái phải
	{
		Vx = 0;
		ObjectSprite->SelectIndex(4);
		IsAttacking = 0;
		return;
	}
	
	if (IsAttacking == 0 && IsMoving == 1) //Trạng thái di chuyển
	{
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4) 
			x -= Vx;

		if (ObjectSprite->_index > 7) ObjectSprite->_index = 5;
		ObjectSprite->Update(t);
		return;
		
	}
	if (IsAttacking == 1 && IsMoving == 1) //Di chuyển tấn công trái phải
	{
		IsAttacking = 0;
		IsMoving = 0;
		x += Vx;
		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (pos.x <= Size->FrameWidth / 4 || pos.x > G_ScreenWidth - Size->FrameWidth / 4) x -= Vx;

		ObjectSprite->_index = 19;
		if (ObjectSprite->_index > 20)
		{
			ObjectSprite->_index = 19;
		}
		ObjectSprite->Update(t);
		return;

	}
	ObjectSprite->SelectIndex(4);
	

}

void Player::DrawObject(Camera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == -1) ObjectSprite->DrawFlipX(pos.x, pos.y);
	else ObjectSprite->Draw(pos.x, pos.y);
}
