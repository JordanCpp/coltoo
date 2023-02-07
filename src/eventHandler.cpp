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
// FILE		: eventHandler.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: EventHandler
//
// DESCRIPTION	: Basis class for event handling: mouse, keyb, sound...
//

#include "eventHandler.h"
#include "globalData.h"

EventHandler::EventHandler()
{
	m_pGame = NULL;
}

EventHandler::EventHandler(GameEngine* game)
: m_pGame(game)
{
}

EventHandler::~EventHandler()
{
}

//Methods
bool EventHandler::Init(void)
{
    return true;
}

void EventHandler::Update(){

	SDL_Event event;
	GlobalData*		m_pData = m_pGame->GetData();


	while(SDL_WaitEvent(&event))
    {
		//Keyboard
		if(event.type == SDL_KEYDOWN){
			checkKeyBoard(m_pData->getContext(),event.key.keysym.sym);
		}

		//Mouse
		if(event.button.type==SDL_MOUSEBUTTONDOWN){
			int mouseX,mouseY;
			SDL_GetMouseState(&mouseX,&mouseY);
			checkMouse(m_pData->getContext(),mouseX,mouseY);
		}

		if(event.type == SDL_QUIT){
		}	
    }
}

bool EventHandler::WaitAnyKey()
{
	SDL_Event event;

	while(SDL_WaitEvent(&event))
    {
        if ( event.type == SDL_KEYDOWN )
                break;
    }
	return true;
}

bool EventHandler::WaitKey(int key)
{
	SDL_Event event;

	while(SDL_WaitEvent(&event))
    {
        if ( event.type == SDL_KEYDOWN )
        {
            if (event.key.keysym.sym == key)
                break;
        }
    }
	return true;
}

void EventHandler::checkKeyBoard(enum context cont, int key)
{
	if(cont == MAINSCREEN){
		switch(key){
		case SDLK_ESCAPE: break;
		case SDLK_KP_1:	  break;
		case SDLK_KP_2:	  break;
		case SDLK_KP_3:	  break;
		case SDLK_KP_4:	  break;
		case SDLK_KP_5:	  break;
		case SDLK_KP_6:	  break;
		case SDLK_KP_7:	  break;
		case SDLK_KP_8:	  break;
		case SDLK_KP_9:	  break;
		default: break;
		}
		

	}

	if(cont == HCS){
		switch(key){
		case SDLK_ESCAPE: break;
		default: break;
		}
	}

	if(cont == CDS){
		switch(key){
		case SDLK_ESCAPE: break;
		default: break;
		}
	}
}

void EventHandler::checkMouse(enum context cont, int x, int y)
{
	if(cont == MAINSCREEN){
	}
	if(cont == HCS){
	}
	if(cont == CDS){
	}
}

//
// $Id: eventHandler.cpp,v 1.8 2004/06/23 15:37:05 sikon Exp $
//

