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

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"
// >>>
#include "unit.h"
// <<<

/*---------------------------Orders----------------------------*/
void GraphicsEngine::Orders(int i)  //in Unit class??
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();

/*  Check to see if the tile to be plowed is already plowed,
    or if the tile to get a colony already has a colony, etc.
    See if the tile is a water, or Peak tile*/

    switch (i)
    {
      case (9): //clear
      {
        if(map->getTile(data->mapnum)->Is(TILE_FOREST))
        {
          map->ClearForest(data->mapnum);
          ScreenUpdate();
        }
//added 6/1
//if no forest
        else {MessageWindow(11);}
        break;
      }
      case (10): //plow
      {
        if(!(map->getTile(data->mapnum)->Is(TILE_PLOWED) ||
             map->getTile(data->mapnum)->Is(TILE_WATER)  ||
             map->getTile(data->mapnum)->Is(TILE_PEAK)   ||
             map->getTile(data->mapnum)->Is(TILE_FOREST)))
        {
          map->getTile(data->mapnum)->setFlags(TILE_PLOWED, true);
          ScreenUpdate();
        }
//added 6/1
//if already plowed        
        else
        {
          if(map->getTile(data->mapnum)->Is(TILE_PLOWED)) {MessageWindow(12);}
        }
        break;
      }
      case (11): //road
      {
        if(!(map->getTile(data->mapnum)->Is(TILE_ROAD)  ||
             map->getTile(data->mapnum)->Is(TILE_WATER) ||
             map->getTile(data->mapnum)->Is(TILE_PEAK)))
        {
          map->PlaceRoad(data->mapnum);
          ScreenUpdate();
        }
//added 6/1
//if already road        
        else
        {
          if(map->getTile(data->mapnum)->Is(TILE_ROAD))
          {
            MessageWindow(13); 
          }
        }        
        break;
      }
    case (20): //end active unit's turn
    {
      data->mf=0;
      break;
    }
    default:    //build
    {
      if(!(map->getTile(data->mapnum)->Is(TILE_BUILD) ||
             map->getTile(data->mapnum)->Is(TILE_WATER) ||
             map->getTile(data->mapnum)->Is(TILE_PEAK)))
      {
//        map->PlaceRoad(data->mapnum);
//        map->getTile(data->mapnum)->setFlags(TILE_BUILD, true);
            
//added 6/1
//assigns a new colony a number and stores its location            
//        data->colony[data->colonyCount].colonyLoc=data->mapnum;
//        data->colonyCount++;            
          Colony *col = m_pGame->PlaceColony(data->unitList[data->turn], data->mapnum);        
          ScreenUpdate();
          
          if(data->unitList[data->turn]->getNation() == data->nation)
          {
              DrawTILE(map1,screen,0,0,screenResX,screenResY,0,0);
              DrawTILE(screen,cds1,0,0,screenResX,screenResY,0,0);
              UpdateCDS(col);
              UpdateScreen0();
              data->scrndsply = 1;
          }
      }
//added 6/1
//if already a colony      
      else
      {
        if(map->getTile(data->mapnum)->Is(TILE_BUILD))
        {
          MessageWindow(14); 
        }
      }
    }
  }
}

/*--------------------------ClearForest---------------------------*/
void Map::ClearForest(long idx)
{
//  Clear the Forest flag for the tile, removing the link flags
//  for the tile. Then update the links for the 4 connecting tiles.

    int x = tiles[idx]->getXPos(), y = tiles[idx]->getYPos();

    tiles[idx]->setFlags(TILE_FOREST, false);

    //update surrounding links
    UpdateTileLinks(TILE_FOREST, x  , y-1); //N
    UpdateTileLinks(TILE_FOREST, x+1, y  ); //E
    UpdateTileLinks(TILE_FOREST, x  , y+1); //S
    UpdateTileLinks(TILE_FOREST, x-1, y  ); //W

    //TO DO: add logged wood to nearest colony
}


/*---------------------------PlaceRoad----------------------------*/

void Map::PlaceRoad(long idx)
{
//  Set the Road flag for the tile, then set the link flags for
//  the tile and the links for the 8 connecting tiles.

    int x = tiles[idx]->getXPos(), y = tiles[idx]->getYPos();
    tiles[idx]->setFlags(TILE_ROAD, true);
    UpdateTileLinks(TILE_ROAD, x  , y  );

    UpdateTileLinks(TILE_ROAD, x-1, y-1); //NW
    UpdateTileLinks(TILE_ROAD, x  , y-1); //N
    UpdateTileLinks(TILE_ROAD, x+1, y-1); //NE
    UpdateTileLinks(TILE_ROAD, x+1, y  ); //E
    UpdateTileLinks(TILE_ROAD, x+1, y+1); //SE
    UpdateTileLinks(TILE_ROAD, x  , y+1); //S
    UpdateTileLinks(TILE_ROAD, x-1, y+1); //SW
    UpdateTileLinks(TILE_ROAD, x-1, y  ); //W
}

/*------------------------UpdateTileLinks-------------------------*/
void Map::UpdateTileLinks(enum tileTypes type, int x, int y)
{
    long ii = y*width + x;

    //test if tile indices are out of bounds
    if(x<0 || x>width-1 || y<0 || y>height-1) return;

    switch(type)
    {
    case TILE_ROAD: //Links in 8 directions
        if(!tiles[ii]->Is(TILE_ROAD)) return;
        if(x>0)
        {
            tiles[ii]->setLink(type,W,getTileAt(x-1,y)->Is(type));
            if(y>0) tiles[ii]->setLink(type,NW,getTileAt(x-1,y-1)->Is(type));
            if(y<height-1) tiles[ii]->setLink(type,SW,getTileAt(x-1,y+1)->Is(type));
        }
        if(x<width-1)
        {
            tiles[ii]->setLink(type,E,getTileAt(x+1,y)->Is(type));
            if(y>0) tiles[ii]->setLink(type,NE,getTileAt(x+1,y-1)->Is(type));
            if(y<height-1) tiles[ii]->setLink(type,SE,getTileAt(x+1,y+1)->Is(type));
        }
        if(y>0) tiles[ii]->setLink(type,N,getTileAt(x,y-1)->Is(type));
        if(y<height-1) tiles[ii]->setLink(type,S,getTileAt(x,y+1)->Is(type));
        break;

    case TILE_PEAK    : case TILE_FAKEPEAK    : //links in 4 directions
    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN: // N, E, S and W
    case TILE_HILL    : case TILE_FAKEHILL    :
    case TILE_FOREST  : case TILE_FAKEFOREST  :
        if(x>0)
        {
            tiles[ii]->setRealLink(type,W,getTileAt(x-1,y)->IsReal(type));
            tiles[ii]->setFakeLink(type,W,getTileAt(x-1,y)->IsFake(type));
        }
        if(x<width-1)
        {
            tiles[ii]->setRealLink(type,E,getTileAt(x+1,y)->IsReal(type));
            tiles[ii]->setFakeLink(type,E,getTileAt(x+1,y)->IsFake(type));
        }
        if(y>0)
        {
            tiles[ii]->setRealLink(type,N,getTileAt(x,y-1)->IsReal(type));
            tiles[ii]->setFakeLink(type,N,getTileAt(x,y-1)->IsFake(type));
        }
        if(y<height-1)
        {
            tiles[ii]->setRealLink(type,S,getTileAt(x,y+1)->IsReal(type));
            tiles[ii]->setFakeLink(type,S,getTileAt(x,y+1)->IsFake(type));
        }
        break;

    case TILE_RIVER:
        if(!tiles[ii]->Is(TILE_RIVER)) return;
        if(x>0)
        {
            tiles[ii]->setLink(type,W,getTileAt(x-1,y)->Is(type)||
                                      getTileAt(x-1,y)->Is(TILE_WATER));
            if(y>0) tiles[ii]->setLink(type,NW,getTileAt(x-1,y-1)->Is(type)||
                                               getTileAt(x-1,y-1)->Is(TILE_WATER));
            if(y<height-1) tiles[ii]->setLink(type,SW,getTileAt(x-1,y+1)->Is(type)||
                                               getTileAt(x-1,y+1)->Is(TILE_WATER));
        }
        if(x<width-1)
        {
            tiles[ii]->setLink(type,E,getTileAt(x+1,y)->Is(type)||
                                      getTileAt(x+1,y)->Is(TILE_WATER));
            if(y>0) tiles[ii]->setLink(type,NE,getTileAt(x+1,y-1)->Is(type)||
                                               getTileAt(x+1,y-1)->Is(TILE_WATER));
            if(y<height-1) tiles[ii]->setLink(type,SE,getTileAt(x+1,y+1)->Is(type)||
                                                      getTileAt(x+1,y+1)->Is(TILE_WATER));
        }
        if(y>0) tiles[ii]->setLink(type,N,getTileAt(x,y-1)->Is(type)||
                                          getTileAt(x,y-1)->Is(TILE_WATER));
        if(y<height-1) tiles[ii]->setLink(type,S,getTileAt(x,y+1)->Is(type)||
                                                 getTileAt(x,y+1)->Is(TILE_WATER));
        break;
//        if(x>0       ) tiles[ii]->setLink(type,W,getTileAt(x-1,y)->Is(type));
//        if(x<width-1 ) tiles[ii]->setLink(type,E,getTileAt(x+1,y)->Is(type));
//        if(y>0       ) tiles[ii]->setLink(type,N,getTileAt(x,y-1)->Is(type));
//        if(y<height-1) tiles[ii]->setLink(type,S,getTileAt(x,y+1)->Is(type));
//        break;

    default:
        break;
    }
}

//
// $Id: orders1.cpp,v 1.9 2004/06/23 15:37:05 sikon Exp $
//

