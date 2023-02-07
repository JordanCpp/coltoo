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
// FILE		: player.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: Player
//
// DESCRIPTION	: Basis class for player control.
//

#include <string.h>
#include "player.h"

//Constructor, destructor
Player::Player()
{
    Color = NULL;
}

Player::~Player()
{
    if(Color) delete Color;
    vector<Unit*>::iterator it = unitList.begin();
    for( it = unitList.begin(); it != unitList.end(); it++ )
    {
        if (*it) delete (*it);
    }
    unitList.clear();
}

bool Player::Init(void)
{
	setName("Player");
	Color = new ColorData();
	if(Color) return true;
	else return false;
}

void Player::setAttitude(short att[3])
{
    int i;
    for(i=0;i<3;i++) attitude[i] = att[i];
}

void Player::setAttitude(const char *att)
{
    int i = 0;
    short sig[3] = { 1, 1, 1 };
    int a = 0;
    
    while(i<strlen(att))
    {
        if(att[i]==',')
        {
            a++;
            if(a>=3) break;
        }
        else if(att[i]=='-')
        {
            sig[a] = -sig[a];
        }
        else if((att[i]>='0') && (att[i]<='9'))
        {
            char t[2] = "0";
            t[0] = att[i];
            attitude[a] = attitude[a]*10 + atoi(t);
        }
        i++;
    }
    for(i=0;i<3;i++) attitude[i] *= sig[i];
}

//
// $Id: player.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//
