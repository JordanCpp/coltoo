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
// FILE		: Unit.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  October 2003
//
// CLASS	: Unit
//
// DESCRIPTION	: Units informations and manipulations.
//

#include "unit.h"

//Constructor, destructor
Unit::Unit()
{
    turnStatus = false;
    orders = 0;
    skill = NULL;
    eGraphic = 0;
    eSkillType = 0;   
}

Unit::~Unit(){
}

Unit* Unit::loadUnitFile(int type)
{
    /*Unit format :
            <name>Colonists</name>
	    	<class>Civil</class>
            <move>1</move>
	    	<hits>0</hits>
	    	<visual>1</visual>
	    	<attack>0</attack>
	    	<defence>1</defence>
	    	<skill>0</skill>
	    	<transport>0</transport>
	    	<cargo>0</cargo>
	    	<size>1</size>*/


    Unit* unit = new Unit();
    string tmp;
    
    TiXmlBase::SetCondenseWhiteSpace( false );
    
    TiXmlDocument unitFile("data/text/dataunits.xml");
    
    bool loadOkay = unitFile.LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file 'dataunits.xml'. Error='%s'. Exiting.\n", unitFile.ErrorDesc() );
		exit( 1 );
	}
    
    TiXmlNode* node = 0;
    TiXmlElement* unitListElement = 0;
	TiXmlElement* unitElement = 0;
	
	node = unitFile.FirstChild( "unitlist" );
	unitListElement = node->ToElement();
	
	node = unitListElement->FirstChildElement();
	unitElement = node->ToElement();
	int i;
	unitElement->Attribute("type",&i);
	while(i != type)
	{   
	     node = node->NextSibling();
	     unitElement = node->ToElement();
	     unitElement->Attribute("type",&i);
	}
	unit->type = type;
	
	//At this point , unitElement = the node beginning an unit definition
    node = unitElement->FirstChild("name");
	unit->setName((node->FirstChild())->Value());
		
	node = unitElement->FirstChild("class");
	tmp = (node->FirstChild())->Value();
	unit->setClassType(tmp);
	
	node = unitElement->FirstChild("move");
	tmp = (node->FirstChild())->Value();
	unit->setMoveCapability(atoi(tmp.c_str()));

	node = unitElement->FirstChild("hits");
	//NOT USED FOR NOW
	
	node = unitElement->FirstChild("visual");
	tmp = (node->FirstChild())->Value();
	unit->setVisual(atoi(tmp.c_str()));
	
	node = unitElement->FirstChild("attack");
	tmp = (node->FirstChild())->Value();
	unit->setAttack(atoi(tmp.c_str()));
	
	node = unitElement->FirstChild("defense");
	tmp = (node->FirstChild())->Value();
	unit->setDefense(atoi(tmp.c_str()));
 	
 	node = unitElement->FirstChild("skill");
	//NOT USED FOR NOW
	
	node = unitElement->FirstChild("transport");
	tmp = (node->FirstChild())->Value();
	unit->setTransportCapacity(atoi(tmp.c_str()));
	
	node = unitElement->FirstChild("cargo");
	tmp = (node->FirstChild())->Value();
	unit->setCargoCapacity(atoi(tmp.c_str()));
	
	node = unitElement->FirstChild("size");
	tmp = (node->FirstChild())->Value();
	unit->setSize(atoi(tmp.c_str()));
	
// >>>
    node = unitElement->FirstChild("graphic");
	tmp = (node->FirstChild())->Value();
	unit->graphic = atoi(tmp.c_str());
	
	node = unitElement->FirstChild("grsmall");
	tmp = (node->FirstChild())->Value();
	unit->setGSmall(atoi(tmp.c_str()));
	
	if(node = unitElement->FirstChild("egraphic"))
	{
	    node->ToElement()->Attribute("skill", &unit->eSkillType);
	    unit->eGraphic = atoi(node->FirstChild()->Value());
    }

	unit->setOnboardFlag(false);
// <<<
    return unit;
}

bool Unit::isBoat()
{
    if(classType == "Naval")
        return true;
    else
        return false;
}

bool Unit::addPassenger(Unit* u)
{
    //Transport capability and capacity check
    
    if(passengers.size() < transportCapacity){
        passengers.push_back(u);
        return true;     //success
    }   	
    return false;     // error
}

bool Unit::removeAllPassengers()
{
    passengers.clear();
    return true;
}

bool Unit::removePassenger(Uint8 index)
{
//TODO :: ugly function, rewrite !
    vector<Unit*>::iterator p;
    p = passengers.begin();
    p += index;
    
    if(passengers.size() > index)
    {
        passengers.erase(p);
        cout << "Size: " << passengers.size();
        return true;
    }
    return false;
}

bool Unit::addResources(Resources* r)
{
    //Cargo capability and capacity check
    
    if(cargoInside.size() < cargoCapacity)
    {
        cargoInside.push_back(r);
        return true;     //success
    }   	
    return false;     // error
}

bool Unit::removeAllResources()
{
    cargoInside.clear();
    return true;
}

bool Unit::removeResources(Uint8 index)
{
//TODO :: ugly function, rewrite !
    vector<Resources*>::iterator p;
    p = cargoInside.begin();
    p += index;
    
    if(cargoInside.size() > index){
        cargoInside.erase(p);
        return true;
    }
    return false;
}

//More Methods
bool Unit::disband()
{
    return false;
}

/*bool Unit::fortify()
{
    return false;
}

bool Unit::sentry()
{
    return false;
} */

bool Unit::buildColony()
{
    return false;
}

bool Unit::joinColony()
{
    return false;
}

bool Unit::establishMision()
{
    return false;
}


bool Unit::move(Uint8 direction)
{
    return false;
}

int Unit::getGraphic()
{
    if(skill && (type == IDU_COLONIST))
        return skill->getGraphic();
    if(skill && eSkillType && isExpert())
        return eGraphic;
    return graphic;
}

bool Unit::isExpert()
{
    return skill && (skill->getType() == eSkillType);
}

char *Unit::getSkillName()
{
    if(skill && eSkillType && isExpert())
        return "Expert";
    else if(skill)
        return (char *)skill->getName().c_str();
    return NULL;
}

//
// $Id: unit.cpp,v 1.8 2004/06/23 15:37:05 sikon Exp $
//

