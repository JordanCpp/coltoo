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
#include "unit.h"
#include "player.h"

/*--------------------------Buttons------------------------------*/
void GraphicsEngine::Buttons(int x1,int dx,int y1,int dy,int i,int x2,int y2,
                             int w,int h)
{
    GlobalData* data = _GlobalData;
    /*draw the button with label*/
    DrawTILE(screen,extra1,x1,y1,w,h,x2,y2);
//    drawString(screen,font1,x1+dx,y1+dy,"%s",data->Labels[i]);
    drawString(screen,fontPushButtons,x1+(dx-1),y1+dy-1,true,"%s",data->Labels[i]);
}

/*---------------------------Buttons2-----------------------------*/
void GraphicsEngine::Buttons2(int x1,int dx,int y1,int dy,int i,int x2,int y2,
                              int x2b,int w,int h)
{
    GlobalData* data = _GlobalData;
    /*push and release a button*/

    /*if zoomed in use 'Zoom Out' label*/
    if(i==7&&data->zl==0){i=8;}

    Buttons(x1,dx-1,y1,dy-1,i,x2,y2,w,h);
    UpdateScreen1(x1,y1,w,h);
    SDL_Delay(100);    
    Buttons(x1,dx,y1,dy,i,x2b,y2,w,h);
    UpdateScreen1(x1,y1,w,h);
}

/*--------------------------UnitTerrainCheck----------------------*/
void GraphicsEngine::UnitTerrainCheck(short turn)
{
    GlobalData* data = _GlobalData;
    /*if land draw the scout; if not, draw the ship.*/

    short pos;
    int icon = data->unitList[data->turn]->getGraphic();

    if(data->unitList[data->turn]->isBoat())
     pos = 1;
    else
     pos = 2;
  
    if(data->scrnum<11)
    {
//added 6/2
//place nation box on screen
      NationBox(data->stile[data->scrnum][XPOS], data->stile[data->scrnum][YPOS],
            data->unitList[data->turn]->getNation(), pos,
            data->unitList[data->turn]->getOrders());    
      DrawTILE(screen, uniticons, data->stile[data->scrnum][XPOS],
            data->stile[data->scrnum][YPOS],
            data->tw, data->th-data->yextra-5, data->tile50[icon][0],
            /*data->tiley[1]+data->yextra+5*/data->tile50[icon][1]);
    }
    else
    {
//added 6/2
//place nation box on screen
      NationBox(data->stile[data->scrnum][XPOS],
            data->stile[data->scrnum][YPOS]-data->yextra-5,
            data->unitList[data->turn]->getNation(),pos,
            data->unitList[data->turn]->getOrders());
      DrawTILE(screen, uniticons, data->stile[data->scrnum][XPOS],
            data->stile[data->scrnum][YPOS]-data->yextra-5,
            data->tw,data->th,data->tile50[icon][0],data->tile50[icon][1]);
    }
}

/*--------------------------SetGrid-------------------------------*/
void GraphicsEngine::SetGrid(void)
{
    GlobalData* data = _GlobalData;
    /*depresses or releases the grid button 'G'.
      Also sets the grid flag to tell the SetTerrain3() function to 
      draw the grid.*/
  
    int x0=990;

    if(data->grid==0)
    {
        data->grid=1;
        DrawTILE(screen,extra1,x0,146,24,24,26,71);
//        drawString(screen,font1,x0+8,146+5,"%s",data->Labels[19]);
        drawString(screen,fontPushButtons,x0+7,146+4,true,"%s",data->Labels[19]);
    }
    else
    {
        data->grid=0;
        DrawTILE(screen,extra1,x0,146,24,24,1,71);
//        drawString(screen,font1,x0+9,146+6,"%s",data->Labels[19]);
        drawString(screen,fontPushButtons,x0+8,146+5,true,"%s",data->Labels[19]);
    }
    UpdateScreen1(x0,146,24,24);
    ScreenUpdate();
}

/*--------------------------ScreenUpdate--------------------------*/
void GraphicsEngine::ScreenUpdate(void)
{
    GlobalData* data = _GlobalData;
    /*calls SetTerrain() and updates the screen.
      Updates the bck1 surface (where the unit is), 
      and then places the unit on the screen.*/

    SetTerrain();
    UpdateScreen1(5,25,830,725);
    DrawTILE(bck1,screen,0,0,data->tw,data->th,data->stile[data->scrnum][XPOS],
             data->stile[data->scrnum][YPOS]-data->yextra-5);

    if(data->visible==1){UnitTerrainCheck(data->turn);}
            
    UpdateScreen1(data->stile[data->scrnum][XPOS],
                  data->stile[data->scrnum][XPOS]-data->yextra-5,
                  data->tw,data->th+data->yextra+5);
}

/*--------------------------RemoveExtraSpaceH---------------------*/
void GraphicsEngine::RemoveExtraSpaceH(SDL_Surface *from,int x,int y,
                                       int w,int h)
{
    GlobalData* data = _GlobalData;
    /*find the true width of the graphic,
      instead of just the tile size.*/

    int i,k;
    Uint32 ret,pink;

    data->leftspace=0;data->rightspace=0;
    pink=SDL_MapRGB(from->format,255,0,255);
	
    Slock(from);	
    for(i=x;i<x+w;i++)
    {
        for(k=y;k<y+h;k++)
        {
            ret=getpixel(from,i,k); 
            if(ret!=pink){data->leftspace=i-x;goto right;}
		}
	}

    right:
       for(i=x+w-1;i>x;i--)
       {
           for(k=y+h-1;k>y;k--)
           {
               ret=getpixel(from,i,k);
               if(ret!=pink){data->rightspace=x+w-i-1;goto Done;}
		   }
       }
    Done:	
       Sulock(from);
}

/*--------------------------RemoveExtraSpaceV--------------------*/
void GraphicsEngine::RemoveExtraSpaceV(SDL_Surface *from,int x,int y,
                                       int w,int h)
{
    GlobalData* data = _GlobalData;
    /*find the true heighth of the graphic,
      instead of just the tile size.*/

    int i,k;
    Uint32 ret,pink;

    data->topspace=0;data->bottomspace=0;
	pink=SDL_MapRGB(from->format,255,0,255);
	
    Slock(from);	
    for(i=y;i<y+h;i++)
    {
        for(k=x;k<x+w;k++)
        {
            ret=getpixel(from,k,i); 
            if(ret!=pink){data->topspace=i-y;goto bottom;}
        }
    }

    bottom:
        for(i=y+h-1;i>y;i--)
        {
            for(k=x+w-1;k>x;k--)
            {
                ret=getpixel(from,k,i);
                if(ret!=pink){data->bottomspace=y+h-i;goto Done2;}
            }
        }
	Done2:	
	    Sulock(from);
}

/*--------------------------RemoveExtraSpaceH2--------------------*/
int GraphicsEngine::RemoveExtraSpaceH2(SDL_Surface *from,int x,int y,
                                       int w,int h,int dh)
{
    /*find the distance from the graphic to the right side of the tile.
      used for placing the natioality box.*/

    int i,/*k,*/boxX=0;
    Uint32 ret,pink;

    pink=SDL_MapRGB(from->format,255,0,255);
    Slock(from);	

	for(i=x+w-1;i>x;i--)
    {
        ret=getpixel(from,i,y+h-dh);
        if(ret!=pink){boxX=x+w-i-1;break;}
   	}
   	Sulock(from);
   	return boxX;
}

/*--------------------------Buttons3------------------------------*/
void GraphicsEngine::Buttons3(SDL_Surface *font,int x1,int dx,int y1,int dy,
                              int i,int x2,int y2,int w,int h)
{
    GlobalData* data = _GlobalData;
    /* buttons useing SoLfont*/

    int swidth;

    swidth=stringWidthSoL1(data->Labels[i]);
    DrawTILE(screen,extra1,x1,y1,w,h,x2,y2);
    drawString2(screen,font,x1+dx+((w-swidth)/2),y1+dy,data->Labels[i]);
}

/*---------------------------Buttons4-----------------------------*/
void GraphicsEngine::Buttons4(SDL_Surface *font,int x1,int dx,int y1,int dy,
                              int i,int x2,int y2,int x2b,int w,int h)
{
    GlobalData* data = _GlobalData;
    /* buttons useing SoLfont*/

    if(i==7&&data->zl==0){i=8;}

    Buttons3(font,x1,dx-1,y1,dy-1,i,x2,y2,w,h);
    UpdateScreen1(x1,y1,w,h);
    SDL_Delay(100);    
    Buttons3(font,x1,dx,y1,dy,i,x2b,y2,w,h);
    UpdateScreen1(x1,y1,w,h);
}

/*---------------------------UpdateGold---------------------------*/
void GraphicsEngine::UpdateGold(char scr)
{
    GlobalData* data = _GlobalData;
    long gold = data->playerlist[data->nation]->getGold(); //added 16/6
    /*updates the gold total.*/

    int g1, g2, g3, x = 764, y = 3;

    FillRect(screen, x, y, 93, 14, 48, 48, 48);
    Border(screen, 764, 3, 92, 13);

    if(gold < 1000)
    {
        drawString2(screen, data->SoLfont1[3], x + 43, y + 3, "%3i gps", gold);
    }
    else if(gold > 999 && gold < 1000000)
    {
        g1 = gold % 1000;
        g2 = gold / 1000;

        drawString2(screen, data->SoLfont1[3], x + 15, y + 3, "%3i %03i gps", g2, g1);
    }
    else
    {
        g1 = gold % 1000;
        g2 = (gold / 1000) % 1000;
        g3 = gold / 1000000;

        drawString2(screen, data->SoLfont1[3], x + 1, y + 3, "%i %03i %03i gps", g3, g2, g1);
    }
}

/*---------------------------DefaultShipName----------------------*/
void GlobalData::DefaultShipName(short num, char array1[][25], short num2)
/*builds a string (character array) using the ship type and the 
  number of ships of that type.*/
{  
    sprintf(units_ships[shipnum].name, "%s%03i", array1[num2], num);
}

/*-------------------------ShipCharacteristics--------------------*/
void GlobalData::ShipCharacteristics(short type)
{
    /*sets up the various ship characteristics.*/
    int i;

    switch(type)
    {
        case(1):{units_ships[shipnum].capacity=200;break;}
        case(2):{units_ships[shipnum].capacity=400;break;}
        case(3):{units_ships[shipnum].capacity=600;break;}
        case(4):{units_ships[shipnum].capacity=200;break;}
        case(5):{units_ships[shipnum].capacity=400;break;}
        default:{units_ships[shipnum].capacity=600;break;}
    }

    units_ships[shipnum].passengernum=0;
    units_ships[shipnum].cargototal=0;
    units_ships[shipnum].cargonum=0;

    for(i=0;i<units_ships[shipnum].capacity;i+=100)
    {
        units_ships[shipnum].passenger[i]=0;
    }

    for(i=0;i<20;i++)
    {
        units_ships[shipnum].cargo[i][0]=0;
        units_ships[shipnum].cargo[i][1]=0;
    }
}

/*-------------------------SubtractGold---------------------------*/
void GraphicsEngine::SubtractGold(int cost)
{
    GlobalData* data = _GlobalData;
    long gold = data->playerlist[data->nation]->getGold(); //added 16/6
    data->playerlist[data->nation]->setGold(gold-cost);
    UpdateGold(0);
    UpdateScreen1(764,3,93,14);
}

/*-------------------------CheckMouseButton-----------------------*/
char GraphicsEngine::CheckMouseButton(void)
{
    GlobalData* data = _GlobalData;
    /*see if the left mouse button was released.*/

    SDL_PollEvent(&data->event);
    if(data->event.button.button==SDL_BUTTON_LEFT&&
       data->event.button.type==SDL_MOUSEBUTTONUP){return 1;}
    return 0;
}

/*-------------------------NationBox-----------------------*/
void GraphicsEngine::NationBox(int x, int y, Uint8 nation, short pos,
 Uint8 order)
{
//places nationality box next to unit

  GlobalData* data = _GlobalData;
  short bx, by, r, g, b;
  char letter[2] = { 0, 0 };
  
  NationColors(nation, r, g, b);
  
  if(pos == 1)
  { bx = 5; by = 5; }
  else if(pos == 2)
  { bx = 54; by = 5;}
  else if(pos == 3)
  { bx = 54; by = 34;}
  
  FillRect(screen, x + bx, y + by, 12, 16, 0, 0, 0);
  FillRect(screen, x + bx + 1, y + by + 1, 10, 14, r, g, b);
  letter[0] = data->msg->GetOrderLetter(order);

  drawString3(screen, data->SoLfont1[0], x + bx + 3, y + by + 4,
            0, 0, 0, 32, 32, 32, letter);
}

void GraphicsEngine::NationColors(Uint8 nation, short& r, short& g, short& b)
{
//    int nationID = (int) nation;  // For what? You don't need a direct cast - Sikon
    GlobalData* data = _GlobalData;
    if(nation < data->playerlist.size())
    {
        r = data->playerlist[nation]->Color->Red();
        g = data->playerlist[nation]->Color->Green();
        b = data->playerlist[nation]->Color->Blue();
    }
    else if(nation == NATION_TRIBE)
    { r = 160; g = 128; b = 0; }
    else // if(nationID == 99)
    {r = 80; g = 64; b = 0;}
}

//
// $Id: misc1.cpp,v 1.11 2004/06/26 11:33:43 sikon Exp $
//

