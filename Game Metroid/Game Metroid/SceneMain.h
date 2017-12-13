#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "Sprite.h"
#include "Object.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
class SceneMain : public Game
{
public:
	Camera *camera;
	Map *map;
	Player *player;
	SceneMain(int _nCmdShow);
	~SceneMain();

protected:
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);
};

#endif