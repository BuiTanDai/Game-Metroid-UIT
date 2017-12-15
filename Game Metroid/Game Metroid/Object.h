#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <d3dx9.h>
#include "Sprite.h"
#include "Camera.h"

class Object
{
public:
	float x;	// Vị trí theo trục X
	float y;	// Vị trí theo trục Y

	float Vx;	// Vận tốc theo trục X
	float Vy;	// Vận tốc theo trục Y

	bool isMove;	// Đang di chuyển = 1; Đứng yên = 0;
	int IsAttacking;
	int Trend;		// Phương hướng, trái = -1, phải = 1;

	float Speed; // Tốc độ

	Sprite* ObjectSprite;
	GTexture* Size;

public:
	Object();
	~Object();							// Hàm hủy Object

	int GetX();
	int GetY();
	float GetSpeed();
	float GetVx();
	float GetVy();
	int GetMoving();
	int GetAttacking();
	void SetMoving(int a);
	int GetTrend();
	void SetTrend(int a);

	void MoveLeft();
	void MoveRigh();
	void Stop();
	void Star();
	void Attack();
	virtual void Update(Camera *camera, int t);
	virtual void DrawObject(Camera *camera);
};

#endif
