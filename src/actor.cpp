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
// FILE		: actor.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: Actor
//
// DESCRIPTION	: Basis class for players control.
//

#include "actor.h"

//Constructor, destructor
Actor::Actor()
{
    Color = NULL;
}

Actor::~Actor()
{
}

char *Actor::getName()
{
    return (char *)name.c_str();
}

void Actor::setName(const char *n)
{
    name = n;
}

//
// $Id: actor.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//
