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

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"

/*-----------------------------DrawBG----------------------------*/
bool GraphicsEngine::DrawBG(void)
{
    GlobalData* data = m_pGame->GetData();
    short x,y,i;
    int x0,y0;

    SDL_Surface *bckgrnd = ImageLoad("data/graphics/bckgrnd.jpg");
    if(!bckgrnd)
    {
       cout << "bckgrnd.jpg couldn't be loaded.\n";
       return false;
    }

    /*fill the 3 surfaces with wood background*/
    for(y=0;y<screenResY;y+=256)
    {
        for(x=0;x<screenResX;x+=256)
        {
            DrawSURF(map1,bckgrnd,x,y);
            DrawSURF(cds1,bckgrnd,x,y);
            DrawSURF(hcs1,bckgrnd,x,y);
        }
    }
    SDL_FreeSurface(bckgrnd);

    /*put map1 surface on screen*/
    DrawSURF(screen,map1,0,0);

    /*put menu buttons at top of screen; then put labels on them*/
    x0=5;y0=2;
    for(x=5;x<386;x+=76){DrawTILE(screen,extra1,x,y0,76,18,267,52);}

    drawString(screen,fontPushButtons,x0+19,y0,true,"%s",data->Labels[0]);

    drawString(screen,fontPushButtons,x0+101,y0,true,"%s",data->Labels[1]);

    drawString(screen,fontPushButtons,x0+171,y0,true,"%s",data->Labels[2]);

    drawString(screen,fontPushButtons,x0+243,y0,true,"%s",data->Labels[3]);

    drawString(screen,fontPushButtons,x0+325,y0,true,"%s",data->Labels[4]);

    drawString(screen,fontPushButtons,x0+390,y0,true,"%s",data->Labels[7]);

    DrawTILE(screen,extra1,x0+456,y0,132,18,1,52);
    drawString(screen,fontPushButtons,x0+489,y0,true,"%s",data->Labels[5]);

    DrawTILE(screen,extra1,x0+938,y0,76,18,267,52);
    drawString(screen,fontPushButtons,x0+957,y0,true,"%s",data->Labels[6]);

    /*put the 'order' buttons on right side of screen*/
    i=9;x=990;
    for(y=50;y<194;y+=24)
    {
        if(i==13){i=19;}
        DrawTILE(screen,extra1,x,y,24,24,1,71);
        drawString(screen,fontPushButtons,x+7,y+4,true,"%s",data->Labels[i]);
        i++;
    }

    /*put the 'screen buttons at bottom*/
    i=13;y=734;
    for(x=438;x<537;x+=49)
    {
        DrawTILE(screen,extra1,x,y,49,24,51,71);
        drawString(screen,fontPushButtons,x+12,y+4,true,"%s",data->Labels[i]);
        i++;
    }
  
    /*prepare the HCS & CDS screens*/
    DrawHCS();
    DrawCDS();

    /*copy part of main screen for use with 'zoom' function*/
    DrawTILE(mapback,screen,0,0,836,708,0,20);

    return true;
}


//
// $Id: bckgrnd.cpp,v 1.9 2004/06/23 15:37:05 sikon Exp $
//

