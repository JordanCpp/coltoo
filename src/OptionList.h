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
// FILE		: Options.h
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: OptionList
//
// DESCRIPTION	: Basis class for Options control.
//
#ifndef OPTIONLIST_H
#define OPTIONLIST_H

#define IDO_WINDOW 0
#define IDO_FULLSCRN 1

#include <iostream>
#include <string>

using namespace std;

class OptionList
{
public:
    OptionList();
    OptionList(const char *filename);
    ~OptionList();
    
    void OptionListInit(void);
    void OptionListInit(const char *filename);
    
    short WindowMode(void);
    void WindowMode(short m);
    
    bool Opening(void);
    int OpeningDelay(void);
    void Opening(bool o, int d);
    
    bool Splash(void);
    int SplashDelay(void);
    void Splash(bool s, int d);
    
private:
    short windowMode;
    bool useOpening;
    int openingDelay;
    bool useSplash;
    int splashDelay;
};

#endif

//
// $Id: OptionList.h,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

