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

/*---------------------------DrawCDSMarket-------------------------*/
void GraphicsEngine::DrawCDSMarket(int x0,int y0)
{
    int x,x1;

    FillRect(cds1,x0,y0,657+34,55,162,162,162);

    DrawTILE(cds1,extra1,x0,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x0+5,y0+21,7,13,67,132);
    DrawTILE(cds1,extra1,x0+657+17,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x0+657+17+6,y0+21,7,13,75,132);

    x1=1;
    for(x=x0+18;x<x0+674;x+=41)
    {
        FillRect(cds1,x,y0+1,40,53,48,48,48);
        DrawTILE(cds1,extra1,x,y0-3,40,50,x1+5,1);
        x1+=51;
    }
    Border(cds1,x0,y0,656+34,54);
}

/*---------------------------DrawCDSSlots-------------------------*/
void GraphicsEngine::DrawCDSSlots(int x0,int y0)
{
    GlobalData* data = m_pGame->GetData();

    int y,swidth,/*r1=150,g1=170,b1=120,r2=110,g2=140,b2=90,
                        r3=90,g3=120,b3=70,r4=70,g4=90,b4=40,
                        r5=50,g5=80,b5=60,*/r6=64,g6=64,b6=64;

/*puts 'grass' background in building display block*/

    /*first column*/
    for(y=y0;y<y0+361;y+=120)
    {
        DrawTILE(cds1,buildings1,x0,y,120,120,1,1);
        DrawTILE(cds1,buildings1,x0+120,y,120,120,1,1);
        DrawTILE(cds1,buildings1,x0+400,y,120,120,1,1);
    }

    /*second column*/
    for(y=y0;y<y0+321;y+=160)
    {
        DrawTILE(cds1,buildings1,x0+240,y,160,160,484,485);
    }

    /*third column*/
    for(y=y0;y<y0+241;y+=120)
    {
        DrawTILE(cds1,buildings1,x0+520,y,120,120,1,1);
        DrawTILE(cds1,buildings1,x0+640,y,120,120,1,1);
    }

    /*docks*/
    DrawTILE(cds1,buildings1,x0+520,y0+360,240,120,483,646);

    /*fence area*/
    FillRect(cds1,x0,y0+480,760,100,r6,g6,b6);

    /*under orders*/
    DrawTILE(cds1,extra1,x0,y0+480,52,17,63,96);
    DrawTILE(cds1,extra1,x0+177,y0+480,52,17,63,96);

    DrawTILE(cds1,extra1,x0+17,y0+480+6,14,7,37,136);
    DrawTILE(cds1,extra1,x0+21+177,y0+480+6,14,7,52,136);

    DrawTILE(cds1,extra1,x0+52,y0+480,125,17,169,96);
    swidth=stringWidthSoL1(data->Labels[31]);
    drawString2(cds1,data->SoLfont1[2],x0+((125-swidth)/2)+4+52,
                y0+4+480,data->Labels[31]);

    /*unassigned*/
    DrawTILE(cds1,extra1,x0+265,y0+480,52,17,63,96);
    DrawTILE(cds1,extra1,x0+265+17,y0+480+6,14,7,37,136);

    DrawTILE(cds1,extra1,x0+317,y0+480,125,17,169,96);
    swidth=stringWidthSoL1(data->Labels[32]);
    drawString2(cds1,data->SoLfont1[2],x0+((125-swidth)/2)+4+317,
                y0+4+480,data->Labels[32]);

    DrawTILE(cds1,extra1,x0+442,y0+480,52,17,63,96);
    DrawTILE(cds1,extra1,x0+21+442,y0+480+6,14,7,52,136);

    /*transports*/
    DrawTILE(cds1,extra1,x0+531,y0+480,52,17,63,96);
    DrawTILE(cds1,extra1,x0+531+17,y0+480+6,14,7,37,136);

    DrawTILE(cds1,extra1,x0+583,y0+480,125,17,169,96);
    swidth=stringWidthSoL1(data->Labels[33]);
    drawString2(cds1,data->SoLfont1[2],x0+((125-swidth)/2)+4+583,
                y0+4+480,data->Labels[33]);

    DrawTILE(cds1,extra1,x0+708,y0+480,52,17,63,96);
    DrawTILE(cds1,extra1,x0+21+708,y0+480+6,14,7,52,136);

    Border(cds1,x0,y0,759,579);
}

/*---------------------------DrawCDSConstruction------------------*/
void GraphicsEngine::DrawCDSConstruction(int x0,int y0)
{
    FillRect(cds1,x0,y0,242,254,64,64,64);
    Border(cds1,x0,y0,241,253);           
}

/*---------------------------DrawCDSFields------------------------*/
void GraphicsEngine::DrawCDSFields(int x0,int y0)
{
    FillRect(cds1,x0-12,y0-26,242,182,0,0,0);
    Border(cds1,x0-12,y0-26,241,181);           
}

/*---------------------------DrawCDSProduction--------------------*/
void GraphicsEngine::DrawCDSProduction(int x0,int y0)
{
    FillRect(cds1,x0,y0,242,255,64,64,64);
    Border(cds1,x0,y0,241,254);           
}

/*---------------------------DrawCDSMapButton--------------------*/
void GraphicsEngine::DrawCDSMapButton(int x0,int y0)
{           
    GlobalData* data = m_pGame->GetData();

    DrawTILE(cds1,extra1,x0,y0,76,18,267,52);
    //drawString(cds1,font1,x0+27,y0+1,"%s",data->Labels[15]);
    drawString(cds1,fontPushButtons,x0+26,y0,true,"%s",data->Labels[15]);          
}

/*---------------------------DrawCDSSelected--------------------*/
void GraphicsEngine::DrawCDSSelected(int x0,int y0)
{
    GlobalData* data = m_pGame->GetData();

    int x1,x2;

    FillRect(cds1,x0,y0,691,55,128,128,192);
    Border(cds1,x0,y0,690,54);

    FillRect(cds1,x0+1,y0+1,209,12,48,48,48);
    FillRect(cds1,x0+1,y0+14,209,12,48,48,48);
    FillRect(cds1,x0+1,y0+27,209,12,48,48,48);

    drawString2(cds1,data->SoLfont1[3],x0+3,y0+1+2,"Name:");
    drawString2(cds1,data->SoLfont1[3],x0+3,y0+1+2+12,"Type:");
    drawString2(cds1,data->SoLfont1[3],x0+3,y0+1+2+26,"Capacity:");

    /*capacity bar*/  
    FillRect(cds1,x0+1,y0+40,209,14,48,48,48);
    FillRect(cds1,x0+2,y0+41,207,12,0,0,0);
    FillRect(cds1,x0+3,y0+42,205,10,50,140,20);  

    /*pass. display*/
    x1=x0+211;  
    FillRect(cds1,x1+18,y0,204,55,16,80,32);

    DrawTILE(cds1,extra1,x1,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x1+5,y0+21,7,13,67,132);
    DrawTILE(cds1,extra1,x1+223,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x1+223+6,y0+21,7,13,75,132);

    /*cargo display*/
    x2=x0+211+240;  
    FillRect(cds1,x2+18,y0,204,55,48,48,48);

    DrawTILE(cds1,extra1,x2,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x2+5,y0+21,7,13,67,132);
    DrawTILE(cds1,extra1,x2+223,y0,17,55,781,89);
    DrawTILE(cds1,extra1,x2+223+6,y0+21,7,13,75,132);      
}


//
// $Id: Drawcds1.cpp,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

