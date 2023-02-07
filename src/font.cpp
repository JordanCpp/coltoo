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

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string>

#include "graphicsEngine.h"

using namespace std;


/*---------------------------drawString----------------------------*/
void GraphicsEngine::drawString(SDL_Surface *screen, SDLFont *font,int x,int y,bool shadow,
                                char *str,...)
{

	//TEMPORARY drawString WRAPPER
	//Brett,November 2003

	char buffer[1024];

	va_list ap;
    va_start(ap,str);
    vsprintf(buffer,str,ap);
    va_end(ap);

	string tmpString = buffer;
	
	//Erase last char
	tmpString = tmpString.erase(tmpString.size()-1,1);

	if(shadow){
		SDL_Color black = { 0x00, 0x00, 0x00, 0 };

		blitString(screen,font->font,x+1,y+1,(char *)tmpString.c_str(),black);
	}

		blitString(screen,font,x,y,(char *)tmpString.c_str());

}

//
// $Id: font.cpp,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

