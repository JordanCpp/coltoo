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
 
#ifndef MESSAGE_H
#define MESSAGE_H 1
 
#include <string>
#include <vector>
using namespace std;

#define MSG_RUMOR 0
#define MSG_NEWRECRUIT 1
#define MSG_VILLAGE 2
#define MSG_NOROOMPASS 3
#define MSG_NOROOMCARGO 4
#define MSG_NOTIMPLEMENTED 10
#define MSG_ALREADYCLEARED 11
#define MSG_ALREADYPLOWED 12
#define MSG_ALREADYROAD 13
#define MSG_ALREADYCOLONY 14
#define MSG_TIMESCALE 15
#define MSG_CANTATTACK 16
#define MSG_COMBAT 17
#define MSG_ENDOFTURN 18
#define MSG_NOCDS 19

#define SYS_NOTIMPLEMENTED 0
#define SYS_ALREADYROAD 1
#define SYS_ALREADYPLOWED 2
#define SYS_ALREADYCOLONY 3
#define SYS_ALREADYCLEARED 4
#define SYS_NOROOMPASS 5
#define SYS_NOROOMCARGO 6
#define SYS_TIMESCALE 7
#define SYS_CANTATTACK 8
#define SYS_COMBAT 9
#define SYS_ENDOFTURN 10
#define SYS_NOCDS 11

#define COUNTRIES 4
#define NATION_ENG 0
#define NATION_FR 1
#define NATION_SPAN 2
#define NATION_DUT 3
#define NATION_TRIBE 4

class Tile;
 
class Message
{
public:
    Message();
    ~Message();
    void ParseXml(string xmlFile, vector<string> *array, string root, string item);
    void ReadMessages();
    string GetSysMessage(int message);
    string GetVillageMessage(Tile *village);
    string GetRumorMessage(Tile *rumor);
    char *GetShortNation(int nation);
    char GetOrderLetter(Uint8 order);
private:
    vector<string> *SysMsg, *VillMsg, *RumorMsg;
};

#endif

//
// $Id: message.h,v 1.5 2004/06/23 15:37:05 sikon Exp $
//

