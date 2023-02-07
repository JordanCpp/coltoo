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
#include <SDL.h>
#include <string>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"

/*---------------------------InitArrays1------------------------*/
void GraphicsEngine::InitArrays1(void)
{
//    GlobalData* data = m_pGame->GetData();
//    Map* map = m_pGame->GetMap();
//    int x,y,rr,k,i;
//    long ii,mapnumold;

/*  Set the elements of the maptile array to 0
    Assigns the col and row position to the first two elements
    Sets the shroud element to 2*/
    
/*
  rr=0;
  for(y=25;y<725;y+=50)
  {
      for(x=8;x<833;x+=75)
      {
          data->stile[rr][XPOS]=x;
          data->stile[rr][YPOS]=y;
          rr++;
      }
  }
*/
/*
ii=0;
  for(y=0;y<200;y++)
  {
    for(x=0;x<150;x++)
    {
      map->getTile(ii)->setXPos(x);
      map->getTile(ii)->setYPos(y);
      map->getTile(ii)->setShrdstate(2);
//      map->getTile(ii)->setRdlnks(0);
      map->getTile(ii)->setFkterrain(0);
//      map->getTile(ii)->setForestlnks(0);
//      map->getTile(ii)->setFkforestlnks(0);
      map->getTile(ii)->setVillages(0);
//      map->getTile(ii)->set10(0); //not used
*/
/*  If not water or river, randomly make it a fake tile*/
/*      k=(rand()%8);
      if(k==1)
      {
        if(map->getTile(ii)->Is(TILE_WATER) ||
           map->getTile(ii)->Is(TILE_RIVER)){}
        else{FalseTerrain(ii);}
      }
*/
/*  If not water or a Peak (unreachable terrain for a ground unit)
    randomly put a rumor on it*/        
/*      if(map->getTile(ii)->Is(TILE_WATER) ||
         map->getTile(ii)->Is(TILE_PEAK)){}
      else
      {
        k=(rand()%25);
        if(k==1&&ii!=data->units[1][2])
        {
            map->getTile(ii)->setFlags(TILE_RUMOR, true);
        }
        if(k==2&&ii!=data->units[1][2])
        {
          map->getTile(ii)->setVillages(map->getTile(ii)->getVillages()+(rand()%3)+1);
          mapnumold=data->mapnum;
          data->mapnum=ii;
          PlaceRoad();
          data->mapnum=mapnumold;
        }
      }
      ii++;
    }
  }
*/
/*  Set up the Surfaces for the terrain blend
    Copies the terrain to new surfaces blender and blender2
    Copies the blend masks to the new surface blender and blender2
    Copies the partial shroud to blender2
    Creates the full shroud (FillRect(); with black)*/
/*
  for(y=0;y<3;y++)
  {
    for(x=0;x<11;x++)
    {
      DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[y],data->tw,data->th,
                data->tilex[x],data->tiley[0]);
      DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[y],data->tw,data->th,
                data->tilex[x],data->tiley[0]);
      DrawSURF(blender2,pshrd,data->tilex[x],data->tiley[y]);
    }
    FillRect(blender,data->tilex[11],data->tiley[y],data->tw,data->th,0,0,0);
  }

  for(x=0;x<12;x++)
  {
    DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[0],data->tw,data->th,
            data->tilex[0],data->tiley[1]);
    DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[1],data->tw,data->th,
            data->tilex[1],data->tiley[1]);
    DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[2],data->tw,data->th,
            data->tilex[2],data->tiley[1]);

    DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[0],data->tw,data->th,
            data->tilex[0],data->tiley[1]);
    DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[1],data->tw,data->th,
            data->tilex[1],data->tiley[1]);
    DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[2],data->tw,data->th,
            data->tilex[2],data->tiley[1]);
  }
*/
/*
  k=0;
  for(y=1;y<257;y+=51)
  {
    for(x=1;x<838;x+=76)
    {
      data->tile50[k][0]=x;data->tile50[k][1]=y;
      k++;
    }
  }
*/

/*put the data for the ship on the map into the shipstruct array.*/
/*  DefaultShipName(data->shiptypenum[data->caravel],data->Buy,data->caravel);
  strcpy(data->units_ships[data->shipnum].type,data->Buy[data->caravel]);
  data->units_ships[data->shipnum].typenum=data->caravel;
  ShipCharacteristics(data->units_ships[data->shipnum].typenum);
*/
/*zero the value of the SelectedShipstart & 
  SelectedShipCargo arrays;*/
/*  for(i=0;i<100;i++){data->SSstart[i]=0;}
  for(i=0;i<100;i++){data->SSCstart[i]=0;}
*/
}


//
// $Id: initarrays.cpp,v 1.4 2004/06/23 15:37:05 sikon Exp $
//

