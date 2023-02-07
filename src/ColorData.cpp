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

#include "ColorData.h"
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

//Constructor, destructor
ColorData::ColorData()
{
    l_red = 0;
    l_green = 0;
    l_blue = 0;
}

ColorData::~ColorData()
{
}

void ColorData::SetColor(const char *color)
{
    short t = 0;
    short c[3] = { 0, 0, 0 };
    int i = 0;
    
    while(i<strlen(color))
    {
        if(color[i]==',')
        {
                t++;
                if(t>2) break;
        }
        else if((color[i]>='0') && (color[i]<='9'))
        {
                char m[2] = "0";
                m[0] = color[i];
                c[t] = c[t] * 10 + atoi(m);
        }
        i++;
    }
    #ifdef _DEBUG
    cout<<"    Color("<<c[0]<<","<<c[1]<<","<<c[2]<<")"<<endl;
    #endif
    l_red = c[0];
    l_green = c[1];
    l_blue = c[2];
}

//
// $Id: ColorData.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//
