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
// FILE		: colony.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  October 2003
//
// CLASS	: Colony
//
// DESCRIPTION	: Colony information and manipulation.
//

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>

//forward declarations
class Unit;
class Tile;

using namespace std;

#ifndef colony_H
#define colony_H

#define TOTAL_GOODS 16
#define FIRST_BUILDINGS 7
#define BGR_SMALL 0
#define BGR_LARGE 1
#define BGR_DOCKS 2

#define CDS_BUILD_XTILES 6
#define CDS_BUILD_YTILES 4

enum CargoTypes {IDC_FOOD = 0, IDC_SUGAR, IDC_TOBACCO, IDC_COTTON, IDC_FURS,
    IDC_LUMBER, IDC_ORE, IDC_SILVER, IDC_HORSES, IDC_RUM, IDC_SIGARS, IDC_CLOTH,
    IDC_COATS, IDC_TRADEGOODS, IDC_TOOLS, IDC_MUSKETS};
    
enum Buildings {IDB_TOWNHALL = 2000, IDB_CARPSHOP, IDB_FURHOUSE, IDB_BLACKHOUSE,
    IDB_DISTHOUSE, IDB_TOBHOUSE, IDB_WEAVHOUSE};

class Building    //Stores building info from Colony Display
{
public:

//Constructor, destructor
    Building(){};
    ~Building(){};
    
    static Building *loadFromFile(int type);
    int getGraphic();
    int getGraphicType();

    int x, y;
private:
    int         buildingType;           //determining type of building
    int         buildingID;             //BuildingID(weaver's house, shop,
                                        // mill) 0 = No building
    int         graphic;
    int         graphicType;
    vector<Unit*> unitsPresent;         //units in this building
    int         prerequisite;           //previous building needed ?SURE?
                                        // Founding Fathers...
};

class Colony
{
public:

//Constructor, destructor
     Colony(bool isPort);
     ~Colony();

//Methods
    void   initBuildings();

    void   setName   (string name);
    void   setNation (int nat);
    void   setTile(long til);
    void   setStock(int goods, int quantity);

    string getName();
    int    getNation();
    int    getSize();
    long   getTile();
    int    getStock(int goods);
    bool   isPort();
    int    getBuildingNum();
    Building *getBuilding(int i);

    Uint8       squares[CDS_BUILD_XTILES][CDS_BUILD_YTILES];
    Uint8       lgSquare;
private:
    int 		colonyID;               //global ID for referencing all colonies
//    int         xpos;                   //Map position from Upper left corner
//    int         ypos;
    bool        portFlag;
    long        tile;
    string      m_Name;                 //the TEXT name of a colony
    int         m_Nation;               //Nationality of the colony (or tribe)
    int 		m_Size;	                //number of colonists in the colony
    vector<Unit*>  colonists;          //vector of units in the colony
    vector<Unit*>  visitors;           //vector of units outside the colony
    int         warehouse[TOTAL_GOODS];          //goods produced and stored
    int         nextTurnProduction[TOTAL_GOODS]; //goods produced on next turn
    vector<Building*> colonyBuildings;  //15x building sites in Colony Display.
//    Production  building;               //object containing colony production
                                        //buildings, ships, artilleries
    int         bells;                  //liberty bells of the colony
    int         crosses;                //crosses of the colony
    Uint8       wall;                   //no wall, stockade, Fort, Fortress
    int         capacity;               //storage capacity

};

#endif //colony_H

//
// $Id: colony.h,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

