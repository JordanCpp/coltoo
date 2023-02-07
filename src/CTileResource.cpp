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
// FILE		: CTileResource.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileResource
//
// DESCRIPTION	: Tile Resource information
//

#include "CTileResource.h"

CTileResource::CTileResource(void)
{
}

CTileResource::~CTileResource(void)
{
}

//GET Methods
int CTileResource::ResourceID(void)
{
    return resID;
}

const char *CTileResource::ResourceName(void)
{
    return resName.c_str();
}

int CTileResource::ResourceValue(void)
{
    return resValue;
}

int CTileResource::ResourceKeep(void)
{
    return resKeep;
}

//SET Methods
void CTileResource::ResourceID(int id)
{
    resID = id;
}

void CTileResource::ResourceName(const char *n)
{
    resName = n;
}

void CTileResource::ResourceValue(int v)
{
    resValue = v;
}

void CTileResource::ResourceKeep(int k)
{
    resKeep = k;
}

