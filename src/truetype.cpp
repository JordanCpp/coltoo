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
// FILE		: truetype.cpp
//
// VERSION	: 0.2
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: GameEngine
//
// DESCRIPTION	: Handle true type drawing (fonts)
//

#include "graphicsEngine.h"

/*-----------------------------initTrueType------------------------------*/
bool GraphicsEngine::initTrueType()
{
	fontPushButtons = new SDLFont();
	fontInformation = new SDLFont();
	fontColNameCDS = new SDLFont(); //new font for colony name on cds
	fontColNameMap = new SDLFont(); //new font for colony names on map 	

	if(TTF_Init()==-1) {

		printf("TTF_Init: %s\n", TTF_GetError());

		return false;
	}

	fontPushButtons->font = TTF_OpenFont("data/fonts/Vera.ttf", 12);
	fontInformation->font = TTF_OpenFont("data/fonts/Vera.ttf", 14);
	fontColNameCDS->font = TTF_OpenFont("data/fonts/Vera.ttf", 20);
	fontColNameMap->font = TTF_OpenFont("data/fonts/Vera.ttf", 16);

	if(!fontPushButtons || !fontInformation || !fontColNameCDS || !fontColNameMap)
  {
		cout << "TTF_OpenFont: " << TTF_GetError() << endl;
		return false;
	}

	SDL_Color yellow = { 0xFF, 0xFF, 0x00, 0 };
	SDL_Color black  = { 0x00, 0x00, 0x00, 0 };
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
	SDL_Color dullYellow = { 0xCC, 0xCC, 0x00, 0 };

	fontPushButtons->color = yellow;
	fontInformation->color = black;
	fontColNameCDS->color = dullYellow;
	fontColNameMap->color = white;

	return true;
}

/*-----------------------------quitTrueType------------------------------*/
void GraphicsEngine::quitTrueType()
{
    if(fontPushButtons != NULL)
    {
        #ifdef DEBUG
        cout<<"  deleting font push buttons {"<<endl;
        #endif
        if(fontPushButtons->font)
        {
            #ifdef DEBUG
            cout<<"    Closing Font"<<endl;
            #endif
            TTF_CloseFont(fontPushButtons->font);
        }
        #ifdef DEBUG
        cout<<"    Releasing Font"<<endl;
        #endif
        delete fontPushButtons;
        #ifdef DEBUG
        cout<<"  }"<<endl;
        #endif
    }
    fontPushButtons = NULL;

    if(fontInformation != NULL)
    {
        #ifdef DEBUG
        cout<<"  deleting font information {"<<endl;
        #endif
        if(fontInformation->font)
        {
            #ifdef DEBUG
            cout<<"    Closing Font"<<endl;
            #endif
            TTF_CloseFont(fontInformation->font);
        }
        #ifdef DEBUG
        cout<<"    Releasing Font"<<endl;
        #endif
        delete fontInformation;
        #ifdef DEBUG
        cout<<"  }"<<endl;
        #endif
    }
    fontInformation = NULL;

    if(fontColNameCDS != NULL)
    {
        #ifdef DEBUG
        cout<<"  deleting font ColName CDS {"<<endl;
        #endif
        if(fontColNameCDS->font)
        {
            #ifdef DEBUG
            cout<<"    Closing Font"<<endl;
            #endif
            TTF_CloseFont(fontColNameCDS->font);
        }
        #ifdef DEBUG
        cout<<"    Releasing Font"<<endl;
        #endif
        delete fontColNameCDS;
        #ifdef DEBUG
        cout<<"  }"<<endl;
        #endif
    }
    fontColNameCDS = NULL;

    if(fontColNameMap != NULL)
    {
        #ifdef DEBUG
        cout<<"  deleting font ColName Map {"<<endl;
        #endif
        if(fontColNameMap->font)
        {
            #ifdef DEBUG
            cout<<"    Closing Font"<<endl;
            #endif
            TTF_CloseFont(fontColNameMap->font);
        }
        #ifdef DEBUG
        cout<<"    Releasing Font"<<endl;
        #endif
        delete fontColNameMap;
        #ifdef DEBUG
        cout<<"  }"<<endl;
        #endif
    }
    fontColNameMap = NULL;
  
    #ifdef DEBUG
    cout<<"  TTF Quiting"<<endl;
    #endif
    TTF_Quit();	
}

/*-----------------------------blitString------------------------------*/
void GraphicsEngine::blitString(SDL_Surface *screen,TTF_Font *font,int x,int y,
								char *str,SDL_Color color)
{
	SDL_Surface *text_surface;
	SDL_Rect destinationRect;

    destinationRect.x=x;
    destinationRect.y=y;

	text_surface = TTF_RenderText_Blended(font,str,color);

	SDL_BlitSurface(text_surface,NULL,screen,&destinationRect);

	SDL_FreeSurface(text_surface);
}

/*-----------------------------blitString------------------------------*/
void GraphicsEngine::blitString(SDL_Surface* screen,SDLFont *font,int x,int y,char *str)
{
	blitString(screen,font->font,x,y,str,font->color);	
}

//
// $Id: truetype.cpp,v 1.11 2004/06/23 15:37:05 sikon Exp $
//

