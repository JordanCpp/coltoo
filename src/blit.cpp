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
#include <SDL_image.h>
#include <cstdlib>
#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"

#define RED_TRANSPARENCY 255
#define GREEN_TRANSPARENCY 0
#define BLUE_TRANSPARENCY 255

/*Loads bmp into memory*/
SDL_Surface* GraphicsEngine::ImageLoad(char *file)
{
    SDL_Surface *temp1 = NULL, *temp2 = NULL;
    temp1 = IMG_Load(file);
//    temp1 = SDL_LoadBMP(file);
    if (temp1)
    {
        temp2 = SDL_ConvertSurfaceFormat(temp1, SDL_GetWindowPixelFormat(_Window), 0);
        SDL_FreeSurface(temp1);
        return temp2;
    }
    else return NULL;
}

/*copies one part of a surface onto another surface*/
void GraphicsEngine::DrawTILE(SDL_Surface* to,SDL_Surface* from,int x,int y,
                              int w,int h,int x2,int y2)
{
    GlobalData * data = m_pGame->GetData();

    SDL_Rect dest;
    dest.x=x;
    dest.y=y;
    SDL_Rect dest2;
    dest2.x=x2;
    dest2.y=y2;
    dest2.w=w;
    dest2.h=h;
    /*Next line sets the transparent color for the copying*/
    SDL_SetColorKey(from, SDL_TRUE, SDL_MapRGB(from->format, data->red, data->green, BLUE_TRANSPARENCY));
    SDL_BlitSurface(from,&dest2,to,&dest);
}

/*copies a complete image onto another surface*/
void GraphicsEngine::DrawSURF(SDL_Surface* to,SDL_Surface* from,int x,int y)
{
    GlobalData * data = m_pGame->GetData();

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_SetColorKey(from, SDL_TRUE, SDL_MapRGB(from->format, data->red, data->green, BLUE_TRANSPARENCY));

    SDL_BlitSurface(from, NULL, to, &dest);
}

/*creates a new surface in the proper display format, using the surface given
  as example*/
SDL_Surface* GraphicsEngine::CreateSurface(SDL_Surface* scr,short w,short h)
{
	SDL_Surface *er;
	SDL_PixelFormat *form=scr->format;
	er=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,form->BitsPerPixel,
                            form->Rmask,form->Gmask,form->Bmask,form->Amask);
	return er;
}

//
// $Id: blit.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

