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
#include <SDL2/SDL.h>
#include <iostream>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"
#include "unit.h"
#include "CTileType.h"

/*---------------------------DrawScene----------------------------*/

void GraphicsEngine::DrawScene(void)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();

    int dx,dy,steps=25,i,x,y,x1,y1;
    long mapnumold;
    short box=0,pos;
    int icon = data->unitList[data->turn]->getGraphic();
    
    /*Replaces image of unit with stored background image*/    
    DrawSURF(screen,bck1,data->stile[data->oldloc][0],
             data->stile[data->oldloc][1]-data->yextra-5);

    /*Checks to see if the unit moved*/  
    if(data->flag&data->NoMoveFlag){data->flag&=~data->NoMoveFlag;}    
    else 
    {
        //added 20/6
        #ifdef DEBUG
        cout<<"Unit "<<data->unitList[data->turn]->getName()<<" ";
        #endif
        Tile *t = map->getTile(data->unitList[data->turn]->getTile());
        #ifdef DEBUG
        cout<<"is on terrain "<<t->getTerrain()<<" ";
        #endif
        CTileType *tt = map->TileType(t);
        #ifdef DEBUG
        if(tt) cout<<"("<<tt->TileName()<<")";
        cout<<endl;
        cout<<"Revealing terrain"<<endl;
        #endif
        Reveal();
        #ifdef DEBUG
        cout<<"Getting Terrain Movement Cost"<<endl;
        if(tt) cout<<"Terrain: "<<tt->TileName()<<endl;
        #endif
        //changed 20/6
        if(tt) data->mf -= tt->Movement();
        else data->mf--;
        #ifdef DEBUG
        cout<<"MF: "<<data->mf<<endl;
        #endif
        if(data->mf<=0) data->mf = 0;
        FillRect(screen,979,384,30,12,48,48,48);
        drawString2(screen,data->SoLfont1[3],984,386,"%i/%i",data->mf,data->tmf);
        
        SlideUnit(data->unitList[data->turn], data->scrnum, data->oldloc);
    }

/* put new background image in bck1*/
    DrawTILE(bck1,screen,0,0,data->tw,data->th,data->stile[data->scrnum][XPOS],
          data->stile[data->scrnum][YPOS]-data->yextra-5);
    data->oldloc=data->scrnum;

/*  If the unit is on a water tile use a ship icon
if not, use the scout icon*/     
    if(!(data->unitList[data->turn]->isOnboard()))
    {
     UnitTerrainCheck(data->turn);
    }   

    UpdateScreen1(data->stile[data->scrnum][XPOS],
          data->stile[data->scrnum][YPOS]-data->yextra-5,data->tw,data->th);

/*  Check to see if the tile has a Rumor on it
If so, call the MessageWindow and then RemoveRumor*/

    if(map->getTile(data->mapnum)->Is(TILE_RUMOR))
    {
      MessageWindow(0);
      RemoveRumor();
    }

    /*if unit disembarks on a rumor*/  
    if(data->RumorFlag)
    {
      mapnumold=data->mapnum;
      data->mapnum=data->RumorFlag;
      MessageWindow(0);
      map->getTile(data->mapnum)->setFlags(TILE_RUMOR, false);
      SetTerrain();
      UpdateScreen0();
      data->mapnum=mapnumold;
      data->RumorFlag=0;
    }

    /*if the unit tried to move onto a village*/  
    if(data->flag&data->VillageFlag)
    {
      data->flag&=~data->VillageFlag;
      MessageWindow(2);
      data->mf--;
      FillRect(screen,979,384,30,12,48,48,48);
      drawString2(screen,data->SoLfont1[3],984,386,"%d/%d",data->mf,data->tmf);
      UpdateScreen1(979,384,30,12);        
    }
}

/*---------------------------Reveal------------------------------*/

void GraphicsEngine::Reveal(void)
{
    /*Test to see if mapnum is legit (0-29999)
      Check to see if maptile is either to the left or right of the 
      unit's position (no 'wrap around')
      Then, if the tile was shrouded it becomes partially shrouded
      If partially shrouded it becomes revealed*/

    GlobalData* data = m_pGame->GetData();
    Uint8 n = data->nationTurn;
    Map* map = m_pGame->GetMap();

    if(data->mapnum-302>-1 &&
       map->getTile(data->mapnum-302)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-302)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-302)->setShrdstate(n, 1);
    }

    if(data->mapnum-301>-1 &&
       map->getTile(data->mapnum-301)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-301)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-301)->setShrdstate(n, 1);
    }

    if(data->mapnum-300>-1 &&
       map->getTile(data->mapnum-300)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-300)->setShrdstate(n, 1);
    }

    if(data->mapnum-299>-1 &&
       map->getTile(data->mapnum-299)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-299)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-299)->setShrdstate(n, 1);
    }

    if(data->mapnum-298>-1 &&
       map->getTile(data->mapnum-298)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-298)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-298)->setShrdstate(n, 1);
    }

    if(data->mapnum-152>-1 &&
       map->getTile(data->mapnum-152)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-152)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-152)->setShrdstate(n, 1);
    }

    if(data->mapnum-151>-1 &&
       map->getTile(data->mapnum-151)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-151)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum-151)->setShrdstate(n, 0);
    }

    if(data->mapnum-150>-1 &&
       map->getTile(data->mapnum-150)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum-150)->setShrdstate(n, 0);
    }

    if(data->mapnum-149>-1 &&
       map->getTile(data->mapnum-149)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-149)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum-149)->setShrdstate(n, 0);
    }

    if(data->mapnum-148>-1 &&
       map->getTile(data->mapnum-148)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-148)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-148)->setShrdstate(n, 1);
    }

    if(data->mapnum-2>-1 &&
       map->getTile(data->mapnum-2)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-2)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum-2)->setShrdstate(n, 1);
    }

    if(data->mapnum-1>-1 &&
       map->getTile(data->mapnum-1)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum-1)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum-1)->setShrdstate(n, 0);
    }

    map->getTile(data->mapnum)->setShrdstate(n, 0);

    if(data->mapnum+1<data->mapmax+1 &&
       map->getTile(data->mapnum+1)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+1)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum+1)->setShrdstate(n, 0);
    }

    if(data->mapnum+2<data->mapmax+1 &&
       map->getTile(data->mapnum+2)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+2)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+2)->setShrdstate(n, 1);
    }

    if(data->mapnum+148<data->mapmax+1 &&
       map->getTile(data->mapnum+148)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+148)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+148)->setShrdstate(n, 1);
    }

    if(data->mapnum+149<data->mapmax+1 &&
       map->getTile(data->mapnum+149)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+149)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum+149)->setShrdstate(n, 0);
    }

    if(data->mapnum+150<data->mapmax+1 &&
       map->getTile(data->mapnum+150)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum+150)->setShrdstate(n, 0);
    }

    if(data->mapnum+151<data->mapmax+1 &&
       map->getTile(data->mapnum+151)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+151)->getShrdstate(n)>0)
    {
        map->getTile(data->mapnum+151)->setShrdstate(n, 0);
    }

    if(data->mapnum+152<data->mapmax+1 &&
       map->getTile(data->mapnum+152)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+152)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+152)->setShrdstate(n, 1);
    }

    if(data->mapnum+298<data->mapmax+1 &&
       map->getTile(data->mapnum+298)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+298)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+298)->setShrdstate(n, 1);
    }

    if(data->mapnum+299<data->mapmax+1 &&
       map->getTile(data->mapnum+299)->getXPos() <
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+299)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+299)->setShrdstate(n, 1);
    }

    if(data->mapnum+300<data->mapmax+1 &&
       map->getTile(data->mapnum+300)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+300)->setShrdstate(n, 1);
    }

    if(data->mapnum+301<data->mapmax+1 &&
       map->getTile(data->mapnum+301)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+301)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+301)->setShrdstate(n, 1);
    }

    if(data->mapnum+302<data->mapmax+1 &&
       map->getTile(data->mapnum+302)->getXPos() >
         map->getTile(data->mapnum)->getXPos()&&
       map->getTile(data->mapnum+302)->getShrdstate(n)==2)
    {
        map->getTile(data->mapnum+302)->setShrdstate(n, 1);
    }
}

/*---------------------------Reveal------------------------------*/
void GraphicsEngine::Reveal(int x, int y, int radius)
{
/*  Check to see if maptile is either to the left or right of the 
  unit's position (no 'wrap around')
  Then, if the tile was shrouded it becomes partially shrouded
  If partially shrouded it becomes revealed*/
  GlobalData *data = m_pGame->GetData();
  Map* map = m_pGame->GetMap();

// Test to see if coordinates are legit
  if(x<0 || x>=map->GetWidth() || y<0 || y>=map->GetHeight()) return;
  
  Uint8 n = data->nationTurn;
   
  #ifdef DEBUG
  cout<<"Nation "<<(int)n<<endl;
  #endif

  int xx=0, yy=0, ii=0, jj=0;
  for(xx=x-radius, ii=0; ii < 2*radius+1; ii++)
  {
    // Check for map edges
    if(xx>=0 && xx<map->GetWidth())
    {
      for(yy=y-radius, jj=0; jj < 2*radius+1; jj++)
      {
        if(yy>=0 && yy<map->GetHeight())
        {
          switch(map->getTileAt(xx,yy)->getShrdstate(n))
          {
          case 2:
            if(ii>radius-2 && ii<radius+2)
              map->getTileAt(xx,yy)->setShrdstate(n, 0);
            else
              map->getTileAt(xx,yy)->setShrdstate(n, 1);
            break;
          case 1:
            if(ii>radius-2 && ii<radius+2)
              map->getTileAt(xx,yy)->setShrdstate(n, 0);
            else
              map->getTileAt(xx,yy)->setShrdstate(n, 1);
            break;
          default:
            break;
          }
        }
      }
    }
  }
}

/*-----------------------BlinkUnit---------------------------*/
void GraphicsEngine::BlinkUnit(Unit* theUnit, long &LastUpdate, bool &blink, bool &a2)
{
  short Speed=432;

  GlobalData* data = m_pGame->GetData();

  if(LastUpdate+Speed<SDL_GetTicks())
  {
    if(blink)
    {
        if(startY==0)
        {
          DrawTILE(screen,bck1,
                   data->stile[data->scrnum][XPOS],
                   data->stile[data->scrnum][YPOS],
                   data->tw,data->th-data->yextra,
                   0,data->yextra);
        }
        else
        {
          DrawSURF(screen,bck1,data->stile[data->scrnum][XPOS],
                   data->stile[data->scrnum][YPOS]-data->yextra);
        }
        blink=false;
    }
    else
    {
/**/      UnitTerrainCheck(data->turn);
      blink=true;
    }
    LastUpdate=SDL_GetTicks();
  }

  if(a2!=blink)
  {
/**/    UpdateScreen1(data->stile[data->scrnum][XPOS],
                  data->stile[data->scrnum][YPOS]-data->yextra,
                  data->tw,data->th);
    a2=blink;
  }
}

void GraphicsEngine::SlideUnit(Unit *unit, short newloc, short oldloc)
{
    GlobalData* data = m_pGame->GetData();
    int dx,dy,steps=25,i,x,y,x1,y1;
    short box = 0,pos;
    int icon = unit->getGraphic();

        if(unit->isBoat())
         pos = 1;
        else
         pos = 2;

        /*does the screen need to be recentered?*/
        if(data->flag&data->ReCenFlag)
        {
            data->flag&=~data->ReCenFlag;
        }
        else
        {
//slide        
        dx=(data->stile[newloc][XPOS]-data->stile[oldloc][0])/steps; //changed 26/6; this should be steps so it's not hardcoded
        dy=(data->stile[newloc][YPOS]-data->stile[oldloc][1])/steps; //changed 26/6; see above comment
        x=data->stile[oldloc][0];
        y=data->stile[oldloc][1]-data->yextra-5;

//if move is north and by mouse draw 'move to' box        
        if(data->stile[newloc][YPOS]-data->stile[oldloc][1]==-data->th &&
              data->mouseClick==1) {box=1;}
        DrawTILE(bck1,screen,0,0,data->tw,data->th,x,y);

        
        for(i=0;i<steps;i++)
        {
              DrawSURF(screen,bck1,x,y);

              x+=dx;
              y+=dy;
              DrawTILE(bck1,screen,0,0,data->tw,data->th,x,y);
              
              if(newloc<11)
              {
                NationBox(x, y+data->yextra+5,
                 unit->getNation(), pos,
                 unit->getOrders());
                DrawTILE(screen, uniticons, x, y+data->yextra+5,
                  data->tw, data->th-data->yextra-5, data->tile50[icon][0],
                  data->tile50[icon][1]);
              }
              else
              {
                NationBox(x,y,unit->getNation(), pos,
                 unit->getOrders());
                DrawTILE(screen, uniticons, x, y, data->tw, data->th,
                      data->tile50[icon][0], data->tile50[icon][1]);
                if(box==1)
                {
                  DrawTILE(screen,tilesheet1,data->stile[newloc][XPOS],
                        data->stile[newloc][YPOS],data->tw,data->th,
                        data->tilex[10],data->tiley[3]);
                }
              }
              if(data->stile[oldloc][0]<data->stile[newloc][XPOS])
              {x1=x-dx;}
              else
              {x1=x+dx;}
              if(data->stile[oldloc][1]<data->stile[newloc][YPOS])
              {y1=y-dy;}
              else
              {y1=y+dy;}
              UpdateScreen1(x1,y1,data->tw+dx,data->th+dy+data->yextra+5);
              SDL_Delay(5);              
        }
      }
    SetTerrain();         /*draw new screen*/
    UpdateScreen0();      /*Update screen*/
    DrawTILE(bck1,screen,0,0,data->tw,data->th,
             data->stile[oldloc][0],
             data->stile[oldloc][1]-data->yextra-5); //added 26/6; restore unit bck1
}

//
// $Id: display.cpp,v 1.13 2004/06/26 14:44:27 chainsword Exp $
//
