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

/*---------------------------SelectedShip1------------------------*/
void GraphicsEngine::SelectedShip1(void)
{
  GlobalData *data = _GlobalData;

  int x0=392,y0=478,swidth;

  FillRect(hcs1,x0,y0+17,240,165,128,128,192);
  FillRect(hcs1,x0+1,y0+18,238,12,48,48,48);
  FillRect(hcs1,x0+1,y0+31,238,12,48,48,48);
  FillRect(hcs1,x0+1,y0+44,238,12,48,48,48);
  Border(hcs1,x0,y0,239,181);
  
  DrawTILE(hcs1,extra1,x0,y0,240,17,193,114);
  swidth=stringWidthSoL1("Selected Ship");
  drawString2(hcs1,data->SoLfont1[2],x0+((240-swidth)/2),y0+4,
                "Selected Ship");
    
  drawString2(hcs1,data->SoLfont1[3],x0+3,y0+18+2,"Name:");
  drawString2(hcs1,data->SoLfont1[3],x0+3,y0+18+2+12,"Type:");
  drawString2(hcs1,data->SoLfont1[3],x0+3,y0+18+2+26,"Passengers:");
  drawString2(hcs1,data->SoLfont1[3],x0+3+128,y0+18+2+26,"Cargo:");

  FillRect(hcs1,x0+18,y0+57,204,55,16,80,32);
  
  DrawTILE(hcs1,extra1,x0,y0+57,17,55,781,89);
  DrawTILE(hcs1,extra1,x0+5,y0+57+21,7,13,67,132);
  DrawTILE(hcs1,extra1,x0+223,y0+57,17,55,781,89);
  DrawTILE(hcs1,extra1,x0+223+6,y0+57+21,7,13,75,132);
  
  FillRect(hcs1,x0+1,y0+57+56,238,12,48,48,48);
  FillRect(hcs1,x0+2,y0+57+57,183,10,0,0,0);
  FillRect(hcs1,x0+3,y0+57+58,181,8,50,140,20);
  
  FillRect(hcs1,x0+18,y0+70+56,204,55,48,48,48);
  
  DrawTILE(hcs1,extra1,x0,y0+70+56,17,55,781,89);
  DrawTILE(hcs1,extra1,x0+5,y0+70+56+21,7,13,67,132);
  DrawTILE(hcs1,extra1,x0+223,y0+70+56,17,55,781,89);
  DrawTILE(hcs1,extra1,x0+223+6,y0+70+56+21,7,13,75,132);
}

/*---------------------------RecruitSelection1-------------------*/
int GraphicsEngine::RecruitSelection1(void)
{
  GlobalData* data = _GlobalData;

  int k,fudge=0;

  k=(rand()%1000)+data->turnnum+fudge;
  if(k>650)
  {
    k=(rand()%12);
    if(k<5){return 20;}else{if(k>8){return 22;}else{return 21;}}
  }
  else
  {
    k=(rand()%101);
    if(k<10){return 1;}           /*ore miner*/
    if(k>9&&k<19){return 2;}
    if(k>18&&k<27){return 3;}
    if(k>26&&k<35){return 4;}
    if(k>34&&k<42){return 5;}
    if(k>41&&k<48){return 6;}     /*sawyer*/
    if(k>47&&k<54){return 7;}
    if(k>53&&k<60){return 8;}
    if(k>59&&k<66){return 9;}
    if(k>65&&k<71){return 10;}
    if(k>70&&k<76){return 23;}    /*explorer*/
    if(k>75&&k<81){return 11;}
    if(k>80&&k<85){return 12;}
    if(k>84&&k<89){return 13;}
    if(k>88&&k<93){return 14;}
    if(k>92&&k<96){return 15;}
    if(k>95&&k<99){return 16;}
    if(k>98&&k<101){return 17;}
  }
  return 22;
}

/*---------------------------SelectedShipName---------------------*/
void GraphicsEngine::SelectedShipName(int num,char flag)
{
  GlobalData* data = _GlobalData;

  int x0=392,y0=478,dx=0,dx2=0;
  float k;

  FillRect(screen,x0+40,y0+18,199,13,128,128,192);
  FillRect(screen,x0+40,y0+18,199,12,48,48,48);
  FillRect(screen,x0+40,y0+31,199,12,48,48,48);
  FillRect(screen,x0+87,y0+44,27,12,48,48,48);
  FillRect(screen,x0+188,y0+44,27,12,48,48,48);
  
  FillRect(screen,x0+3,y0+57+58,181,8,50,140,20);
  FillRect(screen,x0+188,y0+57+56,49,12,48,48,48);

  if(flag)
  {    
    drawString2(screen,data->SoLfont1[3],x0+40,y0+20,
                data->units_ships[num].name);
    drawString2(screen,data->SoLfont1[3],x0+40,y0+32,
                data->units_ships[num].type);
    drawString2(screen,data->SoLfont1[3],x0+97,y0+46,"%d",
                data->units_ships[num].passengernum);
  
    if(data->units_ships[num].cargototal<10){dx2=14;}
    else{if(data->units_ships[num].cargototal<100){dx2=7;}}
    
    drawString2(screen,data->SoLfont1[3],x0+186+7+dx2,y0+46,"%d",
                data->units_ships[num].cargototal);
    
    k=(181/(float)(data->units_ships[num].capacity))*
          ((float)((data->units_ships[num].passengernum*100)+
            data->units_ships[num].cargototal));
    FillRect(screen,x0+3,y0+57+58,(int)k,8,180,10,10);

    if((data->units_ships[num].passengernum*100)+
        data->units_ships[num].cargototal<10){dx=14;}
    else
    {
      if((data->units_ships[num].passengernum*100)+
          data->units_ships[num].cargototal<100){dx=7;}
    }
  
    drawString2(screen,data->SoLfont1[3],x0+188+dx,y0+57+56+2,"%d/%d",
      (data->units_ships[num].passengernum*100)+
       data->units_ships[num].cargototal,data->units_ships[num].capacity);
  }
  UpdateScreen1(x0+40,y0+20,199,38);
  UpdateScreen1(x0+3,y0+57+56,240,12);
}

/*------------------------SelectedShipPassengers--------------------*/
int GraphicsEngine::SelectedShipPassengers(short n,char m)
{
  GlobalData* data = _GlobalData;

  int SSx=410,SSy=535,SSxx,i,w,bx,www,dx,a;

  SSxx=SSx;
  FillRect(screen,SSx,SSy,193,55,16,80,32);
    
  for(i=m;i<data->units_ships[n].passengernum;i++)
  {
    a=data->units_ships[n].passenger[i];    
    RemoveExtraSpaceH(uniticons,data->tile50[a][0],data->tile50[a][1],75,50);
    w=75-data->leftspace-data->rightspace;
    
    bx=RemoveExtraSpaceH2(uniticons,data->tile50[a][0],data->tile50[a][1],
            75,50,8);
    www=75-data->leftspace-bx;
    if(5+w>5+www+14){dx=5+w;}else{dx=5+www+14;}
    
    if(SSxx+5+dx>SSx+199){break;}
    
    if(i==m){FillRect(screen,SSx+2,SSy+2,www+6+14,51,32,120,48);}

    FillRect(screen,SSxx+5+www+2,SSy+2+37,12,16,0,0,0);

    short r, g, b;
    NationColors(data->nation, r, g, b);
    FillRect(screen,SSxx+5+www+3,SSy+2+37+1,10,14, r, g, b);
    drawString3(screen,data->SoLfont1[0],SSxx+5+www+5,SSy+2+37+4,
            0,0,0,32,32,32,"S");
    
    DrawTILE(screen,uniticons,SSxx+5,SSy+1,w,50,
             data->tile50[a][0]+data->leftspace,data->tile50[a][1]);
    if(5+w>5+www+14){SSxx+=5+w;}else{SSxx+=5+www+14;}
  }
  UpdateScreen1(SSx,SSy,204,55);
  return 0;
}

/*------------------------ShipsInPortDisplay---------------------*/
void GraphicsEngine::ShipsInPortDisplay(int x,int y1,char start,char index,
                          char array[],short array2[])
{
  GlobalData* data = _GlobalData;

  int xx,w,ii,bx,www,dx,w2;
//  char a;

  xx=x;                
  FillRect(screen,x,y1,229,60,16,32,64);
  for(ii=start;ii<index;ii++)
  {
    RemoveExtraSpaceH(uniticons,data->tile50[array[ii]][0],
                      data->tile50[array[ii]][1],75,50);
    w=75-data->leftspace-data->rightspace;
    
    bx=RemoveExtraSpaceH2(uniticons,data->tile50[array[ii]][0],
                          data->tile50[array[ii]][1],75,50,35);
    www=75-data->leftspace-bx;
    if(5+w>5+www+14){dx=5+w;}else{dx=5+www+14;}
    
    if(xx+dx>x+225){break;}
    if(ii==start)
    {
      if(w>www+14){w2=w;}else{w2=www+14;}
      FillRect(screen,x+2,y1+2,w2+6,56,48,96,192);
    }
    
    FillRect(screen,xx+5+www+2,y1+2+10,12,16,0,0,0);

    short r, g, b;
    NationColors(data->nation, r, g, b);
    FillRect(screen,xx+5+www+3,y1+2+10+1,10,14, r, g, b);
    if(data->units_ships[array2[ii]].cargonum==0)
    {
      drawString3(screen,data->SoLfont1[0],xx+5+www+5,y1+2+10+4,
            0,0,0,32,32,32,"-");
    }
    else
    {
      drawString3(screen,data->SoLfont1[0],xx+5+www+5,y1+2+10+4,
            0,0,0,32,32,32,"%d",data->units_ships[array2[ii]].cargonum);
    }
    
    DrawTILE(screen,uniticons,xx+5,y1+5,w,50,
             data->tile50[array[ii]][0]+data->leftspace,
             data->tile50[array[ii]][1]);
    if(5+w>5+www+14){xx+=5+w;}else{xx+=5+www+14;}
  }
  UpdateScreen1(x,y1,230,60);
}

/*------------------------DocksWaitingDisplay---------------------*/
void GraphicsEngine::DocksWaitingDisplay(int x,int y1,char start,char index,
                          char array[])
{
  GlobalData* data = _GlobalData;

  int xx,w,ii,bx,www,dx,dh;

  xx=x;
  FillRect(screen,x,y1,230,60,16,80,32);
  
  for(ii=start;ii<index;ii++)
  {
    RemoveExtraSpaceH(uniticons,data->tile50[array[ii]][0],
                      data->tile50[array[ii]][1],75,50);
    w=75-data->leftspace-data->rightspace;
    
    if(array[ii]>35){dh=35;}else{dh=8;}
    bx=RemoveExtraSpaceH2(uniticons,data->tile50[array[ii]][0],
                          data->tile50[array[ii]][1],75,50,dh);
    www=75-data->leftspace-bx;
    if(5+w>5+www+14){dx=5+w;}else{dx=5+www+14;}
    
    if(xx+dx>x+225){break;}
    if(ii==start){FillRect(screen,x+2,y1+2,www+6+14,56,32,120,48);}
    
    if(array[ii]>35){dh=10;}else{dh=37;}
    FillRect(screen,xx+5+www+2,y1+2+dh,12,16,0,0,0);

    short r, g, b;
    NationColors(data->nation, r, g, b);
    FillRect(screen,xx+5+www+3,y1+2+dh+1,10,14, r, g, b);
    drawString3(screen,data->SoLfont1[0],xx+5+www+5,y1+2+dh+4,
            0,0,0,32,32,32,"-");
            
    DrawTILE(screen,uniticons,xx+5,y1+5,w,50,
             data->tile50[array[ii]][0]+data->leftspace,
             data->tile50[array[ii]][1]);
    if(5+w>5+www+14){xx+=5+w;}else{xx+=5+www+14;}
  }
  UpdateScreen1(x,y1,230,60);
}

/*------------------------SelectedShipCargo------------------------*/
void GraphicsEngine::SelectedShipCargo(short n,char m,int a)
{
  GlobalData* data = _GlobalData;

  int SSx=410,SSy=604,SSxx,i,w;

  SSxx=SSx;
  FillRect(screen,SSx+1,SSy,203,55,48,48,48);
    
  if(data->units_ships[n].cargototal>0)
  {
    for(i=m;i<m+5;i++)
    {
      if(data->units_ships[n].cargo[i][0]!=0)
      {    
        DrawRect(screen,SSxx,SSy,41,54,160,160,160);
    
        if(i==a){FillRect(screen,SSxx+1,SSy+1,40,53,64,64,64);}
        else{FillRect(screen,SSxx+1,SSy+1,40,53,56,56,56);}
    
        DrawTILE(screen,extra1,SSxx+1,SSy-1,40,50,
                    data->units_ships[n].cargo[i][0]+5,1);
    
        w=(40-stringWidthSoL1("%d",data->units_ships[n].cargo[i][1]))/2; 
        drawString2(screen,data->SoLfont1[3],SSxx+1+w,SSy+1+43,
            "%d",data->units_ships[n].cargo[i][1]);
      }
      SSxx+=41;
    }
  }
  UpdateScreen1(SSx,SSy,206,55);
}


//
// $Id: deuro3.cpp,v 1.4 2004/06/23 15:37:05 sikon Exp $
//

