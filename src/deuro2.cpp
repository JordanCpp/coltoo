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
#include <cstring>

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"

/*---------------------------DrawDocks1---------------------------*/
void GraphicsEngine::DrawDocks1(void)
{
    GlobalData* data = m_pGame->GetData();

    int x0=10,y0=196,/*dx,*/swidth;

    /*Port*/
    x0=398;y0=368;
    FillRect(hcs1,x0,y0+17,229,60,16,32,64);
    Border(hcs1,x0,y0,228,93);

    DrawTILE(hcs1,extra1,x0,y0,229,17,327,89);
    swidth=stringWidthSoL1(data->Labels[29]);
    drawString2(hcs1,data->SoLfont1[2],x0+((229-swidth)/2)+4,y0+4,
                data->Labels[29]);

    DrawTILE(hcs1,extra1,x0,y0+60+17,52,17,63,96);
    DrawTILE(hcs1,extra1,x0+177,y0+60+17,52,17,63,96);

    DrawTILE(hcs1,extra1,x0+17,y0+60+6+17,14,7,37,136);
    DrawTILE(hcs1,extra1,x0+21+177,y0+60+6+17,14,7,52,136);

    DrawTILE(hcs1,extra1,x0+52,y0+60+17,125,17,421,52);
    swidth=stringWidthSoL1(data->Labels[24]);
    drawString2(hcs1,data->SoLfont1[1],x0+((125-swidth)/2)+5+52,
                y0+4+77,data->Labels[24]);

    /*Docks*/
    x0=643;
    FillRect(hcs1,x0,y0+17,230,60,16,80,32);
    Border(hcs1,x0,y0,229,93);

    DrawTILE(hcs1,extra1,x0,y0,229,17,327,89);
    swidth=stringWidthSoL1(data->Labels[30]);
    drawString2(hcs1,data->SoLfont1[2],x0+((229-swidth)/2)+4,y0+4,
                data->Labels[30]);

    DrawTILE(hcs1,extra1,x0+52,y0+60+17,63,17,65,114);
    swidth=stringWidthSoL1(data->Labels[25]);
    drawString2(hcs1,data->SoLfont1[1],x0+((63-swidth)/2)+5+52,
                y0+4+77,data->Labels[25]);

    DrawTILE(hcs1,extra1,x0+52+63,y0+60+17,63,17,65,114);
    swidth=stringWidthSoL1(data->Labels[26]);
    drawString2(hcs1,data->SoLfont1[1],x0+((63-swidth)/2)+5+52+63,
                y0+4+77,data->Labels[26]);

    DrawTILE(hcs1,extra1,x0,y0+60+17,52,17,63,96);
    DrawTILE(hcs1,extra1,x0+178,y0+60+17,52,17,63,96);

    DrawTILE(hcs1,extra1,x0+17,y0+60+6+17,14,7,37,136);
    DrawTILE(hcs1,extra1,x0+21+178,y0+60+6+17,14,7,52,136);

    /*sailed*/
    x0=153;
    FillRect(hcs1,x0,y0+17,229,60,16,32,64);
    Border(hcs1,x0,y0,228,76);

    DrawTILE(hcs1,extra1,x0,y0,52,17,63,96);
    DrawTILE(hcs1,extra1,x0+177,y0,52,17,63,96);

    DrawTILE(hcs1,extra1,x0+17,y0+6,14,7,37,136);
    DrawTILE(hcs1,extra1,x0+21+177,y0+6,14,7,52,136);

    DrawTILE(hcs1,extra1,x0+52,y0,125,17,169,96);
    swidth=stringWidthSoL1(data->Labels[27]);
    drawString2(hcs1,data->SoLfont1[2],x0+((125-swidth)/2)+4+52,
                y0+4,data->Labels[27]);

    /*due soon*/
    y0=275;
    FillRect(hcs1,x0,y0+17,229,60,16,32,64);
    Border(hcs1,x0,y0,228,76);

    DrawTILE(hcs1,extra1,x0,y0,52,17,63,96);
    DrawTILE(hcs1,extra1,x0+177,y0,52,17,63,96);

    DrawTILE(hcs1,extra1,x0+17,y0+6,14,7,37,136);
    DrawTILE(hcs1,extra1,x0+21+177,y0+6,14,7,52,136);

    DrawTILE(hcs1,extra1,x0+52,y0,125,17,169,96);
    swidth=stringWidthSoL1(data->Labels[28]);
    drawString2(hcs1,data->SoLfont1[2],x0+((125-swidth)/2)+4+52,
                y0+4,data->Labels[28]);
}

/*---------------------------PlaceNUDocks1-------------------------*/
int GraphicsEngine::PlaceNUDocks1(int x,int y1,char &Zstart,char ZIndex,
                    char Zarray[],SDL_Surface *temp)
{
    GlobalData* data = m_pGame->GetData();

    int /*i,*/w,ii,xx,w2=0,bx=0,w3=0,dx,bx2=0,w4=0,dx2=0;

    xx=x;
    FillRect(temp,x,y1,230,60,16,80,32);

    for(ii=Zstart;ii<ZIndex;ii++)
    {
        RemoveExtraSpaceH(uniticons,data->tile50[Zarray[ii]][0],
                          data->tile50[Zarray[ii]][1],75,50);
        w=75-data->leftspace-data->rightspace;

        bx=RemoveExtraSpaceH2(uniticons,data->tile50[Zarray[ii]][0],
                              data->tile50[Zarray[ii]][1],75,50,8);
        w3=75-data->leftspace-bx;
        if(w>w3+14){dx=5+w;}
        else{dx=5+w3+14;}

        if(xx+dx>x+225)
        {
            while(xx+dx-dx2>x+225)
            {
                RemoveExtraSpaceH(uniticons,data->tile50[Zarray[Zstart]][0],
                                  data->tile50[Zarray[Zstart]][1],75,50);
                w2=75-data->leftspace-data->rightspace;

                bx2=RemoveExtraSpaceH2(uniticons,data->tile50[Zarray[Zstart]][0],
                                       data->tile50[Zarray[Zstart]][1],75,50,8);
                w4=75-data->leftspace-bx2+14;
                if(w2>w4){dx2+=w2;}
                else{dx2+=w4;}
                Zstart++;
                if(Zstart>ZIndex-1){Zstart=ZIndex-1;}
            }
            return 1;
        }

        if(ii==Zstart){FillRect(temp,x+2,y1+2,w3+6+14,56,32,120,48);}

        FillRect(temp,xx+5+w3+2,y1+2+37,12,16,0,0,0);
        short r, g, b;
        NationColors(data->nation, r, g, b);
        FillRect(temp, xx + 5 + w3 + 3, y1 + 2 + 37 + 1, 10, 14, r, g, b);

        drawString3(screen,data->SoLfont1[0],xx+5+w3+5,y1+2+37+4,0,0,0,32,32,32,"-");    

        DrawTILE(temp,uniticons,xx+5,y1+5,w,50,data->tile50[Zarray[ii]][0]+
                 data->leftspace,data->tile50[Zarray[ii]][1]);
        if(w>w3+14){xx+=5+w;}
        else{xx+=5+w3+14;}
    }
    return 0;
}

/*---------------------------HCSArrowButtons--------------------*/
void GraphicsEngine::HCSArrowButtons(int x1,int y1,int dx,int dy,int w1,int h1,
                        int x2,int y2,int dx2,int dy2,int w2,int h2,
                        int x3,int y3)
{
    DrawTILE(screen,extra1,x1+dx,y1+dy,w1,h1,x2,y2);
    DrawTILE(screen,extra1,x1+dx2,y1+dy2,w2,h2,x3,y3);
    UpdateScreen1(x1+dx,y1+dy,w1,h1);
}

/*---------------------------PTArrowShift-------------------------*/
void GraphicsEngine::PTArrowShift(short &Zstart,char &ZHL,int i,int ii,
                  char array1[][25],char array2[][25],
                  char TorP,int x0,int y0,int w,int h,char limit,
                  char dz,char newhl)
{
    GlobalData* data = m_pGame->GetData();
    Zstart=Zstart+dz;ZHL=newhl;data->HLCheckOld[i]=-1;

    if(dz<0){if(Zstart<limit){Zstart=limit;}}
    else{if(Zstart>limit){Zstart=limit;}}

    HCSDNewUnitHL(ZHL,HCSWin[ii],Zstart,array1,array2,TorP);
    DrawSURF(screen,HCSWin[ii],x0,y0);
    UpdateScreen1(x0,y0,w,h);
}

/*---------------------------BuyHireButton-----------------------*/
void GraphicsEngine::BuyHireButton(char &ZIndex,char &Zstart,char array[],int x,
                    int y1,SDL_Surface *temp,short n)
{
  if(x==643)
  {
    if(PlaceNUDocks1(x,y1,Zstart,ZIndex,array,temp))
    {PlaceNUDocks1(x,y1,Zstart,ZIndex,array,temp);}
  }
  else
  {
    if(PlaceNUDocks2(x,y1,Zstart,ZIndex,array,temp,n))
    {PlaceNUDocks2(x,y1,Zstart,ZIndex,array,temp,n);}    
  }
  if(temp==screen){UpdateScreen1(x,y1,230,60);}
}

/*---------------------------PlaceNUDocks2-------------------------*/
int GraphicsEngine::PlaceNUDocks2(int x,int y1,char &Zstart,char ZIndex,
                    char Zarray[],SDL_Surface *temp,short n)
{
    GlobalData* data = m_pGame->GetData();

    int /*i,*/w,ii,xx,w2=0,bx=0,w3=0,dx,bx2=0,w4=0,dx2=0,w5;

    xx=x;
    FillRect(temp,x,y1,229,60,16,32,64);

    for(ii=Zstart;ii<ZIndex;ii++)
    {
        RemoveExtraSpaceH(uniticons,data->tile50[Zarray[ii]][0],
                          data->tile50[Zarray[ii]][1],75,50);
        w=75-data->leftspace-data->rightspace;

        bx=RemoveExtraSpaceH2(uniticons,data->tile50[Zarray[ii]][0],
                              data->tile50[Zarray[ii]][1],75,50,35);
        w3=75-data->leftspace-bx;
        if(w>w3+14){dx=5+w;}
        else{dx=5+w3+14;}

        if(xx+dx>x+225)
        {
            while(xx+dx-dx2>x+225)
            {
                RemoveExtraSpaceH(uniticons,data->tile50[Zarray[Zstart]][0],
                                  data->tile50[Zarray[Zstart]][1],75,50);
                w2=75-data->leftspace-data->rightspace;

                bx2=RemoveExtraSpaceH2(uniticons,data->tile50[Zarray[Zstart]][0],
                                       data->tile50[Zarray[Zstart]][1],75,50,35);
                w4=75-data->leftspace-bx2+14;
                if(w2>w4){dx2+=w2;}
                else{dx2+=w4;}
                Zstart++;
                if(Zstart>ZIndex-1){Zstart=ZIndex-1;}
            }
            return 1;
        }

        if(ii==Zstart)
        {
            if(w>w3+14){w5=w;}else{w5=w3+14;}
            FillRect(temp,x+2,y1+2,w5+6,56,48,96,192);
        }

        FillRect(temp,xx+5+w3+2,y1+2+10,12,16,0,0,0);
        short r, g, b;
        NationColors(data->nation, r, g, b);
        FillRect(temp, xx + w3 + 8, y1 + 13, 10, 14, r, g, b);

        if(data->units_ships[n].cargonum==0)
        {
            drawString3(temp,data->SoLfont1[0],xx+5+w3+5,y1+2+10+4,
                        0,0,0,32,32,32,"-");
        }
        else
        {
            drawString3(temp,data->SoLfont1[0],xx+5+w3+5,y1+2+10+4,
                        0,0,0,32,32,32,"%d",data->units_ships[n].cargonum);
        }

        DrawTILE(temp,uniticons,xx+5,y1+5,w,50,data->tile50[Zarray[ii]][0]+
                               data->leftspace,data->tile50[Zarray[ii]][1]);
        if(w>w3+14){xx+=5+w;}
        else{xx+=5+w3+14;}
    }
    return 0;
}


//
// $Id: deuro2.cpp,v 1.4 2004/06/23 15:37:05 sikon Exp $
//

