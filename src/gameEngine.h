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
// FILE		: gameEngine.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: GameEngine
//
// DESCRIPTION	: Main class for overall game control.
//

#ifndef gameEngine_H
#define gameEngine_H

#include <iostream>
#include <SDL_types.h>
#include "OptionList.h"

using namespace std;

//forward declarations
class EventHandler;
class GraphicsEngine;
class Map;
class Actor;
class Player; //add 15/6
class GlobalData;
class Unit;
// >>>
class Colony;
class Skill;
// <<<
class OptionList; //added 17/6

class GameEngine    //Controls everything in the game
{
public:

//Constructor, destructor
    GameEngine();
    ~GameEngine();

//Methods
    bool Init(int argc = 0, char  *argv[] = NULL);
    bool GameLoop(void);
    void unitLoop();

    GlobalData*		GetData()			{ return m_pData; }
    Map*			GetMap()			{ return m_pMap;  }
	GraphicsEngine*	GetGraphicsEngine()	{ return m_pGfxEngine;}
	EventHandler*	GetEventHandler()	{ return m_pKeyb; }
	OptionList*     GetOptions()        { return m_pOptions; } //added 17/6

    Unit *FindUnitAt(long tile, bool isBoat);
    Unit *PlaceNewUnit(int unitID, int nation);
    void UnitBoardShip(Unit *unit, Unit *ship);
    void CombatAnalysis(Unit *attacker, Unit *defender);
    Colony *PlaceColony(Unit *builder, long tile);
    Colony *FindColonyAt(long tile);
    Colony *FindColonyOf(int nation);
    Skill *FindSkill(int type);
    
    bool workPlayer(Uint8 nation, int unit, int& done);
    void workIndian(void);

private:
    GlobalData*       m_pData;       //Globals
    EventHandler*     m_pKeyb;       //Keyboard Handler
    EventHandler*     m_pSound;      //Sound Handler
    GraphicsEngine*   m_pGfxEngine;  //game Graphics engine
    Map*              m_pMap;        //global map
    OptionList*       m_pOptions;    //added 17/6; global game options
    Actor*            m_pPlayer;     //player data
    Actor*            m_pAI[10];     //other nations and tribes
};

#endif //gameEngine_H


//
// $Id: gameEngine.h,v 1.12 2004/06/23 15:37:05 sikon Exp $
//

