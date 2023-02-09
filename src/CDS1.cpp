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
// >>>
#include "colony.h"

#define CDS_MARKET_LEFT     325
#define CDS_MARKET_TOP      681
#define CDS_MARKET_DELTAX    41
#define CDS_MARKET_DELTAY    42
#define CDS_MARKET_TILEDELTA 51

#define CDS_BUILD_LEFT      256
#define CDS_BUILD_TOP        34
#define CDS_BUILD_SSIZE     120
#define CDS_BUILD_LSIZE     160
// <<<

/*---------------------------DrawCDS-------------------------*/
void GraphicsEngine::DrawCDS(void)
{
    DrawCDSMarket(CDS_MARKET_LEFT, CDS_MARKET_TOP);
    DrawCDSSlots(256,34);
    DrawCDSConstruction(8,34);
    DrawCDSFields(20,320);
    Counter1(cds1,256,620);
    DrawCDSProduction(8,481);
    DrawCDSMapButton(943,1);
    DrawCDSSelected(325,620);
    DrawCDSUnitList(256, 534);
    DrawCDSUnitList(256 + 265, 534);
    DrawCDSUnitList(256 + 531, 534);
}

// >>>

void GraphicsEngine::DrawCDSUnitList(int x, int y)
{
    int r2=16,g2=80,b2=32;

    FillRect(cds1, x, y, 229, 62, 128, 192, 128);
    Border(cds1, x, y, 228, 61);
    FillRect(cds1, x + 1, y + 1, 75, 60, r2, g2, b2);
    FillRect(cds1, x + 77, y + 1, 75, 60, r2, g2, b2);
    FillRect(cds1,x + 153, y + 1, 75, 60, r2, g2, b2);
}

void GraphicsEngine::UpdateCDS(Colony *col)
{
    UpdateGold(0); //??? What does this 0 mean?
    UpdateCDSColName(col);
    UpdateCDSFields(col);
    UpdateCDSMarket(col);
    UpdateCDSBuildings(col);
}

void GraphicsEngine::UpdateCDSColName(Colony *col)
{
    int renderW, renderH;
    char *colName = (char *)col->getName().c_str();
    TTF_SizeText(fontColNameCDS->font, colName, &renderW, &renderH);      
            
    drawString(screen, fontColNameCDS, (screenResX - renderW) / 2, 3, true,
        colName);
}

void GraphicsEngine::UpdateCDSFields(Colony *col)
{
    DrawCDSFields2(col->getTile());
//TODO: place colonists working on the fields
}

void GraphicsEngine::UpdateCDSMarket(Colony *col)
{
    GlobalData* data = m_pGame->GetData();
    int x, x1, swidth, c;

    for(x = CDS_MARKET_LEFT + 18, x1 = 1, c = IDC_FOOD; x < CDS_MARKET_LEFT + 674;
     x += CDS_MARKET_DELTAX, x1 += CDS_MARKET_TILEDELTA, c++)
    {
        swidth = (CDS_MARKET_DELTAX - stringWidthSoL1("%i", col->getStock(c))) / 2; 
        drawString2(screen, data->SoLfont1[3], x + swidth,
            CDS_MARKET_TOP + CDS_MARKET_DELTAY, "%i", col->getStock(c));
    }
}

void GraphicsEngine::UpdateCDSBuildings(Colony *col)
{
    int i, j, k;
    
    for(i = 0; i < CDS_BUILD_XTILES; i++)
        for(j = 0; j < CDS_BUILD_YTILES; j++)
            if(i == CDS_BUILD_XTILES - 1 && j == CDS_BUILD_YTILES - 1)
            {
                ;
            }
            else if(i == CDS_BUILD_XTILES - 2 && j == CDS_BUILD_YTILES - 1)
            {
                DrawTILE(screen, buildings1,
                CDS_BUILD_LEFT + (i - 1) * CDS_BUILD_SSIZE + CDS_BUILD_LSIZE,
                CDS_BUILD_TOP + j * CDS_BUILD_SSIZE, CDS_BUILD_SSIZE * 2, CDS_BUILD_SSIZE,
                724 + (col->squares[i][j] - 1) * (2 * CDS_BUILD_SSIZE + 1), 646);
            }
            else if(col->squares[i][j] && i != col->lgSquare)
            {
                DrawTILE(screen, buildings1,
                CDS_BUILD_LEFT + (i - 1) * CDS_BUILD_SSIZE +
                (i < col->lgSquare ? CDS_BUILD_SSIZE : CDS_BUILD_LSIZE),
                CDS_BUILD_TOP + j * CDS_BUILD_SSIZE, CDS_BUILD_SSIZE, CDS_BUILD_SSIZE,
                1 + (col->squares[i][j] - 1) * (CDS_BUILD_SSIZE + 1), 364);
            }
            else if(col->squares[i][j] && i == col->lgSquare && (j < CDS_BUILD_YTILES - 1))
            {
                DrawTILE(screen, buildings1, CDS_BUILD_LEFT + i * CDS_BUILD_SSIZE,
                CDS_BUILD_TOP + j * CDS_BUILD_LSIZE, CDS_BUILD_LSIZE, CDS_BUILD_LSIZE,
                645 + (col->squares[i][j] - 1) * (CDS_BUILD_LSIZE + 1), 485);
            }
    
    for(k = 0; k < col->getBuildingNum(); k++)
    {
        switch(col->getBuilding(k)->getGraphicType())
        {
            case BGR_SMALL:
                i = (col->getBuilding(k)->getGraphic() % 10);
                j = (col->getBuilding(k)->getGraphic() / 10);
                
                DrawTILE(screen, buildings1,
                CDS_BUILD_LEFT + (col->getBuilding(k)->x - 1) * CDS_BUILD_SSIZE +
                (col->getBuilding(k)->x < col->lgSquare ? CDS_BUILD_SSIZE : CDS_BUILD_LSIZE),
                CDS_BUILD_TOP + col->getBuilding(k)->y * CDS_BUILD_SSIZE,
                CDS_BUILD_SSIZE, CDS_BUILD_SSIZE,
                1 + i * (CDS_BUILD_SSIZE + 1), 1 + j * (CDS_BUILD_SSIZE + 1));
                break;
            case BGR_LARGE:
                i = col->getBuilding(k)->getGraphic();
                j = col->getBuilding(k)->y;
                
                DrawTILE(screen, buildings1, CDS_BUILD_LEFT + col->lgSquare * CDS_BUILD_SSIZE,
                CDS_BUILD_TOP + j * CDS_BUILD_LSIZE, CDS_BUILD_LSIZE, CDS_BUILD_LSIZE,
                1 + i * (CDS_BUILD_LSIZE + 1), 485);
                break;
            case BGR_DOCKS:
                i = col->getBuilding(k)->getGraphic();
                
                DrawTILE(screen, buildings1,
                CDS_BUILD_LEFT + (CDS_BUILD_XTILES - 2) * CDS_BUILD_SSIZE + CDS_BUILD_LSIZE,
                CDS_BUILD_TOP + (CDS_BUILD_YTILES - 1) * CDS_BUILD_SSIZE,
                CDS_BUILD_SSIZE, CDS_BUILD_SSIZE, 1 + i * (2 * CDS_BUILD_SSIZE + 1), 646);
                break;
        }
    }
}

//
// $Id: CDS1.cpp,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

