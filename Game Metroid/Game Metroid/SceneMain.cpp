#include "SceneMain.h"

SceneMain::SceneMain(int _nCmdShow) : Game(_nCmdShow)
{

}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));

	player->Update(camera, t);
    camera->SetVCam(player->GetVx());
	camera->SetFolowPos(player->GetX(), player->GetY());
	camera->UpdateCamera();

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	map->DrawMap(camera);
	player->DrawObject(camera);
	G_SpriteHandler->End();
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	bool check = false;
	if (IsKeyDown(DIK_C))
	{
		player->Attack();
		check = true;
	}
	if (IsKeyDown(DIK_X))
	{
		player->Jump();
		check = true;
	}
	if (IsKeyDown(DIK_UP))
	{
		player->LookUp();
		check = true;
	}
	if (IsKeyDown(DIK_LEFT))
	{
		player->MoveLeft();
		check = true;
	}
	if (IsKeyDown(DIK_RIGHT))
	{
		player->MoveRigh();
		check = true;
	}
	if (!check) 
	{
		player->Stop();
	}
	
	
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	map = new Map();
	camera = new Camera();
	camera->SetSizeMap(G_MapWidth, 0);

	player = new Player();
}

void SceneMain::OnKeyDown(int KeyCode)
{

}

SceneMain::~SceneMain(void)
{
}
