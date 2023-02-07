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
#include <ctime>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"
#include "unit.h"

/*---------------------------MouseCheck--------------------------*/
int GraphicsEngine::MouseCheck(void)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
  
  int /*x,*/y,xM,yM,i,/*k,*/tempoldx,tempoldy,no,x0,y0;
  short done=0,TXoffset=4,TYoffset=5,a=0,hl=0,hlold=0;
  unsigned char move=99;
  SDL_Surface *temp;
  long mapclick=0;
  short colnum,cName;
  string text;
  int renderW,renderH;

  temp=CreateSurface(screen,data->tw,data->th);

/*  Handles mouse events*/

  if(SDL_GetMouseState(&xM,&yM)&SDL_BUTTON(1))
  {

/*check to see if the main screen is displayed*/
  if(data->scrndsply==0)
  {
  
x0=5;y0=2;  
    if(xM>x0+938&&xM<x0+938+76&&yM>y0&&yM<y0+18)         /*quit*/
    {
      DrawTILE(screen,extra1,x0+938,y0,76,18,344,52);
//      drawString(screen,font1,x0+957,y0,"%s",data->Labels[6]);
      drawString(screen,fontPushButtons,x0+956,y0-1,true,"%s",data->Labels[6]);
      UpdateScreen1(x0+938,y0,76,18);
      SDL_Delay(100);
      done=1;return done;
    }    

    if(xM>x0&&xM<x0+76&&yM>y0&&yM<y0+18)                 /*game*/
    {
      Buttons2(x0,20,y0,1,0,344,52,267,76,18);
      MessageWindow(10);
      return 0;
    }    
    if(xM>x0+76&&xM<x0+76+76&&yM>y0&&yM<y0+18)           /*view*/
    {
      Buttons2(x0+76,26,y0,1,1,344,52,267,76,18);
      MessageWindow(10);
      return 0;
    }   
    if(xM>x0+152&&xM<x0+152+76&&yM>y0&&yM<y0+18)        /*orders*/
    {
      Buttons2(x0+152,20,y0,1,2,344,52,267,76,18);
      MessageWindow(10);
      return 0;
    }  
    if(xM>x0+228&&xM<x0+228+76&&yM>y0&&yM<y0+18)       /*reports*/
    {
      Buttons2(x0+228,16,y0,1,3,344,52,267,76,18);
      MessageWindow(10);
      return 0;
    }
    if(xM>x0+304&&xM<x0+304+76&&yM>y0&&yM<y0+18)         /*trade*/
    {
      Buttons2(x0+304,22,y0,1,4,344,52,267,76,18);
      MessageWindow(10);
      return 0;
    }
    if(xM>x0+380&&xM<x0+380+76&&yM>y0&&yM<y0+18)         /*zoom*/
    {
      Buttons2(x0+380,11,y0,1,7,344,52,267,76,18);
      Zoom1();return 0;
    }    
    if(xM>x0+456&&xM<x0+456+132&&yM>y0&&yM<y0+18)    /*assistance*/
    {
      Buttons2(x0+456,34,y0,1,5,134,52,1,132,18);
      MessageWindow(10);
      return 0;
    }

x0=990;    
    i=9;
    for(y=50;y<146;y+=24)                    /*order buttons*/
    {
      if(xM>x0&&xM<x0+24&&yM>y&&yM<y+24&&data->zl==0&&data->visible==1)
      {Buttons2(x0,8,y,5,i,26,71,1,24,24);Orders(i);return 0;}
      i++;
    }

/*grid button*/    
    if(xM>x0&&xM<x0+24&&yM>146&&yM<170&&data->zl==0){SetGrid();return 0;}

/*end active unit's turn*/
    if(xM>x0&&xM<x0+24&&yM>170&&yM<194&&data->zl==0)  
    {Buttons2(x0,8,170,5,20,26,71,1,24,24);Orders(20);return 0;}

/*copy main screen to map1 surface.
  draw CDS to main screen.
  place buildings (FillSlots()) for colony variations.
  draw fields based on current position of the scout.
  update the player's gold.
  reset the market counter (amount of goods moved).*/
    x0=438;y0=734;    
    if(xM>x0&&xM<x0+49&&yM>y0&&yM<y0+24&&data->zl==0)     /*CDS*/
    {
      Colony *col;
      Buttons2(x0,13,y0,5,13,101,71,51,49,24);
      if(!(col = m_pGame->FindColonyOf(data->nation)))
      {
          MessageWindow(MSG_NOCDS);
          return 0;
      }
      
      DrawTILE(map1,screen,0,0,screenResX,screenResY,0,0);
      DrawTILE(screen,cds1,0,0,screenResX,screenResY,0,0);
//use first colony for buildings, fields and name
/*      FillSlots1(0);
      DrawCDSFields2(0);
      UpdateGold(0);
      data->counterbutton=2;data->counterspace=0;data->tons=100;data->counter=100;

      text=data->colName[data->nation][0];
      text = text.substr(0,text.size()-1); //Remove the carriage return
      TTF_SizeText(fontColNameCDS->font,(char *)text.c_str(),&renderW,&renderH);      
            
      drawString(screen, fontColNameCDS, 512-(renderW/2), 3, true,
       data->colName[data->nation][0]); */
      UpdateCDS(col);
    
      UpdateScreen0();
      data->scrndsply = 1;
      return 0;
    }
    
/*copy screen to map1 surface.
  draw HCS to main screen.
  update the player's gold.
  reset the market counter (amount of goods moved).*/
x0=487;
    if(xM>x0&&xM<x0+49&&yM>y0&&yM<y0+24&&data->zl==0)    /*HCS*/
    {
    Buttons2(x0,13,y0,5,14,101,71,51,49,24);    
    DrawSURF(map1,screen,0,0);    
    DrawTILE(screen,hcs1,0,0,screenResX,y0-1,0,0);
    UpdateGold(0);
    data->counterbutton=2;data->counterspace=0;data->tons=100;data->counter=100;
    UpdateScreen0();
    data->scrndsply=2;data->HCSradio1=0;
    return 0;
    }


/*  Check to see if the mouse click was on the unit tile
    If so, check to see which tile the mouse button was released on
    Then move the unit*/
if(data->zl==0)
{
    xM=xM+TXoffset;yM=yM+TYoffset;
    if(xM>=data->stile[data->scrnum][0]&&
       xM< data->stile[data->scrnum][0]+data->tw&&
       yM>=data->stile[data->scrnum][YPOS]&&
       yM< data->stile[data->scrnum][YPOS]+data->th&&
       data->visible==1)
    {

/*draw the active unit on the map. (negates the 'blink'.*/
      UnitTerrainCheck(data->turn);
      UpdateScreen1(data->stile[data->scrnum][XPOS],
                    data->stile[data->scrnum][YPOS]-data->yextra-5,
                    data->tw,data->th+5);

/*store image of unit and unit tile.
  store screen location of unit's tile.*/
      DrawTILE(temp,screen,0,0,data->tw,data->th,data->stile[data->scrnum][XPOS],
                    data->stile[data->scrnum][YPOS]);
      tempoldx=data->stile[data->scrnum][XPOS];
      tempoldy=data->stile[data->scrnum][YPOS];

/*loop while mouse button is pressed.*/
      while(!a)
      {
        SDL_PollEvent(&data->event);

/*check to see which tile the mouse is over.
  if tile is a legitimate move, draw 'box'.
  else draw 'no move' symbol'.
  (only do this if the mouse is on a new tile.)*/
        switch(HighLight1())
        {
          case (1):
          {
            hl=1;
            if(hl!=hlold)
            {
              if(HighLight3(-data->mNE)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,-data->sNE,no);
              hlold=hl;
            }
            break;
          }
          case (2):
          {
            hl=2;
            if(hl!=hlold)
            {
              if(HighLight3(data->mE)==0){no=0;}else{no=1;}  
              HighLight2(temp,tempoldx,tempoldy,data->sE,no);
              hlold=hl;
            }
            break;
          }
          case (3):
          {
            hl=3;
            if(hl!=hlold)
            {
              if(HighLight3(data->mSE)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,data->sSE,no);
              hlold=hl;
            }
            break;
          }
          case (4):
          {
            hl=4;
            if(hl!=hlold)
            {
              if(HighLight3(data->mS)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,data->sS,no);
              hlold=hl;
            }
            break;
          }
          case (5):
          {
            hl=5;
            if(hl!=hlold)
            {
              if(HighLight3(data->mSW)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,data->sSW,no);
              hlold=hl;
            }
            break;
          }
          case (6):
          {
            hl=6;
            if(hl!=hlold)
            {
              if(HighLight3(-data->mW)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,-data->sW,no);
              hlold=hl;
            }
            break;
          }
          case (7):
          {
            hl=7;
            if(hl!=hlold)
            {
              if(HighLight3(-data->mNW)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,-data->sNW,no);
              hlold=hl;
            }
            break;
          }
          case (8):
          {
            hl=2;
            if(hl!=hlold)
            {
              if(HighLight3(-data->mN)==0){no=0;}else{no=1;}
              HighLight2(temp,tempoldx,tempoldy,-data->sN,no);
              hlold=hl;
            }
            break;
          }
          default:
          {
            hl=9;
            if(hl!=hlold)
            {
              DrawSURF(screen,temp,tempoldx,tempoldy);
              UpdateScreen1(tempoldx,tempoldy,data->tw,data->th);
              hlold=9;
            }
          }
        }

/*if the mouse button is released.*/       
         if(data->event.button.button==SDL_BUTTON_LEFT&&
            data->event.button.type==SDL_MOUSEBUTTONUP)
         {
/*flag to end 'while mouse button is pressed' loop.*/         
            a=1;
                
            move=HighLight1();
            if(move>0 && move<9){data->flag|=data->MoveFlag;}
          }
        }
     }

/*  If the mouse was used to move the unit, move the unit*/
    if(data->flag&data->MoveFlag)
    {
      data->mouseClick=1;
      MoveUnit(move);
      DrawScene();
      data->mouseClick=0;
      data->flag&=~data->MoveFlag;
      return 0;
    }
    
//bring up CDS    
    if(!move && map->getTile(data->mapnum)->Is(TILE_BUILD))
    {
      Colony *col = m_pGame->FindColonyAt(data->mapnum);
      DrawTILE(map1,screen,0,0,screenResX,screenResY,0,0);
      DrawTILE(screen,cds1,0,0,screenResX,screenResY,0,0);

//added 6/1
//find the colony number      
/*      for(i=0;i<data->colonyCount;i++)
      {
        if(data->colony[i].colonyLoc==data->mapnum)
        {
          colnum=i;
          break;
        }
      } 
//place buildings and fields
      FillSlots1(colnum);
      DrawCDSFields2(colnum);
      
      UpdateGold(0);
      data->counterbutton=2;data->counterspace=0;data->tons=100;data->counter=100;
//put colony name on cds
      if(colnum >= data->colNameCount[data->nation])
      {
          cName = data->colNameCount[data->nation] - 1;
      }
      else
      {
          cName = colnum;
      }
      
      text=data->colName[data->nation][cName];
      text = text.substr(0,text.size()-1); //Remove the carriage return
      TTF_SizeText(fontColNameCDS->font,(char *)text.c_str(),&renderW,&renderH);      
            
      drawString(screen,fontColNameCDS,512-(renderW/2),3,true,
            data->colName[data->nation][cName]); */
      UpdateCDS(col);
      
      UpdateScreen0();
      data->scrndsply=1;
      return 0;
    }

//added 6/1
//was click on a colony?
//if so bring up cds for that colony
  for(i=0;i<data->scrmax+1;i++)
  {
    if(xM>data->stile[i][XPOS]&&
       xM<data->stile[i][XPOS]+data->tw&&
       yM>data->stile[i][YPOS]&&
       yM<data->stile[i][YPOS]+data->th)
    {
      mapclick=data->start+((i/11)*150)+i%11;

// >>>
      if(map->getTile(mapclick)->Is(TILE_UNIT))
      {
          Unit *temp;
          bool b = map->getTile(mapclick)->Is(TILE_WATER);
          if((temp = m_pGame->FindUnitAt(mapclick, b)) &&
           (temp->getNation() == data->nation))
          {
              if(temp->getOrders() != ORD_NONE)
                  temp->setOrders(ORD_NONE);
          }
      }
// <<<

      if(map->getTile(mapclick)->Is(TILE_BUILD))
      {
        Colony *col = m_pGame->FindColonyAt(mapclick);
        DrawTILE(map1,screen,0,0,screenResX,screenResY,0,0);
        DrawTILE(screen,cds1,0,0,screenResX,screenResY,0,0);
        
/*        for(i=0;i<data->colonyCount;i++)
        {
          if(data->colony[i].colonyLoc==mapclick)
          {
            colnum=i;
            break;
          }
        } 
        FillSlots1(colnum);
        DrawCDSFields2(colnum);
        UpdateGold(0);
        data->counterbutton=2;data->counterspace=0;data->tons=100;data->counter=100;
        
        if(colnum >= data->colNameCount[data->nation])
        {
         cName = data->colNameCount[data->nation] - 1;
        }
        else
        {
         cName = colnum;
        }
              
        text=data->colName[data->nation][cName];
        text = text.substr(0,text.size()-1); //Remove the carriage return
        TTF_SizeText(fontColNameCDS->font,(char *)text.c_str(),&renderW,&renderH);      
            
        drawString(screen,fontColNameCDS,512-(renderW/2),3,true,
              data->colName[data->nation][cName]); */
        UpdateCDS(col);
        
        UpdateScreen0();
        data->scrndsply=1;
        return 0;      
      }
    }
  }

/*  If the map is zoomed in Recenter on the tile clicked*/
    TileCenter(xM,yM);

/*  Check to see if the mouse click was off of the map.
    If so, recenter so the unit tile is once more the center 
    square*/  
    xM=xM-TXoffset;yM=yM-TYoffset;
    if((xM<data->stile[0][XPOS]||
        xM>data->stile[10][XPOS]+data->tw||
        yM<data->stile[0][YPOS]||
        yM>data->stile[153][YPOS]+data->th))
    {
      ReCenter();
      data->flag&=~data->ReCenFlag;
      SetTerrain();
      UpdateScreen1(5,25,825,700);
      DrawTILE(bck1,screen,0,0,data->tw,data->th,
               data->stile[data->scrnum][XPOS],
               data->stile[data->scrnum][YPOS]-data->yextra-5);
      data->oldloc=data->scrnum;
      UnitTerrainCheck(data->turn);
      UpdateScreen1(data->stile[data->scrnum][XPOS],
                    data->stile[data->scrnum][YPOS]-data->yextra-5,
                    data->tw,data->th+5);
      data->visible=1;
    }
  }
}

/*if the map IS NOT being displayed on the main screen.*/
  else
  {
  
/*if the CDS is being displayed*/
    if(data->scrndsply==1)
    {
x0=943;y0=1;

/*if click is on map button, replace CDS with stored map.*/
      if(xM>x0&&xM<x0+76&&yM>y0&&yM<y0+18)         /*MAP-CDS*/
      {
        Buttons2(x0,27,y0,1,15,344,52,267,76,18);
        DrawSURF(screen,map1,0,0);    
        UpdateGold(0);
        UpdateScreen0();
        data->scrndsply=0;
        return 0;
      }
/*if click is NOT on map button, go to CDSMouseCheck*/
      else{CDSMouseCheck(xM,yM);}  
    }
    
/*if the HCS is being displayed*/
    else
    {    
x0=536;y0=734;

/*if click is on map button, replace HCS with stored map.*/
      if(xM>x0&&xM<x0+49&&yM>y0&&yM<y0+24)         /*MAP-HCS*/
      {
        Buttons2(x0,13,y0,5,15,101,71,51,49,24);
        DrawSURF(hcs1,screen,0,0);
        DrawSURF(screen,map1,0,0);    
        UpdateGold(0);
        UpdateScreen0();
        data->scrndsply=0;
        return 0;
      }
      
/*if click is NOT on map button, go to HCSMouseCheck*/      
      else{HCSMouseCheck(xM,yM,0);}
    }
  }
  }
  return 0;
}

/*---------------------------TileCenter--------------------------*/
void GraphicsEngine::TileCenter(int xM,int yM)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();

    int i;
    long oldmapnum;

/*centers map on tile clicked.
  if click is off map, recenters on active unit.*/
  
/*was click on a map tile?*/
  for(i=0;i<data->scrmax+1;i++)
  {
    if(xM>data->stile[i][XPOS]&&
       xM<data->stile[i][XPOS]+data->tw&&
       yM>data->stile[i][YPOS]&&
       yM<data->stile[i][YPOS]+data->th)
    {
      oldmapnum=data->mapnum;
      data->mapnum=data->start+(((int)i/11)*150)+i%11;
      ReCenter();
      data->flag&=~data->ReCenFlag;
      SetTerrain();

/*  Check to see if the unit tile is visible on the new screen*/
      data->mapnum=oldmapnum;
      data->visible=0;
      if(map->getTile(data->mapnum)->getXPos()>=
          map->getTile(data->start)->getXPos()    &&
         map->getTile(data->mapnum)->getXPos()<
          map->getTile(data->start)->getXPos()+11 &&
         map->getTile(data->mapnum)->getYPos()>=
          map->getTile(data->start)->getYPos()    &&
         map->getTile(data->mapnum)->getYPos()<
          map->getTile(data->start)->getYPos()+14)
      {
        data->visible=1;
        data->scrnum=(map->getTile(data->mapnum)->getYPos()-
                      map->getTile(data->start)->getYPos())*11+
                     (map->getTile(data->mapnum)->getXPos()-
                      map->getTile(data->start)->getXPos());
                      
        data->oldloc=data->scrnum;
        
/*  If the unit is visible, draw it on the display*/
        UnitTerrainCheck(data->turn);
      }
      UpdateScreen1(5,25,825,700);
    }
  }
}

/*---------------------------HighLight1--------------------------*/
int GraphicsEngine::HighLight1(void)
{
    GlobalData* data = m_pGame->GetData();

    int xM,yM;
    short TXoffset=4,TYoffset=5;

/*determines which of the adjacent tiles has the mouse foucus.
returns the tile number. 0=unit tile. 1=NE, 4=S, 8=N.*/
  SDL_GetMouseState(&xM,&yM);
  xM=xM+TXoffset;yM=yM+TYoffset;

  if(xM>=data->stile[data->scrnum][XPOS]-data->tw &&
     xM< data->stile[data->scrnum][XPOS])
    {
      if(yM>=data->stile[data->scrnum][YPOS]-data->th&&
         yM< data->stile[data->scrnum][YPOS])
        {return 7;}
      if(yM>=data->stile[data->scrnum][YPOS]&&
         yM< data->stile[data->scrnum][YPOS]+data->th)
        {return 6;}
      if(yM>=data->stile[data->scrnum][YPOS]+data->th&&
         yM< data->stile[data->scrnum][YPOS]+(2*data->th))
        {return 5;}
    }

    if(xM>=data->stile[data->scrnum][XPOS]+data->tw&&
       xM< data->stile[data->scrnum][XPOS]+(2*data->tw))
    {
      if(yM>=data->stile[data->scrnum][YPOS]-data->th&&
         yM< data->stile[data->scrnum][YPOS])
        {return 1;}
      if(yM>=data->stile[data->scrnum][YPOS]&&
         yM< data->stile[data->scrnum][YPOS]+data->th)
        {return 2;}
      if(yM>=data->stile[data->scrnum][YPOS]+data->th&&
         yM< data->stile[data->scrnum][YPOS]+(2*data->th))
        {return 3;}
    }

    if(xM>=data->stile[data->scrnum][XPOS]&&
       xM< data->stile[data->scrnum][XPOS]+data->tw)
    {
      if(yM>=data->stile[data->scrnum][YPOS]-data->th&&
         yM< data->stile[data->scrnum][YPOS])
        {return 8;}
      if(yM>=data->stile[data->scrnum][YPOS]&&
         yM< data->stile[data->scrnum][YPOS]+data->th)
        {return 0;}
      if(yM>=data->stile[data->scrnum][YPOS]+data->th&&
         yM< data->stile[data->scrnum][YPOS]+(2*data->th))
        {return 4;}
    }
  return 9;
}

/*---------------------------HighLight2--------------------------*/
void GraphicsEngine::HighLight2(SDL_Surface *temp,int &tempoldx,int &tempoldy,
                  int dir,int no)
{
    GlobalData* data = m_pGame->GetData();

/*checks to see if the adjacent tile is displayed on the screen 
  (not off the edge of the map display).
  If it is, then draw the 'box' or 'no move' symbol.*/
  if(data->scrnum+dir>=0&&data->scrnum+dir<=data->scrmax)
  {
    if(data->stile[data->scrnum][XPOS]==data->stile[0][XPOS]&&
      (dir==-data->sNW||dir==-data->sW||dir==data->sSW))
    {
      DrawSURF(screen,temp,tempoldx,tempoldy);
      UpdateScreen1(tempoldx,tempoldy,data->tw,data->th);
    }
    else
    {
      if(data->stile[data->scrnum][XPOS]==data->stile[10][XPOS]&&
        (dir==-data->sNE||dir==data->sE||dir==data->sSE))
      {
        DrawSURF(screen,temp,tempoldx,tempoldy);
        UpdateScreen1(tempoldx,tempoldy,data->tw,data->th);
      }
      else
      {
        DrawSURF(screen,temp,tempoldx,tempoldy);
        UpdateScreen1(tempoldx,tempoldy,data->tw,data->th);
        DrawTILE(temp,screen,0,0,data->tw,data->th,
                 data->stile[data->scrnum+dir][XPOS],
                 data->stile[data->scrnum+dir][YPOS]);
        tempoldx=data->stile[data->scrnum+dir][XPOS];
        tempoldy=data->stile[data->scrnum+dir][YPOS];
        
/*draw the 'box'.*/
        if(no==0)
        {
          DrawTILE(screen,tilesheet1,data->stile[data->scrnum+dir][XPOS],
                   data->stile[data->scrnum+dir][YPOS],data->tw,data->th,
                   data->tilex[10],data->tiley[3]);
        }
        
/*draw the 'no move' symbol.*/
        else
        {
          DrawTILE(screen,tilesheet1,data->stile[data->scrnum+dir][XPOS],
                   data->stile[data->scrnum+dir][YPOS],data->tw,data->th,
                   data->tilex[11],data->tiley[3]);
        }

      UpdateScreen1(data->stile[data->scrnum+dir][XPOS],
                    data->stile[data->scrnum+dir][YPOS],
                    data->tw,data->th);

      if(dir==-data->sN){UnitTerrainCheck(data->turn);}
      UpdateScreen1(data->stile[data->scrnum][XPOS],
                    data->stile[data->scrnum][YPOS]-data->yextra,
                    data->tw,data->th);
      }
    }
  }
  else
  {
    DrawSURF(screen,temp,tempoldx,tempoldy);
    UpdateScreen1(tempoldx,tempoldy,data->tw,data->th);
  }
}

/*---------------------------HighLight3--------------------------*/
int GraphicsEngine::HighLight3(int dir)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    Unit *tmp = m_pGame->FindUnitAt(data->mapnum+dir,true);

/*determines if the adjacent tile is a legitmate move for the active 
  unit.*/
  if(data->unitList[data->turn]->isBoat())
  { 
    if(map->getTile(data->mapnum+dir)->getTerrain()==TERRAIN_LAKE ||
       map->getTile(data->mapnum+dir)->getTerrain()==TERRAIN_OCEAN ||
       map->getTile(data->mapnum+dir)->getTerrain()==TERRAIN_HIGHSEAS)
       return false; //move boat to sea tile 
    if(tmp->getNation()==data->unitList[data->turn]->getNation())
            return false; //move boat to a tile occupied by foreign boat
        return true;
   }
       
   if(!(data->unitList[data->turn]->isBoat()))
   {
      if(tmp)
      {
        if(tmp->getNation()==data->unitList[data->turn]->getNation())
            return false; //move scout to land tile or boat
        return true;
      }
      else
      {
        return (!(map->getTile(data->mapnum+dir)->getTerrain()!=TERRAIN_LAKE&&
        map->getTile(data->mapnum+dir)->getTerrain()!=TERRAIN_HIGHSEAS&&
        map->getTile(data->mapnum+dir)->getTerrain()!=TERRAIN_OCEAN));
      }
   }
     
   if((data->unitList[data->turn]->isBoat() &&
      data->unitList[data->turn]->getNumberOfPassenger() &&
      map->getTile(data->mapnum+dir)->getVillages()==0 &&
      data->nativeOnTile[data->mapnum+dir]==0)||
     (data->turn==1 && data->mapnum+dir==data->unitList[0]->getTile()))
     return false; //move boat to unload passenger
}


//
// $Id: mouse.cpp,v 1.13 2004/06/26 15:00:25 chainsword Exp $
//

