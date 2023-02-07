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
// FILE		: Colony.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: Colony
//
// DESCRIPTION	: Colony information and manipulation.
//

#include "colony.h"
// >>>
#include "tinyxml.h"
// <<<

//Constructor, destructor
Colony::Colony(bool isPort)
{
    m_Name   = "";
    m_Nation = 0;
    capacity = 100;
// >>>
    memset(warehouse, 0, sizeof(warehouse));
    setStock(IDC_FOOD, 10);
    setStock(IDC_LUMBER, rand() % 5);
    portFlag = isPort;
    initBuildings();
// <<<
}

Colony::~Colony()
{
    ;
}

//Methods
void Colony::setName   (string name)
{
    m_Name = name;
}

void Colony::setNation (int nat)
{
    m_Nation = nat;
}

string Colony::getName()
{
    return m_Name;
}

int Colony::getNation()
{
    return m_Nation;
}

int Colony::getSize()
{
    return m_Size;
}

// >>>
long Colony::getTile()
{
    return tile;
}

void Colony::setTile(long til)
{
    tile = til;
}

int Colony::getStock(int goods)
{
    return warehouse[goods];
}

void Colony::setStock(int goods, int quantity)
{
    warehouse[goods] = quantity;
}

bool Colony::isPort()
{
    return portFlag;
}

void Colony::initBuildings()
{
    int i, j, type, x, y;
    Building *build;
    lgSquare = rand() % (CDS_BUILD_XTILES - 2);
    
    for(i = 0; i < CDS_BUILD_XTILES; i++)
        for(j = 0; j < CDS_BUILD_YTILES; j++)
            if(i == lgSquare)
            {
                squares[i][j] = (rand() % (CDS_BUILD_YTILES - 2)) + 1;
            }
            else
            {
                squares[i][j] = (rand() % (CDS_BUILD_YTILES - 1)) + 1;
            }

    if(isPort())
    {
            squares[CDS_BUILD_XTILES - 2][CDS_BUILD_YTILES - 1] = 1;
            squares[CDS_BUILD_XTILES - 2][CDS_BUILD_YTILES - 1] = 1;
    }
    else
    {
            squares[CDS_BUILD_XTILES - 2][CDS_BUILD_YTILES - 1] = 2;
            squares[CDS_BUILD_XTILES - 2][CDS_BUILD_YTILES - 1] = 2;
    }
    
    for(i = 0, type = IDB_TOWNHALL; i < FIRST_BUILDINGS; i++, type++)
    {
        build = Building::loadFromFile(type);
        colonyBuildings.push_back(build);
        
        switch(build->getGraphicType())
        {
        case BGR_SMALL:
            j = 0;
            while(!j)
            {
                x = rand() % CDS_BUILD_XTILES;
                y = rand() % CDS_BUILD_YTILES;
                if(x == lgSquare || !squares[x][y] ||
                 (x >= CDS_BUILD_XTILES - 2 && y == CDS_BUILD_YTILES - 1))
                    continue;
                j = 1;
            }
            squares[x][y] = 0;
            build->x = x;
            build->y = y;
            break;
        case BGR_LARGE:
            x = lgSquare;
            y = rand() % (CDS_BUILD_YTILES - 1);
            squares[x][y] = 0;
            build->x = x;
            build->y = y;
            break;
        case BGR_DOCKS:
            squares[CDS_BUILD_XTILES - 2][CDS_BUILD_YTILES - 1] = 0;
            squares[CDS_BUILD_XTILES - 1][CDS_BUILD_YTILES - 1] = 0;
            build->x = CDS_BUILD_XTILES - 2;
            build->y = CDS_BUILD_YTILES - 1;
            break;
        }
    }
}

int Colony::getBuildingNum()
{
    return colonyBuildings.size();
}

Building *Colony::getBuilding(int i)
{
    return colonyBuildings[i];
}

Building *Building::loadFromFile(int type)
{
    Building *build = new Building();
    char *tmp;

    TiXmlBase::SetCondenseWhiteSpace( false );
    
    TiXmlDocument buildFile("data/text/databuildings.xml");
    
	if(!buildFile.LoadFile())
	{
		printf("Could not load file 'databuildings.xml'. Error='%s'. Exiting.\n",
          buildFile.ErrorDesc());
		exit(1);
	}
    
    TiXmlNode* node = 0;
    TiXmlElement* buildListElement = 0;
	TiXmlElement* buildElement = 0;
	
	node = buildFile.FirstChild("buildings");
	buildListElement = node->ToElement();
	
	node = buildListElement->FirstChildElement();
	buildElement = node->ToElement();
	int i;
	buildElement->Attribute("type", &i);
	while(i != type)
	{   
	     node = node->NextSibling();
	     buildElement = node->ToElement();
	     buildElement->Attribute("type", &i);
	}
	build->buildingType = type;
	
/*    node = buildElement->FirstChild("name");
	build->setName((node->FirstChild())->Value()); */
	
    node = buildElement->FirstChild("graphic");
    tmp = (char *)node->ToElement()->Attribute("type");
    switch(toupper(tmp[0]))
    {
    case 'S':
        build->graphicType = BGR_SMALL;
        break;
    case 'L':
        build->graphicType = BGR_LARGE;
        break;
    case 'D':
        build->graphicType = BGR_DOCKS;
        break;
    default:
        cerr << "Invalid graphic type" << endl;
        exit(1);
    }
	build->graphic = atoi(node->FirstChild()->Value());
	return build;
}

int Building::getGraphic()
{
    return graphic;
}

int Building::getGraphicType()
{
    return graphicType;
}

//
// $Id: colony.cpp,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

