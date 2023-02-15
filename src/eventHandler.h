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
// FILE		: eventHandler.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: EventHandler
//
// DESCRIPTION	: Basis class for event handling: mouse, keyb, sound...
//

#ifndef eventHandler_H
#define eventHandler_H

#include <SDL.h>
#include "globalData.h"
#include "gameEngine.h"
#include "graphicsEngine.h"
//using namespace std;

//forward declarations

class EventHandler
{
public:
	bool WaitKey(int key);
	bool WaitAnyKey();
	void Update();

//Constructor, destructor
	EventHandler(GlobalData* globalData);
    ~EventHandler();

//Methods
    bool Init(void);

private:
	void checkMouse(enum context cont,int x, int y);
	void checkKeyBoard(enum context cont, int key);
	GlobalData* _GlobalData;
};

#endif //eventHandler_H


//
// $Id: eventHandler.h,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

