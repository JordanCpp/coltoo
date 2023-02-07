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
// FILE		: Options.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: OptionList
//
// DESCRIPTION	: Basic class for Options control.
//

#include "OptionList.h"

#include <iostream>
#include <string>
#include "tinyxml.h"

OptionList::OptionList()
{
    #ifdef DEBUG
    cout<<"  Initializing OptionList"<<endl;
    #endif
    windowMode = IDO_FULLSCRN;
    useOpening = false;
    openingDelay = 0;
    useSplash = false;
    splashDelay = 0;
    OptionListInit("data/text/options.xml");
}

OptionList::OptionList(const char *filename)
{
    #ifdef DEBUG
    cout<<"  Initializing OptionList["<<filename<<"]"<<endl;
    #endif
    windowMode = IDO_FULLSCRN;
    useOpening = false;
    openingDelay = 0;
    useSplash = false;
    splashDelay = 0;
    OptionListInit();
}

OptionList::~OptionList()
{
    #ifdef DEBUG
    cout<<"  Destroying OptionList"<<endl;
    #endif
}
void OptionList::OptionListInit(void)
{
    OptionListInit("data/text/options.xml");
}

void OptionList::OptionListInit(const char *filename)
{
    /*Options format
    <options>
        <graphic mode="fullscreen">
            <opening use="yes" delay="1000"/>
            <splash use="yes" delay="1500"/>
        </graphic>
    </options>*/
    string tmp;

    TiXmlBase::SetCondenseWhiteSpace( false );
	
    #ifdef DEBUG
	cout<<"  Loading options"<<endl;
    #endif
    TiXmlDocument pFile(filename);
    
    bool loadOkay = pFile.LoadFile();
    
	if ( !loadOkay )
	{
		printf( "Could not load file '", filename, "'. Error='%s'. Exiting.\n", pFile.ErrorDesc() );
		exit( 1 );
	}
	
	TiXmlNode *node = 0;
	TiXmlNode *pNodeList = 0;
	TiXmlElement *pNode = 0;
	TiXmlElement *sElem = 0;
	
    #ifdef DEBUG
	cout<<"  Getting Options list {"<<endl;
    #endif
	node = pFile.FirstChild("options");
	pNodeList = node->ToElement();
    
    #ifdef DEBUG
    cout<<"    Graphic {"<<endl;
    #endif
    node = pNodeList->FirstChild("graphic");
    pNode = node->ToElement();
    
    tmp = pNode->Attribute("mode");
    #ifdef DEBUG
    cout<<"      Mode: "<<tmp<<endl;
    #endif
    windowMode = IDO_FULLSCRN;
    if(tmp=="window") windowMode = IDO_WINDOW;
        
    #ifdef DEBUG
    cout<<"      Opening {"<<endl;
    #endif
    node = pNode->FirstChild("opening");
    sElem = node->ToElement();
    useOpening = false;
    if(sElem) 
    {
        useOpening = true;
        tmp = sElem->Attribute("use");
        if(tmp!="yes") useOpening = false;
        #ifdef DEBUG
        cout<<"        Use: "<<useOpening<<endl;
        #endif
        tmp = sElem->Attribute("delay");
        openingDelay = atoi(tmp.c_str());
        #ifdef DEBUG
        cout<<"        delay: "<<openingDelay<<endl;
        #endif
    }
    #ifdef DEBUG
    cout<<"      } Opening"<<endl;
    #endif
    
    #ifdef DEBUG
    cout<<"      Splash {"<<endl;
    #endif
    node = pNode->FirstChild("splash");
    sElem = node->ToElement();
    useSplash = false;
    if(sElem) 
    {
        useSplash = true;
        tmp = sElem->Attribute("use");
        if(tmp!="yes") useSplash = false;
        #ifdef DEBUG
        cout<<"        Use: "<<useSplash<<endl;
        #endif
        tmp = sElem->Attribute("delay");
        splashDelay = atoi(tmp.c_str());
        #ifdef DEBUG
        cout<<"        delay: "<<splashDelay<<endl;
        #endif
    }
    #ifdef DEBUG
    cout<<"      } Splash"<<endl;
    #endif
    
    #ifdef DEBUG
    cout<<"    } Graphic"<<endl;
    #endif
    
    #ifdef DEDBUG
    cout<<"  } Options"<<endl;
    #endif
}

short OptionList::WindowMode(void)
{
    return windowMode;
}

void OptionList::WindowMode(short n)
{
    windowMode = n;
}

bool OptionList::Opening(void)
{
    return useOpening;
}

int OptionList::OpeningDelay(void)
{
    return openingDelay;
}

void OptionList::Opening(bool o, int d)
{
    useOpening = o;
    openingDelay = d;
}

bool OptionList::Splash(void)
{
    return useSplash;
}

int OptionList::SplashDelay(void)
{
    return splashDelay;
}

void OptionList::Splash(bool s, int d)
{
    useSplash = s;
    splashDelay = d;
}


//
// $Id: OptionList.cpp,v 1.4 2004/06/23 15:37:05 sikon Exp $
//
