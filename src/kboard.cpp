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
#include <cstdio>
#include <cstdlib>
#include <SDL.h>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "unit.h"

/*---------------------------KeyBoard-----------------------------*/
int GraphicsEngine::KeyBoard(int k)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    unsigned char move;

  if(k==SDLK_ESCAPE){return 1;}
  if(k==SDLK_q){return 1;}
  
//changed 5/31
//space bar ends unit turn even if not visible  
  if(k == SDLK_SPACE && data->scrndsply == 0 && !data->zl)
  {
      data->mf = 0;
      data->visible = 1;
      return 0;
  }

  /*Checks the zoom state and if the unit is visible
    Handles keypad movement
    Handles hotkeys B,P,R,etc.*/

  if(data->zl==0&&data->visible==1&&data->scrndsply==0)
  {
  
    UnitTerrainCheck(data->turn);
    UpdateScreen1(data->stile[data->scrnum][XPOS],
                  data->stile[data->scrnum][YPOS]-data->yextra-5,
                  data->tw,data->th+5);
              
    switch (k)
    {
      case (SDLK_KP_9):                 /*NE*/
      case (SDLK_PAGEUP):
      {
        move=1;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_6):                 /*E*/
      case (SDLK_RIGHT):
      {
        move=2;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_3):                 /*SE*/
      case (SDLK_PAGEDOWN):
      {
        move=3;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_2):                  /*S*/
      case (SDLK_DOWN):
      {
        move=4;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_1):                  /*SW*/
      case (SDLK_END):
      {
        move=5;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_4):                  /*W*/
      case (SDLK_LEFT):
      {
        move=6;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_7):                  /*NW*/
      case (SDLK_HOME):
      {
        move=7;
        data->flag|=data->MoveFlag;
        break;
      }
      case (SDLK_KP_8):                  /*N*/
      case (SDLK_UP):
      {
        move=8;
        data->flag|=data->MoveFlag;
        break;
      }
      
      case (SDLK_KP_5):                  /*ReCenter*/
      {
        ReCenter();
        data->flag|=data->ReCenFlag+data->UpDateFlag;
        SetTerrain();
        UnitTerrainCheck(data->turn);              /*Water or Land?*/
        UpdateScreen1(5,25,830,725);
        data->visible=1;
        break;
      }
      case SDLK_f:
       data->unitList[data->turn]->fortify();
       data->mf = 0;
       ScreenUpdate();
       break;
              
      case SDLK_s:
       data->unitList[data->turn]->sentry();
       data->mf = 0;
       ScreenUpdate();
       break;
              
      case (SDLK_b):                    /*colony*/
      {
        Orders(12);
        break;
      }        
      case (SDLK_c):                    /*clear*/
      {
        Orders(9);
        break;
      }        
      case (SDLK_p):                    /*plow*/
      {
        Orders(10);
        break;
      }
      case (SDLK_r):                    /*road*/
      {
        Orders(11);
        break;
      }
      case (SDLK_g):                    /*grid*/
      {
        SetGrid();
        break;
      }
      case (SDLK_a):                    /*clears shroud*/
      {
        map->RevealAll();
        SetTerrain();
        UpdateScreen0();
        break;
      }              
      default: 
        data->flag&=~data->MoveFlag;
    }

/*  If a key moved the unit, update the screen */    
    if(data->flag&data->MoveFlag)
    {
      MoveUnit(move);
      DrawScene();
      data->flag&=~data->MoveFlag;
    }
  }
  
  if(k==SDLK_z&&data->scrndsply==0){Zoom1();}
              
  return 0;
}


//
// $Id: kboard.cpp,v 1.8 2004/06/23 15:37:05 sikon Exp $
//

