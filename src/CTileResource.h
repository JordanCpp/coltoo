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
// FILE		: CTileResource.h
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileResource
//
// DESCRIPTION	: Tile Resource information
//

#ifndef CTILERESOURCE_H
#define CTILERESOURCE_H

#include <string>

using namespace std;

class CTileResource
{
public:
    CTileResource(void);
    ~CTileResource(void);
    
    int ResourceID();
    const char *ResourceName(void);
    int ResourceValue();
    int ResourceKeep();
    
    void ResourceID(int ID);
    void ResourceName(const char *n);
    void ResourceValue(int v);
    void ResourceKeep(int k);
    
private:
    int resID;
    string resName;
    int resValue;
    int resKeep;
};
#endif

