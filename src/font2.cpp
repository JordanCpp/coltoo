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
#include <cstdarg>
#include <cstring>
#include <SDL.h>

#include "graphicsEngine.h"

/*---------------------------drawString2--------------------------*/
void GraphicsEngine::drawString2(SDL_Surface *screen,SDL_Surface *font,
                                 int x,int y,char *str,...)
{
    char string[1024];
    int xx=0,xpos[128],ypos=1,i,x2;

    va_list ap;
    va_start(ap,str);
    vsprintf(string,str,ap);
    va_end(ap);

    int len=strlen(string);

    x2=1;
    for(i=0;i<128;i++){xpos[i]=x2;x2+=7;}
    
    for(i=0;i<len;i++)
    {  
        DrawTILE(screen,font,xx+x,y,6,11,xpos[(int)string[i]],ypos);
        xx+=6+1;
    }
}

/*---------------------------stringWidthSoL1---------------------------*/
int GraphicsEngine::stringWidthSoL1(char *str,...)
{
    char string[1024];

    va_list ap;
    va_start(ap,str);
    vsprintf(string,str,ap);
    va_end(ap);

    int len=strlen(string),xx=0;
    xx=(6*len)+(len-1);
    return xx;
}

/*---------------------------drawString3---------------------------*/
void GraphicsEngine::drawString3(SDL_Surface *screen,SDL_Surface *font,int x,
                                 int y, Uint32 r1,Uint32 g1,Uint32 b1,
                                 Uint32 r2,Uint32 g2,Uint32 b2,char *str,...)
{
    char string[1024];
    int xx=0,xpos[128],ypos=1,i,x2,q;//,w;

    va_list ap;
    va_start(ap,str);
    vsprintf(string,str,ap);
    va_end(ap);

    int len=strlen(string);
    SDL_Surface *temp=SDL_CreateRGBSurface(SDL_SWSURFACE,font->w,font->h,
                                           font->format->BitsPerPixel,
                                           font->format->Rmask,
                                           font->format->Gmask,
                                           font->format->Bmask,
                                           font->format->Amask);

    FillSurface(temp,255,0,255);               
    DrawSURF(temp,font,0,0);

    Uint32 ret,newcolor,yellow,black,newshade;
    newcolor=SDL_MapRGB(temp->format,r1,g1,b1);
    yellow=SDL_MapRGB(temp->format,255,255,0);
    newshade=SDL_MapRGB(temp->format,r2,g2,b2);
	black=SDL_MapRGB(temp->format,0,0,0);

    /*lock the surface*/	
    if(SDL_MUSTLOCK(temp))SDL_LockSurface(temp);

    for(q=0;q<temp->h;q++)
    {
        for(int w=0;w<temp->w;w++)
        {
            ret=getpixel(temp,w,q);
            if(ret==black){putpixel(temp,w,q,newshade);continue;}
            if(ret==yellow){putpixel(temp,w,q,newcolor);}			
        }
    }

    /*Unlock the surface*/	
    if(SDL_MUSTLOCK(temp))SDL_UnlockSurface(temp);

    x2=1;
    for(i=0;i<128;i++){xpos[i]=x2;x2+=7;}

    for(i=0;i<len;i++)
    {  
        DrawTILE(screen,temp,xx+x,y,6,11,xpos[(int)string[i]],ypos);
        xx+=6+1;
    }

    SDL_FreeSurface(temp);
}

/*---------------------------SetFontColor-------------------------*/
SDL_Surface* GraphicsEngine::SetFontColor(SDL_Surface *font,Uint32 r1,Uint32 g1,
                                        Uint32 b1,Uint32 r2,Uint32 g2,Uint32 b2)
{
    SDL_Surface *temp=SDL_CreateRGBSurface(SDL_SWSURFACE,font->w,font->h,
                                           font->format->BitsPerPixel,
                                           font->format->Rmask,
                                           font->format->Gmask,
                                           font->format->Bmask,
                                           font->format->Amask);

    Uint32 ret,newcolor,yellow,black,newshade;
    int q,w;

    FillSurface(temp,255,0,255);               
    DrawSURF(temp,font,0,0);

	newcolor = SDL_MapRGB(temp->format,r1,g1,b1);
	yellow   = SDL_MapRGB(temp->format,255,255,0);
	newshade = SDL_MapRGB(temp->format,r2,g2,b2);
	black    = SDL_MapRGB(temp->format,0,0,0);

	if(SDL_MUSTLOCK(temp)){SDL_LockSurface(temp);}

	for(q=0;q<temp->h;q++)
    {
		for(w=0;w<temp->w;w++)
        {
			ret=getpixel(temp,w,q);
            if(ret==black){putpixel(temp,w,q,newshade);continue;}
                if(ret==yellow){putpixel(temp,w,q,newcolor);}			
        }
    }

	if(SDL_MUSTLOCK(temp))SDL_UnlockSurface(temp);

    return temp;
}


//
// $Id: font2.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

