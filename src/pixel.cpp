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
#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include "graphicsEngine.h"

/*------------------------DrawPixel-------------------------------*/
void GraphicsEngine::DrawPixel(SDL_Surface *screen, int x, int y,
                                    Uint8 R, Uint8 G, Uint8 B)
{
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    switch (screen->format->BytesPerPixel)
    {

    /* Assuming 8-bpp */  
    case 1: 
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
      
/* Probably 15-bpp or 16-bpp */      
    case 2: 
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
      
/* Slow 24-bpp mode, usually not used */      
    case 3: 
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
      
/* Probably 32-bpp */
    case 4:
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
    }
}

/*--------------------------Slock-----------------------------*/
void GraphicsEngine::Slock(SDL_Surface *screen)
{
    if(SDL_MUSTLOCK(screen)){if(SDL_LockSurface(screen)<0){return;}}
}

/*--------------------------Sulock-----------------------------*/
void GraphicsEngine::Sulock(SDL_Surface *screen)
{
    if(SDL_MUSTLOCK(screen)){SDL_UnlockSurface(screen);}
}

/*--------------------------FillRect-----------------------------*/
void GraphicsEngine::FillRect(SDL_Surface *temp,int x,int y,int w,int h,
                              Uint32 r,Uint32 g,Uint32 b)
{
	Uint32 color;
	SDL_Rect dest;
    dest.x=x;dest.y=y;
    dest.w=w;dest.h=h;
	color=SDL_MapRGB(temp->format,r,g,b);
	SDL_FillRect(temp,&dest,color);
}

/*--------------------------Border--------------------------------*/
void GraphicsEngine::Border(SDL_Surface *temp,int x1,int y1,int w1,int h1)
{
    DrawLine(temp,x1-3,y1-3,x1+w1+2,y1-3,1,167,116,33);
    DrawLine(temp,x1-3,y1-3,x1-3,y1+h1+2,0,167,116,33);
    DrawLine(temp,x1-2,y1-2,x1+w1+2,y1-2,1,167,116,33);
    DrawLine(temp,x1-2,y1-2,x1-2,y1+h1+2,0,167,116,33);
    DrawLine(temp,x1-1,y1-1,x1+w1+1,y1-1,1,0,0,0);
    DrawLine(temp,x1-1,y1-1,x1-1,y1+h1+2,0,0,0,0);
    DrawLine(temp,x1-3,y1+h1+3,x1+w1+3,y1+h1+3,1,187,116,33);
    DrawLine(temp,x1+w1+3,y1-3,x1+w1+3,y1+h1+3,0,187,116,33);
    DrawLine(temp,x1-2,y1+h1+2,x1+w1+2,y1+h1+2,1,187,116,33);
    DrawLine(temp,x1+w1+2,y1-2,x1+w1+2,y1+h1+2,0,187,116,33);
    DrawLine(temp,x1-1,y1+h1+1,x1+w1+1,y1+h1+1,1,229,200,95);
    DrawLine(temp,x1+w1+1,y1-1,x1+w1+1,y1+h1+1,0,229,200,95);
}

/*--------------------------DrawLine------------------------------*/
void GraphicsEngine::DrawLine(SDL_Surface *temp,int x1,int y1,int x2,int y2,int flag,
                              Uint8 r,Uint8 g,Uint8 b)
{
    int x,y;

    Slock(temp);
    if(flag==1){for(x=x1;x<x2+1;x++){DrawPixel(temp,x,y1,r,g,b);}}
    else {for(y=y1;y<y2+1;y++){DrawPixel(temp,x1,y,r,g,b);}}
    Sulock(temp);
}

/*--------------------------DrawRect------------------------------*/
void GraphicsEngine::DrawRect(SDL_Surface *temp,int x1,int y1,int w,int h,
        Uint8 r,Uint8 g,Uint8 b)
{
    int x,y;

    Slock(temp);
    for(x=x1;x<x1+w+1;x++)
    {
        DrawPixel(temp,x,y1,r,g,b);
        DrawPixel(temp,x,y1+h,r,g,b);
    }

    for(y=y1+1;y<y1+h;y++)
    {
        DrawPixel(temp,x1,y,r,g,b);
        DrawPixel(temp,x1+w,y,r,g,b);
    }
    Sulock(temp);
}


//
// $Id: pixel.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

