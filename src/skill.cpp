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
#include <iostream>
#include "skill.h"
#include "tinyxml.h"

string Skill::getName()
{
    return name;
}

string Skill::getLongName()
{
    return longName;
}

int Skill::getGraphic()
{
    return graphic;
}

int Skill::getType()
{
    return type;
}

void Skill::setName(string nm)
{
    name = nm;
}

void Skill::setLongName(string l)
{
    longName = l;
}

void Skill::setGraphic(int g)
{
    graphic = g;
}

void Skill::loadSkills(vector<Skill*> *array)
{
    TiXmlBase::SetCondenseWhiteSpace(false);
    TiXmlDocument labelFile("data/text/dataskills.xml");
    
	if(!(labelFile.LoadFile()))
	{
		cerr << "Could not load file 'data/text/dataskills.xml'. Error= " <<
         labelFile.ErrorDesc() << ".\nExiting...\n";
		return;
	}
    
    TiXmlNode*	node			= 0;
    TiXmlElement* listElement	= 0;
	TiXmlElement* element		= 0;
	
	node = labelFile.FirstChild("skills");
	listElement = node->ToElement();
	
	node = listElement->FirstChild("skill");
	element = node->ToElement();
	
	do {
	    Skill *skill = new Skill;
 
		node = element->FirstChild("name");
		skill->name = node->FirstChild()->Value();

		node = element->FirstChild("long");
		skill->longName = node->FirstChild()->Value();

		node = element->FirstChild("graphic");
		skill->graphic = atoi(node->FirstChild()->Value());
		
		element->Attribute("type", &skill->type);
		array->push_back(skill);
		
		element = element->NextSiblingElement();
	} while(element);
}

//
// $Id: skill.cpp,v 1.3 2004/06/23 15:37:05 sikon Exp $
//

