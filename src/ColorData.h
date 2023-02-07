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
// FILE		: color.h
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: Color
//
// DESCRIPTION	: Basis class for color routines.
//

#ifndef COLORDATA_H
#define COLORDATA_H

#include <iostream>
#include <cstring>

using namespace std;

class ColorData
{
    public:
//Constructor, destructor
    ColorData();
    ~ColorData();

//Methods
    short Red(void) { return l_red; }
    short Green(void) { return l_green; }
    short Blue(void) { return l_blue; }
    void SetRed(short r) { l_red = r; }
    void SetGreen(short g) { l_green = g; }
    void SetBlue(short b) { l_blue = b; }
    void SetColor(const char *color);
    
    private:
    short l_red;
    short l_green;
    short l_blue;
};

#endif //COLORDATA_H

//
// $Id: ColorData.h,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

