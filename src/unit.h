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
// FILE		: unit.h
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  October 2003
//
// CLASS	: Unit
//
// DESCRIPTION	: Units informations and manipulations.
//

#ifndef unit_H
#define unit_H

#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include "resources.h"
#include "tinyxml.h"
#include "skill.h"

#define IDU_COLONIST    1000
#define IDU_SOLDIER     1001
#define IDU_PIONEER     1002
#define IDU_DRAGOON     1004
#define IDU_SCOUT       1005
#define IDU_REGULAR     1006
#define IDU_CAVALRY     1008
#define IDU_TREASURE    1010
#define IDU_ARTILLERY   1011
#define IDU_CARAVEL     1013
#define IDU_MERCHANTMAN 1014
#define IDU_GALLEON     1015
#define IDU_PRIVATEER   1016
#define IDU_MANOWAR     1018

#define ORD_NONE      0
#define ORD_CLEAR     1
#define ORD_PLOW      2
#define ORD_ROAD      3
#define ORD_FORTIFY   4
#define ORD_SENTRY    5
#define ORD_FORTIFIED 6

using namespace std;

class Unit
{

public:

//Constructor, destructor
    Unit();
    ~Unit();
   
    static Unit* loadUnitFile(int type);        
//Accessors
    int 		getType()                       {return type;}
    string      getName()                       {return name;}
    string      getClassType()                  {return classType;}
    Uint8		getMoveCapability()             {return moveCapability;}
    Uint8       getVisual()                     {return visual;}
    Uint8		getAttack()                     {return attack;}
    Uint8		getDefense()                    {return defense;}
	Uint8		getSkillLevel()                 {return skillLevel;}
	bool		hasMoved()                      {return turnStatus;}
	bool		isBoat();
	Uint8       getOrders()                     {return orders;}
	Uint8       getSize()                       {return size;}
	int         getPositionX()                  {return positionX;}
	int         getPositionY()                  {return positionY;}
// >>>
	long        getTile()                       {return tile;}
	long        getStartNumber()                {return startNumber;}
	bool        isOnboard()                     {return onboard;}
	int         getBasicGraphic()               {return graphic;}
	int         getExpertGraphic()              {return eGraphic;}
	int         getGSmall()                     {return gSmall;}
	Uint8       getNation()                     {return nation;}
	Skill*      getSkill()                      {return skill;}
	int         getGraphic();
	bool        isExpert();
	char*       getSkillName();
// <<<
	
	bool		isTransport()                   {return transportCapacity > 0;}
	Uint8		getTransportCapacity()          {return transportCapacity;}
	Unit*		getPassenger(Uint8 index)       {return passengers[index];}
	Uint8		getNumberOfPassenger()          {return passengers.size();}
	
	bool		isCargo()                       {return cargoCapacity > 0;}
	Uint8		getCargoCapacity()              {return cargoCapacity;}
	Resources*	getCargoInside(Uint8 index)     {return cargoInside[index];}
	Uint8		getNumberOfCargo()              {return cargoInside.size();}

//Modifiers
	void		setType(int t)                  {type = t;}
	void        setName(string n)               {name = n;}
	void        setClassType(string ct)         {classType = ct;}
	void		setMoveCapability(Uint8 m)      {moveCapability = m;}
	void        setVisual(Uint8 v)              {visual = v;}
	void		setAttack(Uint8 a)              {attack = a;}
	void		setDefense(Uint8 d)             {defense = d;}
	void		setSkillLevel(Uint8 l)          {skillLevel = l;}
	void		setTurnStatus(bool b)           {turnStatus = b;}
	void        setOrders(Uint8 o)              {orders = o;}
	void        setSize(Uint8 s)                {size = s;}
	void        setPositionX(int x)             {positionX = x;}
	void        setPositionY(int y)             {positionY = y;}
// >>>
    void        setTile(long t)                 {tile = t;}
    void        setStartNumber(long l)          {startNumber = l;}
    void        setGSmall(int i)                {gSmall = i;}
    void        setSkill(Skill *sk)             {skill = sk;}
// <<<
	
	void		setTransportCapacity(Uint8 tc)  {transportCapacity = tc;}      
	bool		addPassenger(Unit* u);
	bool		removeAllPassengers();
	bool		removePassenger(Uint8 index); //Starting at 0
	
	void		setCargoCapacity(Uint8 cc)      {cargoCapacity = cc;}
	bool		addResources(Resources* r);
	bool		removeAllResources();
	bool		removeResources(Uint8 index); //Starting at 0

//More Methods
    bool        disband();
    void        fortify()                       {orders = ORD_FORTIFY;}
    void        sentry()                        {orders = ORD_SENTRY;}	
    bool        buildColony();
    bool        joinColony();
    bool        establishMision();
    bool        move(Uint8 direction);
    Uint8       getMovesLeft()                  {return movesLeft;}
// >>>
    void        setMovesLeft(Uint8 value)       {movesLeft = value;}
    void        setOnboardFlag(bool flag)       {onboard = flag;}
    void        setNation(Uint8 n)              {nation = n;}
// <<<
    void        setUnitID(int id)               {unitID = id;}
    int         getUnitID(void)                 {return unitID;}

private:
    int 		type;					//colon, miner, farmer etc...
    string      name;                   //the TEXT name of a unit
    string      classType;              //Civil,naval,military etc...
    Uint8		moveCapability;			//number of moves possible
    Uint8       visual;                 //How far does it reveal the map
    Uint8		attack;					//Attack coefficient
    Uint8		defense;				//Defence coefficient
    Uint8		skillLevel;				//general , specialist, elite
    bool		turnStatus;				//already moved this turn ?
    Uint8       orders;                 //doing something ?
    Uint8       size;                   //size taken when transported
    int         positionX;              //Map position from Upper left corner
    int         positionY;
    long        tile;
    long        startNumber;
    bool        onboard;
    int         graphic;
    int         gSmall;
    int         eGraphic;
    Uint8       nation;
    Skill*      skill;
    int         eSkillType;
    int         unitID; //added 15/6
    
    Uint8		transportCapacity;
	vector<Unit*>       passengers;		//vector of passengers units

	Uint8		cargoCapacity;			//total number of cargo possible
	vector<Resources*>	cargoInside;	//vector of cargos resources

    Uint8       movesLeft;              //how many moves left in this turn
};

#endif //unit_H

//
// $Id: unit.h,v 1.10 2004/06/23 15:37:05 sikon Exp $
//

