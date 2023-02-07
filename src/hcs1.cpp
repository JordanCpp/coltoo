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

/*---------------------------DrawHCS-------------------------*/
void GraphicsEngine::DrawHCS(void)
{
  
  DrawMarket1();
  HCSButtons();
  HCSDRecruit();
  HCSDPurchase();
  HCSDTrain();
  DrawSURF(hcs1,HCSWin[1],640,244);
  DrawDocks1();
  SelectedShip1();
  Counter1(hcs1,648,544);
}

/*----------------------HCSRadioButtons1-------------------*/
void GraphicsEngine::HCSRadioButtons1(void)
{
    GlobalData* data = m_pGame->GetData();
    int x1=643,y1=222,swidth,x0=640,y0=244;

  if(data->HCSradio1==0)
  {
    DrawTILE(screen,extra1,x1,y1,76,18,344,52);  
    DrawTILE(screen,extra1,x1+76,y1,76,18,267,52);
    DrawTILE(screen,extra1,x1+152,y1,76,18,267,52);

    swidth=stringWidthSoL1(data->Labels[16]);
    drawString2(screen,data->SoLfont1[1],
                x1+((76-swidth)/2)+4,y1+4,data->Labels[16]);
                  
    swidth=stringWidthSoL1(data->Labels[17]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+76,y1+5,
                  data->Labels[17]);
  
    swidth=stringWidthSoL1(data->Labels[18]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+152,y1+5,
                  data->Labels[18]);

    DrawSURF(screen,HCSWin[0],x0,y0);
    DrawSURF(screen,HCSWin[1],x0,y0);
  }
  if(data->HCSradio1==1)
  {
    DrawTILE(screen,extra1,x1,y1,76,18,267,52);  
    DrawTILE(screen,extra1,x1+76,y1,76,18,344,52);
    DrawTILE(screen,extra1,x1+152,y1,76,18,267,52);

    swidth=stringWidthSoL1(data->Labels[16]);
    drawString2(screen,data->SoLfont1[1],
                x1+((76-swidth)/2)+4,y1+5,data->Labels[16]);
                  
    swidth=stringWidthSoL1(data->Labels[17]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+76,y1+4,
                  data->Labels[17]);
  
    swidth=stringWidthSoL1(data->Labels[18]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+152,y1+5,
                  data->Labels[18]);

    data->Pstart=0;
    HCSDNewUnitHL(0,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
    DrawSURF(screen,HCSWin[0],x0,y0);
    DrawSURF(screen,HCSWin[2],x0,y0);
  }
  if(data->HCSradio1==2)
  {
    DrawTILE(screen,extra1,x1,y1,76,18,267,52);  
    DrawTILE(screen,extra1,x1+76,y1,76,18,267,52);
    DrawTILE(screen,extra1,x1+152,y1,76,18,344,52);

    swidth=stringWidthSoL1(data->Labels[16]);
    drawString2(screen,data->SoLfont1[1],
                x1+((76-swidth)/2)+4,y1+5,data->Labels[16]);
                  
    swidth=stringWidthSoL1(data->Labels[17]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+76,y1+5,
                  data->Labels[17]);
  
    swidth=stringWidthSoL1(data->Labels[18]);
    drawString2(screen,data->SoLfont1[1],x1+((76-swidth)/2)+4+152,y1+4,
                  data->Labels[18]);

    data->Tstart=1;
    HCSDNewUnitHL(0,HCSWin[3],data->Tstart,data->Jobs,data->JobsCost,1);  
    DrawSURF(screen,HCSWin[0],x0,y0);
    DrawSURF(screen,HCSWin[3],x0,y0);
  }
  UpdateScreen1(x0,y0-22,235,149);
}


//
// $Id: hcs1.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

