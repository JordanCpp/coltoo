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
// FILE		: tile.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Brett Anthoine,  November 2003
//
// CLASS	: Tile
//
// DESCRIPTION	: A tile is a piece of map.
//

#include "tile.h"
#include "resources.h"

Tile::Tile()
{
    m_Flags = new tileFlags;

    m_Flags->forest      = false;
    m_Flags->rain        = false;
    m_Flags->mountain    = false;
    m_Flags->hill        = false;
    m_Flags->peak        = false;
    m_Flags->river       = false;
    m_Flags->water       = false;
    m_Flags->clear       = false;
    m_Flags->plowed      = false;
    m_Flags->road        = false;
    m_Flags->build       = false;
    m_Flags->unit        = false;
    m_Flags->fake        = false;
    m_Flags->rumor       = false;
    m_Flags->fakeRumor   = false;
    m_Flags->fakeForest  = false;
    m_Flags->fakeMountain= false;
    m_Flags->fakeHill    = false;
    m_Flags->fakePeak    = false;

    xpos       = 0;
    ypos       = 0;
    terrain    = 0;
    fkterrain  = 0;
    villages   = 0;

    //shrdstate  = 0;

    m_RoadLinks         = NULL;
    m_ForestLinks       = NULL;
    m_FakeForestLinks   = NULL;
    m_HillLinks         = NULL;
    m_FakeHillLinks     = NULL;
    m_MountainLinks     = NULL;
    m_FakeMountainLinks = NULL;
    m_PeakLinks         = NULL;
    m_FakePeakLinks     = NULL;
    m_RiverLinks        = NULL;
}

Tile::~Tile()
{
    if(m_Flags) delete m_Flags;
    m_Flags = NULL;
    if(m_RoadLinks) delete m_RoadLinks;
    m_RoadLinks = NULL;
    if(m_ForestLinks) delete m_ForestLinks;
    m_ForestLinks = NULL;
    if(m_PeakLinks) delete m_PeakLinks;
    m_PeakLinks = NULL;
    if(m_MountainLinks) delete m_MountainLinks;
    m_MountainLinks = NULL;
    if(m_HillLinks) delete m_HillLinks;
    m_HillLinks = NULL;
    if(m_RiverLinks) delete m_RiverLinks;
    m_RiverLinks = NULL;
    shrdstate.clear();
}

//flags
bool Tile::Is(enum tileTypes t)
{
    switch(t)
    {
    case TILE_FOREST:       return m_Flags->forest;
    case TILE_RAIN:         return m_Flags->rain;
    case TILE_MOUNTAIN:     return m_Flags->mountain;
    case TILE_HILL:         return m_Flags->hill;
    case TILE_PEAK:         return m_Flags->peak;
    case TILE_RIVER:        return m_Flags->river;
    case TILE_WATER:        return m_Flags->water;
    case TILE_CLEAR:        return m_Flags->clear;
    case TILE_PLOWED:       return m_Flags->plowed;
    case TILE_ROAD:         return m_Flags->road;
    case TILE_BUILD:        return m_Flags->build;
    case TILE_UNIT:         return m_Flags->unit;
    case TILE_FAKE:         return m_Flags->fake;
    case TILE_RUMOR:        return m_Flags->rumor;
    case TILE_FAKERUMOR:    return m_Flags->fakeRumor;
    case TILE_FAKEFOREST:   return m_Flags->fakeForest;
    case TILE_FAKEMOUNTAIN: return m_Flags->fakeMountain;
    case TILE_FAKEHILL:     return m_Flags->fakeHill;
    case TILE_FAKEPEAK:     return m_Flags->fakePeak;
    default: return false;
    }
}

bool Tile::IsReal(enum tileTypes t)
{
    switch(t)
    {
    case TILE_FOREST: case TILE_FAKEFOREST:
        return Is(TILE_FOREST);
    case TILE_HILL: case TILE_FAKEHILL:
        return Is(TILE_HILL);
    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN:
        return Is(TILE_MOUNTAIN);
    case TILE_PEAK: case TILE_FAKEPEAK:
        return Is(TILE_PEAK);
    default: return Is(t);
    }
}

bool Tile::IsFake(enum tileTypes t)
{
    switch(t)
    {
    case TILE_FOREST: case TILE_FAKEFOREST:
        return Is(TILE_FAKEFOREST);
    case TILE_HILL: case TILE_FAKEHILL:
        return Is(TILE_FAKEHILL);
    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN:
        return Is(TILE_FAKEMOUNTAIN);
    case TILE_PEAK: case TILE_FAKEPEAK:
        return Is(TILE_FAKEPEAK);
    default: return Is(t);
    }
}

void Tile::setFlags(enum tileTypes flag, bool onoff)
{
    switch(flag)
    {
    case TILE_FOREST:
        m_Flags->forest = onoff;
        if(onoff==false && !hasLink(TILE_FAKEFOREST,ANY_DIR))  //we're clearing the forest
        {
            if(m_ForestLinks) delete m_ForestLinks;
            m_ForestLinks = NULL;
            if(m_FakeForestLinks) delete m_FakeForestLinks;
            m_FakeForestLinks = NULL;
        }
        break;
    case TILE_ROAD:
        m_Flags->road = onoff;
        if(onoff==true && m_RoadLinks==NULL)
            m_RoadLinks = new tileLinks();
        break;
    case TILE_RAIN:         m_Flags->rain         = onoff; break;
    case TILE_MOUNTAIN:     m_Flags->mountain     = onoff; break;
    case TILE_HILL:         m_Flags->hill         = onoff; break;
    case TILE_PEAK:         m_Flags->peak         = onoff; break;
    case TILE_RIVER:        m_Flags->river        = onoff; break;
    case TILE_WATER:        m_Flags->water        = onoff; break;
    case TILE_CLEAR:        m_Flags->clear        = onoff; break;
    case TILE_PLOWED:       m_Flags->plowed       = onoff; break;
    case TILE_BUILD:        m_Flags->build        = onoff; break;
    case TILE_UNIT:         m_Flags->unit         = onoff; break;
    case TILE_FAKE:         m_Flags->fake         = onoff; break;
    case TILE_RUMOR:        m_Flags->rumor        = onoff; break;
    case TILE_FAKERUMOR:    m_Flags->fakeRumor    = onoff; break;
    case TILE_FAKEFOREST:   m_Flags->fakeForest   = onoff; break;
    case TILE_FAKEMOUNTAIN: m_Flags->fakeMountain = onoff; break;
    case TILE_FAKEHILL:     m_Flags->fakeHill     = onoff; break;
    case TILE_FAKEPEAK:     m_Flags->fakePeak     = onoff; break;
    default: break;
    }
}

//method for setting the links of a tile (all types of link)
void Tile::setRealLink(enum tileTypes type, enum directions d, bool onoff)
{
    switch(type)
    {
    case TILE_ROAD: case TILE_RIVER:
        setLink(type,d,onoff); break;
    case TILE_FOREST: case TILE_FAKEFOREST:
        setLink(TILE_FOREST,d,onoff); break;
    case TILE_HILL: case TILE_FAKEHILL:
        setLink(TILE_HILL,d,onoff); break;
    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN:
        setLink(TILE_MOUNTAIN,d,onoff); break;
    case TILE_PEAK: case TILE_FAKEPEAK:
        setLink(TILE_PEAK,d,onoff); break;
    default: return;
    }
}

void Tile::setFakeLink(enum tileTypes type, enum directions d, bool onoff)
{
    switch(type)
    {
    case TILE_ROAD: case TILE_RIVER:
        setLink(type,d,onoff); break;
    case TILE_FOREST: case TILE_FAKEFOREST:
        setLink(TILE_FAKEFOREST,d,onoff); break;
    case TILE_HILL: case TILE_FAKEHILL:
        setLink(TILE_FAKEHILL,d,onoff); break;
    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN:
        setLink(TILE_FAKEMOUNTAIN,d,onoff); break;
    case TILE_PEAK: case TILE_FAKEPEAK:
        setLink(TILE_FAKEPEAK,d,onoff); break;
    default: return;
    }
}

void Tile::setLink(enum tileTypes type, enum directions d,bool onoff)
{
    switch(type)
    {
        case TILE_ROAD:
            if(!m_RoadLinks) return;
            if(d==E ) m_RoadLinks->E  = onoff;
            if(d==N ) m_RoadLinks->N  = onoff;
            if(d==W ) m_RoadLinks->W  = onoff;
            if(d==S ) m_RoadLinks->S  = onoff;
            if(d==NE) m_RoadLinks->NE = onoff;
            if(d==SE) m_RoadLinks->SE = onoff;
            if(d==NW) m_RoadLinks->NW = onoff;
            if(d==SW) m_RoadLinks->SW = onoff;
            break;
        case TILE_FOREST:
            if(!m_ForestLinks) m_ForestLinks = new tileLinks();
            if(d==E ) m_ForestLinks->E  = onoff;
            if(d==N ) m_ForestLinks->N  = onoff;
            if(d==W ) m_ForestLinks->W  = onoff;
            if(d==S ) m_ForestLinks->S  = onoff;
            break;
        case TILE_FAKEFOREST:
            if(!m_FakeForestLinks) m_FakeForestLinks = new tileLinks();
            if(d==E ) m_FakeForestLinks->E  = onoff;
            if(d==N ) m_FakeForestLinks->N  = onoff;
            if(d==W ) m_FakeForestLinks->W  = onoff;
            if(d==S ) m_FakeForestLinks->S  = onoff;
            break;
        case TILE_PEAK:
            if(!m_PeakLinks) m_PeakLinks = new tileLinks();
            if(d==E ) m_PeakLinks->E  = onoff;
            if(d==N ) m_PeakLinks->N  = onoff;
            if(d==W ) m_PeakLinks->W  = onoff;
            if(d==S ) m_PeakLinks->S  = onoff;
            break;
        case TILE_FAKEPEAK:
            if(!m_FakePeakLinks) m_FakePeakLinks = new tileLinks();
            if(d==E ) m_FakePeakLinks->E  = onoff;
            if(d==N ) m_FakePeakLinks->N  = onoff;
            if(d==W ) m_FakePeakLinks->W  = onoff;
            if(d==S ) m_FakePeakLinks->S  = onoff;
            break;
        case TILE_MOUNTAIN:
            if(!m_MountainLinks) m_MountainLinks = new tileLinks();
            if(d==E ) m_MountainLinks->E  = onoff;
            if(d==N ) m_MountainLinks->N  = onoff;
            if(d==W ) m_MountainLinks->W  = onoff;
            if(d==S ) m_MountainLinks->S  = onoff;
            break;
        case TILE_FAKEMOUNTAIN:
            if(!m_FakeMountainLinks) m_FakeMountainLinks = new tileLinks();
            if(d==E ) m_FakeMountainLinks->E  = onoff;
            if(d==N ) m_FakeMountainLinks->N  = onoff;
            if(d==W ) m_FakeMountainLinks->W  = onoff;
            if(d==S ) m_FakeMountainLinks->S  = onoff;
            break;
        case TILE_HILL:
            if(!m_HillLinks) m_HillLinks = new tileLinks();
            if(d==E ) m_HillLinks->E  = onoff;
            if(d==N ) m_HillLinks->N  = onoff;
            if(d==W ) m_HillLinks->W  = onoff;
            if(d==S ) m_HillLinks->S  = onoff;
            break;
        case TILE_FAKEHILL:
            if(!m_FakeHillLinks) m_FakeHillLinks = new tileLinks();
            if(d==E ) m_FakeHillLinks->E  = onoff;
            if(d==N ) m_FakeHillLinks->N  = onoff;
            if(d==W ) m_FakeHillLinks->W  = onoff;
            if(d==S ) m_FakeHillLinks->S  = onoff;
            break;
        case TILE_RIVER:
            if(!m_RiverLinks) m_RiverLinks = new tileLinks();
            if(d==E ) m_RiverLinks->E  = onoff;
            if(d==N ) m_RiverLinks->N  = onoff;
            if(d==W ) m_RiverLinks->W  = onoff;
            if(d==S ) m_RiverLinks->S  = onoff;
            if(d==NE) m_RiverLinks->NE = onoff;
            if(d==SE) m_RiverLinks->SE = onoff;
            if(d==NW) m_RiverLinks->NW = onoff;
            if(d==SW) m_RiverLinks->SW = onoff;
            break;
        default: break;
    }
}

//method for getting the links of a tile (all types of link)
bool Tile::hasLink(enum tileTypes type, enum directions d)
{
    switch(type)
    {
        case TILE_ROAD:
            if(!m_RoadLinks) return false;
            switch(d)
            {
                case E : return m_RoadLinks->E ;
                case N : return m_RoadLinks->N ;
                case W : return m_RoadLinks->W ;
                case S : return m_RoadLinks->S ;
                case NE: return m_RoadLinks->NE;
                case SE: return m_RoadLinks->SE;
                case NW: return m_RoadLinks->NW;
                case SW: return m_RoadLinks->SW;
                case ANY_DIR: return (m_RoadLinks->E  || m_RoadLinks->N  ||
                                      m_RoadLinks->W  || m_RoadLinks->S  ||
                                      m_RoadLinks->NE || m_RoadLinks->SE ||
                                      m_RoadLinks->NW || m_RoadLinks->SW);
                default: return false;
            }
        case TILE_FOREST:
            if(!m_ForestLinks) return false;
            switch(d)
            {
                case E : return m_ForestLinks->E ;
                case N : return m_ForestLinks->N ;
                case W : return m_ForestLinks->W ;
                case S : return m_ForestLinks->S ;
                case ANY_DIR: return (m_ForestLinks->E  || m_ForestLinks->N  ||
                                      m_ForestLinks->W  || m_ForestLinks->S  );
                default: return false;
            }
        case TILE_FAKEFOREST:
            if(!m_FakeForestLinks) return false;
            switch(d)
            {
                case E : return m_FakeForestLinks->E ;
                case N : return m_FakeForestLinks->N ;
                case W : return m_FakeForestLinks->W ;
                case S : return m_FakeForestLinks->S ;
                case ANY_DIR: return (m_FakeForestLinks->E  || m_FakeForestLinks->N  ||
                                      m_FakeForestLinks->W  || m_FakeForestLinks->S  );
                default: return false;
            }
        case TILE_PEAK:
            if(!m_PeakLinks) return false;
            switch(d)
            {
                case E : return m_PeakLinks->E ;
                case N : return m_PeakLinks->N ;
                case W : return m_PeakLinks->W ;
                case S : return m_PeakLinks->S ;
                case ANY_DIR: return (m_PeakLinks->E  || m_PeakLinks->N  ||
                                      m_PeakLinks->W  || m_PeakLinks->S  );
                default: return false;
            }
        case TILE_FAKEPEAK:
            if(!m_FakePeakLinks) return false;
            switch(d)
            {
                case E : return m_FakePeakLinks->E ;
                case N : return m_FakePeakLinks->N ;
                case W : return m_FakePeakLinks->W ;
                case S : return m_FakePeakLinks->S ;
                case ANY_DIR: return (m_FakePeakLinks->E  || m_FakePeakLinks->N  ||
                                      m_FakePeakLinks->W  || m_FakePeakLinks->S  );
                default: return false;
            }
        case TILE_MOUNTAIN:
            if(!m_MountainLinks) return false;
            switch(d)
            {
                case E : return m_MountainLinks->E ;
                case N : return m_MountainLinks->N ;
                case W : return m_MountainLinks->W ;
                case S : return m_MountainLinks->S ;
                case ANY_DIR: return (m_MountainLinks->E  || m_MountainLinks->N  ||
                                      m_MountainLinks->W  || m_MountainLinks->S  );
                default: return false;
            }
        case TILE_FAKEMOUNTAIN:
            if(!m_FakeMountainLinks) return false;
            switch(d)
            {
                case E : return m_FakeMountainLinks->E ;
                case N : return m_FakeMountainLinks->N ;
                case W : return m_FakeMountainLinks->W ;
                case S : return m_FakeMountainLinks->S ;
                case ANY_DIR: return (m_FakeMountainLinks->E  || m_FakeMountainLinks->N  ||
                                      m_FakeMountainLinks->W  || m_FakeMountainLinks->S  );
                default: return false;
            }
        case TILE_HILL:
            if(!m_HillLinks) return false;
            switch(d)
            {
                case E : return m_HillLinks->E ;
                case N : return m_HillLinks->N ;
                case W : return m_HillLinks->W ;
                case S : return m_HillLinks->S ;
                case ANY_DIR: return (m_HillLinks->E  || m_HillLinks->N  ||
                                      m_HillLinks->W  || m_HillLinks->S  );
                default: return false;
            }
        case TILE_FAKEHILL:
            if(!m_FakeHillLinks) return false;
            switch(d)
            {
                case E : return m_FakeHillLinks->E ;
                case N : return m_FakeHillLinks->N ;
                case W : return m_FakeHillLinks->W ;
                case S : return m_FakeHillLinks->S ;
                case ANY_DIR: return (m_FakeHillLinks->E  || m_FakeHillLinks->N  ||
                                      m_FakeHillLinks->W  || m_FakeHillLinks->S  );
                default: return false;
            }
        case TILE_RIVER:
            if(!m_RiverLinks) return false;
            switch(d)
            {
                case E : return m_RiverLinks->E ;
                case N : return m_RiverLinks->N ;
                case W : return m_RiverLinks->W ;
                case S : return m_RiverLinks->S ;
                case NE: return m_RiverLinks->NE;
                case SE: return m_RiverLinks->SE;
                case NW: return m_RiverLinks->NW;
                case SW: return m_RiverLinks->SW;
                case ANY_DIR: return (m_RiverLinks->E  || m_RiverLinks->N  ||
                                      m_RiverLinks->W  || m_RiverLinks->S  ||
                                      m_RiverLinks->NE || m_RiverLinks->SE ||
                                      m_RiverLinks->NW || m_RiverLinks->SW);
                default: return false;
            }
        default: return false;
    }
}

bool Tile::hasFakeLink(enum tileTypes type, enum directions d)
{
    switch(type)
    {
    case TILE_FAKEFOREST  : case TILE_FAKEHILL:
    case TILE_FAKEMOUNTAIN: case TILE_FAKEPEAK:
    case TILE_RIVER       :
        return hasLink(type, d);
    case TILE_FOREST:
        return hasLink(TILE_FAKEFOREST, d);
    case TILE_HILL:
        return hasLink(TILE_FAKEHILL, d);
    case TILE_MOUNTAIN:
        return hasLink(TILE_FAKEMOUNTAIN, d);
    case TILE_PEAK:
        return hasLink(TILE_FAKEPEAK, d);
    default: return false;
    }
}

bool Tile::hasRealLink(enum tileTypes type, enum directions d)
{
    switch(type)
    {
    case TILE_FOREST  : case TILE_HILL:
    case TILE_MOUNTAIN: case TILE_PEAK:
    case TILE_RIVER   :
        return hasLink(type, d);
    case TILE_FAKEFOREST:
        return hasLink(TILE_FOREST, d);
    case TILE_FAKEHILL:
        return hasLink(TILE_HILL, d);
    case TILE_FAKEMOUNTAIN:
        return hasLink(TILE_MOUNTAIN, d);
    case TILE_FAKEPEAK:
        return hasLink(TILE_PEAK, d);
    default: return false;
    }
}

void Tile::InitShrdstate(vector<Player*> pl)
{
    ShrdstateType st = { "", 0 };
    int i;
    for(i=0; i<pl.size(); i++)
    {
        st.nationName = pl[i]->country.name;
        shrdstate.push_back(st);
    }
}

void Tile::InitShrdstate(Player *pl)
{
    ShrdstateType st = { "", 0 };
    int i;
    for(i=0; i<shrdstate.size(); i++)
    {
        if(shrdstate[i].nationName==pl->country.name)
        {
            return;
        }
    }
    st.nationName = pl->country.name;
    shrdstate.push_back(st);
}

Uint8 Tile::getShrdstate(Uint8 n)
{
    int nt = (int) n;
    if((nt>=0) && (nt<=shrdstate.size())) return shrdstate[nt].state;
    return 0;
}

void Tile::setShrdstate(Uint8 t)
{
    int i;
    for(i=0;i<shrdstate.size();i++) setShrdstate(i,t);
}

void Tile::setShrdstate(Uint8 n,Uint8 t)
{
    int nt = (int) n;
    if((nt>=0) && (nt<=shrdstate.size()))
    {
        shrdstate[nt].state = t;
    }
}

//
// $Id: tile.cpp,v 1.7 2004/06/23 15:37:05 sikon Exp $
//

