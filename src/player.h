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
// FILE		: player.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: player
//
// DESCRIPTION	: Basis class for player control.
//

#ifndef player_H
#define player_H

#include <vector>
#include <list>
#include "actor.h"
#include "unit.h"    //add 14/6

//using namespace std;

class Unit;

struct CountryType
{
    string name;
    string nationality;
    string abbrev;
    string homeport;    
};
struct ColonyType
{
    string name;
    string independent;
    string mission;
};

class Player : public Actor
{
public:

//Constructor, destructor
    Player();
    virtual ~Player();

//Methods
    short getAttitude(int pos);
    long getGold(void) { return gold; }
    void setAttitude(short att[3]);
    void setAttitude(const char *att);
    void setGold(long g) { gold = g; }
    virtual bool Init(void);
    Uint8 getNationID(void) { return nationID; }
    void setNationID(Uint8 n) { nationID = n; }
    
private:
    
public: //add 14/6
    vector<Unit*> unitList;
    CountryType country;
    ColonyType NewWorld;
    
private:
    short attitude[3];
    long gold;
    Uint8 nationID;
};

#endif //player_H


//
// $Id: player.h,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

