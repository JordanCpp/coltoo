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
#include "unit.h"
// >>>
#include "colony.h"
// <<<

/*--------------------------SetTerrain----------------------------*/
void GraphicsEngine::SetTerrain(void)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    short x,y,rr;
    long ii;

/*
    Check to see if the tile isn't fully shrouded
    Draw the tile (this should be changed if a fake)
    If the tile is a fake and partially shrouded, draw the fake 
    terrain
    If the tile is fully revealed, then remove the Fake flags
    If the tile is partially revealed, then put the partial shroud
    on it
*/
    rr=0;ii=data->start;
    for(y=0;y<14;y++)
    {
        for(x=0;x<11;x++)
        {
            if(map->getTile(ii+x)->getShrdstate(data->nationTurn)<2)
            {
                DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                         data->stile[rr][YPOS],
                         data->tw,data->th,
                         map->getTile(ii+x)->getTerrain(),1);

                if(map->getTile(ii+x)->Is(TILE_FAKE) &&
                   map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
                {
                    DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                             data->stile[rr][YPOS],
                             data->tw,data->th,
                             map->getTile(ii+x)->getFkterrain(),1);
                }
                else
                {
                    map->getTile(ii+x)->setFlags(TILE_FAKE, false);
                    map->getTile(ii+x)->setFlags(TILE_FAKERUMOR, false);
                    map->getTile(ii+x)->setFlags(TILE_FAKEFOREST, false);
                }
                if(map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
                {
                    DrawSURF(screen,pshrd,data->stile[rr][XPOS],
                             data->stile[rr][YPOS]);
                }
            }
            else
            {
                DrawSURF(screen,shrd,data->stile[rr][XPOS],
                         data->stile[rr][YPOS]);
            }
            rr++;
        }
        ii+=150;
    }
    SetTerrain2();
}

/*--------------------------SetTerrain2---------------------------*/
void GraphicsEngine::SetTerrain2(void)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    int rr,i;
    long ii;

/*
    Blend the terrain
    check if it needs a partial shroud
    check if it is a fake tile
*/

    data->red=0;data->green=255;
    ii=data->start;
    for(rr=0;rr<144;rr+=11)
    {
        for(i=0;i<11;i++)
        {
            if(map->getTile(ii+i)->getXPos() < map->GetWidth()-1)
            {
                if(map->getTile(ii+i+1)->getShrdstate(data->nationTurn)<2)
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS]+60,
                             data->stile[rr+i][YPOS],15,50,
                             map->getTile(ii+i+1)->getTerrain()+60,1);

                    if(map->getTile(ii+i+1)->getShrdstate(data->nationTurn)==1)
                    {
                        if(map->getTile(ii+i+1)->Is(TILE_FAKE))
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS]+60,
                                     data->stile[rr+i][YPOS],15,50,
                                     map->getTile(ii+i+1)->getFkterrain()+60,1);
                        }
                        else
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS]+60,
                                     data->stile[rr+i][YPOS],15,50,
                                     map->getTile(ii+i+1)->getTerrain()+60,1);
                        }
                    }
                }
                else
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS]+60,
                             data->stile[rr+i][YPOS],15,50,data->tilex[11]+60,1);
                }
            }
        }
        ii+=150;
    }
  
    ii=data->start;
    for(rr=0;rr<154;rr+=11)
    {
        for(i=0;i<11;i++)
        {
            if(map->getTile(ii+i)->getYPos() < map->GetHeight()-1)
            {
                if(map->getTile(ii+i+150)->getShrdstate(data->nationTurn)<2)
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS],
                             data->stile[rr+i][YPOS]+35,75,15,
                             map->getTile(ii+i+150)->getTerrain(),
                             data->tiley[1]+35);

                    if(map->getTile(ii+i+150)->getShrdstate(data->nationTurn)==1)
                    {
                        if(map->getTile(ii+i+150)->Is(TILE_FAKE))
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS],
                                     data->stile[rr+i][YPOS]+35,75,15,
                                     map->getTile(ii+i+150)->getFkterrain(),
                                     data->tiley[1]+35);
                        }
                        else
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS],
                                     data->stile[rr+i][YPOS]+35,75,15,
                                     map->getTile(ii+i+150)->getTerrain(),
                                     data->tiley[1]+35);
                        }
                    }
                }
                else
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS],
                             data->stile[rr+i][YPOS]+35,75,15,
                             data->tilex[11],data->tiley[1]+35);
                }
            }
        }
        ii+=150;
    }

    ii=data->start;
    for(rr=0;rr<144;rr+=11)
    {
        for(i=0;i<10;i++)
        {
            if(map->getTile(ii+i)->getXPos() < map->GetWidth()-1  &&
               map->getTile(ii+i)->getYPos() < map->GetHeight()-1 )
            {
                if(map->getTile(ii+i+151)->getShrdstate(data->nationTurn)<2)
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS]+60,
                             data->stile[rr+i][YPOS]+35,15,15,
                             map->getTile(ii+i+151)->getTerrain()+60,
                             data->tiley[2]+35);

                    if(map->getTile(ii+i+151)->getShrdstate(data->nationTurn)==1)
                    {
                        if(map->getTile(ii+i+151)->Is(TILE_FAKE))
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS]+60,
                                     data->stile[rr+i][YPOS]+35,15,15,
                                     map->getTile(ii+i+151)->getFkterrain()+60,
                                     data->tiley[2]+35);
                        }
                        else
                        {
                            DrawTILE(screen,blender2,data->stile[rr+i][XPOS]+60,
                                     data->stile[rr+i][YPOS]+35,15,15,
                                     map->getTile(ii+i+151)->getTerrain()+60,
                                     data->tiley[2]+35);
                        }
                    }
                }
                else
                {
                    DrawTILE(screen,blender,data->stile[rr+i][XPOS]+60,
                             data->stile[rr+i][YPOS]+35,15,15,
                             data->tilex[11]+60,data->tiley[2]+35);
                }
            }
        }
        ii+=150;
    }
    data->red=255;data->green=0;
    SetTerrain3();
}

/*--------------------------SetTerrain3----------------------------*/
void GraphicsEngine::SetTerrain3(void)
{
  GlobalData* data = _GlobalData;
  Map* map = _Map;
  short x,y,rr,i,rowmax=14,colmax=11,pos;
  int icon;
  long ii;
//  short colnum,cName;
  string text;
  int renderW,renderH;    

    /* Place the plowed tile overlay*/
    rr=0;ii=data->start;
    for(y=0;y<rowmax;y++)
    {
        for(x=0;x<colmax;x++,rr++)
        {
            if(map->getTile(ii+x)->getShrdstate(data->nationTurn)<2)
            {                               
                if(map->getTile(ii+x)->Is(TILE_PLOWED))
                {
         /*if tile is at the top of the screen only copy part of the tile to 
           prevent overlap*/
                    if(rr<11)
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS],data->tw,data->th-3,
                                 data->tilex[11],data->tiley[0]+3);
                    }
                    else
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS]-3,data->tw,data->th,
                                 data->tilex[11],data->tiley[0]);
                    }
                }

    /*forests*/
                if(map->getTile(ii+x)->Is(TILE_FAKE))
                {
                    if(map->getTile(ii+x)->Is(TILE_FAKEFOREST))
                    {
                        Links1(ii+x,TILE_FAKEFOREST,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_FAKEPEAK))
                    {
                        Links1(ii+x,TILE_FAKEPEAK,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_FAKEMOUNTAIN))
                    {
                        Links1(ii+x,TILE_FAKEMOUNTAIN,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_FAKEHILL))
                    {
                        Links1(ii+x,TILE_FAKEHILL,rr);
                    }
                }
                else
                {
                    if(map->getTile(ii+x)->Is(TILE_FOREST))
                    {
                        Links1(ii+x,TILE_FOREST,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_PEAK))
                    {
                        Links1(ii+x,TILE_PEAK,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_MOUNTAIN))
                    {
                        Links1(ii+x,TILE_MOUNTAIN,rr);
                    }
                    if(map->getTile(ii+x)->Is(TILE_HILL))
                    {
                        Links1(ii+x,TILE_HILL,rr);
                    }
                }

                //rivers
                if(map->getTile(ii+x)->Is(TILE_RIVER))
                {
                    Links1(ii+x,TILE_RIVER,rr);
                }
            }

            //Real and fake rumors
            if(map->getTile(ii+x)->Is(TILE_RUMOR)&&
               map->getTile(ii+x)->getShrdstate(data->nationTurn)==0)
            {
                DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                         data->stile[rr][YPOS]-2,data->tw,data->th,
                         TERRAIN_RUMOR,data->tiley[1]);
            }

            if(map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
            {
                if(map->getTile(ii+x)->Is(TILE_RUMOR) &&
                !map->getTile(ii+x)->Is(TILE_FAKE))
                {
                    DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                             data->stile[rr][YPOS]-2,data->tw,data->th,
                             TERRAIN_RUMOR,data->tiley[1]);
                    DrawTILE(screen,mask1,data->stile[rr][XPOS]-3,
                             data->stile[rr][YPOS]-2,data->tw,data->th,
                             TERRAIN_RUMOR,data->tiley[1]);
                }
                 
                if(map->getTile(ii+x)->Is(TILE_FAKE))
                {
                    if(map->getTile(ii+x)->Is(TILE_FAKERUMOR))
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS]-2,data->tw,data->th,
                                 TERRAIN_RUMOR,data->tiley[1]);
                        DrawTILE(screen,mask1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS]-2,data->tw,data->th,
                                 TERRAIN_RUMOR,data->tiley[1]);
                    }
                }
            }
        }
        ii+=150;  
    }

    //Place the Colonies, roads and the grid on the map
    rr=0;ii=data->start;
    for(y=0;y<rowmax;y++)
    {
        for(x=0;x<colmax;x++,rr++)
        {
            if(map->getTile(ii+x)->getShrdstate(data->nationTurn)<2)
            {            
                //roads
                if(map->getTile(ii+x)->Is(TILE_ROAD))
                {
                    //dont draw the road if there is no connection and
                    //the tile contains a village
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,ANY_DIR)==false)
                    {
                        if(map->getTile(ii+x)->getVillages()==0)
                        {
                            DrawRoad(rr,0,ii+x);
                        }
                    }
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,NE))
                    {DrawRoad(rr,1,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,E))
                    {DrawRoad(rr,2,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,SE))
                    {DrawRoad(rr,3,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,S))
                    {DrawRoad(rr,4,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,SW))
                    {DrawRoad(rr,5,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,W))
                    {DrawRoad(rr,6,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,NW))
                    {DrawRoad(rr,7,ii+x);}
                    if(map->getTile(ii+x)->hasLink(TILE_ROAD,N))
                    {DrawRoad(rr,8,ii+x);}
                }

                // Place the grid on the map
                if(data->grid==1)
                {
                    DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                             data->stile[rr][YPOS],data->tw,data->th,
                             data->tilex[9],data->tiley[3]);
                }

                //Colonies
                if(map->getTile(ii + x)->Is(TILE_BUILD))
                {
                    Colony *col = FindColonyAt(ii + x);
                    if(rr < 11)
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS],data->tw,data->th-6,
                                 data->tilex[8],data->tiley[1]+6);
                                 
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS],data->tw,data->th-21,
                                 data->tilex[5 + col->getNation()], data->tiley[2] + 21);
                    }
                    else
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS]-6,data->tw,data->th,
                                 data->tilex[8],data->tiley[1]);

                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-3,
                                 data->stile[rr][YPOS] - 21,data->tw,data->th,
                                 data->tilex[5 + col->getNation()], data->tiley[2]);
                    }
                }
                if(map->getTile(ii+x)->getVillages()>0&&
                   (!(map->getTile(ii+x)->Is(TILE_FAKE))))
                {
                    if(rr<11)
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                                 data->stile[rr][YPOS],data->tw,data->th-2,
                                 data->tilex[map->getTile(ii+x)->getVillages()-1],
                                 data->tiley[2]+2);
                    }
                    else
                    {
                        DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                                 data->stile[rr][YPOS]-2,data->tw,data->th,
                                 data->tilex[map->getTile(ii+x)->getVillages()-1],
                                 data->tiley[2]);
                    }

                    if(map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
                    {
                        if(rr<11)
                        {
                            DrawTILE(screen,mask1,data->stile[rr][XPOS],
                                     data->stile[rr][YPOS],data->tw,data->th-2,
                                     data->tilex[map->getTile(ii+x)->getVillages()-1],
                                     data->tiley[2]+2);
                        }
                        else
                        {
                            DrawTILE(screen,mask1,data->stile[rr][XPOS],
                                     data->stile[rr][YPOS]-2,data->tw,data->th,
                                     data->tilex[map->getTile(ii+x)->getVillages()-1],
                                     data->tiley[2]);
                        }
                    }                           
                }
            }
        }
        ii+=150;  
    }

//added 6/2
/* Place the Colony Names on the map*/

    rr = 0; ii = data->start;
    for(y = 0; y < rowmax; y++)
    {
      for(x = 0; x < colmax; x++)
      {
        Tile *tile = map->getTile(ii+x);
        
        if(tile->Is(TILE_BUILD) && tile->getShrdstate(data->nationTurn) != SHROUD_FULL)
        {
          char *colName = (char *)FindColonyAt(ii + x)->getName().c_str();

          TTF_SizeText(fontColNameMap->font,(char *)text.c_str(),&renderW,&renderH);

          if(renderW>data->tw && rr%11>8)
          {
            if(rr<142)
            {
              drawString(screen,fontColNameMap,
                    (data->stile[rr][XPOS]+data->tw)-(renderW+5),
                    data->stile[rr][YPOS]+40,true, colName);
            }
            else
            {
              drawString(screen,fontColNameMap,
                    (data->stile[rr][XPOS]+data->tw)-(renderW+5),
                    data->stile[rr-11][YPOS]+20,true, colName);
            }
          }
          else
          {
            if(rr<142)
            {
              drawString(screen,fontColNameMap,data->stile[rr][XPOS],
                    data->stile[rr][YPOS]+40,true, colName);
            }
            else
            {
              drawString(screen,fontColNameMap,data->stile[rr][XPOS],
                    data->stile[rr-11][YPOS]+20,true, colName);
            }
          }
        }
        rr++;
      }
      ii+=150;
    }

    /* Place the Units on the map*/
//added 6/2
//puts natives and nationality boxs on map

    rr=0;ii=data->start;
    for(y=0;y<rowmax;y++)
    {
      for(x=0;x<colmax;x++)
      {
        if(map->getTile(ii+x)->getShrdstate(data->nationTurn)<2)
        {
            
          if(data->nativeOnTile[ii+x]>0)
          {
            if(data->mapnum==ii+x && data->turn == data->unitList.size())
            ;
            else
            {
              if(rr<11)
              {
                NationBox(data->stile[rr][XPOS], data->stile[rr][YPOS],
                 NATION_TRIBE, 3, ORD_NONE);
                DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                      data->stile[rr][YPOS],
                      data->tw,data->th-data->yextra-5,data->tilex[4],
                      data->tiley[2]+data->yextra+5);
                       
                if(map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
                {
                  NationBox(data->stile[rr][XPOS], data->stile[rr][YPOS], 99, 3,
                   ORD_NONE);
                  DrawTILE(screen,mask1,data->stile[rr][XPOS],
                        data->stile[rr][YPOS],
                        data->tw,data->th-data->yextra-5,data->tilex[4],
                        data->tiley[2]+data->yextra+5);
                }
              }
              else
              {
                NationBox(data->stile[rr][XPOS],
                 data->stile[rr][YPOS]-data->yextra - 5, NATION_TRIBE, 3, ORD_NONE);
                DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                      data->stile[rr][YPOS]-data->yextra-5,
                      data->tw,data->th,data->tilex[4],data->tiley[2]);
                       
                if(map->getTile(ii+x)->getShrdstate(data->nationTurn)==1)
                {
                  NationBox(data->stile[rr][XPOS],
                        data->stile[rr][YPOS]-data->yextra - 5, 99, 3, ORD_NONE);
                  DrawTILE(screen,mask1,data->stile[rr][XPOS],
                        data->stile[rr][YPOS]-data->yextra-5,
                        data->tw,data->th,data->tilex[4],data->tiley[2]);
                }
              }
            }
          }
            
          for(i = 0;i < data->unitList.size();i++)
          {
            if(!(data->unitList[i]->isBoat()) &&
             data->unitList[i]->isOnboard())
            continue;
            else
            {
              if(data->unitList[i]->getTile() == ii + x && data->turn != i)
              {
                if(data->unitList[i]->isBoat())
                 pos = 1;
                else
                 pos = 2;
                icon = data->unitList[i]->getGraphic();
                
                if(rr<11)
                {
                  NationBox(data->stile[rr][XPOS],
                        data->stile[rr][YPOS], data->unitList[i]->getNation(), pos,
                        data->unitList[i]->getOrders());
                  DrawTILE(screen, uniticons, data->stile[rr][XPOS],
                        data->stile[rr][YPOS],data->tw,
                        data->th-data->yextra-5,
                        data->tile50[icon][0], data->tile50[icon][1]);
                }
                else
                {
                  NationBox(data->stile[rr][XPOS],
                        data->stile[rr][YPOS]-data->yextra-5,
                        data->unitList[i]->getNation(), pos,
                        data->unitList[i]->getOrders());       
                  DrawTILE(screen, uniticons, data->stile[rr][XPOS],
                        data->stile[rr][YPOS]-data->yextra-5,
                        data->tw,data->th,
                        data->tile50[icon][0], data->tile50[icon][1]);
                }
              }
            }
          }
        }
        rr++;
      }
      ii+=150;  
    }
}

/*--------------------------DrawRoad----------------------------*/
void GraphicsEngine::DrawRoad(int rr,int x,long num)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    if(!(map->getTile(num)->Is(TILE_FAKE)))
    {
        if(rr<11)
        {
            DrawTILE(screen,tilesheet1,data->stile[rr][XPOS],
                     data->stile[rr][YPOS],
                     data->tw,data->th-6,data->tilex[x],data->tiley[3]+6);
        }
        else
        {
            DrawTILE(screen,tilesheet1,data->stile[rr][XPOS]-6,
                     data->stile[rr][YPOS]-6,
                     data->tw,data->th,data->tilex[x],data->tiley[3]);
        }
        if(map->getTile(num)->getShrdstate(data->nationTurn)==1)
        {
            if(rr<11)
            {
                DrawTILE(screen,mask1,data->stile[rr][XPOS],
                         data->stile[rr][YPOS],
                         data->tw,data->th-6,data->tilex[x],data->tiley[3]+6);
            }
            else
            {
                DrawTILE(screen,mask1,data->stile[rr][XPOS]-6,
                         data->stile[rr][YPOS]-6,
                         data->tw,data->th,data->tilex[x],data->tiley[3]);
            }
        }
    }
}

/*--------------------------Links1-------------------------------*/
//void GraphicsEngine::Links1(long ii,int e,int sn)
void GraphicsEngine::Links1(long ii,enum tileTypes e,int sn)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;

/*  This function can be used to place those overlays that have
    'connections' (other than the roads)
    'e' is the element of the maptiles array that holds the 
    information for that paricular overlay (Forests, Hills, etc.)
    Since the partial shroud is already on the tile, a mask is used
    that only places a partial shroud on the part of the overlay
    that is visible  (That is a forest mask is a semi-transparent 
    tile that only covers the forest shape of the tile.  The rest 
    of the tile is the 'magic' color 255,0,255)
*/

    Uint8 xx=0,yy=0;
    int xpos = map->getTile(ii)->getXPos();
    int ypos = map->getTile(ii)->getYPos();
    
    if(e!=TILE_ROAD)
    {
        if(map->getTileAt(xpos+1,ypos)->getShrdstate(data->nationTurn)==1)
        {
            if(map->getTileAt(xpos+1,ypos)->Is(TILE_FAKE))
            {
                if(map->getTile(ii)->hasFakeLink(e,E)) xx+=BIT1;
            }
            else if(map->getTile(ii)->hasRealLink(e,E)) xx+=BIT1;
        }
        else if(map->getTileAt(xpos+1,ypos)->getShrdstate(data->nationTurn)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,E)) xx+=BIT1;
        }

        if(map->getTileAt(xpos,ypos+1)->getShrdstate(data->nationTurn)==1)
        {
            if(map->getTileAt(xpos,ypos+1)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,S)) xx+=BIT2;
            }
            else if(map->getTile(ii)->hasRealLink(e,S)) xx+=BIT2;
        }
        else if(map->getTileAt(xpos,ypos+1)->getShrdstate(data->nationTurn)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,S)) xx+=BIT2;
        }

        if(map->getTileAt(xpos-1,ypos)->getShrdstate(data->nationTurn)==1)
        {
            if(map->getTileAt(xpos-1,ypos)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,W)) xx+=BIT3;
            }
            else if(map->getTile(ii)->hasRealLink(e,W)) xx+=BIT3;
        }
        else if(map->getTileAt(xpos-1,ypos)->getShrdstate(data->nationTurn)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,W)) xx+=BIT3;
        }

        if(map->getTileAt(xpos,ypos-1)->getShrdstate(data->nationTurn)==1)
        {
            if(map->getTileAt(xpos,ypos-1)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,N)) xx+=BIT4;
            }
            else if(map->getTile(ii)->hasRealLink(e,N)) xx+=BIT4;
        }
        else if(map->getTileAt(xpos,ypos-1)->getShrdstate(data->nationTurn)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,N)) xx+=BIT4;
        }

        switch (xx)
        {
        case 0 : xx=0 ;break;  //none
        case 1 : xx=1 ;break;  //e
        case 2 : xx=2 ;break;  //s
        case 4 : xx=3 ;break;  //w
        case 8 : xx=4 ;break;  //n
        case 3 : xx=5 ;break;  //e+s
        case 5 : xx=6 ;break;  //e+w
        case 9 : xx=7 ;break;  //e+n
        case 6 : xx=8 ;break;  //s+w
        case 10: xx=9 ;break;  //s+n
        case 12: xx=10;break;  //w+n
        case 11: xx=11;break;  //e+s+n
        case 14: xx=12;break;  //w+s+n
        case 7 : xx=13;break;  //e+s+w
        case 13: xx=14;break;  //e+n+w
        default: break;        //e+s+w+n
        }
    }

    switch(e)
    {
    case TILE_FOREST:
        {
            switch(map->getTile(ii)->getTerrain())
            {
                case TERRAIN_OPENS:    case TERRAIN_STEPPE: yy=1; break;
                case TERRAIN_SAVANNAH: case TERRAIN_PRAIRIE: yy=2; break;
                case TERRAIN_DESERT:   case TERRAIN_CHAPARRAL: yy=3; break;
                default: yy=0; break;
            }

            //actually draw the tile
            if(sn==0)
            {
                DrawTILE(screen,tilesheetF,data->stile[sn][XPOS],
                         data->stile[sn][YPOS],data->tw-6,44,
                         data->tilex[xx]+6,data->tiley2[yy]+21);
                if(map->getTile(ii)->Is(TILE_RAIN))
                {
                    DrawTILE(screen,tilesheet1,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,data->th-6,
                             data->tilex[11]+6,data->tiley[1]+6);
                }
                if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                {
                    DrawTILE(screen,forestmask,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,44,
                             data->tilex[xx]+6,data->tiley2[yy]+21);
                    if(map->getTile(ii)->Is(TILE_RAIN))
                    {
                        DrawTILE(screen,mask1,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS],data->tw-6,data->th-6,
                                 data->tilex[11]+6,data->tiley[1]+6);
                    }
                }
            }
            else
            {
                if(sn>0&&sn<11)
                {
                    DrawTILE(screen,tilesheetF,data->stile[sn][XPOS]-6,
                             data->stile[sn][YPOS],data->tw,44,
                             data->tilex[xx],data->tiley2[yy]+21);
                    if(map->getTile(ii)->Is(TILE_RAIN))
                    {
                        DrawTILE(screen,tilesheet1,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,data->th-6,
                                 data->tilex[11],data->tiley[1]+6);
                    }
                    if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                    {
                        DrawTILE(screen,forestmask,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,44,
                                 data->tilex[xx],data->tiley2[yy]+21);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,mask1,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS],data->tw,
                                     data->th-6,data->tilex[11],data->tiley[1]+6);
                        }
                    }
                }
                else
                {
                    if(sn>10&&sn%11==0)
                    {
                        DrawTILE(screen,tilesheetF,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                 data->tilex[xx]+6,data->tiley2[yy]);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,tilesheet1,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-6,data->tw-6,
                                     data->th,data->tilex[11]+6,data->tiley[1]);
                        }
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,forestmask,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                     data->tilex[xx]+6,data->tiley2[yy]);
                            if(map->getTile(ii)->Is(TILE_RAIN))
                            {
                                DrawTILE(screen,mask1,data->stile[sn][XPOS],
                                         data->stile[sn][YPOS]-6,data->tw-6,data->th,
                                         data->tilex[11]+6,data->tiley[1]);
                            }
                        }
                    }
                    else
                    {       
                        DrawTILE(screen,tilesheetF,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS]-15-6,data->tw,65,
                                 data->tilex[xx],data->tiley2[yy]);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,tilesheet1,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-6,data->tw,data->th,
                                     data->tilex[11],data->tiley[1]);
                        }
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,forestmask,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-15-6,data->tw,65,
                                     data->tilex[xx],data->tiley2[yy]);
                            if(map->getTile(ii)->Is(TILE_RAIN))
                            {
                                DrawTILE(screen,mask1,data->stile[sn][XPOS]-6,
                                         data->stile[sn][YPOS]-6,data->tw,data->th,
                                         data->tilex[11],data->tiley[1]);
                            }
                        }
                    }
                }    
            }
            break;
        }

    case TILE_FAKEFOREST:
        {
            switch(map->getTile(ii)->getFkterrain())
            {
            case TERRAIN_OPENS:    case TERRAIN_STEPPE: yy=1; break;
            case TERRAIN_SAVANNAH: case TERRAIN_PRAIRIE: yy=2; break;
            case TERRAIN_DESERT:   case TERRAIN_CHAPARRAL: yy=3; break;
            default: yy=0; break;
            }

            //actually draw the tile
            if(sn==0)
            {
                DrawTILE(screen,tilesheetF,data->stile[sn][XPOS],
                         data->stile[sn][YPOS],data->tw-6,44,
                         data->tilex[xx]+6,data->tiley2[yy]+21);
                if(map->getTile(ii)->Is(TILE_RAIN))
                {
                    DrawTILE(screen,tilesheet1,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,data->th-6,
                             data->tilex[11]+6,data->tiley[1]+6);
                }
                if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                {
                    DrawTILE(screen,forestmask,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,44,
                             data->tilex[xx]+6,data->tiley2[yy]+21);
                    if(map->getTile(ii)->Is(TILE_RAIN))
                    {
                        DrawTILE(screen,mask1,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS],data->tw-6,data->th-6,
                                 data->tilex[11]+6,data->tiley[1]+6);
                    }
                }
            }
            else
            {
                if(sn>0&&sn<11)
                {
                    DrawTILE(screen,tilesheetF,data->stile[sn][XPOS]-6,
                             data->stile[sn][YPOS],data->tw,44,
                             data->tilex[xx],data->tiley2[yy]+21);
                    if(map->getTile(ii)->Is(TILE_RAIN))
                    {
                        DrawTILE(screen,tilesheet1,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,data->th-6,
                                 data->tilex[11],data->tiley[1]+6);
                    }
                    if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                    {
                        DrawTILE(screen,forestmask,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,44,
                                 data->tilex[xx],data->tiley2[yy]+21);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,mask1,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS],data->tw,
                                     data->th-6,data->tilex[11],data->tiley[1]+6);
                        }
                    }
                }
                else
                {
                    if(sn>10&&sn%11==0)
                    {
                        DrawTILE(screen,tilesheetF,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                 data->tilex[xx]+6,data->tiley2[yy]);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,tilesheet1,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-6,data->tw-6,
                                     data->th,data->tilex[11]+6,data->tiley[1]);
                        }
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,forestmask,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                     data->tilex[xx]+6,data->tiley2[yy]);
                            if(map->getTile(ii)->Is(TILE_RAIN))
                            {
                                DrawTILE(screen,mask1,data->stile[sn][XPOS],
                                         data->stile[sn][YPOS]-6,data->tw-6,data->th,
                                         data->tilex[11]+6,data->tiley[1]);
                            }
                        }
                    }
                    else
                    {       
                        DrawTILE(screen,tilesheetF,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS]-15-6,data->tw,65,
                                 data->tilex[xx],data->tiley2[yy]);
                        if(map->getTile(ii)->Is(TILE_RAIN))
                        {
                            DrawTILE(screen,tilesheet1,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-6,data->tw,data->th,
                                     data->tilex[11],data->tiley[1]);
                        }
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,forestmask,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-15-6,data->tw,65,
                                     data->tilex[xx],data->tiley2[yy]);
                            if(map->getTile(ii)->Is(TILE_RAIN))
                            {
                                DrawTILE(screen,mask1,data->stile[sn][XPOS]-6,
                                         data->stile[sn][YPOS]-6,data->tw,data->th,
                                         data->tilex[11],data->tiley[1]);
                            }
                        }
                    }
                }    
            }
            break;
        }

    case TILE_MOUNTAIN: case TILE_HILL: case TILE_PEAK:
        {
/* 
    Since the partial shroud is already on the tile, a mask is used
    that only places a partial shroud on the part of the overlay
    that is visible  (That is a mountain mask is a semi-transparent 
    tile that only covers the mountain shape of the tile.  The rest 
    of the tile is the 'magic' color 255,0,255)
*/

            if(e==TILE_HILL)     yy=0;
            if(e==TILE_MOUNTAIN) yy=1;
            if(e==TILE_PEAK)     yy=2;

            /*check for overlaps at top and left of screen*/
            if(sn==0)
            {
                DrawTILE(screen,tilesheetM,data->stile[sn][XPOS],
                         data->stile[sn][YPOS],data->tw-6,44,
                         data->tilex[xx]+6,data->tiley2[yy]+21);
                if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                {
                    DrawTILE(screen,Mmask,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,44,
                             data->tilex[xx]+6,data->tiley2[yy]+21);
                }
            }
            else
            {
                if(sn>0&&sn<11)
                {
                    DrawTILE(screen,tilesheetM,data->stile[sn][XPOS]-6,
                             data->stile[sn][YPOS],data->tw,44,
                             data->tilex[xx],data->tiley2[yy]+21);
                    if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                    {
                        DrawTILE(screen,Mmask,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,44,
                                 data->tilex[xx],data->tiley2[yy]+21);
                    }
                }
                else
                {
                    if(sn>10&&sn%11==0)
                    {
                        DrawTILE(screen,tilesheetM,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                 data->tilex[xx]+6,data->tiley2[yy]);
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,Mmask,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                     data->tilex[xx]+6,data->tiley2[yy]);
                        }
                    }
                    else
                    {
                        DrawTILE(screen,tilesheetM,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS]-15-6,data->tw,65,
                                 data->tilex[xx],data->tiley2[yy]);
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,Mmask,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-15-6,data->tw,65,
                                     data->tilex[xx],data->tiley2[yy]);
                        }
                    }
                }
            }
            break;
        }

    case TILE_RIVER:
        {
            /*check for overlaps at top and left of screen*/
            if(sn==0)
            {
                DrawTILE(screen,tilesheetR,data->stile[sn][XPOS],
                         data->stile[sn][YPOS],data->tw-6,44,
                         data->tilex[xx]+6,data->tiley2[yy]+21);
                if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                {
                    DrawTILE(screen,Rmask,data->stile[sn][XPOS],
                             data->stile[sn][YPOS],data->tw-6,44,
                             data->tilex[xx]+6,data->tiley2[yy]+21);
                }
            }
            else
            {
                if(sn>0&&sn<11)
                {
                    DrawTILE(screen,tilesheetR,data->stile[sn][XPOS]-6,
                             data->stile[sn][YPOS],data->tw,44,
                             data->tilex[xx],data->tiley2[yy]+21);
                    if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                    {
                        DrawTILE(screen,Rmask,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS],data->tw,44,
                                 data->tilex[xx],data->tiley2[yy]+21);
                    }
                }
                else
                {
                    if(sn>10&&sn%11==0)
                    {
                        DrawTILE(screen,tilesheetR,data->stile[sn][XPOS],
                                 data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                 data->tilex[xx]+6,data->tiley2[yy]);
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,Rmask,data->stile[sn][XPOS],
                                     data->stile[sn][YPOS]-15-6,data->tw-6,65,
                                     data->tilex[xx]+6,data->tiley2[yy]);
                        }
                    }
                    else
                    {
                        DrawTILE(screen,tilesheetR,data->stile[sn][XPOS]-6,
                                 data->stile[sn][YPOS]-15-6,data->tw,65,
                                 data->tilex[xx],data->tiley2[yy]);
                        if(map->getTile(ii)->getShrdstate(data->nationTurn)==1)
                        {
                            DrawTILE(screen,Rmask,data->stile[sn][XPOS]-6,
                                     data->stile[sn][YPOS]-15-6,data->tw,65,
                                     data->tilex[xx],data->tiley2[yy]);
                        }
                    }
                }
            }
            break;
        }
    default: break;
    }
}

/*--------------------------Rivers1-----------------------------*/
Uint8 GraphicsEngine::Rivers1(long ii)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    Uint8 riverLinks=0;

/*Sets the 'connections' for River*/
    if(map->getTile(ii)->getXPos()<149)
    {
        if(map->getTile(ii+1)->Is(TILE_RIVER)||
           map->getTile(ii+1)->Is(TILE_WATER))
        {
            //riverLinks|=data->E;
        }
    }

    if(map->getTile(ii)->getYPos()<199)
    {
        if(map->getTile(ii+150)->Is(TILE_RIVER)||
           map->getTile(ii+150)->Is(TILE_WATER))
        {
            //riverLinks|=data->S;
        }
    }
           
    if(map->getTile(ii)->getXPos()>0)
    {
        if(map->getTile(ii-1)->Is(TILE_RIVER)||
           map->getTile(ii-1)->Is(TILE_WATER))
        {
           //riverLinks|=data->W;
        }
    }

    if(map->getTile(ii)->getYPos()>0)
    {
        if(map->getTile(ii-150)->Is(TILE_RIVER)||
           map->getTile(ii-150)->Is(TILE_WATER))
        {
            //riverLinks|=data->N;
        }
    }
    return riverLinks;
}

//
// $Id: terrain1.cpp,v 1.18 2004/06/23 15:37:05 sikon Exp $
//

