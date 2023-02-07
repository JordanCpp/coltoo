/*
 *  Copyright (C) 2002 Travis Wells<traviswells@mchsi.com> 
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

/*Modified on December 16, 2002 by John D. Dilley*/
/*Modified on November  8, 2003 by Goose Bonis   */

#include <cstdio>
#include <cstdlib>
#include "graphicsEngine.h"
using namespace std;
				
SDL_Surface * GraphicsEngine::CreateMask(SDL_Surface *from)
{
	if(!from)return NULL;
	
	// Create new surface just like the old one.
	//New surface width and height modified by JDD.
	SDL_Surface *temp=SDL_CreateRGBSurface(SDL_SWSURFACE,1217,288,
                from->format->BitsPerPixel,from->format->Rmask,
                from->format->Gmask,from->format->Bmask,
                from->format->Amask);
	if(!temp)return NULL;
	
	// Copy the original image into the mask surface.
	//Rectangle dest2 added by JDD.
	SDL_Rect r;
	r.x=0;r.y=0;
    SDL_Rect dest2;
    dest2.x=0;dest2.y=0;
    dest2.w=1217;dest2.h=288;
	SDL_BlitSurface(from,&dest2,temp,&r); 

	//Ret is temporary storage, black and magicpink store the colors so we don't have to recalc them every pixel.
	Uint32 ret,black,magicpink;
	black=SDL_MapRGB(temp->format,0,0,0);
	magicpink=SDL_MapRGB(temp->format,255,0,255);

	// Lock the surface for direct pixel access (if needed)
	if(SDL_MUSTLOCK(temp))SDL_LockSurface(temp);
	
	for(int q=0;q<temp->h;q++){  			// Rows
		for(int w=0;w<temp->w;w++){  		//Columns
			ret=getpixel(temp,w,q); 
			if(ret!=magicpink)putpixel(temp,w,q,black);
		}
	}
	
	if(SDL_MUSTLOCK(temp))SDL_UnlockSurface(temp);  // Unlock the surface
	
	return temp;
	
}

// getpixel and putpixel are from the SDL guide.
Uint32 GraphicsEngine::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


void GraphicsEngine::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void GraphicsEngine::FillSurface(SDL_Surface *temp,Uint32 r,Uint32 g,Uint32 b)
{
	Uint32 color;
	color=SDL_MapRGB(temp->format,r,g,b);
	SDL_FillRect(temp,NULL,color);
}

//
// $Id: makemask.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

