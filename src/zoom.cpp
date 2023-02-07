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

/*---------------------------Zoom1-------------------------------*/
void GraphicsEngine::Zoom1(void)
{
    GlobalData* data = m_pGame->GetData();

    if(!data->zl)
    {
        DrawTILE(map1,screen,0,0,836,708,0,20);
        DrawTILE(screen,mapback,0,20,836,708,0,0);
        Border(screen,362,184,299,399);
        MiniMap();
        data->zl = 1;
    }
    else
    {
        DrawTILE(screen,map1,0,20,836,708,0,0);
        data->zl = 0;
    }
    UpdateScreen0();   
}

/*---------------------------MiniMap------------------------------*/
void GraphicsEngine::MiniMap(void)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();

    int x,y,k,x0,y0,x2,y2,step,xoffset,yoffset,s;
    long i,mapold;
    Uint8 r,g,b;

    x0=362;y0=184;x2=662;y2=584;step=2;

    Slock(screen);
  
    i=0;
    for(y=y0;y<y2;y+=step)
    {
        for(x=x0;x<x2;x+=step)
        {
            k=map->getTile(i)->getTerrain();
            s=map->getTile(i)->getShrdstate(data->nationTurn);

            switch (k)
            {
                case (TERRAIN_OCEAN):
                {
                    r=0;g=64;b=190;
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=0;g=32;b=95;}
                    break;
                }
                case (TERRAIN_HIGHSEAS):                    //added 5/23
                {
                    r=16;g=96;b=160;
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=8;g=64;b=95;}
                    break;
                }                
                case (TERRAIN_ARCTIC):
                {
                    r=255;g=255;b=255;
                    if(map->getTile(i)->Is(TILE_WATER)&&
                       map->getTile(i)->Is(TILE_RIVER))
                    {
                        r=192;g=192;b=255;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=128;g=128;b=128;}
                    break;
                }
                case (TERRAIN_TUNDRA):
                {
                    r=96;g=160;b=176;
                    if(map->getTile(i)->Is(TILE_FOREST))
                    {
                        r=64;g=128;b=144;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=48;g=80;b=88;}
                    break;
                }
                case (TERRAIN_PRAIRIE):
                {
                    r=160;g=160;b=80;
                    if(map->getTile(i)->Is(TILE_FOREST))
                    {
                        r=120;g=120;b=60;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=80;g=80;b=40;}
                    break;
                }
                case (TERRAIN_GRASS):
                {
                    r=96;g=196;b=32;
                    if(map->getTile(i)->Is(TILE_FOREST))
                    {
                        r=64;g=128;b=24;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=48;g=98;b=16;}
                    break;
                }
                case (TERRAIN_SAVANNAH):
                {
                    r=96;g=192;b=128;
                    if(map->getTile(i)->Is(TILE_FOREST))
                      {r=64;g=160;b=96;}
                    if(map->getTile(i)->Is(TILE_FOREST) &&
                       map->getTile(i)->Is(TILE_RAIN))
                    {
                        r=64;g=160;b=128;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=48;g=96;b=64;}
                    break;
                }
                case (TERRAIN_DESERT):
                {
                    r=180;g=160;b=104;
                    if(map->getTile(i)->Is(TILE_FOREST))
                    {
                        r=120;g=130;b=60;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=90;g=80;b=52;}
                    break;
                }
                case (TERRAIN_STEPPE):
                {
                    r=80;g=150;b=110;
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=40;g=75;b=55;}
                    break;
                }
                case (TERRAIN_OPENS):
                {
                    r=120;g=140;b=100;
                    if(map->getTile(i)->Is(TILE_FOREST))
                    {
                        r=100;g=120;b=80;
                    }
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=60;g=70;b=50;}
                    break;
                }        
                case (TERRAIN_CHAPARRAL):
                {
                    r=120;g=100;b=60;
                    if(s==2){r=0;g=0;b=0;}
                    if(s==1){r=60;g=50;b=30;}
                }
                default: break;
            }

            if(map->getTile(i)->Is(TILE_RIVER))
            {
                r=64;g=128;b=196;
                if(s==2){r=0;g=0;b=0;}
                if(s==1){r=32;g=64;b=98;}
            }

            FillRect(screen,x,y,2,2,r,g,b);
            i++;
        }
    }

/*    xoffset=2*(map->getTile(data->mapnum)->getXPos());
    yoffset=2*(map->getTile(data->mapnum)->getYPos());
    FillRect(screen,x0+xoffset-1,y0+yoffset-1,3,3,255,255,0);

    if(data->turn==0){i=1;}else{i=0;}
    mapold=data->mapnum;
    data->mapnum = data->unitList[i]->getTile();
    xoffset=2*(map->getTile(data->mapnum)->getXPos());
    yoffset=2*(map->getTile(data->mapnum)->getYPos());
    FillRect(screen,x0+xoffset-1,y0+yoffset-1,3,3,255,0,0);
    data->mapnum=mapold; */
    for(i = 0; i < data->unitList.size(); i++)
    {
        if(data->unitList[i]->isOnboard()) continue;
        mapold = data->unitList[i]->getTile();
        //added 18/6; check if unit is shrouded
        if(data->unitList[i]->getNation()!=data->nationTurn)
        {
            if(map->getTile(mapold)->getShrdstate(data->nationTurn)==2) continue;
            int k = (rand()%5);
            //added 18/6; 1 in 5 of seeing a partial shrouded unit
            if((k!=1)&&(map->getTile(mapold)->getShrdstate(data->nationTurn)==1)) continue;
        }
        xoffset = 2 * (map->getTile(mapold)->getXPos());
        yoffset = 2 * (map->getTile(mapold)->getYPos());
        r = data->playerlist[data->unitList[i]->getNation()]->Color->Red();
        g = data->playerlist[data->unitList[i]->getNation()]->Color->Green();
        b = data->playerlist[data->unitList[i]->getNation()]->Color->Blue();
        if(i == data->turn)
            FillRect(screen, x0 + xoffset - 1, y0 + yoffset - 1, 3 ,3, 200, 200, 0);
        else
            FillRect(screen, x0 + xoffset - 1, y0 + yoffset - 1, 3 ,3, r, g, b);
    }

    Sulock(screen);
}

//
// $Id: zoom.cpp,v 1.10 2004/06/23 15:37:05 sikon Exp $
//

