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
// FILE		: main.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: main
//
// DESCRIPTION	: program launcher.
//

#include <iostream>
#include "gameEngine.h"
#include <SDL.h>

#ifdef DEBUG
#include <fstream>
#endif

int main(int argc, char* argv[])
{
    GameEngine colToo;

#if defined(DEBUG) //&& defined(TEXTLOG) //log output to stdout.txt file
    freopen("./stdout.txt", "w", stdout);
    freopen("./stderr.txt", "w", stderr);
#endif

    if (colToo.Init(argc, argv))
        colToo.GameLoop();

    return 0;
}

//
// $Id: main.cpp,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

