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
// FILE		: CTileTypes.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Chainsword,  June 2004
//
// CLASS	: CTileTypes
//
// DESCRIPTION	: Tile information
//

#include "CTileTypes.h"
#include <string>
#include <vector>
#include "tinyxml.h"
#include "tile.h"

CTileTypes::CTileTypes()
{
    current_tile = -1;
    current_resource = -1;
}

CTileTypes::~CTileTypes()
{
  vector<CTileType*>::iterator t = ttypes.begin();
  for(t=ttypes.begin(); t!=ttypes.end(); t++)
  {
      if(*t) delete (*t);
  }
  ttypes.clear();
  vector<CTileResource*>::iterator r = tresources.begin();
  for(r=tresources.begin(); r!=tresources.end(); r++)
  {
      if(*r) delete (*r);
  }
  tresources.clear();
}

void CTileTypes::InitTileTypes()
{
    /* Tile Format:
    <terrain>
        <tiles>
            <tile type="unforest" name="Tundra" res="Game"
                  move="1" defensive="0" improvement="4" value="2">
                <production farmer="2" sugar="0" tabacco="0" cotton="0"
                            furs="0" wood="0" ore="2" silver="0" fish="0"/>
            </tile>
        </tiles>
        <resources>
            <resource name="Depleted Mine" value="6" keep="4"/>
        </resources>
    </terrain>*/
    
    string tmp;
    CTileType *t;
    CTileResource *r;
    int ID = 0, i, j;
    
    TiXmlBase::SetCondenseWhiteSpace( false );
    
    TiXmlDocument tileFile("data/text/tiles.xml");
    
    bool loadOkay = tileFile.LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file 'tiles.xml'. Error='%s'. Exiting.\n", tileFile.ErrorDesc() );
		exit( 1 );
	}
    
    TiXmlNode* node = 0;
    TiXmlElement* tileListElement = 0;
	TiXmlElement* tileElement = 0;
	TiXmlElement* tileResource = 0;
	TiXmlNode*    tnode = 0;
    
    #ifdef DEBUG
    cout<<"  Loading terrain types {"<<endl;
    #endif
    node = tileFile.FirstChild("terrain");
    tileListElement = node->FirstChild("tiles")->ToElement();
    tnode = tileListElement->FirstChild("tile");
    while(tnode)
    {
        tileElement = tnode->ToElement();
        ID++;
        #ifdef DEBUG
        cout<<"    reading tile["<<ID<<"] - ";
        #endif
        t = new CTileType();
        t->TileID(ID);
        if(tileElement->Attribute("name")) t->TileName(tileElement->Attribute("name"));
        tmp = tileElement->Attribute("type");
        if(tmp=="unforested")
        {
            t->TileType(TL_UNFORESTED);
        }
        else if(tmp=="forested")
        {
            t->TileType(TL_FORESTED);
        }
        else if(tmp=="other")
        {
            t->TileType(TL_OTHER);
        }
        else
        {
            t->TileType(TL_UNDEFINED);
        }
        if(tileElement->Attribute("becomes")) t->NewTileName(tileElement->Attribute("becomes"));
        if(tileElement->Attribute("res")) t->ResourceName(tileElement->Attribute("res"));
        tileElement->Attribute("move",&i); t->Movement(i);
        tileElement->Attribute("defensive",&i); t->Defensive(i);
        tileElement->Attribute("improvement",&i); t->Improvement(i);
        tileElement->Attribute("value",&i); t->Value(i);
        t->LoadProduction(tileElement, t);
        #ifdef DEBUG
        cout<<"    got terrain "<<t->TileName()<<endl;
        #endif
        ttypes.push_back(t);
        tnode = tnode->NextSibling("tile");
    }
    #ifdef DEBUG
    cout<<"  }"<<endl<<"  Loading terrain resources {"<<endl;
    #endif
    ID = 0;
    tileListElement = node->FirstChild("resources")->ToElement();
    tnode = tileListElement->FirstChild("resource");
    while(tnode)
    {
        tileElement = tnode->ToElement();
        ID++;
        #ifdef DEBUG
        cout<<"    reading resource["<<ID<<"] - ";
        #endif
        r = new CTileResource();
        r->ResourceID(ID);
        if(tileElement->Attribute("name")) r->ResourceName(tileElement->Attribute("name"));
        tileElement->Attribute("value", &i); r->ResourceValue(i);
        tileElement->Attribute("keep", &i); r->ResourceKeep(i);
        #ifdef DEBUG
        cout<<"  got resource "<<r->ResourceName()<<endl;
        #endif
        tresources.push_back(r);
        tnode = tnode->NextSibling("resource");
    }
    #ifdef DEBUG
    cout<<"  }"<<endl;
    #endif
    for(ID=0; ID<ttypes.size(); ID++)
    {
        t = FindTileType(ttypes[ID]->NewTileName());
        if(t) ttypes[ID]->NewTileID(t->TileID());
        r = FindTileResource(ttypes[ID]->ResourceName());
        if(r) ttypes[ID]->ResourceID(r->ResourceID());
    }
}

CTileType *CTileTypes::FindTileType(const char *name)
{
    int i;
    for(i=0; i<ttypes.size(); i++)
    {
        if(strcmp(ttypes[i]->TileName(),name)==0) return ttypes[i];
    }
    return NULL;
}

CTileType *CTileTypes::FindTileType(int id)
{
    int i;
    for(i=0; i<ttypes.size(); i++)
    {
        if(ttypes[i]->TileID()==id) return ttypes[i];
    }
    return NULL;
}

CTileType *CTileTypes::FindTileTypeFrom(Tile *t)
{
    switch(t->getTerrain())
    {
        case TERRAIN_ARCTIC:
        #ifdef DEBUG
        cout<<"Got Arctic"<<endl;
        #endif
        return FindTileType("Arctic");
        case TERRAIN_TUNDRA:
        #ifdef DEBUG
        cout<<"Got ";
        if(t->Is(TILE_FOREST)) cout<<"forested ";
        cout<<"Tundra"<<endl;
        #endif
        if(t->Is(TILE_FOREST)) return FindTileType("Boreal");
        return FindTileType("Tundra");
        case TERRAIN_DESERT:
        #ifdef DEBUG
        cout<<"Got Desert"<<endl;
        #endif
        return FindTileType("Desert");
        case TERRAIN_OPENS:
        #ifdef DEBUG
        cout<<"Got Sea Lane"<<endl;
        #endif
        return FindTileType("Sea Lane");
        case TERRAIN_SAVANNAH:
        #ifdef DEBUG
        cout<<"Got ";
        if(t->Is(TILE_FOREST)) cout<<"forested ";
        cout<<"Savannah"<<endl;
        #endif
        if(t->Is(TILE_FOREST)) return FindTileType("Tropical");
        return FindTileType("Savannah");
        case TERRAIN_GRASS:
        #ifdef DEBUG
        cout<<"Got ";
        if(t->Is(TILE_FOREST)) cout<<"forested ";
        cout<<"Grassland"<<endl;
        #endif
        if(t->Is(TILE_FOREST)) return FindTileType("Conifer");
        return FindTileType("Grassland");
        case TERRAIN_PRAIRIE:
        #ifdef DEBUG
        cout<<"Got ";
        if(t->Is(TILE_FOREST)) cout<<"forested ";
        cout<<"Prairie"<<endl;
        #endif
        if(t->Is(TILE_FOREST)) return FindTileType("Broadleaf");
        return FindTileType("Prairie");
        case TERRAIN_STEPPE:
        #ifdef DEBUG
        cout<<"Got ";
        if(t->Is(TILE_FOREST)) cout<<"forested ";
        cout<<"Plains"<<endl;
        #endif
        if(t->Is(TILE_FOREST)) return FindTileType("Mixed");
        return FindTileType("Plains");
        case TERRAIN_CHAPARRAL:
        #ifdef DEBUG
        cout<<"Got Scrub"<<endl;
        #endif
        return FindTileType("Scrub");
        case TERRAIN_LAKE:
        #ifdef DEBUG
        cout<<"Got Lake"<<endl;
        #endif
        return FindTileType("Ocean");
        case TERRAIN_OCEAN:
        #ifdef DEBUG
        cout<<"Got Ocean"<<endl;
        #endif
        return FindTileType("Ocean");
        case TERRAIN_HIGHSEAS:
        #ifdef DEBUG
        cout<<"Got High Seas"<<endl;
        #endif
        return FindTileType("Sea Lane");
        default:
        #ifdef DEBUG
        cout<<"No terrain was found"<<endl;
        #endif
        return NULL;
    }
}

CTileResource *CTileTypes::FindTileResource(const char *name)
{
    int i;
    for(i=0; i<tresources.size(); i++)
    {
        if(tresources[i]->ResourceName()==name) return tresources[i];
    }
    return NULL;
}

CTileResource *CTileTypes::FindTileResource(int id)
{
    int i;
    for(i=0; i<tresources.size(); i++)
    {
        if(tresources[i]->ResourceID()==id) return tresources[i];
    }
    return NULL;
}

CTileType *CTileTypes::TileType(void)
{
    return TileType(current_tile);
}

CTileType *CTileTypes::TileType(int id)
{
    if((id>=0) && (id<ttypes.size()))
    {
        current_tile = id;
        return ttypes[id];
    }
}

CTileResource *CTileTypes::TileResource(void)
{
    return TileResource(current_resource);
}

CTileResource *CTileTypes::TileResource(int id)
{
    if((id>=0) && (id<tresources.size()))
    {
        current_resource = id;
        return tresources[id];
    }
}
