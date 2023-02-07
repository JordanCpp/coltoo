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
#include <cstring>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"

/*---------------------------Counter1-----------------------------*/
void GraphicsEngine::Counter1(SDL_Surface *temp,int x,int y)
{
    GlobalData* data = m_pGame->GetData();

    FillRect(temp,x,y,64,116,48,48,48);
    FillRect(temp,x+46,y+79,12,26,191,112,32);
    Border(temp,x,y,63,115);
    Border(temp,x+5,y+82,42,19);

    DrawTILE(temp,extra1,x+4,y+5,13,13,51,122);
    DrawTILE(temp,extra1,x+4,y+23,13,13,37,122);
    DrawTILE(temp,extra1,x+4,y+41,13,13,51,122);
    DrawTILE(temp,extra1,x+4,y+59,13,13,51,122);

    drawString2(temp,data->SoLfont1[3],x+24,y+8,"50");
    drawString2(temp,data->SoLfont1[3],x+19,y+26,"100");
    drawString2(temp,data->SoLfont1[3],x+20,y+44,"All");
    drawString2(temp,data->SoLfont1[3],x+20,y+62,"Custom");
    drawString3(temp,data->SoLfont1[0],x+17,y+88,0,0,0,0,0,0,"%d",data->counter);

    DrawTILE(temp,extra1,x+46,y+80,12,12,37,109);
    DrawTILE(temp,extra1,x+47,y+92,12,12,37,109);
    DrawTILE(temp,extra1,x+46,y+81,12,12,37,96);
    DrawTILE(temp,extra1,x+47,y+93,12,12,50,96);
}

/*---------------------------Counter2-----------------------------*/
void GraphicsEngine::Counter2(char num,char counterspace,int x,int y)
{
    GlobalData* data = m_pGame->GetData();

    char x1,x2,x3,x4;

    switch(num)
    {
        case(1):{x1=37;x2=51;x3=51;x4=51;break;}
        case(2):{x1=51;x2=37;x3=51;x4=51;break;}
        case(3):{x1=51;x2=51;x3=37;x4=51;break;}
        default:{x1=51;x2=51;x3=51;x4=37;}
    }

    DrawTILE(screen,extra1,x+4,y+5,13,13,x1,122);
    DrawTILE(screen,extra1,x+4,y+23,13,13,x2,122);
    DrawTILE(screen,extra1,x+4,y+41,13,13,x3,122);
    DrawTILE(screen,extra1,x+4,y+59,13,13,x4,122);

    if(num==4)
    {
        FillRect(screen,x+5,y+82,41,20,225,225,225);
        drawString3(screen,data->SoLfont1[0],x+17+counterspace,y+88,0,0,0,
                    96,64,16,"%d",data->counter);
    }
    else
    {  
        FillRect(screen,x+5,y+82,41,20,48,48,48);
        drawString3(screen,data->SoLfont1[0],x+17+counterspace,y+88,
                    0,0,0,0,0,0,"%d",data->counter);
    }
    UpdateScreen1(x,y,64,116);
}

/*---------------------------Counter3-----------------------------*/
char GraphicsEngine::Counter3(void)
{
    GlobalData* data = m_pGame->GetData();

    if(data->counter<10){return 14;}
    if(data->counter>99){return 0;}
    return 7;
}

/*---------------------------Counter4-----------------------------*/
void GraphicsEngine::Counter4(int x,int y,char counterspace)
{
    GlobalData* data = m_pGame->GetData();

    FillRect(screen,x+5,y+82,41,20,225,225,225);
    drawString3(screen,data->SoLfont1[0],x+17+counterspace,y+88,0,0,0,
                96,64,16,"%d",data->counter);
    UpdateScreen1(x,y,64,116);     
    SDL_Delay(125);
}


//
// $Id: deuro4.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

