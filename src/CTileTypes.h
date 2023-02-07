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
// FILE		: CTileTypes.h
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileTypes
//
// DESCRIPTION	: Tile information
//

#ifndef CTILETYPES_H
#define CTYLETYPES_H

#include <vector>
#include "CTileType.h"
#include "CTileResource.h"
#include "tile.h"

using namespace std;

class CTileType;
class CTileResource;

class CTileTypes
{
public:
    CTileTypes();
    ~CTileTypes();
    
    //Methods
    void InitTileTypes(void);
    
    CTileType *FindTileType(const char *name);
    CTileType *FindTileType(int ID);
    
    CTileType *FindTileTypeFrom(Tile *t);
    
    CTileResource *FindTileResource(const char *name);
    CTileResource *FindTileResource(int ID);
    
    CTileType *TileType(void);
    CTileType *TileType(int ID);
    
    CTileResource *TileResource(void);
    CTileResource *TileResource(int ID);

private:
    vector<CTileType*> ttypes;
    int current_tile;
    vector<CTileResource*> tresources;
    int current_resource;
};
#endif
