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
//
// FILE		: gameEngine.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: GameEngine
//
// DESCRIPTION	: Main class for overall game control.
//

#include <iostream>
#include "gameEngine.h"
#include "eventHandler.h"
#include "graphicsEngine.h"
#include "map.h"
#include "player.h"
#include "ai.h"
#include "globalData.h"
#include "tile.h"
#include <ctime>
// >>>
#include "unit.h"
#include "colony.h"
// <<<

//Constructor, destructor---------------------------------------------------------------//
GameEngine::GameEngine(GraphicsEngine* graphicsEngine, GlobalData* globalData, OptionList* optionList, Map* map) :
    m_pGfxEngine(graphicsEngine),
    m_pData(globalData),
    m_pOptions(optionList),
    m_pMap(map)
{
    int i;
    for(i=0; i<10; i++)
    {
        m_pAI[i] = NULL;
    }
}

GameEngine::~GameEngine()
{
    #ifdef DEBUG
    cout<<"----------------"<<endl;
    cout<<"Game Ended"<<endl;
    #endif

    #ifdef DEBUG
    cout<<"deleting AIs"<<endl;
    #endif
    int i;
    for(i=0; i<10; i++)
    {
        if(m_pAI[i]) delete m_pAI[i];
    }
    #ifdef DEBUG
    cout<<"Closing Game"<<endl;
    #endif
}

//Methods---------------------------------------------------------------------------------//
bool GameEngine::Init(int argc, char * argv[])
{
    bool bSuccess = true;

    srand(time(NULL));     //random number seed

    #ifdef DEBUG
    cout<<"Creating GameEngine {"<<endl;
    #endif
    m_pGfxEngine = new GraphicsEngine(m_pData, m_pOptions, m_pMap);
    
    if(bSuccess) bSuccess &= m_pGfxEngine->Init();
    else bSuccess = false;

    /*if(bSuccess)
    {
      m_pPlayer = new Player();
      if(m_pPlayer) bSuccess &= m_pPlayer->Init();
      else bSuccess = false;
    }*/

    if(bSuccess)
    {
        #ifdef DEBUG
        cout<<"  Creating AIs {"<<endl;
        #endif
        for(int i=0; i<10 && bSuccess; i++)
        {
            #ifdef DEBUG
            cout<<"    AI["<<i<<"]"<<endl;
            #endif
            m_pAI[i] = new AI();
            if(m_pAI[i]) bSuccess &= m_pAI[i]->Init();
            else bSuccess = false;
        }
        #ifdef DEBUG
        cout<<"  } AIs"<<endl;
        #endif
    }

    #ifndef _DEBUG
    if(bSuccess)
    {
        #ifdef DEBUG
        cout<<"  Splash screen {"<<endl;
        #endif
        bSuccess &= m_pGfxEngine->splash();
        #ifdef DEBUG
        cout<<"  } Splash"<<endl;
        #endif
    }
    #endif

    #ifdef DEBUG
    cout<<"} GameEngine"<<endl;
    #endif
    return bSuccess;
}

//                //
//Method GameLoop //---------------------------------------------------------------------//
//                //
bool GameEngine::GameLoop(void)
{

//    int x,y,a,i,ii,done=0,k,dx,dy,steps=25,x1,y1;
    int a,i,ii,done=0;
// >>>
    static int year = 1492, season = 0;  
// <<<
    short /*Speed = 432,*/ radioold;
    //long LastUpdate = 0;
    //unsigned char blink = 0, a2 = 0;
    //long mapnumold;

    m_pData->mouseClick=0;

//???    m_pData->units[0][0]=0;m_pData->units[0][1]=6;
//???    m_pData->units[1][0]=1;m_pData->units[1][1]=4;
    #ifdef DEBUG
    cout<<"Placing new Units"<<endl;
    #endif
    m_pData->nation = NATION_FR;
    PlaceNewUnit(IDU_CARAVEL,     m_pData->nation);
    PlaceNewUnit(IDU_SCOUT,       NATION_SPAN)->setSkill(FindSkill(IDS_SCOUT));
    PlaceNewUnit(IDU_SOLDIER,     m_pData->nation)->setSkill(FindSkill(IDS_DISTILLER));
    PlaceNewUnit(IDU_COLONIST,    m_pData->nation)->setSkill(FindSkill(IDS_SUGARFMR));
    
    Unit *s = PlaceNewUnit(IDU_CARAVEL, NATION_ENG);
    Unit *u = PlaceNewUnit(IDU_PIONEER, NATION_ENG);
    UnitBoardShip(u, s);
    u = PlaceNewUnit(IDU_SOLDIER, NATION_ENG);
    UnitBoardShip(u, s);
    
    s = PlaceNewUnit(IDU_MERCHANTMAN, NATION_DUT);
    u = PlaceNewUnit(IDU_PIONEER, NATION_DUT);
    UnitBoardShip(u, s);

    #ifdef DEBUG
    cout<<"Placing Natives"<<endl;
    #endif
    for(i = 0; i < 300; i++)
    {
        a = 0;
        while(!a)
        {
            m_pData->natives[i]=(rand()%29700)+150;    // Select starting point for natives 

            if(!m_pMap->getTile(m_pData->natives[i])->Is(TILE_RUMOR) &&
               m_pMap->getTile(m_pData->natives[i])->getTerrain()!=TERRAIN_OCEAN &&
               m_pMap->getTile(m_pData->natives[i])->getTerrain()!=TILE_PEAK &&         
               m_pMap->getTile(m_pData->natives[i])->getTerrain()!=TERRAIN_LAKE &&
               m_pMap->getTile(m_pData->natives[i])->getTerrain()!=TERRAIN_HIGHSEAS &&
               !m_pMap->getTile(m_pData->natives[i])->Is(TILE_FAKE) &&
               !m_pMap->getTile(m_pData->natives[i])->Is(TILE_UNIT))
            {
                m_pData->nativeOnTile[m_pData->natives[i]]++;
                a = 1;
            }
        }
    }


    m_pData->recruitcost = (rand() % 200) + 200;
    m_pData->recruitcostold = m_pData->recruitcost;

    if(m_pGfxEngine->drawBackground() == false) return false;

    //expose the tiles around the 2 units 
    for(m_pData->turn = 0;m_pData->turn < m_pData->unitList.size();
     m_pData->turn++)
    {
        m_pData->nationTurn = m_pData->unitList[m_pData->turn]->getNation(); //added 17/6
        m_pData->mapnum = m_pData->unitList[m_pData->turn]->getTile();
        m_pGfxEngine->Reveal();
    }

    #ifdef DEBUG
    cout<<"Starting Game..."<<endl;
    cout<<"----------------"<<endl;
    #endif
    //start the loop
    while(!done)
    {
// >>>
        //year update
        m_pGfxEngine->FillRect(m_pGfxEngine->screen,635,3,85,13,48,48,48);
        
        if(season == 0)
        {
            #ifdef DEBUG
            cout<<"Spring "<<year<<endl;
            #endif
            m_pGfxEngine->drawString2(m_pGfxEngine->screen, m_pData->SoLfont1[3],
                                  641, 5, "Spring %i", year);
        }
        else
        {
            #ifdef DEBUG
            cout<<"Autumn "<<year<<endl;
            #endif
            m_pGfxEngine->drawString2(m_pGfxEngine->screen, m_pData->SoLfont1[3],
                                  641, 5, "Autumn %i", year);
        }
        
        m_pData->turnnum++;
        
        if(year >= 1500 && season == 0)
        {
            season = 1;
        }
        else
        {
            season = 0;
            year++;
        }
// <<<

        #ifdef DEBUG
        cout<<"Set up new recruits and cost"<<endl;
        #endif
        //set up the new recruits and cost    
        m_pData->recruitcost-=(rand()%20)+15;
        m_pGfxEngine->HCSDRecruitHL(0);
        m_pGfxEngine->DrawSURF(m_pGfxEngine->hcs1,m_pGfxEngine->HCSWin[1],640,244);

        a = 1;
        #ifdef DEBUG
        cout<<"rotating between Nations"<<endl;
        #endif
        //rotate betwwen scout & ship and natives
        for(i=0; i<m_pData->playerlist.size(); i++)
        {
            m_pData->nationTurn = i; //added 17/6; Nation being played
            
            if(year == 1500 && season == 1 && m_pData->turn == 0)
            {
                m_pGfxEngine->MessageWindow(MSG_TIMESCALE);
            }
        
            #ifdef DEBUG
            cout<<"Player "<<i<<" ("<<m_pData->playerlist[i]->unitList.size()<<" units)"<<endl;
            #endif
            for(ii = 0; ii < m_pData->playerlist[i]->unitList.size(); ii++)
            {
                // if the cost of new recruit is less than 100 
                //   put it on the docks                        
                if(m_pData->recruitcost<=100)
                {
                    m_pGfxEngine->MessageWindow(MSG_NEWRECRUIT);
                    radioold=m_pData->HCSradio1;
                    m_pData->HCSradio1=0;
                    m_pGfxEngine->HCSMouseCheck(660,244+91+8,1);  //press recruit button
                    m_pData->HCSradio1=radioold;
                }
                
                if(i == m_pData->nation)
                    a &= workPlayer(i, ii, done);
                else
                    workPlayer(i, ii, done);
                    
                if(done) break;
            }
            if(done) break;
        }
        #ifdef DEBUG
        cout<<"Done: "<<done<<endl;
        #endif
//added 6/2
//checks if native units are visible
//if native moves and is visible show slide
        if(!done)
        {
            workIndian();
        
            if(a)
                m_pGfxEngine->MessageWindow(MSG_ENDOFTURN);
        }
    }
	return true;
}
/*

  A new gameloop essay,

bool GameEngine::GameLoop(void){

	bool exitCondition = false;

	while(!exit){

		m_pKeyb->Update();
		m_pGfxEngine->drawContext(m_pData->getContext());
		m_pGfxEngine->drawMap(m_pMap,v);
		m_pGfxEngine->drawColonies();
		m_pGfxEngine->drawUnits();
	}

}*/

bool GameEngine::workPlayer(Uint8 nation, int unit, int& done)
{
    int x,y;
	//TODO: fix type of Speed and LastUpdate
    short Speed = 432;
    long LastUpdate = 0;
    unsigned char blink = 0, a2 = 0;
    int unitID = m_pData->playerlist[nation]->unitList[unit]->getUnitID();

    //if the scout is active and loaded on ship do nothing
    m_pData->turn = unitID;
    if(m_pData->unitList[unitID]->isOnboard() ||
       m_pData->unitList[unitID]->getOrders() != ORD_NONE)
    {
        return 1;
    }
    //otherwise    
    else
    {
        m_pData->unitList[unitID]->setMovesLeft(m_pData->unitList[unitID]->getMoveCapability());
        m_pData->mf = m_pData->unitList[unitID]->getMovesLeft();
        m_pData->tmf = m_pData->mf;
        m_pData->mapnum=m_pData->unitList[unitID]->getTile();
        m_pData->start=m_pData->unitList[unitID]->getStartNumber();

        m_pMap->getTile(m_pData->mapnum)->setFlags(TILE_UNIT, true);

        m_pGfxEngine->ReCenter();
        m_pData->flag&=~m_pData->ReCenFlag;
        m_pGfxEngine->Reveal();      //removes, or partially removes, the shroud
        m_pGfxEngine->SetTerrain();
        m_pGfxEngine->DrawTILE(m_pGfxEngine->bck1,m_pGfxEngine->screen,
                      0,0,m_pData->tw,m_pData->th,
                      m_pData->stile[m_pData->scrnum][0],
                      m_pData->stile[m_pData->scrnum][1]-m_pData->yextra-5);
        m_pData->oldloc=m_pData->scrnum;
                
        m_pGfxEngine->UpdateUnitInfo(m_pData->unitList[unitID]);

        m_pGfxEngine->FillRect(m_pGfxEngine->screen,979,384,30,12,48,48,48);
        m_pGfxEngine->drawString2(m_pGfxEngine->screen, m_pData->SoLfont1[3],
                                  984, 386, "%i/%i", m_pData->mf, m_pData->tmf);

/*      //coordinates of the mini-ship on the tilesheet
        if(m_pData->unitList[m_pData->turn]->isBoat())
        { x = 67; y = 105; }
        //coordinates of the mini-scout on the tilesheet      	
        else
        { x = 67; y = 53; } */
        x = m_pData->tile26[m_pData->unitList[unitID]->getGSmall()][0];
        y = m_pData->tile26[m_pData->unitList[unitID]->getGSmall()][1];

        //draw 'mini' unit in information window
        m_pGfxEngine->DrawTILE(m_pGfxEngine->activebck,m_pGfxEngine->screen,
                               0,0,32,25,979,351);
        m_pGfxEngine->DrawTILE(m_pGfxEngine->screen,m_pGfxEngine->unitsS,
                               979,351,32,25,x,y);

        m_pGfxEngine->UpdateScreen0();
        m_pGfxEngine->UnitTerrainCheck(unitID);   //Water or Land?
        m_pGfxEngine->UpdateScreen1(m_pData->stile[m_pData->scrnum][0],
                                    m_pData->stile[m_pData->scrnum][1] -
                                    m_pData->yextra-5,m_pData->tw,m_pData->th);


        //keep checking for a mouse click or a keypress
        while(SDL_PollEvent(&m_pData->event));

        LastUpdate=SDL_GetTicks();

        //does the active unit have any MFs left?          
        while (m_pData->mf>0)
        {
            //if the scout boarded a ship end its turn
            if(!(m_pData->unitList[unitID]->isBoat())
                 && m_pData->unitList[unitID]->isOnboard())
            {
                m_pData->mf = 0;
                #ifdef DEBUG
                cout<<"Unit "<<unitID<<" is on board"<<endl;
                #endif
                continue;
            }

            //not sure if these next two lines are really needed       
            m_pData->event.type=0;
            m_pData->event.button.button=0;
            m_pData->event.button.type=0;

            ///check for click or key press or mouse motion
            SDL_PollEvent(&m_pData->event);

            //if mouse moved on the HCS (Home Country Screen see if we have a 
            // 'mouse over' event         
            if(m_pData->event.type==SDL_MOUSEMOTION&&m_pData->scrndsply==2)
            {
                m_pGfxEngine->HCSMouseOverSort();
            }

            //blink the active unit
            if(m_pData->scrndsply == 0 && m_pData->zl == 0 && m_pData->visible == 1)
            {
                if(LastUpdate+Speed < SDL_GetTicks())
                {
                    if(blink)
                    {
                        if(m_pData->scrnum<11)
                        {
                            m_pGfxEngine->DrawTILE(m_pGfxEngine->screen,
                                             m_pGfxEngine->bck1,
                                             m_pData->stile[m_pData->scrnum][0],
                                             m_pData->stile[m_pData->scrnum][1],
                                             m_pData->tw,m_pData->th-m_pData->yextra-5,
                                             0,m_pData->yextra+5); /**/
                        }
                        else
                        {
                            m_pGfxEngine->DrawSURF(m_pGfxEngine->screen,
                                          m_pGfxEngine->bck1,
                                          m_pData->stile[m_pData->scrnum][0],
                                          m_pData->stile[m_pData->scrnum][1]
                                          -m_pData->yextra-5);
                        }
                        blink = 0;       
                    }
                    else
                    {
                        m_pGfxEngine->UnitTerrainCheck(unitID);
                        blink = 1;
                    }
                    LastUpdate = SDL_GetTicks();
                }

                if(a2!=blink)
                {
                    m_pGfxEngine->UpdateScreen1(m_pData->stile[m_pData->scrnum][0],
                                  m_pData->stile[m_pData->scrnum][1]-m_pData->yextra-5,
                                  m_pData->tw,m_pData->th);
                    a2=blink;
                }
            }

            //see if the ESCAPE key was pressed.  if so end program
            if ( m_pData->event.type == SDL_QUIT )
            {
                #ifdef DEBUG
                cout<<"Quiting"<<endl;
                #endif
                done = 1;
                m_pData->mf = 0;
            }

            //handle a click  
            if (m_pData->event.button.type==SDL_MOUSEBUTTONDOWN)
            {
                if(m_pGfxEngine->MouseCheck())
                {
                    #ifdef DEBUG
                    cout<<"Clicked 'Quit'"<<endl;
                    #endif
                    done=1;
                    m_pData->mf=0;
                }
                continue;
            }

            //handle a key press     
            if ( m_pData->event.type == SDL_KEYDOWN )
            {
                if(m_pGfxEngine->KeyBoard(m_pData->event.key.keysym.sym))
                {
                    #ifdef DEBUG
                    cout<<"Key pressed"<<endl;
                    #endif
                    done=1;
                    m_pData->mf=0;
                }
            }
        }

        //if quit button was clicked, or 'Q' or 'q' key, end program 
        if(done)
        {
            #ifdef DEBUG
            cout<<"All Done"<<endl;
            #endif
            return true;
        }

        //store the postition and screen information of the unit at the 
        // end of its turn
        m_pData->unitList[unitID]->setTile(m_pData->mapnum);
        m_pData->unitList[unitID]->setStartNumber(m_pData->start);
        //if the scout is on the ship store the ship information in the 
        //  scouts array
/*      if(m_pData->unitList[m_pData->turn]->isOnboard())
        {
            m_pData->unitList[m_pData->turn]->setTile(m_pData->unitList[0]->getTile());
            m_pData->unitList[m_pData->turn]->setStartNumber(m_pData->unitList[0]->getStartNumber());
        } */

        //erase the mini unit
        m_pGfxEngine->DrawSURF(m_pGfxEngine->screen,m_pGfxEngine->activebck,979,351);

        //pause a half second so the player can see last move of unit
        SDL_Delay(500);
    }
    return false;
}

void GameEngine::workIndian(void)
{
    int x, y, i, ii, k, dx, dy, steps=25, x1, y1;
    long mapnumold;

    for(i = 0; i < 300; i++)
    {
        k=(rand()%8)+1;
        m_pData->mapnum=m_pData->natives[i];
              
        m_pGfxEngine->ReCenter();
        m_pData->flag&=~m_pData->ReCenFlag;
              
        m_pData->oldloc=m_pData->scrnum;
        mapnumold=m_pData->mapnum;
              
        m_pGfxEngine->MoveUnit(k);
              
        if(m_pData->flag & m_pData->NoMoveFlag)
        {
            m_pData->flag &= ~m_pData->NoMoveFlag;
        }
        else
        {
            if(m_pMap->getTile(m_pData->mapnum)->getShrdstate(m_pData->nationTurn)==2 &&
               m_pMap->getTile(mapnumold)->getShrdstate(m_pData->nationTurn)==2)
            {
                m_pData->natives[i]=m_pData->mapnum;
            }
            else
            {
                m_pGfxEngine->SetTerrain();
                m_pGfxEngine->UpdateScreen0();
                  
                m_pData->natives[i]=m_pData->mapnum;

                m_pGfxEngine->DrawTILE(m_pGfxEngine->bck1,m_pGfxEngine->screen,0,0,
                m_pData->tw,m_pData->th,
                m_pData->stile[m_pData->oldloc][XPOS],
                m_pData->stile[m_pData->oldloc][YPOS]-m_pData->yextra-5);
                  
                dx=(m_pData->stile[m_pData->scrnum][XPOS]-
                        m_pData->stile[m_pData->oldloc][0])/25;
                dy=(m_pData->stile[m_pData->scrnum][YPOS]-
                        m_pData->stile[m_pData->oldloc][1])/25;
                x=m_pData->stile[m_pData->oldloc][0];
                y=m_pData->stile[m_pData->oldloc][1]-m_pData->yextra-5;
        
                for(ii=0;ii<steps;ii++)
                {
                    m_pGfxEngine->DrawSURF(m_pGfxEngine->screen,m_pGfxEngine->bck1,x,y);
                    x+=dx;
                    y+=dy;
                    m_pGfxEngine->DrawTILE(m_pGfxEngine->bck1,m_pGfxEngine->screen,0,0,
                           m_pData->tw,m_pData->th,x,y);
              
                    if(m_pData->scrnum<11)
                    {
                      m_pGfxEngine->NationBox(x, y+m_pData->yextra+5, NATION_TRIBE, 3,
                      ORD_NONE);
                      m_pGfxEngine->DrawTILE(m_pGfxEngine->screen,m_pGfxEngine->tilesheet1,
                            x,y+m_pData->yextra+5,
                            m_pData->tw,m_pData->th-m_pData->yextra-5,m_pData->tilex[4],
                            m_pData->tiley[2]+m_pData->yextra+5);
                    }
                    else
                    {
                      m_pGfxEngine->NationBox(x, y, NATION_TRIBE, 3, ORD_NONE);
                      m_pGfxEngine->DrawTILE(m_pGfxEngine->screen,m_pGfxEngine->tilesheet1,
                            x,y,
                             m_pData->tw,m_pData->th,m_pData->tilex[4],m_pData->tiley[2]);
                    }
              
                    if(m_pData->stile[m_pData->oldloc][0]<
                          m_pData->stile[m_pData->scrnum][XPOS])
                      {x1=x-dx;}
                    else
                      {x1=x+dx;}
                      
                    if(m_pData->stile[m_pData->oldloc][1]<
                          m_pData->stile[m_pData->scrnum][YPOS])
                      {y1=y-dy;}
                    else
                      {y1=y+dy;}
                      
                    m_pGfxEngine->UpdateScreen1(x1,y1,
                          m_pData->tw+dx,m_pData->th+dy+m_pData->yextra+5);
                    SDL_Delay(5);              
                }                  
            }
        }    
    }
    m_pGfxEngine->SetTerrain();
    m_pData->flag &= ~m_pData->VillageFlag;
}

Unit *GameEngine::PlaceNewUnit(int unitID, int nation)
{
    m_pData->unitList.push_back(Unit::loadUnitFile(unitID));
    int a, i = m_pData->unitList.size() - 1;
    
    m_pData->unitList[i]->setMovesLeft(m_pData->unitList[i]->getMoveCapability());
    m_pData->unitList[i]->setNation(nation);
    m_pData->nationTurn = nation; //added 17/6

    if(m_pData->unitList[i]->isBoat())
    {
        int x, y = (rand()%150)+25;    // Select starting point for ship 

        for(x = 99; x < 150; x++)
        {
            if(m_pMap->getTile((m_pMap->GetWidth() * y) + x)->getTerrain() ==
             TERRAIN_HIGHSEAS)
            {
                m_pData->unitList[i]->setTile((m_pMap->GetWidth()*y) + x);
                m_pMap->getTile(m_pData->unitList[i]->getTile())->setFlags(TILE_UNIT, true);
                m_pData->unitList[i]->setPositionX(x);
                m_pData->unitList[i]->setPositionY(y);
                m_pData->unitList[i]->setStartNumber
                 (m_pData->unitList[i]->getTile() - 905);
                break;
            }
        }
    }
    else
    {
        int x, y;
        while(1)
        {
            y = (rand() % 150) + 25;    // Select starting point for scout 
            x = (rand() % 15) + 125;
            m_pData->unitList[i]->setPositionX(x); //=(m_pMap->GetWidth()*y)+x;
            m_pData->unitList[i]->setPositionY(y);
            m_pData->unitList[i]->setTile((m_pMap->GetWidth()*y)+x);
            m_pMap->getTile(m_pData->unitList[i]->getTile())->setFlags(TILE_UNIT, true);
            
            if(!m_pMap->getTile(m_pData->unitList[i]->getTile())->Is(TILE_RUMOR) &&
            m_pMap->getTile(m_pData->unitList[i]->getTile())->getTerrain()!=TERRAIN_OCEAN &&
            m_pMap->getTile(m_pData->unitList[i]->getTile())->getTerrain()!=TERRAIN_HIGHSEAS &&
            m_pMap->getTile(m_pData->unitList[i]->getTile())->getTerrain()!=TILE_PEAK &&
            m_pMap->getTile(m_pData->unitList[i]->getTile())->getVillages()==0 &&         
            m_pMap->getTile(m_pData->unitList[i]->getTile())->getTerrain()!=TERRAIN_LAKE)
            {
                m_pData->unitList[i]->setStartNumber(m_pData->unitList[i]->getTile() - 905);
                break;
            }
        }
    }
    m_pData->unitList[i]->setUnitID(m_pData->unitList.size() - 1);
    m_pData->playerlist[nation]->unitList.push_back(m_pData->unitList[i]);
    return m_pData->unitList[i];
}

void GameEngine::UnitBoardShip(Unit *unit, Unit *ship)
{
    if(!(ship->addPassenger(unit))) return;
    unit->setOnboardFlag(true);
    m_pMap->getTile(unit->getTile())->setFlags(TILE_UNIT, false);
    unit->setTile(ship->getTile());
    unit->setStartNumber(ship->getStartNumber());
}

Skill *GameEngine::FindSkill(int type)
{
    int i;
    for(i = 0; i < m_pData->skillList.size(); i++)
    {
        if(m_pData->skillList[i]->getType() == type)
        {
            return m_pData->skillList[i];
        }
    }
    return NULL;
}

//
// $Id: gameEngine.cpp,v 1.20 2004/06/23 15:37:05 sikon Exp $
//

