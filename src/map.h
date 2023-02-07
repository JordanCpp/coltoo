/*
 *  Copyright (C) 2003-2004 The colonization too Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
//
// FILE		: map.h
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: Map
//
// DESCRIPTION	: Map of tiles
//

#ifndef MAP_H
#define MAP_H

#include <string>
#include "tile.h"
#include "CTileTypes.h"
#include "CTileType.h"

using namespace std;

//forward declarations
class Tile;
class GameEngine;
class CTileTypes;

class Map
{
public:
	void RevealAll();

//Constructors, destructor
    Map();
    Map(int w,int h);
    ~Map();

    static Map* loadMap(GameEngine *game, string fileName);
    bool   Init(GameEngine *game);

    int    GetWidth()  { return width;  }
    int    GetHeight() { return height; }

    Tile*  getTile(int index)     const;
    Tile*  getTileAt(int x,int y) const;
    
    CTileTypes *TileTypes(void);
    CTileType *TileType(Tile *t);

    void   setTile(int index,Tile* newTile);
    void   setTileAt(int x,int y,Tile* newTile);

    void   FalseTerrain(long ii);
    void   PlaceRoad(long idx);
    void   ClearForest(long idx);
    void   UpdateTileLinks(enum tileTypes type, int x, int y);


private:
    GameEngine*  m_pGame;
    int          height,width;
    Tile*        tiles[30000]; //shouldn't include a fixed size
                               //do it with a vector
    CTileTypes*  tileTypes;
};

#endif //MAP_H

