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
// FILE		: tile.h
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: Tile
//
// DESCRIPTION	: A tile is a piece of map.
//

#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include "globalData.h"
#include "resources.h"

using namespace std;

//forward declarations
class Unit;
class Player;

#define TERRAIN_ARCTIC       1
#define TERRAIN_TUNDRA      77
#define TERRAIN_DESERT      153
#define TERRAIN_OPENS       229
#define TERRAIN_SAVANNAH    305
#define TERRAIN_GRASS       381
#define TERRAIN_PRAIRIE     457
#define TERRAIN_STEPPE      533
#define TERRAIN_CHAPARRAL   609
#define TERRAIN_LAKE        685
#define TERRAIN_OCEAN       761
// Sikon to Chainsword 06/21:
// this is the X offset of a tile graphic, not its unique ID!
#define TERRAIN_RUMOR       381
//added HIGHSEAS 5/23
#define TERRAIN_HIGHSEAS    913

#define SHROUD_NONE 0
#define SHROUD_PART 1
#define SHROUD_FULL 2

enum tileTypes { TILE_ROAD=1, TILE_RAIN , TILE_FOREST  , TILE_FAKEFOREST  ,
                 TILE_WATER , TILE_CLEAR, TILE_MOUNTAIN, TILE_FAKEMOUNTAIN,
                 TILE_PLOWED, TILE_RIVER, TILE_HILL    , TILE_FAKEHILL    ,
                 TILE_BUILD , TILE_UNIT , TILE_PEAK    , TILE_FAKEPEAK    ,
                 TILE_FAKE  , TILE_RUMOR, TILE_FAKERUMOR };

typedef struct
{
    bool                forest;
    bool                rain;
    bool                mountain;
    bool                hill;
    bool                peak;
    bool                river;
    bool                water;
    bool                clear;
    bool                plowed;
    bool                road;
    bool                build;
    bool                unit; //should this be here?
    bool                fake;
    bool                rumor;
    bool                fakeRumor;
    bool                fakeForest;
    bool                fakeMountain;
    bool                fakeHill;
    bool                fakePeak;
} tileFlags ;

typedef struct
{
    string nationName;
    Uint8 state;
} ShrdstateType;

class tileLinks
{
public:
    tileLinks(){E=N=W=S=NW=SW=NE=SE=false;}
    ~tileLinks(){};

    bool   E;
    bool   N;
    bool   W;
    bool   S;
    bool   NW;
    bool   SW;
    bool   NE;
    bool   SE;
};

class Tile
{
public:
    Tile();
    ~Tile();

    tileFlags*    getFlags() { return m_Flags;   }


    Uint8     getXPos()      { return xpos;      }
    Uint8     getYPos()      { return ypos;      }
    Uint16    getTerrain()   { return terrain;   }
    Uint8     getShrdstate(Uint8 n); //changed 16/6
    Uint16    getFkterrain() { return fkterrain; }
    Uint8     getVillages()  { return villages;  }
    long      getIndex()     { return index; }

    void   setXPos(Uint8 t)       { xpos = t;      }
    void   setYPos(Uint8 t)       { ypos = t;      }
    void   setTerrain(Uint16 t)   { terrain = t;   }
    void   setShrdstate(Uint8 t); //changed 16/6
    void   setShrdstate(Uint8 nation,Uint8 t); //changed 16/6
    void   setFkterrain(Uint16 t) { fkterrain = t; }
    void   setVillages(Uint8 t)   { villages = t;  }
    void   setIndex(long t)       { index = t; }

    void   setFlags(enum tileTypes flag, bool onoff);
    
    void   InitShrdstate(vector<Player*> pl);
    void   InitShrdstate(Player* pl);

    //Real link methods apply to the basic real tile type, so that
    //calls to RealLink using (for example) TILE_HILL and TILE_FAKEHILL
    //act as being applied to the basic tile type TILE_HILL and so on.
    //Fake link methods to the same but using the basic fake tile type.
    //FakeLink with TILE_PEAK and TILE_FAKEPEAK apply to TILE_FAKEPEAK.
    bool   Is(enum tileTypes t);
    bool   IsReal(enum tileTypes t);
    bool   IsFake(enum tileTypes t);

    void   setLink(enum tileTypes type, enum directions d, bool onoff);
    void   setFakeLink(enum tileTypes type, enum directions d, bool onoff);
    void   setRealLink(enum tileTypes type, enum directions d, bool onoff);

    bool   hasLink(enum tileTypes type, enum directions d);
    bool   hasFakeLink(enum tileTypes type, enum directions d);
    bool   hasRealLink(enum tileTypes type, enum directions d);

private:

    tileFlags*    m_Flags;        //flags for the tile
    Uint8         xpos;           //x position on map 0..Map::width -1
    Uint8         ypos;           //y position on map 0..Map::height-1
    Uint16        terrain;        //terrain type: Arctic, Tundra... in tilesheet
    Uint16        fkterrain;      //fake terrain type
    Uint8         villages;       //village type placed on the tile

    vector<ShrdstateType> shrdstate;      //tile is shrouded, partially or revealed
                                  //should be placed in Player Class - One for
                                  //each player/AI

    tileLinks*    m_RoadLinks;    //new tile surrounding roads

    tileLinks*    m_ForestLinks;     //tile surrounding forests
    tileLinks*    m_FakeForestLinks; //tile surrounding fake forests
    Uint32        m_ForestIcon;      //forest icon to display //Needed??

    tileLinks*    m_HillLinks;    //tile surrounding hills
    tileLinks*    m_FakeHillLinks;//tile surrounding fake hills
    Uint32        m_HillIcon;     //hill icon to display //Needed??

    tileLinks*    m_MountainLinks;    //tile surrounding mountains
    tileLinks*    m_FakeMountainLinks;//tile surrounding fake mountains
    Uint32        m_MountainIcon;     //mountain icon to display //Needed??

    tileLinks*    m_PeakLinks;     //tile surrounding peaks
    tileLinks*    m_FakePeakLinks; //tile surrounding fake peaks
    Uint32        m_PeakIcon;      //peak icon to display //Needed??

    tileLinks*    m_RiverLinks;    //new tile surrounding rivers REVIEW IMPLEMENTATION???
    Uint32        m_RiverIcon;     //river icon to display //TO DO

    Unit*               workingUnit;
    vector<Unit*>       walkingUnits;
    vector<Resources*>  resources;
    
    long          index; //added 16/6
};
#endif //TILE_H

//
// $Id: tile.h,v 1.10 2004/06/23 15:37:05 sikon Exp $
//
