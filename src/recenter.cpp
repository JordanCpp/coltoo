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

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"

/*---------------------------ReCenter-----------------------------*/
void GraphicsEngine::ReCenter(void)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();

/*Recenters the unit with checks to see if the map edge or corners 
  have been reached.*/
  data->scrnum=71;data->start=data->mapnum-905;

/*If the unit is within 5 rows of the North or South map edge the 
  number of rows between it and the START tile is set. 
  (150 tiles/row)*/

  if((map->getTile(data->mapnum)->getYPos()<6)||
     (map->getTile(data->mapnum)->getYPos()>data->rows-8))
  {
    switch(map->getTile(data->mapnum)->getYPos())
    {
      case(193):{data->scrnum=82;data->start=data->mapnum-1055;break;}
      case(194):{data->scrnum=93;data->start=data->mapnum-1205;break;}   
      case(195):{data->scrnum=104;data->start=data->mapnum-1355;break;}
      case(196):{data->scrnum=115;data->start=data->mapnum-1505;break;}
      case(197):{data->scrnum=126;data->start=data->mapnum-1655;break;}
      case(198):{data->scrnum=137;data->start=data->mapnum-1805;break;}
      case(199):{data->scrnum=148;data->start=data->mapnum-1955;break;}
   
      case(5):{data->scrnum=60;data->start=data->mapnum-755;break;}   
      case(4):{data->scrnum=49;data->start=data->mapnum-605;break;}
      case(3):{data->scrnum=38;data->start=data->mapnum-455;break;}
      case(2):{data->scrnum=27;data->start=data->mapnum-305;break;}
      case(1):{data->scrnum=16;data->start=data->mapnum-155;break;}
   
      default:{data->scrnum=5;data->start=data->mapnum-5;}
    }
  }   

/*If the unit is within 5 tiles of the West edge, or 4 tiles of the
  East edge, the number of columns from the START tile is set.*/   
  if((map->getTile(data->mapnum)->getXPos()<5)||
     (map->getTile(data->mapnum)->getXPos()>data->cols-6))
  {
    switch(map->getTile(data->mapnum)->getXPos())
    {
      case(145):{data->scrnum+=1;data->start=data->mapnum-906;break;}
      case(146):{data->scrnum+=2;data->start=data->mapnum-907;break;}
      case(147):{data->scrnum+=3;data->start=data->mapnum-908;break;}
      case(148):{data->scrnum+=4;data->start=data->mapnum-909;break;}   
      case(149):{data->scrnum+=5;data->start=data->mapnum-910;break;}

      case(4):{data->scrnum-=1;data->start=data->mapnum-904;break;}
      case(3):{data->scrnum-=2;data->start=data->mapnum-903;break;}
      case(2):{data->scrnum-=3;data->start=data->mapnum-902;break;}
      case(1):{data->scrnum-=4;data->start=data->mapnum-901;break;}
      default:{data->scrnum-=5;data->start=data->mapnum-900;}
    }
  }

/*If the unit is in one of the 4 corners, the distance from the 
  START tile is set.*/
  if((map->getTile(data->mapnum)->getXPos()<5)&&
     (map->getTile(data->mapnum)->getYPos()<6))
  {
      data->start=data->mapnum-((int(data->scrnum/11)*data->cols)+
                                (map->getTile(data->mapnum)->getXPos()));
  }
  if((map->getTile(data->mapnum)->getXPos()<5)&&
     (map->getTile(data->mapnum)->getYPos()>data->rows-8))
  {
      data->start=data->mapnum-((int(data->scrnum/11)*data->cols)+
                                 map->getTile(data->mapnum)->getXPos());
  }
  if((map->getTile(data->mapnum)->getXPos()>data->cols-6)&&
     (map->getTile(data->mapnum)->getYPos()<5))
  {
      data->start=data->cols-11;
  }
  if((map->getTile(data->mapnum)->getXPos()>data->cols-7)&&
     (map->getTile(data->mapnum)->getYPos()>data->rows-8))
  {
      data->start=data->mapmax-1960;
  }

  data->flag|=data->ReCenFlag;
}

/*---------------------------ReCenter-----------------------------*/
void GraphicsEngine::ReCenter(int x, int y)
{
  GlobalData* data = m_pGame->GetData();
  Map* map = m_pGame->GetMap();

  //update the start tile, checking map borders.
  if(x < 0 || x >= map->GetWidth() || y<0 || y>= map->GetHeight())
    cout << "Recenter Error: indices out of range\n";
  else
  {
    int coordX = x - GetScreenWidth()/2;
    if(coordX < 0)
    {
      startX = 0;
    }
    else if(coordX > map->GetWidth()- GetScreenWidth())
         {
           startX = map->GetWidth()-GetScreenWidth();
         }
         else startX = coordX;

    int coordY = y - GetScreenHeight()/2;
    if(coordY < 0)
    {
      startY = 0;
    }
    else if(coordY > map->GetHeight()- GetScreenHeight())
         {
           startY = map->GetHeight()-GetScreenHeight();
         }
         else startY = coordY;

    data->flag&=~data->ReCenFlag;
  }
}

//
// $Id: recenter.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

