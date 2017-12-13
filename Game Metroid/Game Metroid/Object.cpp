#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
	delete ObjectSprite;
	delete Size;
}

int Object::GetX()
{
	return x;
}

int Object::GetY()
{
	return y;
}

void Object::Update(Camera *camera, int t)
{
}

void Object::DrawObject(Camera *camera)
{
}

float Object::GetSpeed()
{
	return Speed;
}

float Object::GetVx()
{
	return Vx;
}

float Object::GetVy()
{
	return Vy;
}

int Object::GetMoving()
{
	return IsMoving;
}

int Object::GetAttacking()
{
	return IsAttacking;
}

void Object::SetMoving(int a)
{
	IsMoving = a;
}

int Object::GetTrend()
{
	return Trend;
}

void Object::SetTrend(int a)
{
	Trend = a;
}


void Object::MoveLeft()
{
	Vx = -Speed;
	IsMoving = 1;
	Trend = -1;
}
void Object::MoveRigh()
{
	Vx = Speed;
	IsMoving = 1;
	Trend = 1;
}
void Object::Stop()
{
	Vx = 0;
	IsMoving = 0;
	IsAttacking = 0;
}

void Object::Star()
{
	if (Trend == -1) this->MoveLeft();
	else this->MoveRigh();
}

void Object::Attack()
{
	IsAttacking = 1;
}


