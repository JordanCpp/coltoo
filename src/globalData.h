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
// FILE		: globalData.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: GlobalData
//
// DESCRIPTION	: storage data class for global data.
//

#ifndef globalData_H
#define globalData_H

#define BIT1 0x01
#define BIT2 0x02
#define BIT3 0x04
#define BIT4 0x08
#define BIT5 0x10
#define BIT6 0x20
#define BIT7 0x40
#define BIT8 0x80
#define BIT9 0x100
#define BIT10 0x200
#define BIT11 0x400
#define BIT12 0x800
#define BIT13 0x1000
#define BIT14 0x2000
#define BIT15 0x4000
#define BIT16 0x8000

#define XPOS         0
#define YPOS         1

#include <SDL.h>

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "resources.h"
#include "tinyxml.h"
// >>>
#include "message.h"
#include "skill.h"
#include "player.h" //added 15/6
// <<<

using namespace std;

class GameEngine;
class Unit;
// >>>
class Colony;
class Player; //added 15/6
// <<<

struct ships1struct  //data structure for each ship
{
    char  name[25];        //ship name
    char  type[25];        //ship type - string
    short capacity;        //ship capacity
    short passengernum:4;  //Bit field (4 bits) to hold the number of passengers
                           //a ship type can hold.  (Caraval-2, Galleon-6)

    short passenger[6];    //type of unit of the passengers on board. Array to store
                           //the unit number of each passenger on board the ship.
                           //(The unit number is the index of another array with the
                           //x and y position of that unit type on the tile sheet.)

    short typenum;         //type of ship - caravel, galleon...
    short cargo[20][2];    //type of cargo & amount. A ship can hold up to 20 different
                           //types of cargo. (Really should be some sort of open-ended
                           //C++ list.)  The first element holds the type of cargo and
                           //the second the amount of that type on board. (As with the
                           //passengers, the type of cargo is set by putting an index
                           //into the first element of this array. That index when used
                           //with another array will give the x and y position of that
                           //cargo type on the tile sheet.)

    short cargototal;      //Total in tons of all types of cargo on board. When added
                           //to the number of passengers*100 can be used to check to see
                           //if it is less than or equal to the ship’s capacity. (You
                           //could get this number from checking all the second elements
                           //in the cargo[20][2] array, but I’m lazy and thought it be
                           //easier to have a separate variable for this.)

    short cargonum;        //number of different cargos

};

//added 6/2
//holds cds information for each colony
struct colonystruct
{
  long colonyLoc;
  int  colSmBuilding[18];
  int  colLgBuild[3];
  int  colDock;
  int  colSmTrees[18];
  int  colLgTrees[3];
};

enum directions {E,S,W,N,NE,SE,SW,NW,ANY_DIR};

//These are the game context, telling if it is main screen, HCS,CDS
enum context {MAINSCREEN,HCS,CDS};

class GlobalData
{
public:

//Constructors, destructor
    GlobalData();
    GlobalData(GameEngine*);
    ~GlobalData();

//Methods
    bool Init(void);

    bool InitPlayers(void);
    
    void DefaultShipName(short num,char array1[][25],short num2);
    void ShipCharacteristics(short type);
    
//Accessors
	enum context getContext() {return m_nContext;}

private:
    const char *GetDataValue(TiXmlNode *node,char *nodeName);
    
    GameEngine*     m_pGame;    //GameEngine
    float           m_nYear;    //Year
  	enum context	m_nContext;		//Game context (hds,cds,mainscreen)...

public:
    SDL_Surface * SoLfont1[4];

    SDL_Event     event;

    typedef struct
    {
	    string	name;
	    int		cost;
    } Job;

//    vector<Job> jobList;    //Seems to be unused - .NET

    vector<Player*> playerlist; //add 15/6
    vector<Skill*> skillList; //added 13.06
    vector<Unit*> unitList; //Using playerlist[].unitlist instead
    vector<Colony*> colonies;  // added 11.06

//////////////////////////////////////////////////////////////////////////

    int tile50[72][2];   //X and Y positions on a tile sheet for tiles that are 50 pixels high.
                         //(Possibly the array used for the units.)
    int tile26[72][2];

    int recruit[3];      //Array to hold the unit type of the 3 possible recruits currently available.
    int recruitcost;     //recruit prices: new price and
    int recruitcostold;  //                current cost.


    int zl;      //Zoom Level: 0 shows the main map; 1 shows the entire map.

    int flag;    //Shows various flags, as if the unit is able to move (make a legal move),
                 //if the unit needs to be recentered, and a few other flags, using these
                 //bits for the flags:
      unsigned char ReCenFlag;   //=BIT1
      unsigned char MoveFlag;    //=BIT2
      unsigned char UpDateFlag;  //=BIT3
      unsigned char NoMoveFlag;  //=BIT4
      unsigned char VillageFlag; //=BIT5
      unsigned char SpaceFlag;   //=BIT6 --not used
      unsigned char RoadFlag;    //=BIT7 --not used
        // Some of these values aren’t used in this version, but some are. In particular
        // the ReCenFlag and the NoMoveFlag are. These tell the program (in display.cpp
        // file) when the screen needs to be recentered; or if the unit tried to make an
        // illegal move and remained on the same tile. (Thus it’s mf is not reduced.)

    int scrmax;  //Maximum number of elements in the screen array. Used to check that a
                 //variable isn’t outside the range of the array.
    int mapmax;  //Maximum number of elements in the map array. Used to check that a
                 //variable isn’t outside the range of the array.

    int red,green; //used for tile blending
    int turnnum;   //Count of the turns used to decide what type (skills) of unit will
                   //appear on the docks. The higher this number the less likely a Skilled
                   //Unit will appear.

    int x_res,y_res; //screen resolution - perhaps it's inside GfxEngine

    short tilex[16]; //X position for the on the tile sheet.(16 columns.)
    short tiley[6];  //Y position on the tile sheet.  (6 rows.)

    short gdstilesX[16]; //X position of the goods on the tile sheet.

    short tiley2[4]; //Y position for tiles that are 65 pixels high.
                     //(The overlays like Mountains, Forests, etc.)

    short stile[154][2]; //X and Y locations of the Screen Tiles.

    short oldloc; //Index for the tile the unit moved from. Used to replace the image of
                  //the unit with a stored image of the tile. oldloc is where the old
                  //scrnum (ScreenNumber) is stored so the old background can be replaced.

    short scrnum;//current tile displayed on the screen (11x9 tiles) 0..98

    short tw,th; //Tile Width=75; Tile Height=50.
    short rows,cols; //map size (200x150)

    short JobCount; //number of entries in those lists
    short visible;//flag to determine whether the active unit is currently onscreen or not
    short yextra; //Fudge factor to position a unit or overlay to look good on the screen.
                  //(On the Y axis.) Used to position the unit up a few pixels from the
                  //bottom of the tile. So the unit looks as if its actually in the tile
                  //and not just standing on the bottom edge.

    short mf; //movement factor for the active unit.
    short turn; //unit selection (caravel =0 or scout =1) flag
    short nationTurn; //added 17/6; nation selection (currently from England to Netherlands)
    short scrndsply; //Screen being displayed:  0=main map; 1=HCS; 2=CDS

    short grid; //flag for the grid (displayed or not)
//    short loaded; //flag for the scout (onboard the ship or not)

    short tmf; //TotalMovementFactor of the active unit. For the display on the main screen.
               //3/6.  Meaning the unit has moved 3 of 6 moves.  This number changes
               //depending on the active unit and its movement factor.
    short HCSradio1; //Button on the HCS currently depressed. Recruit/Purchase/Train.

    short Pstart; //PurchaseStart. The index to indicate where to start to draw the
                  //array of units available to be purchased for the screen display.
                  //(Start with the Artillery if Pstart=0; start with the Galleon if
                  //Pstart=3.

    short Tstart; //TrainStart. The same as Pstart only for the units to be ‘trained’.
                  //(Tstart=0 is the Ore Miner; and so on.)

    short HLCheckOld[3]; //I use this to get rid of a flicker on my machine. While holding
                         //the mouse over the units display box on the HCS I’d get a flicker
                         //as the program constantly redrew the Highlighted Unit. With this
                         //flag I can determine if the mouse has just moved over a new unit
                         //or is still over the old one.

    short shipnum;  //Index number for the ship structure. Each ship has its own unique
                    //number and by plugging this number into the array you can find out
                    //what type of ship that shipnumber is and get it’s characteristics.


    /*screen directions*/ //used to select the actual tile number. Related to screen map (11x9)
    short sNE,sE,sSE,sS,sSW,sW,sNW,sN;

    /*map directions*/ //the same but related to the map (200x150)
    short mNE,mE,mSE,mS,mSW,mW,mNW,mN;

    long start; //This is the ‘mapnum’ of the tile in the upper left of the screen.
                //Is used to recenter the map when the unit reached the edge.

    long mapnum;//current tile. Used overall as the base for graphic operations.
    long gold;  //obvious. Gold pieces
    long RumorFlag; //I added this to handle the eventuality of the Scout disembarking from
                    //the ship directly onto a Rumor. If that is the case I had to temporarily
                    //switch the active unit to the scout to handle the Rumor event before
                    //going back to finish the ship’s moves.

//???    long  units[2][4];  //units placeholder with properties
                        //units[0][] == ship
                        //units[1][] == scout

                        //units[][0] == unit type (0=sea; 1=land) : the same as 'turn'
                        //units[][1] == movement factor
                        //units[][2] == tile number where the unit is located (== mapnum)
                        //units[][3] == start number of the unit (upper left corner of
                        //screen display)

//    unsigned char horz,vert; //Not used. Added when there were scroll bars and these were
                             //flags to indicate which type of scroll bar to draw.
                             //(Horizontal or Vertical.)

//    char VillMess[25][4][40],RumMess[25][4][40];    //messages and data loaded from
    char Jobs[30][25],Order[10][25],Game[9][25];    //data files. Will be replaced with
    char View[2][25],/*Errors[25][3][40],*/Buy[6][25];  //xml files and its handling.
    char BuyCost[6][25],JobsCost[30][25],Labels[35][25];
//  >>>
    Message *msg;
//  <<<

    char leftspace,rightspace,topspace,bottomspace; //Used to remove the extra space from
                                                    //a unit tile so they can be displayed
                                                    //on the HCS & CDS without having to be
                                                    //75 pixels apart. The result is the
                                                    //true width and height of the graphic.

    char rHL,pHL,tHL; //Number of the display on the Recruit/Purchase/Train display that is
                      //currently ‘HighLighted’. (0,1,2 or 1,2,3, not sure which method is
                      //used.)  That is; 2 means the center unit is HighLighted.

    char SSstart[100],SSCstart[100]; //Selected Ship and Selected Ship Cargo
                                     //These hold the number of the ship/cargo that is used
                                     //to start the display. That is; if the display can
                                     //only show 4 ships, and there are currently 10 ships
                                     //in port, the ship displayed on the left will be the
                                     //one who’s number is in SSstart. The object is to
                                     //always have the last ship in the array somewhere in
                                     //the display.

    char counterbutton; //selected loading options (50 tons, 100 tons, All, Custom.)
    char counterspace;  //offset for the Custom display depending on the number of digits
                        //being displayed.  (0-9,10-99,100-)

    unsigned int text1color[18];//colors for the SoLfont1 font

    //ship types (only caravel used)
    short caravel;     //== 1
    short merchantman = 0; //== 2  //not used
    //short galleon;     //== 3
    //short privateer;   //== 4
    //short frigate;     //== 5
    //short manowar;     //== 6

    short shiptypenum[7]; //number of ships of each type

    short tons; //The amount of a good being shifted on HCS. Set by counterbutton.

    short counter; //Number set by the counterbutton and by the counter display. (The number
                   //that can be adjusted by pressing on the up and down buttons on the
                   //counter display.)

    short price[16][2]; //buy/sell prices of the goods on the HCS. (loaded from pricelist.txt)

    struct ships1struct units_ships[256]; //all ships that can be created (bought) in the HCS.
                                          //should not be here -->unit or Player

    long natives[300];                   //store mapnum for tile native is on
    short *nativeOnTile;           //flag to show native on mapnum
    short mouseClick;                    //flag to show movement was by mouse
    short colonyCount;                   //colony number
//    struct colonystruct colony[1000];    //struct to hold cds display information

    short colNameCount[COUNTRIES];               //colony number for each power
    char colName[COUNTRIES][100][30];            //lists of colony names
    int nextColName[COUNTRIES];
    Uint8 nation;
    
    unsigned char move;
};

#endif //globalData_H

//
// $Id: globalData.h,v 1.17 2004/06/23 15:37:05 sikon Exp $
//

