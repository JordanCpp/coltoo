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
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef SKILL_H
#define SKILL_H 1
#include <string>
#include <vector>
using namespace std;

#define IDS_COLONIST 1500
#define IDS_SLVRMINER 1504
#define IDS_DISTILLER 1510
#define IDS_SCOUT 1520
#define IDS_SUGARFMR 1521

class Skill
{
public:
    string getName();
    string getLongName();
    int getGraphic();
    int getType();
    
    void setName(string nm);
    void setLongName(string l);
    void setGraphic(int g);
    
    static void loadSkills(vector<Skill*> *array);
private:
    string name;
    string longName;
    int graphic;
    int type;
};

#endif

//
// $Id: skill.h,v 1.4 2004/06/23 15:37:05 sikon Exp $
//

