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
// FILE		: graphicsEngine.h
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: GraphicsEngine
//
// DESCRIPTION	: Draws a Map , handle all the drawing aspects of the map.
//

#ifndef graphicsEngine_H
#define graphicsEngine_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "eventHandler.h"
#include "tile.h"

using namespace std;

#define UpdateScreen0 UpdateScreen
#define UpdateScreen1 UpdateScreen

//forward declarations
class Unit;
class OptionList; //added 17/6
struct SDL_Surface;

struct SDLFont
{
    TTF_Font	*font;
    SDL_Color	color;
};

class GraphicsEngine
{
public:
    GraphicsEngine(GlobalData* globalData, OptionList* optionList, Map* map);
    ~GraphicsEngine();

    bool splash();                             //shows the splash screen
    bool InitImages();                         //Load the tilesheets
    void UpdateScreen();
    void UpdateScreen(int x,int y,int w,int h);
    bool Init(void);
    bool drawMap(Map m,int centerX,int centerY);
    bool drawBackground(void);
    bool IsOnScreen(int x, int y);
    void UpdateUnitInfo(Unit *unit);

    Unit* FindUnitAt(long tile, bool isBoat);
    Colony* PlaceColony(Unit* builder, long tile);
    Colony* FindColonyAt(long tile);
    Colony* FindColonyOf(int nation);
    void CombatAnalysis(Unit* attacker, Unit* defender);

//Accessors
  unsigned int GetScreenWidth()  {return screenWidth; }
  unsigned int GetScreenHeight() {return screenHeight;}

//makemask.cpp
    SDL_Surface* CreateMask(SDL_Surface *from); //Returns a mask of the from
                                                //surface or NULL if something 
                                                //goes wrong
    unsigned int getpixel(SDL_Surface *surface, int x, int y);
    void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
    void FillSurface(SDL_Surface *temp,unsigned int r,
                     unsigned int g,unsigned int b);
//truetype.cpp
private:
	bool initTrueType();
	void quitTrueType();
	void blitString(SDL_Surface* screen,SDLFont *font,int x,int y,char *str);

public:
	void blitString(SDL_Surface* screen,TTF_Font *font,int x,int y,char *str,SDL_Color color);

//font.cpp
    void  fontDrawIMG(SDL_Surface* screen,SDL_Surface* img,int x,int y,
                      int w,int h,int x2,int y2);

    void  drawString(SDL_Surface *screen,SDLFont *font,int x,int y,bool shadow,
                     char *str,...);

    void  freeFont(SDLFont *font);

//font2.cpp
    void drawString2(SDL_Surface *screen,SDL_Surface *font,int x,int y,
                     char *str,...);
    int  stringWidthSoL1(char *str,...);
    void drawString3(SDL_Surface *screen,SDL_Surface *font,int x,int y,
                     unsigned int r1,unsigned int g1,unsigned int b1,
                     unsigned int r2,unsigned int g2,unsigned int b2,
                     char *str,...);
    SDL_Surface* SetFontColor(SDL_Surface *font,unsigned int r1,unsigned int g1,
                              unsigned int b1,unsigned int r2,unsigned int g2,
                              unsigned int b2);

//blit.cpp
    SDL_Surface* ImageLoad(char *file);
    SDL_Surface* CreateSurface(SDL_Surface* scr,short w,short h);
    void         DrawTILE(SDL_Surface* to,SDL_Surface* from,int x,int y,
                          int w,int h,int x2,int y2);
    void         DrawSURF(SDL_Surface* to,SDL_Surface* from,int x, int y);

//pixel.cpp
    void DrawPixel(SDL_Surface* screen, int x, int y, unsigned char R,
                   unsigned char G, unsigned char B);
    void Slock (SDL_Surface* screen);
    void Sulock(SDL_Surface* screen);
    void FillRect(SDL_Surface *temp,int x,int y,int w,int h, unsigned int r,
                   unsigned int g,  unsigned int b);
    void Border  (SDL_Surface *temp,int x1,int y1,int w1,int h1);
    void DrawLine(SDL_Surface *temp,int x1,int y1,int x2,int y2,int flag,
                  unsigned char r, unsigned char g,unsigned char b);
    void DrawRect(SDL_Surface *temp,int x1,int y1,int w,int h,
                  unsigned char r, unsigned char g,unsigned char b);

//bckgrnd.cpp
    bool DrawBG(void);

//CDS1.cpp
    void DrawCDS(void);
    void DrawCDSUnitList(int x, int y);
    void UpdateCDS(Colony *col);
    void UpdateCDSColName(Colony *col);
    void UpdateCDSFields(Colony *col);
    void UpdateCDSMarket(Colony *col);
    void UpdateCDSBuildings(Colony *col);

//display.cpp
    void DrawScene(void);
    void Reveal(void);
    void Reveal(int x, int y, int radius);
    void BlinkUnit(Unit * theUnit, long & LastUpdate, bool &blink, bool &a2);
    void SlideUnit(Unit *unit, short newloc, short oldloc);

//message.cpp
    void MessageWindow(int k);
    void RemoveRumor(void);
//    void Message(short count,short mess);
    void ShowSysMessage(int message);

	void DisplayMessage(string text,SDLFont *font,SDL_Surface* surf=NULL,SDL_Rect* pos=NULL);

//misc1.cpp
    void Buttons (int x1,int dx,int y1,int dy,int i,int x2,int y2,int w,int h);
    void Buttons2(int x1,int dx,int y1,int dy,int i,int x2,int y2,int x2b,
                  int w,int h);
    void UnitTerrainCheck(short turn);
    void SetGrid(void);
    void ScreenUpdate(void);
//    void UpdateScreen0(void);
//    void UpdateScreen1(int x,int y,int w,int h);
    void RemoveExtraSpaceH(SDL_Surface *from,int x,int y,int w,int h);
    void RemoveExtraSpaceV(SDL_Surface *from,int x,int y,int w,int h);
    int  RemoveExtraSpaceH2(SDL_Surface *from,int x,int y,int w,int h,int dh);
    void Buttons3(SDL_Surface *font,int x1,int dx,int y1,int dy,int i,
                  int x2,int y2,int w,int h);
    void Buttons4(SDL_Surface *font,int x1,int dx,int y1,int dy,int i,
                  int x2,int y2,int x2b,int w,int h);
    void UpdateGold(char scr);
    void SubtractGold(int cost);
    char CheckMouseButton(void);
//added 6/2
//function to place nationality boxes next to unit
    void NationBox(int x, int y, Uint8 nation, short pos, Uint8 order);
    void NationColors(Uint8 nation, short& r, short& g, short& b);

//terrain1.cpp
    void SetTerrain (void);
    void SetTerrain2(void);
    void SetTerrain3(void);
    void DrawRoad   (int rr,int x,long num);
    void Links1     (long ii,enum tileTypes e,int sn);
    Uint8 Rivers1(long ii);

//Drawcds1.cpp
    void DrawCDSMarket       (int x0,int y0);
    void DrawCDSSlots        (int x0,int y0);
    void DrawCDSConstruction (int x0,int y0);
    void DrawCDSFields       (int x0,int y0);
    void DrawCDSProduction   (int x0,int y0);
    void DrawCDSMapButton    (int x0,int y0);
    void DrawCDSSelected     (int x0,int y0);

//deuro4.cpp
    void Counter1(SDL_Surface *temp,int x,int y);
    void Counter2(char num,char counterspace,int x,int y);
    char Counter3(void);
    void Counter4(int x,int y,char counterspace);

//deuro1.cpp
    void DrawMarket1  (void);
    void HCSButtons   (void);
    void HCSDRecruit  (void);
    void HCSDPurchase (void);
    void HCSDTrain    (void);
    void HCSDRecruitHL(short recruitHL);
    void HCSDNewUnitHL(short newunitHL,SDL_Surface *temp,int Ustart,
                       char array1[][25],char array2[][25],char TorP);

//deuro3.cpp
    void SelectedShip1    (void);
    int  RecruitSelection1(void);
    void SelectedShipName (int num,char flag);
    int  SelectedShipPassengers(short n,char m);
    void ShipsInPortDisplay (int x,int y1,char start,char index,
                             char array[],short array2[]);
    void DocksWaitingDisplay(int x,int y1,char start,char index,
                             char array[]);
    void SelectedShipCargo  (short n,char m,int a);

//deuro2.cpp
    void DrawDocks1(void);
    int  PlaceNUDocks1(int x,int y1,char &Zstart,char ZIndex,
                       char Zarray[],SDL_Surface *temp);
    int  PlaceNUDocks2(int x,int y1,char &Zstart,char ZIndex,
                       char Zarray[],SDL_Surface *temp,short n);
    void HCSArrowButtons(int x1,int y1,int dx,int dy,int w1,int h1,
                         int x2,int y2,int dx2,int dy2,int w2,int h2,
                         int x3,int y3);
    void PTArrowShift(short &Zstart,char &ZHL,int i,int ii,
                      char array1[][25],char array2[][25],
                      char TorP,int x0,int y0,int w,int h,char limit,
                      char dz,char newhl);
    void BuyHireButton(char &ZIndex,char &Zstart,char array[],int x,
                       int y1,SDL_Surface *temp,short n);

//initarrays.cpp
    void InitArrays1(void);

//orders1.cpp
    void Orders   (int i);

//hcs1.cpp
    void DrawHCS         (void);
    void HCSRadioButtons1(void);

//recenter.cpp
    void ReCenter(void);
    void ReCenter(int x, int y);

//zoom.cpp
    void Zoom1  (void);
    void MiniMap(void);

//move.cpp
    void  MoveUnit(unsigned char move);
    short LegalTerrainCheck(const short sdir,const short mdir);

//Drawcds2.cpp
    void FillSlots1(int colnum);
    void DrawCDSFields2(long tile);
    void Links2(long ii,enum tileTypes e,long n[][4],int x0,int y0,int i);
    void DrawRoad2(long kx,long ky,int x,long num);
    void DrawRiver(long kx,long ky,int x,long num, int mouth);

//CDSmouse.cpp
    int CDSMouseCheck(int xM,int yM);

//HCSmouse.cpp
    int  HCSMouseCheck(int xM,int yM,char RFlag);
    void HCSMouseOverSort(void);

//kboard.cpp
    int KeyBoard(int k);

//mouse.cpp
    int  MouseCheck(void);
    void TileCenter(int xM,int yM);
    int  HighLight1(void);
    void HighLight2(SDL_Surface *temp,int &tempoldx,int &tempoldy,int dir,
                    int no);
    int  HighLight3(int dir);


private:
    bool fullScreen;
    int  screenResX,screenResY;

    unsigned int screenWidth;   //number of tiles displayed on the screen
    unsigned int screenHeight;

    SDL_Window* _Window;

    GlobalData* _GlobalData;
    OptionList* _OptionList;
    Map* _Map;
public:


  SDL_Surface *icon, *screen, *tilesheet1,*blender,*tilesheetF,*forestmask,
       *tilesheetM,*tilesheetR,*extra1,*bck1,*mapback,*mapsurf,
       *shrd,*pshrd,*blender2,*messageold,*messagenew,*mask1,
       *Mmask,*Rmask,*map1,*cds1,*hcs1,*scrllbutup,*scrllbutdwn,
       *scrllbutbck,*unitsS,*uniticons,*HCSWin[4],*loadedbck,
       *activebck,/**SoLfont1[4],*/*buildings1, *flags;
  SDL_Surface *tilesheetR3,*R3mask; //provisional for rivers

//added 6/2
// 2 new fonts for colony names on cds and map            
	SDLFont *fontPushButtons,*fontInformation,*fontColNameCDS,*fontColNameMap;

  unsigned int startX;  //start tile (coords) displayed on the screen
  unsigned int startY;
};

#endif //graphicsEngine_H


//
// $Id: graphicsEngine.h,v 1.17 2004/06/26 11:33:43 sikon Exp $
//

