#include "Map.h"

Map::Map()
{
	LoadMap();
}

Map::~Map()
{
}

void Map::ReadMatrix()
{
	int i, j;
	FILE *file;
	file = fopen(MATRIXTXT, "r");

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLMN; j++)
		{
			fscanf(file, "%d", &TileMap[i][j]);
		}
	}
	fclose(file);
}

void Map::LoadMap()
{
	ReadMatrix();
	TileTexture = new GTexture(TILEMAP, 6, 8, 48);
	G_MapWidth = TileTexture->FrameWidth*COLMN;
	G_MapHeight = TileTexture->FrameHeight*ROW;
	Maxcolumn = G_ScreenWidth / TileTexture->FrameHeight + 1;

	Tile = new Sprite(TileTexture, 0);
}

void Map::DrawMap(Camera* camera)
{
	int row, column;
	row = int(camera->viewport.y) / TileTexture->FrameHeight;
	column = int(camera->viewport.x) / TileTexture->FrameHeight;
	
	int x, y;
	x = -int(camera->viewport.x) % TileTexture->FrameHeight;
	y = -int(camera->viewport.y) % TileTexture->FrameHeight;

	for (int i = 0 ; i <= Maxcolumn; i++)
	{
		for (int j = 0; j < COLMN; j++)
		{
			Tile->SelectIndex(TileMap[ROW - row + i][column + j]);
			Tile->DrawRaw(x, y);
			x = x + TileTexture->FrameHeight;
		}
		y = y + TileTexture->FrameHeight;
		x = -int(camera->viewport.x) % TileTexture->FrameHeight;
	}
}

