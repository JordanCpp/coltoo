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
// FILE		: graphicsEngine.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: GraphicsEngine
//
// DESCRIPTION	: Handle all the drawing aspects of the game.
//

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "map.h"
#include <vector>
#include <string>
#include <iostream>
#include "globalData.h"
#include "unit.h"
// >>>
#include "skill.h"
// <<<
#include "OptionList.h"

using namespace std;

GraphicsEngine::GraphicsEngine()
{
    m_pGame = NULL;
    fullScreen = false;
    screenResX = -1;
    screenResY = -1;

    icon = screen = tilesheet1 = blender = tilesheetF = forestmask = NULL;
    tilesheetM = tilesheetR = extra1 = bck1 = mapback = mapsurf = NULL;
    shrd = pshrd = blender2 = messageold = messagenew = mask1 = Mmask = NULL;
    Rmask = map1 = cds1 = hcs1 = scrllbutup = scrllbutdwn = scrllbutbck = NULL;
    unitsS = uniticons = activebck = loadedbck = buildings1 = NULL;
    HCSWin[0] = HCSWin[1] = HCSWin[2] = HCSWin[3] = HCSWin[4] = NULL;

    tilesheetR3 = R3mask = NULL;

//added 6/1 2 new fonts
	  fontPushButtons = fontInformation = fontColNameCDS = fontColNameMap = NULL;
}

GraphicsEngine::GraphicsEngine(GameEngine* game)
: m_pGame(game)
{
    fullScreen = false;
    screenResX = -1;
    screenResY = -1;

    icon = screen = tilesheet1 = blender = tilesheetF = forestmask = NULL;
    tilesheetM = tilesheetR = extra1 = bck1 = mapback = mapsurf = NULL;
    shrd = pshrd = blender2 = messageold = messagenew = mask1 = Mmask = NULL;
    Rmask = map1 = cds1 = hcs1 = scrllbutup = scrllbutdwn = scrllbutbck = NULL;
    unitsS = uniticons = activebck = loadedbck = buildings1 = NULL;
    HCSWin[0] = HCSWin[1] = HCSWin[2] = HCSWin[3] = HCSWin[4] = NULL;

    tilesheetR3 = R3mask = NULL;

//added 6/1 2 new fonts
	  fontPushButtons = fontInformation = fontColNameCDS = fontColNameMap = NULL;
}

GraphicsEngine::~GraphicsEngine()
{
  if(icon) SDL_FreeSurface(icon);
  icon = NULL;

  if(screen) SDL_FreeSurface(screen);
  screen = NULL;

  if(tilesheet1) SDL_FreeSurface(tilesheet1);
  tilesheet1 = NULL;

  if(blender) SDL_FreeSurface(blender);
  blender = NULL;

  if(tilesheetF) SDL_FreeSurface(tilesheetF);
  tilesheetF = NULL;

  if(forestmask) SDL_FreeSurface(forestmask);
  forestmask = NULL;

  if(tilesheetM) SDL_FreeSurface(tilesheetM);
  tilesheetM = NULL;

  if(tilesheetR) SDL_FreeSurface(tilesheetR);
  tilesheetR = NULL;

  if(extra1) SDL_FreeSurface(extra1);
  extra1 = NULL;

  if(bck1) SDL_FreeSurface(bck1);
  bck1 = NULL;

  if(mapback) SDL_FreeSurface(mapback);
  mapback = NULL;

  if(mapsurf) SDL_FreeSurface(mapsurf);
  mapsurf = NULL;

  if(shrd) SDL_FreeSurface(shrd);
  shrd = NULL;

  if(pshrd) SDL_FreeSurface(pshrd);
  pshrd = NULL;

  if(blender2) SDL_FreeSurface(blender2);
  blender2 = NULL;

  if(messageold) SDL_FreeSurface(messageold);
  messageold = NULL;

  if(messagenew) SDL_FreeSurface(messagenew);
  messagenew = NULL;

  if(mask1) SDL_FreeSurface(mask1);
  icon = NULL;

  if(Mmask) SDL_FreeSurface(Mmask);
  Mmask = NULL;

  if(Rmask) SDL_FreeSurface(Rmask);
  Rmask = NULL;

  if(map1) SDL_FreeSurface(map1);
  map1 = NULL;

  if(cds1) SDL_FreeSurface(cds1);
  cds1 = NULL;

  if(hcs1) SDL_FreeSurface(hcs1);
  hcs1 = NULL;

  if(scrllbutup) SDL_FreeSurface(scrllbutup);
  scrllbutup = NULL;

  if(scrllbutdwn) SDL_FreeSurface(scrllbutdwn);
  scrllbutdwn = NULL;

  if(scrllbutbck) SDL_FreeSurface(scrllbutbck);
  scrllbutbck = NULL;

  if(unitsS) SDL_FreeSurface(unitsS);
  unitsS = NULL;

  if(uniticons) SDL_FreeSurface(uniticons);
  uniticons = NULL;

  if(activebck) SDL_FreeSurface(activebck);
  activebck = NULL;

  if(loadedbck) SDL_FreeSurface(loadedbck);
  loadedbck = NULL;

  if(buildings1) SDL_FreeSurface(buildings1);
  buildings1 = NULL;

  for(int i = 0; i < 5; i++ )
  {
    if(HCSWin[i]) SDL_FreeSurface(HCSWin[i]);
    HCSWin[i] = NULL;
  }

  if(tilesheetR3) SDL_FreeSurface(tilesheetR3);
  tilesheetR3 = NULL;

  if(R3mask) SDL_FreeSurface(R3mask);
  R3mask = NULL;
  quitTrueType();

  #ifdef DEBUG
  cout<<"Quiting SDL"<<endl;
  #endif
  SDL_Quit();
}

bool GraphicsEngine::Init(void)
{
    GlobalData* data = m_pGame->GetData();
    OptionList* opts = m_pGame->GetOptions();

    #ifdef DEBUG
    cout<<"  Initializing GraphicsEngine"<<endl;
    #endif
    if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<0)
    {
        cout << "Unable to init SDL; " << SDL_GetError() << endl;
        return false;
    }

    fullScreen = true;screenResX = data->x_res; screenResY = data->y_res;

    //SDL_WM_SetCaption("Coltoo", "Coltoo");

    #ifdef DEBUG
    cout << "   Loading icon..." << endl;
    #endif
    //SDL_WM_SetIcon must use SDL_LoadBMP. SDL_Image needs the video mode
    //to be set before loading images, which is not compatible with the
    //method SDL_WM_SetIcon.
    icon = SDL_LoadBMP("data/graphics/col2ico.bmp");

    //if(!icon) cout << "Couldn't load icon col2ico.bmp: " << SDL_GetError() << endl;
	//else SDL_WM_SetIcon(icon, NULL);

    #ifdef DEBUG
    cout << "   Setting video mode..." << endl;
    #endif
    if(opts->WindowMode() == IDO_FULLSCRN)
    {
        _Window = SDL_CreateWindow("My Game Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screenResX, screenResY,
            SDL_WINDOW_SHOWN);
    }
    else
    {
        _Window = SDL_CreateWindow("My Game Window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screenResX, screenResY,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    }

    screen = SDL_GetWindowSurface(_Window);

    if(!screen)
    {
        cout << "Unable to set " << screenResX << "x" << screenResY
             << " video:\n" << SDL_GetError() << endl;
        return false;
    }
    #ifdef DEBUG
    cout << "   Loading images..." << endl;
    #endif
    /*loads the pngs and creates needed surfaces*/
    if(!InitImages())
    {
      cout << "InitImages failed.\n";
      return false;
    }

	//Init true type fonts
    if(!initTrueType())
    {
      cout << "initTrueType failed.\n";
      return false;
    }

    #ifdef DEBUG
    cout << "   Images and TrueType initialized" << endl;
    #endif
//from initarrays1.cpp - begin
    int x = 0, y = 0;

    for(y=0;y<3;y++)
    {
        for(x=0;x<13;x++)
        {
            DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[y],
                     data->tw,data->th,data->tilex[x],data->tiley[0]);
            DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[y],
                     data->tw,data->th,data->tilex[x],data->tiley[0]);
            DrawSURF(blender2,pshrd,data->tilex[x],data->tiley[y]);
        }
        FillRect(blender,data->tilex[11],data->tiley[y],data->tw,data->th,0,0,0);
    }

    for(x=0;x<13;x++)
    {
        DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[0],
                 data->tw,data->th,data->tilex[0],data->tiley[1]);
        DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[1],
                 data->tw,data->th,data->tilex[1],data->tiley[1]);
        DrawTILE(blender,tilesheet1,data->tilex[x],data->tiley[2],
                 data->tw,data->th,data->tilex[2],data->tiley[1]);

        DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[0],
                 data->tw,data->th,data->tilex[0],data->tiley[1]);
        DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[1],
                 data->tw,data->th,data->tilex[1],data->tiley[1]);
        DrawTILE(blender2,tilesheet1,data->tilex[x],data->tiley[2],
                 data->tw,data->th,data->tilex[2],data->tiley[1]);
    }
//from initarrays1.cpp - end
    return true;
}

bool GraphicsEngine::splash()
{
    OptionList* opts = m_pGame->GetOptions();

    #ifdef DEBUG
    cout<<"    Opening title: "<<opts->Opening()<<endl;
    #endif
    if(opts->Opening())
    {
        /*display the opening title*/
        SDL_Surface *opening = NULL;
//      opening = ImageLoad("data/graphics/col2.bmp");
        opening = ImageLoad("data/graphics/coltoo2.jpg");
        if (!opening)
        {
            cout << "splash failed with image col2.jpg :" << SDL_GetError() << endl;
            return false;
        }

        #ifdef DEBUG
        cout<<"    Opening delay: "<<opts->OpeningDelay()<<endl;
        #endif
        DrawSURF(screen,opening,227,295);
        UpdateScreen();
        SDL_FreeSurface(opening);
        SDL_Delay(opts->OpeningDelay());
    }

    #ifdef DEBUG
    cout<<"    Splash screen: "<<opts->Splash()<<endl;
    #endif
    if(opts->Splash())
    {
        SDL_Surface *startUrkki = NULL;
        startUrkki = ImageLoad("data/graphics/start.png");
        if (!startUrkki)
        {
            cout << "startUrkki failed.\n";
            return false;
        }

        #ifdef DEBUG
        cout<<"    Splash delay: "<<opts->SplashDelay()<<endl;
        #endif
        DrawSURF(screen,startUrkki,0,0);
        UpdateScreen();
        SDL_FreeSurface(startUrkki);
        SDL_Delay(opts->SplashDelay());
    }

    return true;
}

void GraphicsEngine::UpdateScreen()
{
/*hides the cursor; updates the entire screen;
  shows the cursor again.*/

    SDL_ShowCursor(0);
    SDL_UpdateWindowSurface(_Window);
    SDL_ShowCursor(1);
}

void GraphicsEngine::UpdateScreen(int x,int y,int w,int h)
{
/*hides the cursor; updates a rectangular area of the screen;
  shows the cursor again.*/

   SDL_ShowCursor(0);
   SDL_UpdateWindowSurface(_Window);
   SDL_ShowCursor(1);
}

bool GraphicsEngine::drawMap(Map m,int centerX,int centerY)
{
	return true;
}

/*  InitImages :
    Load the tilesheets
    Create needed Surfaces
    Create Masks (images for the partial shroud)
    Set the 'alpha' for the masks (semi-transparent)
*/
bool GraphicsEngine::InitImages()
{
    GlobalData* data = m_pGame->GetData();

    tilesheet1  = ImageLoad("data/graphics/tsheet1.png");
    if(!tilesheet1)
    {
       cout << "tsheet1 couldn't be loaded.\n";
       return false;
    }
    #ifdef DEBUG
    cout << "    tsheet1 loaded" << endl;
    #endif
    extra1      = ImageLoad("data/graphics/tsheetxtra1.png");
    if(!extra1)
    {
       cout << "extra1 (tsheetxtra1.png) couldn't be loaded.\n";
       return false;
    }

    messagenew  = ImageLoad("data/graphics/message.png");
    if(!messagenew)
    {
       cout << "messagenew (message.png) couldn't be loaded.\n";
       return false;
    }

    messageold  = ImageLoad("data/graphics/message.png");
    if(!messageold)
    {
       cout << "messageold (message.png) couldn't be loaded.\n";
       return false;
    }

    tilesheetF  = ImageLoad("data/graphics/tsheetF.png");
    if(!tilesheetF)
    {
       cout << "tsheetF (tsheetF.png) couldn't be loaded.\n";
       return false;
    }

    data->SoLfont1[0] = ImageLoad("data/graphics/SoLfont1.png");
    if (!data->SoLfont1[0])
    {
      cout << "SoLfont1 (SoLfont1.png) couldn't be loaded.\n";
      return false;
    }
    #ifdef DEBUG
    cout << "    SoLFont1 loaded" << endl;
    #endif

    data->SoLfont1[1] = SetFontColor(data->SoLfont1[0],data->text1color[0],
                                     data->text1color[1],data->text1color[2],
                                     data->text1color[3],data->text1color[4],
                                     data->text1color[5]);
    data->SoLfont1[2] = SetFontColor(data->SoLfont1[0],data->text1color[6],
                                     data->text1color[7],data->text1color[8],
                                     data->text1color[9],data->text1color[10],
                                     data->text1color[11]);
    data->SoLfont1[3] = SetFontColor(data->SoLfont1[0],data->text1color[12],
                                     data->text1color[13],data->text1color[14],
                                     data->text1color[15],data->text1color[16],
                                     data->text1color[17]);

    buildings1  = ImageLoad("data/graphics/buildings1.png");
    if(!buildings1)
    {
       cout << "buildings1 (buildings1.png) couldn't be loaded.\n";
       return false;
    }

    forestmask  = CreateMask(tilesheetF);
    if(!forestmask)
    {
       cout << "forestmask couldn't be created.\n";
       return false;
    }
    //SDL_SetAlpha(forestmask,SDL_SRCALPHA|SDL_RLEACCEL,128);

    mask1         =    CreateMask(tilesheet1);
    if(!mask1)
    {
       cout << "mask1 couldn't be created.\n";
       return false;
    }
    //SDL_SetAlpha(mask1,SDL_SRCALPHA|SDL_RLEACCEL,128);

    tilesheetM    =    ImageLoad("data/graphics/tsheetM.png");
    if(!tilesheetM)
    {
       cout << "tsheetM (tsheetM.png) couldn't be loaded.\n";
       return false;
    }

    Mmask         =    CreateMask(tilesheetM);
    if(!Mmask)
    {
       cout << "Mmask couldn't be created.\n";
       return false;
    }
    //SDL_SetAlpha(Mmask,SDL_SRCALPHA|SDL_RLEACCEL,128);

    tilesheetR    =    ImageLoad("data/graphics/tsheetR.png");
    if(!tilesheetR)
    {
       cout << "tsheetR (tsheetR.png) couldn't be loaded.\n";
       return false;
    }

    Rmask         =    CreateMask(tilesheetR);
    if(!Rmask)
    {
       cout << "Rmask couldn't be created.\n";
       return false;
    }
    //SDL_SetAlpha(Rmask,SDL_SRCALPHA|SDL_RLEACCEL,128);

    blender       =    CreateSurface(screen,989,154);
    blender2      =    CreateSurface(screen,989,154);

    map1          =    CreateSurface(screen,screenResX,screenResY);
    cds1          =    CreateSurface(screen,screenResX,screenResY);
    hcs1          =    CreateSurface(screen,screenResX,screenResY);
    bck1          =    CreateSurface(screen,75/*tw*/,50/*th*/);
    mapback       =    CreateSurface(screen,screenResX,screenResY);

    shrd          =    CreateSurface(screen,75,50);
    if(!shrd)
    {
       cout << "shrd couldn't be created.\n";
       return false;
    }
    FillRect(shrd,0,0,75,50,0,0,0);
    pshrd         =    CreateSurface(screen,75,50);
    if(!pshrd)
    {
       cout << "pshrd couldn't be created.\n";
       return false;
    }
    FillRect(pshrd,0,0,75,50,0,0,0);

    //SDL_SetAlpha(pshrd,SDL_SRCALPHA|SDL_RLEACCEL,128);

    unitsS=ImageLoad("data/graphics/unitsS.png");
    if(!unitsS)
    {
       cout << "unitsS (unitsS.png) couldn't be loaded.\n";
       return false;
    }

    loadedbck     =    CreateSurface(screen,32,25);
    activebck     =    CreateSurface(screen,32,25);

    uniticons     =    ImageLoad("data/graphics/units.png");
    if(!uniticons)
    {
       cout << "units (units.png) couldn't be loaded.\n";
       return false;
    }

    for(int i=0;i<4;i++)
    {
         HCSWin[i]=CreateSurface(screen,235,112);
    }

    //provisional river links
    tilesheetR3   =    ImageLoad("data/graphics/tsheetR3.png");
    if(!tilesheetR3)
    {
       cout << "tsheetR3 (tsheetR3.png) couldn't be loaded.\n";
       return false;
    }

    R3mask        =    CreateMask(tilesheetR3);
    if(!R3mask)
    {
       cout << "R3mask couldn't be created.\n";
       return false;
    }
    //SDL_SetAlpha(R3mask,SDL_SRCALPHA|SDL_RLEACCEL,128);

    if(blender && blender2 && map1 && cds1 && hcs1 && bck1 &&
       mapback && loadedbck && activebck && uniticons &&
       HCSWin[0] && HCSWin[1] && HCSWin[2] && HCSWin[3] &&
       data->SoLfont1[1] && data->SoLfont1[2] && data->SoLfont1[3])
    {
        #ifdef DEBUG
	cout << "    ImageLoad exited successfully" << endl;
	#endif
        return true;
    }
    else return false;
}

bool GraphicsEngine::drawBackground(void)
{
    if(DrawBG() == false) return false;

    Border(screen,979,384,29,11);                     /*MF block*/

// >>>
    FillRect(screen, 635, 3, 85, 14, 48, 48, 48);            /*year block*/
    Border(screen, 635, 3, 84, 13);

    FillRect(screen, 845, 357, 122, 39, 48, 48, 48);
    Border(screen, 845, 357, 121, 38);
// <<<

    FillRect(screen,764,3,93,14,48,48,48);            /*gold*/
    Border(screen,764,3,92,13);
    UpdateGold(0);

    Border(screen,8,25,824,699);

    SDL_EventState(SDL_KEYUP, SDL_IGNORE);
    return true;
}

bool GraphicsEngine::IsOnScreen(int x, int y)
{
  if (x < startX || x >= startX+GetScreenWidth() ||
      y < startY || y >= startY+GetScreenHeight() )
  {
    return false; //not displayed on the screen
  }
  else return true;
}

void GraphicsEngine::UpdateUnitInfo(Unit *unit)
{
    GlobalData* data = m_pGame->GetData();

    #ifdef DEBUG
    cout<<data->playerlist[unit->getNation()]->country.abbrev<<unit->getName().c_str()<<endl;
    #endif
    FillRect(screen, 845, 357, 122, 39, 48, 48, 48);
    drawString2(screen, data->SoLfont1[3],  847, 359, "%s %s",
    data->playerlist[unit->getNation()]->country.abbrev.c_str(), unit->getName().c_str());

    drawString2(screen, data->SoLfont1[3], 847, 372, "%s", unit->getClassType().c_str());

    if(unit->getTransportCapacity())
    {
        drawString2(screen, data->SoLfont1[3], 847, 385, "Passengers: %i/%i",
            unit->getNumberOfPassenger(), unit->getTransportCapacity());
    }
    else if(unit->getSkillName())
    {
        drawString2(screen, data->SoLfont1[3], 847, 385, "%s", unit->getSkillName());
    }
}


//
// $Id: graphicsEngine.cpp,v 1.24 2004/06/23 15:37:05 sikon Exp $
//

