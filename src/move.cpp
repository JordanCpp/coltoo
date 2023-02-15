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

#include "graphicsEngine.h"
#include "gameEngine.h"
#include "globalData.h"
#include "map.h"
#include "tile.h"
#include "unit.h"
// >>>
#include "colony.h"
// <<<

/*---------------------------MoveUnit-----------------------------*/
void GraphicsEngine::MoveUnit(unsigned char move)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;

    short k;
/*Checks to see if the move is legal
  If not, reset the scrnum and mapnum to what they were
  Checks to see if the move means the screen needs to be 
  recentered*/
  switch (move)
  {
    case (1):        //NE
    {
      data->scrnum-=data->sNE;data->mapnum-=data->mNE;
      if(data->mapnum<0 ||
         map->getTile(data->mapnum+data->mNE)->getXPos()==data->cols-1)
      {
        data->scrnum+=data->sNE;
        data->mapnum+=data->mNE;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(data->sNE,data->mNE);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}

      if(data->scrnum<11||data->scrnum%11>9){ReCenter();}
      
      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum+data->mNE)->setFlags(TILE_UNIT, false);
      }
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum+data->mNE]--;      
      }
      break;
    }
        
    case (2):               //E
    {
      data->scrnum+=data->sE;data->mapnum+=data->mE;
      if(data->scrnum>data->scrmax||data->mapnum>data->mapmax||
         map->getTile(data->mapnum-data->mE)->getXPos()==data->cols-1)
      {
        data->scrnum-=data->sE;
        data->mapnum-=data->mE;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(-data->sE,-data->mE);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}
             
      if(data->scrnum%11>9){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum-data->mE)->setFlags(TILE_UNIT, false);
      }      
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum-data->mE]--;      
      }
      break;
    }
        
    case (3):            //SE
    {
      data->scrnum+=data->sSE;data->mapnum+=data->mSE;
      if(data->scrnum>data->scrmax||data->mapnum>data->mapmax||
         map->getTile(data->mapnum-data->mSE)->getXPos()==data->cols-1)
      {
        data->scrnum-=data->sSE;
        data->mapnum-=data->mSE;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(-data->sSE,-data->mSE);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}

      if(data->scrnum%11>9||data->scrnum>142){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum-data->mSE)->setFlags(TILE_UNIT, false);
      }        
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum-data->mSE]--;      
      }
      break;
    }
        
    case (4):               //S
    {
      data->scrnum+=data->sS;data->mapnum+=data->mS;
      if(data->scrnum>data->scrmax||data->mapnum>data->mapmax)
      {
        data->scrnum-=data->sS;
        data->mapnum-=data->mS;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(-data->sS,-data->mS);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}

      if(data->scrnum>142){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum-data->mS)->setFlags(TILE_UNIT, false);
      }         
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum-data->mS]--;      
      }
      break;
    }
           
    case (5):                      //SW
    {
      data->scrnum+=data->sSW;data->mapnum+=data->mSW;
      if(data->scrnum>data->scrmax||data->mapnum>data->mapmax||
         map->getTile(data->mapnum-data->mSW)->getXPos()==0)
      {
        data->scrnum-=data->sSW;
        data->mapnum-=data->mSW;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(-data->sSW,-data->mSW);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}

      if(data->scrnum>142||data->scrnum%11<1){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum-data->mSW)->setFlags(TILE_UNIT, false);
      }        
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum-data->mSW]--;      
      }
      break;
    }
         
    case (6):               //W
    {
      data->scrnum-=data->sW;data->mapnum-=data->mW;
      if(data->mapnum<0||
         map->getTile(data->mapnum+data->mW)->getXPos()==0)
      {
        data->scrnum+=data->sW;
        data->mapnum+=data->mW;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(data->sW,data->mW);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}

      if(data->scrnum%11<1){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum+data->mW)->setFlags(TILE_UNIT, false);
      }        
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum+data->mW]--;      
      }
      break;
    }
      
    case (7):                     //NW
    {
      data->scrnum-=data->sNW;data->mapnum-=data->mNW;
      if(data->mapnum<0||
         map->getTile(data->mapnum+data->mNW)->getXPos()==0)
      {
        data->scrnum+=data->sNW;
        data->mapnum+=data->mNW;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(data->sNW,data->mNW);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}
         
      if(data->scrnum%11<1||data->scrnum<11){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum+data->mNW)->setFlags(TILE_UNIT, false);
      }        
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum+data->mNW]--;      
      }
      break;
    }
      
    case (8):               //N
    {
      data->scrnum-=data->sN;data->mapnum-=data->mN;
      if(data->mapnum<0)
      {
        data->scrnum+=data->sN;
        data->mapnum+=data->mN;
        data->flag|=data->NoMoveFlag;
        break;
      }

      k=LegalTerrainCheck(data->sN,data->mN);
      if(k==1){break;}
      if(k==2){data->flag|=data->VillageFlag;break;}
         
      if(data->scrnum<11){ReCenter();}

      if(data->turn < data->unitList.size())
      {
        map->getTile(data->mapnum)->setFlags(TILE_UNIT, true);
        map->getTile(data->mapnum+data->mN)->setFlags(TILE_UNIT, false);
      }        
      else
      {
        data->nativeOnTile[data->mapnum]++;
        data->nativeOnTile[data->mapnum+data->mN]--;      
      }
      break;
    }
    default: 
      data->flag|=data->NoMoveFlag;
  }
}

/*--------------------------LegalTerrainCheck----------------------*/

short GraphicsEngine::LegalTerrainCheck(const short sdir,const short mdir)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;

    long mapnumold;

/*This function checks to see if the unit can move onto the new tile.
  The scout can not move onto a tile with a village. It can not move 
  onto water unless the ship is in that water square.
  The ship can not move onto land unless it is carrying the scout.
  In which case the scout is off loaded but the ship remains on the 
  ocean tile.*/
  
//native restrictions
  if(data->turn == data->unitList.size())
  {  
    if(map->getTile(data->mapnum)->Is(TILE_WATER) ||
         map->getTile(data->mapnum)->Is(TILE_RUMOR) ||
         map->getTile(data->mapnum)->Is(TILE_PEAK) ||
         FindUnitAt(data->mapnum, false) ||
         map->getTile(data->mapnum)->Is(TILE_BUILD)) 
    {
      data->scrnum+=sdir;
      data->mapnum+=mdir;
      data->flag|=data->NoMoveFlag;
      return 1;
    }
    
    if(map->getTile(data->mapnum)->Is(TILE_FAKE) &&
        (map->getTile(data->mapnum)->Is(TILE_FAKEPEAK) ||
         map->getTile(data->mapnum)->Is(TILE_FAKERUMOR) ||
         map->getTile(data->mapnum)->getFkterrain()== TERRAIN_LAKE))
    {
      data->scrnum+=sdir;
      data->mapnum+=mdir;
      data->flag|=data->NoMoveFlag;
      return 1;    
    }
    return 0;
  }

//if scout tries to move onto water  
  if(map->getTile(data->mapnum)->Is(TILE_WATER) && !(data->unitList[data->turn]->isBoat()))
  {
   Unit *ship = FindUnitAt(data->mapnum, true);
  
//if not ship tile, no move  
    if(!ship || ship->getNation() != data->unitList[data->turn]->getNation())
    {
      data->scrnum+=sdir;
      data->mapnum+=mdir;
      data->flag|=data->NoMoveFlag;
      return 1;
    }
    
//if ship tile, load scout    
    else                                     
    {
      if(!(ship->addPassenger(data->unitList[data->turn])))
      {
          data->scrnum += sdir;
          data->mapnum += mdir;
          data->flag |= data->NoMoveFlag;
          return 1;
      }
      data->unitList[data->turn]->setOnboardFlag(true);
      map->getTile(data->unitList[data->turn]->getTile())->setFlags(TILE_UNIT, false);
      data->unitList[data->turn]->setTile(ship->getTile());
      data->unitList[data->turn]->setStartNumber(ship->getStartNumber());
      //ship->addPassenger(data->unitList[data->turn]); //Already been added. 
      mapnumold = data->mapnum;
      data->mapnum = data->unitList[data->turn]->getTile();
    }
  }

//if the ship tries to move onto a land tile that doesn't have a village or native unit
  if(!(map->getTile(data->mapnum)->Is(TILE_WATER)) && data->unitList[data->turn]->isBoat() &&
       map->getTile(data->mapnum)->getVillages()==0 && data->nativeOnTile[data->mapnum]==0)
       
//if scout not on ship, no move     
  {
    data->scrnum+=sdir;
    data->mapnum+=mdir;
    data->flag|=data->NoMoveFlag;

    //if scout is on ship
    if(data->unitList[data->turn]->getNumberOfPassenger())
    {
      Unit *tmp = FindUnitAt(data->mapnum - mdir, false); //added 26/6
      if(tmp) //can't unload passenger if dest tile is ocuppied by foreign unit
      {
        if(tmp->getNation()!=data->unitList[data->turn]->getNation()) return 1;
      }
      Unit *pass = data->unitList[data->turn]->getPassenger(0);
      map->getTile(data->mapnum - mdir)->setFlags(TILE_UNIT, true);
      data->unitList[data->turn]->removePassenger(0);

      pass->setOnboardFlag(false);
      pass->setTile(data->mapnum - mdir);
      SlideUnit(pass, data->scrnum - sdir, data->scrnum);
      mapnumold = data->mapnum;
      data->mapnum -= mdir;
      Reveal();
      if(map->getTile(data->mapnum)->Is(TILE_RUMOR))
      {
          data->RumorFlag = data->mapnum;
      }
      
      data->mapnum = mapnumold;
      UpdateUnitInfo(data->unitList[data->turn]);
      UpdateScreen0(); //changed by .Net
    }
    return 1;
  }

//if the Scout tries to move onto a village
  if(map->getTile(data->mapnum)->getVillages() > 0 &&
    !(data->unitList[data->turn]->isBoat()))
  {
    data->scrnum+=sdir;
    data->mapnum+=mdir;
    data->flag|=data->NoMoveFlag;
    return 2;
  }

//if the Scout tries to move onto a native unit
  if(data->nativeOnTile[data->mapnum] > 0 && !(data->unitList[data->turn]->isBoat()))
  {
    data->scrnum+=sdir;
    data->mapnum+=mdir;
    data->flag|=data->NoMoveFlag;

    CombatAnalysis(data->unitList[data->turn], NULL);
    data->mf = 0;
    return 1;
  }
  
  Unit *temp;
  if((temp = FindUnitAt(data->mapnum, data->unitList[data->turn]->isBoat())) &&
   (temp->getNation() != data->unitList[data->turn]->getNation()))
  {
    data->scrnum+=sdir;
    data->mapnum+=mdir;
    data->flag|=data->NoMoveFlag;
    
    CombatAnalysis(data->unitList[data->turn], temp);
    data->mf = 0;
    return 1;
  }
  
  if(map->getTile(data->mapnum)->Is(TILE_BUILD) &&
    !(data->unitList[data->turn]->isBoat()))
  {
      Colony *col = FindColonyAt(data->mapnum);
      col->setNation(data->unitList[data->turn]->getNation());
      return 0;
  }

// if the ship tries to move onto a village
  if((map->getTile(data->mapnum)->getVillages() > 0 ||
    data->nativeOnTile[data->mapnum] > 0) && data->unitList[data->turn]->isBoat())
  {
    data->scrnum+=sdir;
    data->mapnum+=mdir;
    data->flag|=data->NoMoveFlag;
    return 1;
  }
  
  return 0;
}


//
// $Id: move.cpp,v 1.14 2004/06/26 15:34:37 sikon Exp $
//
