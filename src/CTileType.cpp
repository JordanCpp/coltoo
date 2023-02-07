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
// FILE		: CTileType.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileType
//
// DESCRIPTION	: Tile information
//

#include "CTileType.h"

#include <iostream>
#include <string>

CTileType::CTileType()
{
}

CTileType::~CTileType()
{
}

void CTileType::LoadProduction(TiXmlElement *e, CTileType *t)
{
    TiXmlElement *elem = 0;
    tileProduction p;
    elem = e->FirstChild("production")->ToElement();
    if(e)
    {
        e->Attribute("farmer",&(p.farmer));
        e->Attribute("sugar",&(p.sugar));
        e->Attribute("tabacco",&(p.tabacco));
        e->Attribute("cotton",&(p.cotton));
        e->Attribute("furs",&(p.furs));
        e->Attribute("wood",&(p.wood));
        e->Attribute("ore",&(p.ore));
        e->Attribute("silver",&(p.silver));
        e->Attribute("fish",&(p.fish));
    }
    t->Production(p);
}

//GET Methods
int CTileType::TileID()
{
    return tileID;
}

int CTileType::TileType()
{
    return tileType;
}

const char *CTileType::TileName()
{
    return tileName.c_str();
}

int CTileType::NewTileID()
{
    return transfID;
}

const char *CTileType::NewTileName()
{
    return transfName.c_str();
}

int CTileType::Movement()
{
    return tileMovement;
}

int CTileType::Defensive()
{
    return tileDefensive;
}

int CTileType::Improvement()
{
    return tileImprovement;
}

int CTileType::Value()
{
    return tileValue;
}

int CTileType::ResourceID()
{
    return resID;
}

const char *CTileType::ResourceName()
{
    return resName.c_str();
}

tileProduction CTileType::Prodution()
{
    return tproduction;
}

//SET Methods
void CTileType::TileID(int i)
{
    tileID = i;
}

void CTileType::TileName(const char *n)
{
    tileName = n;
}

void CTileType::TileType(int t)
{
    tileType = t;
}

void CTileType::NewTileID(int i)
{
    transfID = i;
}

void CTileType::NewTileName(const char *n)
{
    transfName = n;
}

void CTileType::Movement(int m)
{
    tileMovement = m;
}

void CTileType::Defensive(int d)
{
    tileDefensive = d;
}

void CTileType::Improvement(int i)
{
    tileImprovement = i;
}

void CTileType::Value(int v)
{
    tileValue = v;
}

void CTileType::ResourceID(int d)
{
    resID = d;
}

void CTileType::ResourceName(const char *n)
{
    resName = n;
}

void CTileType::Production(tileProduction p)
{
    tproduction.farmer =  p.farmer;
    tproduction.sugar =   p.sugar;
    tproduction.tabacco = p.tabacco;
    tproduction.cotton =  p.cotton;
    tproduction.furs =    p.furs;
    tproduction.wood =    p.wood;
    tproduction.ore =     p.ore;
    tproduction.silver =  p.silver;
    tproduction.fish =    p.fish;
}

