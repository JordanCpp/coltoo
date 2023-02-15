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
// FILE		: map.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: Map
//
// DESCRIPTION	: Map of tiles
//

#include "map.h"
#include "tile.h"
#include "globalData.h"
#include "gameEngine.h"

//Constructors, destructor
Map::Map()
{
    long i=0;
    width  = 0;
    height = 0;
    tileTypes = NULL;
    for(i=0;i<30000;i++)
        tiles[i]=NULL;
}

Map::~Map()
{
    int i = 0;

    #ifdef DEBUG
    cout << "deleting map tiles" << endl;
    #endif
    if(tileTypes) delete tileTypes;

    for(i = 0; i < 30000; i++)
        if(tiles[i])
            delete tiles[i];
}

Map::Map(int w,int h) : width(w),height(h)
{
    long i=0;
    tileTypes = NULL;
    for(i=0;i<30000;i++)
        tiles[i]=NULL;
}

//Methods
bool Map::Init(GlobalData* globalData)
{
    GlobalData* data = globalData;

    int x=0,y=0,k=0,x1,y1,land=0,x2;
    long ii=0;
    
    //added 20/6
    tileTypes = new CTileTypes();
    tileTypes->InitTileTypes();

//added 5/25
//places a row of arctic tiles along top and bottom edges of map
    for(ii=0;ii<width;ii++)
    {
      tiles[ii]->setTerrain(TERRAIN_ARCTIC);
      tiles[ii]->setFlags(TILE_WATER, false);
      
      tiles[ii]->setFlags(TILE_RIVER, false);
      tiles[ii]->setFlags(TILE_FOREST, false);
      tiles[ii]->setFlags(TILE_RAIN, false);
      tiles[ii]->setFlags(TILE_HILL, false);
      tiles[ii]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii]->setFlags(TILE_PEAK, false);
      
      tiles[ii+(width*(height-1))]->setTerrain(TERRAIN_ARCTIC);
      tiles[ii+(width*(height-1))]->setFlags(TILE_WATER, false);
      
      tiles[ii+(width*(height-1))]->setFlags(TILE_RIVER, false);
      tiles[ii+(width*(height-1))]->setFlags(TILE_FOREST, false);
      tiles[ii+(width*(height-1))]->setFlags(TILE_RAIN, false);
      tiles[ii+(width*(height-1))]->setFlags(TILE_HILL, false);
      tiles[ii+(width*(height-1))]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii+(width*(height-1))]->setFlags(TILE_PEAK, false);      
      
    }

//added 5/25
//adds a column of Ocean and HighSeas to the sides of the map    
    for(ii=width;ii<width*(height-1);ii+=width)
    {
      tiles[ii]->setTerrain(TERRAIN_HIGHSEAS);
      tiles[ii]->setFlags(TILE_WATER, true);
      
      tiles[ii]->setFlags(TILE_RIVER, false);
      tiles[ii]->setFlags(TILE_FOREST, false);
      tiles[ii]->setFlags(TILE_RAIN, false);
      tiles[ii]->setFlags(TILE_HILL, false);
      tiles[ii]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii]->setFlags(TILE_PEAK, false);      
      
      tiles[ii+1]->setTerrain(TERRAIN_OCEAN);
      tiles[ii+1]->setFlags(TILE_WATER, true);
      
      tiles[ii+1]->setFlags(TILE_RIVER, false);
      tiles[ii+1]->setFlags(TILE_FOREST, false);
      tiles[ii+1]->setFlags(TILE_RAIN, false);
      tiles[ii+1]->setFlags(TILE_HILL, false);
      tiles[ii+1]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii+1]->setFlags(TILE_PEAK, false);      
      
      tiles[ii+(width-1)]->setTerrain(TERRAIN_HIGHSEAS);
      tiles[ii+(width-1)]->setFlags(TILE_WATER, true);
      
      tiles[ii+(width-1)]->setFlags(TILE_RIVER, false);
      tiles[ii+(width-1)]->setFlags(TILE_FOREST, false);
      tiles[ii+(width-1)]->setFlags(TILE_RAIN, false);
      tiles[ii+(width-1)]->setFlags(TILE_HILL, false);
      tiles[ii+(width-1)]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii+(width-1)]->setFlags(TILE_PEAK, false);      
      
      tiles[ii+(width-2)]->setTerrain(TERRAIN_OCEAN);
      tiles[ii+(width-2)]->setFlags(TILE_WATER, true);
      
      tiles[ii+(width-2)]->setFlags(TILE_RIVER, false);
      tiles[ii+(width-2)]->setFlags(TILE_FOREST, false);
      tiles[ii+(width-2)]->setFlags(TILE_RAIN, false);
      tiles[ii+(width-2)]->setFlags(TILE_HILL, false);
      tiles[ii+(width-2)]->setFlags(TILE_MOUNTAIN, false);
      tiles[ii+(width-2)]->setFlags(TILE_PEAK, false);      
      
    }

//added 5/25
//checks the east third of map to see if tile is within 3 tiles of land    
  for(y=600;y<29400;y+=150)
  {
    for(x=148;x>99;x--)
    {
      if(tiles[y+x]->getTerrain()==TERRAIN_OCEAN)
      {
        for(y1=y-450;y1<y+600;y1+=150)
        {

//if tile is too close to east edge put a limit on tiles checked        
          switch (x)
          {
            case (148) : {x2=0;break;}
            case (147) : {x2=1;break;}
            case (146) : {x2=2;break;}
            case (145) : {x2=3;break;}
            default : x2=4;
          }

          for(x1=x-3;x1<x+x2;x1++)
          {
            if(!(tiles[y1+x1]->getTerrain()==TERRAIN_OCEAN ||
            tiles[y1+x1]->getTerrain()==TERRAIN_HIGHSEAS)) {land=1;}
          }
        }
        if(land==0 && tiles[y+x+1]->getTerrain()==TERRAIN_HIGHSEAS)
        {
          tiles[y+x]->setTerrain(TERRAIN_HIGHSEAS);
        }
        land=0;
      }
    }
  }    

    //Initialize each tile properties and add random flags
    for(y=0, ii=0; y < height; y++)
    {
        for(x=0; x < width; x++, ii++)
        {
            tiles[ii]->setXPos(x);
            tiles[ii]->setYPos(y);
            tiles[ii]->setShrdstate(2);
            tiles[ii]->setFkterrain(0);
            tiles[ii]->setVillages(0);

            //  If not water or river, randomly make it a fake tile
            k=(rand()%8);
            if(k==1)
            {
                if(!tiles[ii]->Is(TILE_WATER) &&
                   !tiles[ii]->Is(TILE_RIVER) && ii>149 && ii<29849 )  
                {FalseTerrain(ii);}
            }

            // If not water or a Peak (unreachable terrain for a
            // ground unit) randomly put a rumor on it
            if(!tiles[ii]->Is(TILE_WATER) && !tiles[ii]->Is(TILE_PEAK) &&
                  ii>width && ii<data->mapmax-width)
            {
                k=(rand()%40);

//changed 5/25
//prevents rumors from being next to each other (real ones)                
                if(k==1 && !tiles[ii-width-1]->Is(TILE_RUMOR) &&
                      !tiles[ii-width]->Is(TILE_RUMOR) &&
                      !tiles[ii-width+1]->Is(TILE_RUMOR) &&
                      !tiles[ii-1]->Is(TILE_RUMOR))
                {
                    tiles[ii]->setFlags(TILE_RUMOR, true);
                }
                
                k=(rand()%7);

//changed 5/25
//prevents villages from being next to each other (real ones)                
                if(k==1 && !tiles[ii]->Is(TILE_RUMOR) &&
                      tiles[ii-width-1]->getVillages()==0 &&
                      tiles[ii-width]->getVillages()==0 &&
                      tiles[ii-width+1]->getVillages()==0 &&
                      tiles[ii-1]->getVillages()==0)
                {
                  
                    tiles[ii]->setVillages(tiles[ii]->getVillages()+(rand()%4)+1);
                    PlaceRoad(ii);
                }
            }
        }
    }

    //update Tile links for every tile if needed.
    for(y=0, ii=0; y < height; y++)
    {
        for(x=0; x < width; x++, ii++)
        {
            if(tiles[ii]->Is(TILE_PEAK) || tiles[ii]->Is(TILE_FAKEPEAK))
                UpdateTileLinks(TILE_PEAK,x,y);

            if(tiles[ii]->Is(TILE_MOUNTAIN) || tiles[ii]->Is(TILE_FAKEMOUNTAIN))
                UpdateTileLinks(TILE_MOUNTAIN,x,y);

            if(tiles[ii]->Is(TILE_HILL) || tiles[ii]->Is(TILE_FAKEHILL))
                UpdateTileLinks(TILE_HILL,x,y);

            if(tiles[ii]->Is(TILE_FOREST) || tiles[ii]->Is(TILE_FAKEFOREST))
                UpdateTileLinks(TILE_FOREST,x,y);

            if(tiles[ii]->Is(TILE_ROAD))
                UpdateTileLinks(TILE_ROAD,x,y);
            if(tiles[ii]->Is(TILE_RIVER) ||
               tiles[ii]->Is(TILE_WATER)   )
                UpdateTileLinks(TILE_RIVER,x,y);
        }
    }
    return true;
}

void Map::setTileAt(int x,int y,Tile* newTile)
{
  if(x>=width || x<0 || y>=height || y<0)
    cout << "setTileAt ERROR: index out of bounds.\n";
  else
  {
    tiles[y*width + x] = newTile;
    newTile->setIndex(y*width + x);
  }
}

void Map::setTile(int index,Tile* newTile)
{
  if(index < 0 || index >= height*width)
    cout << "setTile ERROR: index out of bounds. \n";
  else
  {
    tiles[index] = newTile;
    newTile->setIndex(index);
  }
} 
       
Tile*   Map::getTileAt(int x,int y) const
{
  if(x>=width || x<0 || y>=height || y<0)
  {
    cout << "getTileAt ERROR: index out of bounds.\n";
    return NULL;
  }
  else
    return tiles[y*width + x];
}

Tile*   Map::getTile(int index) const
{
  if(index < 0 || index >= height*width)
  {
    cout << "getTile ERROR: index out of bounds. \n";
    return NULL;
  }
  else
    return tiles[index];
}
    
Map* Map::loadMap(GlobalData* globalData, string fileName) //should read map size from map file
{
    FILE *fp;
    long i;
    Map* createdMap = new Map(150,200); //change to other dimensions
                                        //than 150x200 tiles
    char mbmap[30001];

    char mapFileNames[11][10]={"map00.txt","map01.txt","map02.txt","map03.txt",
                               "map04.txt","map05.txt","map06.txt","map07.txt",
                               "map08.txt","map09.txt","map10.txt"};

    char filename[25];
    
    GlobalData *data = globalData;
    
    if(fileName == "")
    {
        int k=rand()%11;    
        sprintf(filename,"data/text/%s",mapFileNames[k]);
        #ifdef DEBUG
        cout << "  Loading map " << mapFileNames[k] << endl;
        #endif
    }
    else
    {
        sprintf(filename,"data/text/%s",fileName.c_str());
        #ifdef DEBUG
        cout << "  Loading map " << fileName << endl;
        #endif
    }

    if(!createdMap) { return NULL; }

    if((fp=fopen(filename, "r")) == NULL)
    {
        cout << "ERROR opening file" << filename << endl << endl;
        delete createdMap; return NULL;
    }
  
    fscanf(fp,"%s",&mbmap);
    fclose(fp);
  
    for(i=0;i<30000;i++)
    {
        Tile* currentTile = new Tile();

        if(!currentTile) { delete createdMap; return NULL; }
        currentTile->InitShrdstate(data->playerlist);

        createdMap->setTile(i,currentTile);

        switch(mbmap[i])
        {
            case 'A': currentTile->setFlags(TILE_RIVER, /*true*/ false);
            case 'a': currentTile->setTerrain(TERRAIN_OCEAN);
                      currentTile->setFlags(TILE_WATER, true);
                      break;

            case 'b': currentTile->setTerrain(TERRAIN_LAKE);
                      currentTile->setFlags(TILE_WATER, true);
                      break;

            case 'C': currentTile->setFlags(TILE_RIVER, true);
            case 'c': currentTile->setTerrain(TERRAIN_ARCTIC);
                      break;

            case 'D': currentTile->setFlags(TILE_RIVER, true);
            case 'd': currentTile->setTerrain(TERRAIN_TUNDRA);
                      break;

            case 'E': currentTile->setFlags(TILE_RIVER, true);
            case 'e': currentTile->setTerrain(TERRAIN_PRAIRIE);
                      break;

            case 'F': currentTile->setFlags(TILE_RIVER, true);
            case 'f': currentTile->setTerrain(TERRAIN_GRASS);
                      break;

            case 'G': currentTile->setFlags(TILE_RIVER,true);
            case 'g': currentTile->setTerrain(TERRAIN_SAVANNAH);
                      break;

            case 'H': currentTile->setFlags(TILE_RIVER, true);
            case 'h': currentTile->setTerrain(TERRAIN_DESERT);
                      break;

            case 'I': currentTile->setFlags(TILE_RIVER, true);
            case 'i': currentTile->setTerrain(TERRAIN_TUNDRA); /*boreal*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'J': currentTile->setFlags(TILE_RIVER, true);
            case 'j': currentTile->setTerrain(TERRAIN_GRASS);  /*conifer*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'K': currentTile->setFlags(TILE_RIVER, true);
            case 'k': currentTile->setTerrain(TERRAIN_OPENS); /*mixed*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'L': currentTile->setFlags(TILE_RIVER, true);
            case 'l': currentTile->setTerrain(TERRAIN_PRAIRIE); /*broad*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'M': currentTile->setFlags(TILE_RIVER, true);
            case 'm': currentTile->setTerrain(TERRAIN_SAVANNAH); /*tropic*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'N': currentTile->setFlags(TILE_RIVER, true);
            case 'n': currentTile->setTerrain(TERRAIN_SAVANNAH); /*rain*/
                      currentTile->setFlags(TILE_FOREST, true);
                      currentTile->setFlags(TILE_RAIN, true);
                      break;

            case 'O': currentTile->setFlags(TILE_RIVER, true);
            case 'o': currentTile->setTerrain(TERRAIN_DESERT);  /*shrub*/
                      currentTile->setFlags(TILE_FOREST, true);
                      break;

            case 'Q': currentTile->setFlags(TILE_RIVER, true);
            case 'q': currentTile->setTerrain(TERRAIN_STEPPE);
                      break;

            case 'R': currentTile->setFlags(TILE_RIVER, true);
            case 'r': currentTile->setTerrain(TERRAIN_CHAPARRAL);
                      break;

            case 'S': currentTile->setFlags(TILE_RIVER, true);
            case 's': currentTile->setTerrain(TERRAIN_OPENS);
                      break;

            case 'T': currentTile->setFlags(TILE_RIVER, true);
            case 't': currentTile->setTerrain(TERRAIN_OPENS);   /*hill*/
                      currentTile->setFlags(TILE_HILL, true);
                      break;

            case 'U': currentTile->setFlags(TILE_RIVER, true);
            case 'u': currentTile->setTerrain(TERRAIN_TUNDRA);  /*mountain*/
                      currentTile->setFlags(TILE_MOUNTAIN, true);
                      break;

            case 'V': currentTile->setFlags(TILE_RIVER, true);
            case 'v': currentTile->setTerrain(TERRAIN_ARCTIC);  /*mountain peak*/
                      currentTile->setFlags(TILE_PEAK, true);
                      break;

            default:  //currentTile->setTerrain(TERRAIN_OPENS+37);
                      break;
        }
    }
    return createdMap;
}


void Map::RevealAll()
{
	for(int i=0 ; i < height*width ; i++){
		tiles[i]->setShrdstate(0);
	}
}


CTileTypes *Map::TileTypes(void)
{
    return tileTypes;
}

CTileType *Map::TileType(Tile *t)
{
    #ifdef DEBUG
    if(t->Is(TILE_FOREST)) cout<<"Getting forested terrain "<<t->getTerrain()<<endl;
    else cout<<"Getting terrain "<<t->getTerrain()<<endl;
    #endif
    return tileTypes->FindTileTypeFrom(t);
}

//
// $Id: map.cpp,v 1.18 2004/06/23 15:37:05 sikon Exp $
//
