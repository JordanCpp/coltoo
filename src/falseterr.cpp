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

#include "map.h"
#include "tile.h"

/*---------------------------FalseTerrain---------------------------*/
void Map::FalseTerrain(long ii)
{
    int k;

/*  Sets a tile's flag to Fake
    Then assigns a fake terrain to the tile*/
    
    tiles[ii]->setFlags(TILE_FAKE, true);

    switch(tiles[ii]->getTerrain())
    {
        case(TERRAIN_ARCTIC):
            k=(rand()%5);
            if(k<3) {tiles[ii]->setFkterrain(TERRAIN_TUNDRA);}
            if(k==3){tiles[ii]->setFkterrain(TERRAIN_OPENS);}
            if(k==4){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            break;

        case(TERRAIN_TUNDRA):
            k=(rand()%5);
            if(k<2) {tiles[ii]->setFkterrain(TERRAIN_ARCTIC);}    
            if(k==2){tiles[ii]->setFkterrain(TERRAIN_OPENS);}
            if(k>2) {tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            break;

        case(TERRAIN_DESERT):
            k=(rand()%10);
            if(k<2)      {tiles[ii]->setFkterrain(TERRAIN_PRAIRIE);}
            if(k>1&&k<4) {tiles[ii]->setFkterrain(TERRAIN_GRASS);}
            if(k>3&&k<6) {tiles[ii]->setFkterrain(TERRAIN_STEPPE);}
            if(k==6)     {tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>6&&k<10){tiles[ii]->setFkterrain(TERRAIN_CHAPARRAL);}
            break;

        case(TERRAIN_OPENS):
            k=(rand()%10);
            if(k<2)     {tiles[ii]->setFkterrain(TERRAIN_GRASS);}      
            if(k>1&&k<4){tiles[ii]->setFkterrain(TERRAIN_PRAIRIE);}
            if(k>3&&k<6){tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            if(k>5&&k<8){tiles[ii]->setFkterrain(TERRAIN_STEPPE);}
            if(k>7)     {tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            break;

        case(TERRAIN_SAVANNAH):
            k=(rand()%11);
            if(k<3)     {tiles[ii]->setFkterrain(TERRAIN_GRASS);}
            if(k>2&&k<5){tiles[ii]->setFkterrain(TERRAIN_STEPPE);}
            if(k>4&&k<7){tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            if(k>6&&k<9){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>8)     {tiles[ii]->setFkterrain(TERRAIN_CHAPARRAL);}
            break;

        case(TERRAIN_GRASS):
            k=(rand()%11);
            if(k<2)     {tiles[ii]->setFkterrain(TERRAIN_PRAIRIE);}
            if(k>1&&k<5){tiles[ii]->setFkterrain(TERRAIN_STEPPE);}
            if(k>4&&k<7){tiles[ii]->setFkterrain(TERRAIN_SAVANNAH);}
            if(k>6&&k<9){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>8)     {tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            break;

        case(TERRAIN_PRAIRIE):
            k=(rand()%11);
            if(k<3)     {tiles[ii]->setFkterrain(TERRAIN_GRASS);}
            if(k>2&&k<5){tiles[ii]->setFkterrain(TERRAIN_OPENS);}
            if(k>4&&k<7){tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            if(k>6&&k<9){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>8)     {tiles[ii]->setFkterrain(TERRAIN_CHAPARRAL);}
            break;

        case(TERRAIN_STEPPE):
            k=(rand()%11);
            if(k<3)     {tiles[ii]->setFkterrain(TERRAIN_GRASS);}
            if(k>2&&k<5){tiles[ii]->setFkterrain(TERRAIN_SAVANNAH);}
            if(k>4&&k<7){tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            if(k>6&&k<9){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>8)     {tiles[ii]->setFkterrain(TERRAIN_CHAPARRAL);}
            break;

        case(TERRAIN_CHAPARRAL):
            k=(rand()%11);
            if(k<3)     {tiles[ii]->setFkterrain(TERRAIN_DESERT);}
            if(k>2&&k<5){tiles[ii]->setFkterrain(TERRAIN_SAVANNAH);}
            if(k>4&&k<7){tiles[ii]->setFkterrain(TERRAIN_PRAIRIE);}
            if(k>6&&k<9){tiles[ii]->setFkterrain(TERRAIN_LAKE);}
            if(k>8)     {tiles[ii]->setFkterrain(TERRAIN_GRASS);}
            break;
        default: break;
    }

/*If the tile isn't water, randomly put a fake rumor on it*/ 
   
    k=(rand()%5);
    if(k==1 && tiles[ii]->getFkterrain() != TERRAIN_LAKE)
    {
        tiles[ii]->setFlags(TILE_FAKERUMOR, true);
    }

/*If the tile isn't water or arctic, randomly put a fake forest on it*/

    k=(rand()%10);
    if(k==1 && tiles[ii]->getFkterrain() != TERRAIN_LAKE &&
               tiles[ii]->getFkterrain()!=TERRAIN_ARCTIC   )
    {
        tiles[ii]->setFlags(TILE_FAKEFOREST, true);
    }

//If the tile is arctic, randomly put a fake peak on it

    k=(rand()%5);
    if(k==1 && tiles[ii]->getFkterrain() == TERRAIN_ARCTIC)
        tiles[ii]->setFlags(TILE_FAKEPEAK, true);

//If the tile is tundra, randomly put a fake mountain on it

    k=(rand()%5);
    if(k==1 && tiles[ii]->getFkterrain() == TERRAIN_TUNDRA)
        tiles[ii]->setFlags(TILE_FAKEMOUNTAIN, true);

//If the tile is opens, randomly put a fake hill on it

    k=(rand()%5);
    if(k==1 && tiles[ii]->getFkterrain() == TERRAIN_OPENS)
        tiles[ii]->setFlags(TILE_FAKEHILL, true);
}

//
// $Id: falseterr.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

