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
// FILE		: TileType.h
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileResource, CTileType, CTileTypes
//
// DESCRIPTION	: Tile information
//

#ifndef CTILETYPE_H
#define CTILETYPE_H

#define TL_UNDEFINED -1
#define TL_UNFORESTED 0
#define TL_FORESTED 1
#define TL_OTHER 2

#include <string>
#include <vector>
#include "tinyxml.h"

using namespace std;

typedef struct
{
    int farmer;
    int sugar;
    int tabacco;
    int cotton;
    int furs;
    int wood;
    int ore;
    int silver;
    int fish;    
} tileProduction;

class CTileType
{
public:
    // constructors/destructors
    CTileType(void);
    ~CTileType(void);
    
    // Methods
    
    // GET Methods
    int TileID();
    int TileType();
    const char *TileName();
    const char *NewTileName();
    int NewTileID();
    int Movement();
    int Defensive();
    int Improvement();
    int Value();
    const char *ResourceName();
    int ResourceID();
    tileProduction Prodution();

    // SET Methods
    void TileID(int id);
    void TileType(int t);
    void TileName(const char *n);
    void NewTileName(const char *n);
    void NewTileID(int id);
    void Movement(int m);
    void Defensive(int d);
    void Improvement(int i);
    void Value(int v);
    void ResourceName(const char *n);
    void ResourceID(int id);
    void Production(tileProduction p);
    
    void LoadProduction(TiXmlElement *e, CTileType *t);
    
private:
    int tileID;
    int tileType;
    string tileName;
    string transfName;
    int transfID;
    int tileMovement;
    int tileDefensive;
    int tileImprovement;
    int tileValue;
    string resName;
    int resID;
    tileProduction tproduction;
};

#endif
