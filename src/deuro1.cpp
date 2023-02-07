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

/*---------------------------DrawMarket1----------------------------*/
void GraphicsEngine::DrawMarket1(void)
{
    GlobalData* data = m_pGame->GetData();
    int x,/*y,*/x1,i,swidth,x0,y0;

    x0=166;y0=676;

    FillRect(hcs1,x0,y0,657+34,55,162,162,162);

    DrawTILE(hcs1,extra1,x0,y0,17,55,781,89);
    DrawTILE(hcs1,extra1,x0+5,y0+21,7,13,67,132);
    DrawTILE(hcs1,extra1,x0+657+17,y0,17,55,781,89);
    DrawTILE(hcs1,extra1,x0+657+17+6,y0+21,7,13,75,132);

    x1=1;i=0;
    for(x=x0+18;x<x0+674;x+=41)
    {
        FillRect(hcs1,x,y0+1,40,53,48,48,48);
        DrawTILE(hcs1,extra1,x,y0-3,40,50,x1+5,1);
        x1+=51;

        swidth=(40-stringWidthSoL1("%d/%d",data->price[i][0],
                                   data->price[i][1]))/2; 
        drawString2(hcs1,data->SoLfont1[3],x+swidth,y0+1+40,"%d/%d",
                    data->price[i][0],data->price[i][1]);
    i++;
  }
  Border(hcs1,x0,y0,656+34,54);
}

/*---------------------------HCSButtons----------------------------*/
void GraphicsEngine::HCSButtons(void)
{
    GlobalData* data = m_pGame->GetData();

    int x,/*y,i,*/x1,y1,swidth;

    x1=643;y1=222;

    DrawTILE(hcs1,extra1,x1,y1,76,18,344,52);

    for(x=x1+76;x<x1+153;x+=76)
    {DrawTILE(hcs1,extra1,x,y1,76,18,267,52);}

    swidth=stringWidthSoL1(data->Labels[16]);
    drawString2(hcs1,data->SoLfont1[1],x1+((76-swidth)/2)+4,y1+4,
                data->Labels[16]);
                  
    swidth=stringWidthSoL1(data->Labels[17]);
    drawString2(hcs1,data->SoLfont1[1],x1+((76-swidth)/2)+4+76,y1+5,
                data->Labels[17]);

    swidth=stringWidthSoL1(data->Labels[18]);
    drawString2(hcs1,data->SoLfont1[1],x1+((76-swidth)/2)+4+152,y1+5,
                data->Labels[18]);

    Border(hcs1,x1,y1,228,17);
}

/*---------------------------HCSDRecruit----------------------------*/
void GraphicsEngine::HCSDRecruit(void)
{
    GlobalData* data = m_pGame->GetData();

    int i,x1=3,y1=3,swidth;

    FillRect(HCSWin[1],x1,y1,229,88,128,192,128);
    Border(HCSWin[1],x1,y1,228,104);

    DrawTILE(HCSWin[1],extra1,x1,y1+88,229,17,327,71);

    swidth=stringWidthSoL1(data->Labels[23]);
    drawString2(HCSWin[1],data->SoLfont1[1],x1+((229-swidth)/2)+4,y1+88+4,
                data->Labels[23]);  

    for(i=0;i<3;i++){data->recruit[i]=RecruitSelection1();}

    HCSDRecruitHL(0);
}

/*---------------------------HCSDPurchase--------------------------*/
void GraphicsEngine::HCSDPurchase(void)
{
    GlobalData* data = m_pGame->GetData();

    int /*x,y,i,*/x1=3,y1=3,swidth;

    FillRect(HCSWin[2],x1,y1,229,88,128,192,128);
    Border(HCSWin[2],x1,y1,228,104);

    DrawTILE(HCSWin[2],extra1,x1,y1+88,52,17,63,96);
    DrawTILE(HCSWin[2],extra1,x1+177,y1+88,52,17,63,96);
    DrawTILE(HCSWin[2],extra1,x1+52,y1+88,125,17,421,52);

    DrawTILE(HCSWin[2],extra1,x1+17,y1+88+6,14,7,37,136);
    DrawTILE(HCSWin[2],extra1,x1+21+177,y1+88+6,14,7,52,136);

    swidth=stringWidthSoL1(data->Labels[21]);
    drawString2(HCSWin[2],data->SoLfont1[1],x1+((229-swidth)/2)+4,y1+88+4,
                data->Labels[21]);

    HCSDNewUnitHL(0,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
}

/*---------------------------HCSDTrain----------------------------*/
void GraphicsEngine::HCSDTrain(void)
{
    GlobalData* data = m_pGame->GetData();

    int /*x,y,i,*/x1=3,y1=3,swidth;

    FillRect(HCSWin[3],x1,y1,229,88,128,192,128);
    Border(HCSWin[3],x1,y1,228,104);

    DrawTILE(HCSWin[3],extra1,x1,y1+88,52,17,63,96);
    DrawTILE(HCSWin[3],extra1,x1+177,y1+88,52,17,63,96);
    DrawTILE(HCSWin[3],extra1,x1+52,y1+88,125,17,421,52);

    DrawTILE(HCSWin[3],extra1,x1+17,y1+88+6,14,7,37,136);
    DrawTILE(HCSWin[3],extra1,x1+21+177,y1+88+6,14,7,52,136);

    swidth=stringWidthSoL1(data->Labels[22]);
    drawString2(HCSWin[3],data->SoLfont1[1],x1+((229-swidth)/2)+4,y1+88+4,
                data->Labels[22]);

  HCSDNewUnitHL(0,HCSWin[3],data->Tstart,data->Jobs,data->JobsCost,1);
}

/*---------------------------HCSDRecruitHL--------------------------*/
void GraphicsEngine::HCSDRecruitHL(short recruitHL)
{
    GlobalData* data = m_pGame->GetData();

    int r1=32,g1=120,b1=48,r2=16,g2=80,b2=32,x1=3,y1=3/*,length,dx*/,x,i,swidth;

    FillRect(HCSWin[1],x1,y1+61,229,27,128,192,128);
    FillRect(HCSWin[1],x1+1,y1+62,227,12,48,48,48);
    FillRect(HCSWin[1],x1+1,y1+75,227,12,48,48,48);

    drawString2(HCSWin[1],data->SoLfont1[3],x1+3,y1+64,"Unit:");
    drawString2(HCSWin[1],data->SoLfont1[3],x1+3,y1+77,"Cost:");

    switch(recruitHL)
    {
        case(0):
        {
            FillRect(HCSWin[1],x1+1,y1+1,75,60,r1,g1,b1);
            FillRect(HCSWin[1],x1+1+76,y1+1,75,60,r2,g2,b2);
            FillRect(HCSWin[1],x1+1+152,y1+1,75,60,r2,g2,b2);
            break;
        }
        case(1):
        {
            FillRect(HCSWin[1],x1+1,y1+1,75,60,r2,g2,b2);
            FillRect(HCSWin[1],x1+1+76,y1+1,75,60,r1,g1,b1);
            FillRect(HCSWin[1],x1+1+152,y1+1,75,60,r2,g2,b2);
            break;
        }
        default:
        {
            FillRect(HCSWin[1],x1+1,y1+1,75,60,r2,g2,b2);
            FillRect(HCSWin[1],x1+1+76,y1+1,75,60,r2,g2,b2);
            FillRect(HCSWin[1],x1+1+152,y1+1,75,60,r1,g1,b1);
        }
    }
  
    i=0;
    for(x=x1+1;x<x1+226;x+=76)
    {
        DrawTILE(HCSWin[1],uniticons,x-2,y1+5,75,50,
                 data->tile50[data->recruit[i]][0],
                 data->tile50[data->recruit[i]][1]);
        i++;
    }

    swidth=((227-stringWidthSoL1("Unit:"))-
    stringWidthSoL1(data->Jobs[data->recruit[recruitHL]]))/2;  
  
    drawString2(HCSWin[1],data->SoLfont1[3],x1+stringWidthSoL1("Unit:")+
                swidth+4,y1+64,data->Jobs[data->recruit[recruitHL]]);

    swidth=((227-stringWidthSoL1("Cost:"))-
             stringWidthSoL1("%d",data->recruitcost))/2;
  
    drawString2(HCSWin[1],data->SoLfont1[3],x1+stringWidthSoL1("Cost:")+
                swidth,y1+77,"%d",data->recruitcost); 
}

/*---------------------------HCSDNewUnitHL-------------------------*/
void GraphicsEngine::HCSDNewUnitHL(short newunitHL,SDL_Surface *temp,int Ustart,
                    char array1[][25],char array2[][25],char TorP)
{
    GlobalData* data = m_pGame->GetData();

    int r1=32,g1=120,b1=48,r2=16,g2=80,b2=32,x1=3,y1=3,/*length,*/swidth,x,i;

    FillRect(temp,x1,y1+61,229,27,128,192,128);
    FillRect(temp,x1+1,y1+62,227,12,48,48,48);
    FillRect(temp,x1+1,y1+75,227,12,48,48,48);

    drawString2(temp,data->SoLfont1[3],x1+3,y1+64,"Unit:");
    drawString2(temp,data->SoLfont1[3],x1+3,y1+77,"Cost:");

    if(TorP==0&&Ustart>0){r1=48;g1=96;b1=192;r2=16;g2=32;b2=64;}

    switch(newunitHL)
    {
        case(0):
        {
            if(TorP==0&&Ustart==0){r2=16;g2=32;b2=64;}
            FillRect(temp,x1+1,y1+1,75,60,r1,g1,b1);
            FillRect(temp,x1+1+76,y1+1,75,60,r2,g2,b2);
            FillRect(temp,x1+1+152,y1+1,75,60,r2,g2,b2);
            break;
        }
        case(1):
        {
            FillRect(temp,x1+1,y1+1,75,60,r2,g2,b2);
            if(TorP==0&&Ustart==0){r1=48;g1=96;b1=192;r2=16;g2=32;b2=64;}
            FillRect(temp,x1+1+76,y1+1,75,60,r1,g1,b1);
            FillRect(temp,x1+1+152,y1+1,75,60,r2,g2,b2);
            break;
        }
        default:
        {
            FillRect(temp,x1+1,y1+1,75,60,r2,g2,b2);
            if(TorP==0&&Ustart==0){r1=48;g1=96;b1=192;r2=16;g2=32;b2=64;}
            FillRect(temp,x1+1+76,y1+1,75,60,r2,g2,b2);
            FillRect(temp,x1+1+152,y1+1,75,60,r1,g1,b1);
        }
    }

    i=Ustart;
    for(x=x1+1;x<x1+226;x+=76)
    {
        if(TorP==0)
        {
            DrawTILE(temp,uniticons,x-2,y1+5,75,50,
                     data->tile50[i+36][0],data->tile50[i+36][1]);
        }
        else
        {
            DrawTILE(temp,uniticons,x-2,y1+5,75,50,data->tile50[i][0],
                     data->tile50[i][1]);
        }
        i++;
    }

    swidth=((227-stringWidthSoL1("Unit:"))-
              stringWidthSoL1(array1[Ustart+newunitHL]))/2;  

    drawString2(temp,data->SoLfont1[3],x1+stringWidthSoL1("Unit:")+swidth+4,
                y1+64,array1[Ustart+newunitHL]);

    swidth=((227-stringWidthSoL1("Cost:"))-
             stringWidthSoL1(array2[Ustart+newunitHL]))/2;

    drawString2(temp,data->SoLfont1[3],x1+stringWidthSoL1("Cost:")+swidth+4,
                y1+77,array2[Ustart+newunitHL]);
}


//
// $Id: deuro1.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

