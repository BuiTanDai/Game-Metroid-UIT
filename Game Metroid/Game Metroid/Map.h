#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <conio.h>
#include "Sprite.h"
#include "GTexture.h"
#include "Camera.h"

#define MATRIXTXT "Resources/Matrix.txt"
#define TILEMAP "Resources/tiledset.png"
#define COLMN 60
#define ROW 15

class Map
{
private:
	GTexture *TileTexture;
	Sprite *Tile;
	int Maxcolumn;
	int TileMap[100][100];
public:
	Map();
	~Map();
	void ReadMatrix();
	void LoadMap();
	void DrawMap(Camera *camera);
};

#endif
