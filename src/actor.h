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
// FILE		: actor.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: Actor
//
// DESCRIPTION	: Basis class for players control.
//

#ifndef actor_H
#define actor_H

#include <string>
#include "ColorData.h"

using namespace std;

class ColorData;

class Actor
{
public:

//Constructor, destructor
    Actor();
    virtual ~Actor();

//Methods
    virtual bool Init(void) = 0;
    char *getName();
    void setName(const char *n);
    
private:
    string name;
    
public:
    ColorData* Color;
    
};

#endif //actor_H


//
// $Id: actor.h,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

