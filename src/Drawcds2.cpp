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

/*---------------------------FillSlots1-------------------------*/
void GraphicsEngine::FillSlots1(int colnum)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();


    int y,k,i,b[18],a=0,x0=256,y0=34;
    static int btilex[6]={122,727,1,364,1,364};
    static int btiley[6]={1,1,122,122,243,243};
    static int slot0[18][2];
    static int first=0;


//modifed 5/30
//layout is now saved for each colony

/*randomly put buildings in appropriate slots*/

/*set up slot array first time through*/
  if(first==0)
  {
    y=y0;
    for(i=0;i<4;i++)
    {
      slot0[i][0]=x0;
      slot0[i][1]=y;
      slot0[i+4][0]=x0+120;
      slot0[i+4][1]=y;
      slot0[i+8][0]=x0+400;
      slot0[i+8][1]=y;
      y+=120;
    }
    y=y0;
    for(i=12;i<15;i++)
    {
      slot0[i][0]=x0+520;
      slot0[i][1]=y;
      slot0[i+3][0]=x0+640;
      slot0[i+3][1]=y;
      y+=120;
    }
    first=1;
  }
}


/*this is a mini version of the SetTerrain(); functions.
  should be possible use same code with different arguements*/
/*---------------------------DrawCDSFields2----------------------*/
void GraphicsEngine::DrawCDSFields2(long tile)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    Uint8 nt = data->nationTurn;

    long m,n[9][4],r,rblend,bblend,cblend,rii,bii,cii,k,kx,ky;
    int i,x,y,yc,mc,rc,z,zc,x0=20,y0=320;

  m = tile;
  x=0;y=0;yc=0;mc=0;r=m-151;rc=0;z=-151;zc=0;
  for(i=0;i<9;i++)
  {
    n[i][0]=x;x+=75;if(x>150){x=0;}
    n[i][1]=y;yc++;if(yc>2){yc=0;y+=50;}
    n[i][2]=map->getTile(r)->getTerrain();
    n[i][3]=m+z;z++;zc++;
    if(zc>2&&z<-1){zc=0;z=-1;}
    if(zc>2&&z>1){zc=0;z=149;}
    rblend=map->getTile(r+1)->getTerrain();rii=r+1;
    bblend=map->getTile(r+150)->getTerrain();bii=r+150;
    cblend=map->getTile(r+151)->getTerrain();cii=r+151;
    r++;rc++;

    DrawTILE(screen,tilesheet1,x0+n[i][0],y0+n[i][1],75,50,n[i][2],1);
    data->red=0;data->green=255;

/*right blend*/
    if(map->getTile(rii-1)->getXPos()<149)
    {
      if(map->getTile(rii)->getShrdstate(nt)<2&&rc<3)
      {
        DrawTILE(screen,blender,x0+n[i][0]+60,y0+n[i][1],15,50,
                        rblend+60,1);
        if(map->getTile(rii)->getShrdstate(nt)==1)
        {
          if(map->getTile(rii)->Is(TILE_FAKE))
          {
            DrawTILE(screen,blender2,x0+n[i][0]+60,y0+n[i][1],15,50,
                        map->getTile(rii)->getFkterrain()+60,1);
          }
          else
          {
            DrawTILE(screen,blender2,x0+n[i][0]+60,y0+n[i][1],15,50,
                        map->getTile(rii)->getTerrain()+60,1);
          }
        }
      }
      else
      {
        DrawTILE(screen,blender,x0+n[i][0]+60,y0+n[i][1],15,50,
                 data->tilex[11]+60,1);
      }
    }

/*bottom blend*/
    if(map->getTile(bii-150)->getYPos()<199)
    {
      if(map->getTile(bii)->getShrdstate(nt)<2&&i<6)
      {
        DrawTILE(screen,blender,x0+n[i][0],y0+n[i][1]+35,75,15,
                 bblend,data->tiley[1]+35);
        if(map->getTile(bii)->getShrdstate(nt)==1)
        {
          if(map->getTile(bii)->Is(TILE_FAKE))
          {
            DrawTILE(screen,blender2,x0+n[i][0],y0+n[i][1]+35,75,15,
                     map->getTile(bii)->getFkterrain(),data->tiley[1]+35);
          }
          else
          {
            DrawTILE(screen,blender2,x0+n[i][0],y0+n[i][1]+35,75,15,
                     map->getTile(bii)->getTerrain(),data->tiley[1]+35);
          }
        }
      }
      else
      {
        DrawTILE(screen,blender,x0+n[i][0],y0+n[i][1]+35,75,15,
                 data->tilex[11],data->tiley[1]+35);
      }
    }

/*corner blend*/
    if(map->getTile(rii-1)->getXPos()<149&&
       map->getTile(bii-150)->getYPos()<199)
    {
      if(map->getTile(cii)->getShrdstate(nt)<2&&i<6&&rc<3)
      {                                              
        DrawTILE(screen,blender,x0+n[i][0]+60,y0+n[i][1]+35,15,15,
                 cblend+60,data->tiley[2]+35);
        if(map->getTile(cii)->getShrdstate(nt)==1)
        {
          if(map->getTile(cii)->Is(TILE_FAKE))
          {
            DrawTILE(screen,blender2,x0+n[i][0]+60,y0+n[i][1]+35,15,15,
                     map->getTile(cii)->getFkterrain()+60,data->tiley[2]+35);
          }
          else
          {
            DrawTILE(screen,blender2,x0+n[i][0]+60,y0+n[i][1]+35,15,15,
                     map->getTile(cii)->getTerrain()+60,data->tiley[2]+35);
          }
        }
      }
      else
      {
        DrawTILE(screen,blender,x0+n[i][0]+60,y0+n[i][1]+35,15,15,
                 data->tilex[11]+60,data->tiley[2]+35);
      }
    }

    DrawTILE(screen,blender,x0-75+60,y0,15,50,
             map->getTile(m-151)->getTerrain()+60,1);
    DrawTILE(screen,blender,x0-75+60,y0+50,15,50,
             map->getTile(m-1)->getTerrain()+60,1);
    DrawTILE(screen,blender,x0-75+60,y0+100,15,50,
             map->getTile(m+149)->getTerrain()+60,1);

    DrawTILE(screen,blender,x0-75+60,y0+35,15,15,
             map->getTile(m-1)->getTerrain()+60,data->tiley[2]+35);
    DrawTILE(screen,blender,x0-75+60,y0+50+35,15,15,
             map->getTile(m+149)->getTerrain()+60,data->tiley[2]+35);
    DrawTILE(screen,blender,x0-75+60,y0+100+35,15,15,
             data->tilex[11]+60,data->tiley[2]+35);

    DrawTILE(screen,blender,x0,y0-50+35,75,15,
             map->getTile(m-151)->getTerrain(),data->tiley[1]+35);
    DrawTILE(screen,blender,x0+75,y0-50+35,75,15,
             map->getTile(m-150)->getTerrain(),data->tiley[1]+35);
    DrawTILE(screen,blender,x0+150,y0-50+35,75,15,
             map->getTile(m-149)->getTerrain(),data->tiley[1]+35);

    DrawTILE(screen,blender,x0-75+60,y0-50+35,15,15,
             map->getTile(m-151)->getTerrain()+60,data->tiley[2]+35);
    DrawTILE(screen,blender,x0+60,y0-50+35,15,15,
             map->getTile(m-150)->getTerrain()+60,data->tiley[2]+35);
    DrawTILE(screen,blender,x0+75+60,y0-50+35,15,15,
             map->getTile(m-149)->getTerrain()+60,data->tiley[2]+35);
    DrawTILE(screen,blender,x0+150+60,y0-50+35,15,15,
             data->tilex[11]+60,data->tiley[2]+35);
                              
    data->red=255;data->green=0;
    if(rc>2){rc=0;r+=148-1;}
  }

//display terrain tiles and flags of the CDS
    for(i=0;i<9;i++)
    {
        k=n[i][3];
        kx=x0+n[i][0];
        ky=y0+n[i][1];

        if(map->getTile(k)->getShrdstate(nt)==0)
        {
            //plowed
            if(map->getTile(k)->Is(TILE_PLOWED))
            {
                DrawTILE(screen,tilesheet1,kx-3,ky-3,data->tw,data->th,
                         data->tilex[11],data->tiley[0]);
            }

            //forests
            if(map->getTile(k)->Is(TILE_FOREST))
            {
                //draw real Forest with proper links
                Links2(k,TILE_FOREST,n,x0,y0,i);
            }

            //peaks
            if(map->getTile(k)->Is(TILE_PEAK))
            {
                Links2(k,TILE_PEAK,n,x0,y0,i);
            }

            //mountains
            if(map->getTile(k)->Is(TILE_MOUNTAIN))
            {
                 Links2(k,TILE_MOUNTAIN,n,x0,y0,i);
            }

            //hills
            if(map->getTile(k)->Is(TILE_HILL))
            {
                Links2(k,TILE_HILL,n,x0,y0,i);
            }
        }

        if(map->getTile(k)->getShrdstate(nt)==1)
        {
            //fakeforest
            if(map->getTile(k)->Is(TILE_FAKEFOREST))
            {
                //draw fakeforest with proper links
                Links2(k,TILE_FAKEFOREST,n,x0,y0,i);
            }

            //fakepeaks
            if(map->getTile(k)->Is(TILE_FAKEPEAK))
            {
                Links2(k,TILE_FAKEPEAK,n,x0,y0,i);
            }

            //fakemountains
            if(map->getTile(k)->Is(TILE_FAKEMOUNTAIN))
            {
                Links2(k,TILE_FAKEMOUNTAIN,n,x0,y0,i);
            }

            //fakehills
            if(map->getTile(k)->Is(TILE_FAKEHILL))
            {
                Links2(k,TILE_FAKEHILL,n,x0,y0,i);
            }
        }
    }

//rivers
    for(i=0;i<9;i++)
    {
        k=n[i][3];
        kx=x0+n[i][0];
        ky=y0+n[i][1];

        if(map->getTile(k)->getShrdstate(nt)<2)
        {
            if(map->getTile(k)->Is(TILE_RIVER))
            {
                if(map->getTile(k)->hasLink(TILE_RIVER,ANY_DIR)==false)
                {
                    if(map->getTile(k)->getVillages()==0)
                    {
                        DrawRiver(kx,ky,0,k,0);
                    }
                }
                if(map->getTile(k)->hasLink(TILE_RIVER,NE))
                {
                    DrawRiver(kx,ky,1,k,0);
                }
                if(map->getTile(k-149)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,1,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,E))
                {
                    DrawRiver(kx,ky,2,k,0);
                }
                if(map->getTile(k+1)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,2,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,SE))
                {
                    DrawRiver(kx,ky,3,k,0);
                }
                if(map->getTile(k+151)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,3,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,S))
                {
                    DrawRiver(kx,ky,4,k,0);
                }
                if(map->getTile(k+150)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,4,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,SW))
                {
                    DrawRiver(kx,ky,5,k,0);
                }
                if(map->getTile(k+149)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,5,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,W))
                {
                    DrawRiver(kx,ky,6,k,0);
                }
                if(map->getTile(k-1)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,6,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,NW))
                {
                    DrawRiver(kx,ky,7,k,0);
                }
                if(map->getTile(k-151)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,7,k,1);
                }

                if(map->getTile(k)->hasLink(TILE_RIVER,N))
                {
                    DrawRiver(kx,ky,8,k,0);
                }
                if(map->getTile(k-150)->Is(TILE_WATER))
                {
                    DrawRiver(kx,ky,8,k,1);
                }
            }
        }
    }

/*rumors*/
    for(i=0;i<9;i++)
    {
        k=n[i][3];
        kx=x0+n[i][0];
        ky=y0+n[i][1];

        if(map->getTile(k)->Is(TILE_RUMOR)&&
           map->getTile(k)->getShrdstate(nt)==0)
        {
            DrawTILE(screen,tilesheet1,kx-3,ky-2,data->tw,data->th,
                     TERRAIN_RUMOR,data->tiley[1]);
        }

        if(map->getTile(k)->getShrdstate(nt)==1)
        {
            if(map->getTile(k)->Is(TILE_RUMOR))
            {
                if(map->getTile(k)->Is(TILE_FAKE))
                {
                    if(map->getTile(k)->Is(TILE_FAKERUMOR))
                    {
                        DrawTILE(screen,tilesheet1,kx-3,ky-2,data->tw,data->th,
                                 TERRAIN_RUMOR,data->tiley[1]);
                        DrawTILE(screen,mask1,kx-3,ky-2,data->tw,data->th,
                                 TERRAIN_RUMOR,data->tiley[1]);
                    }
                }
                else
                {
                    DrawTILE(screen,tilesheet1,kx-3,ky-2,data->tw,data->th,
                             TERRAIN_RUMOR,data->tiley[1]);
                    DrawTILE(screen,mask1,kx-3,ky-2,data->tw,data->th,
                             TERRAIN_RUMOR,data->tiley[1]);
                }
            }
        }
    }

/*roads*/
    for(i=0;i<9;i++)
    {
        k=n[i][3];
        kx=x0+n[i][0];
        ky=y0+n[i][1];

        if(map->getTile(k)->getShrdstate(nt)<2)
        {
            if(map->getTile(k)->Is(TILE_ROAD))
            {
                if(map->getTile(k)->hasLink(TILE_ROAD,ANY_DIR)==false)
                {
                    if(map->getTile(k)->getVillages()==0)
                    {
                        DrawRoad2(kx,ky,0,k);
                    }
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,NE))
                {
                    DrawRoad2(kx,ky,1,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,E))
                {
                    DrawRoad2(kx,ky,2,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,SE))
                {
                    DrawRoad2(kx,ky,3,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,S))
                {
                    DrawRoad2(kx,ky,4,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,SW))
                {
                    DrawRoad2(kx,ky,5,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,W))
                {
                    DrawRoad2(kx,ky,6,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,NW))
                {
                    DrawRoad2(kx,ky,7,k);
                }
                if(map->getTile(k)->hasLink(TILE_ROAD,N))
                {
                    DrawRoad2(kx,ky,8,k);
                }
            }
        }
    }

/*colonies & villages*/
    for(i=0;i<9;i++)
    {
        k=n[i][3];
        kx=x0+n[i][0];
        ky=y0+n[i][1];

        if(map->getTile(k)->getShrdstate(nt)<2)
        {            
            if(map->getTile(k)->Is(TILE_BUILD))
            {
                DrawTILE(screen,tilesheet1,kx-3,ky-6,data->tw,data->th,data->tilex[8],
                         data->tiley[1]);
            }

            if(map->getTile(k)->getVillages()>0&&
              (!(map->getTile(k)->Is(TILE_FAKE))))
            {
                DrawTILE(screen,tilesheet1,kx,ky-2,data->tw,data->th,
                         data->tilex[map->getTile(k)->getVillages()-1],data->tiley[2]);

                if(map->getTile(k)->getShrdstate(nt)==1)
                {
                    DrawTILE(screen,mask1,kx,ky-2,data->tw,data->th,
                             data->tilex[map->getTile(k)->getVillages()-1],
                             data->tiley[2]);
                }
            }
        }
    }
}

/*--------------------------Links2-------------------------------*/
//void GraphicsEngine::Links2(long ii,int e,long n[][4],int x0,int y0,int i)
void GraphicsEngine::Links2(long ii,enum tileTypes e,long n[][4],int x0,int y0,int i)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    Uint8 nt = data->nationTurn;

    int xx=0,yy=0;
    int xpos = map->getTile(ii)->getXPos();
    int ypos = map->getTile(ii)->getYPos();
    
    if(e!=TILE_ROAD && e!=TILE_RIVER) //calculate tile icon
    {
        if(map->getTileAt(xpos+1,ypos)->getShrdstate(nt)==1)
        {
            if(map->getTileAt(xpos+1,ypos)->Is(TILE_FAKE))
            {
                if(map->getTile(ii)->hasFakeLink(e,E)) xx+=BIT1;
            }
            else if(map->getTile(ii)->hasRealLink(e,E)) xx+=BIT1;
        }
        else if(map->getTileAt(xpos+1,ypos)->getShrdstate(nt)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,E)) xx+=BIT1;
        }

        if(map->getTileAt(xpos,ypos+1)->getShrdstate(nt)==1)
        {
            if(map->getTileAt(xpos,ypos+1)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,S)) xx+=BIT2;
            }
            else if(map->getTile(ii)->hasRealLink(e,S)) xx+=BIT2;
        }
        else if(map->getTileAt(xpos,ypos+1)->getShrdstate(nt)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,S)) xx+=BIT2;
        }

        if(map->getTileAt(xpos-1,ypos)->getShrdstate(nt)==1)
        {
            if(map->getTileAt(xpos-1,ypos)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,W)) xx+=BIT3;
            }
            else if(map->getTile(ii)->hasRealLink(e,W)) xx+=BIT3;
        }
        else if(map->getTileAt(xpos-1,ypos)->getShrdstate(nt)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,W)) xx+=BIT3;
        }

        if(map->getTileAt(xpos,ypos-1)->getShrdstate(nt)==1)
        {
            if(map->getTileAt(xpos,ypos-1)->Is(TILE_FAKE))
            {
                 if(map->getTile(ii)->hasFakeLink(e,N)) xx+=BIT4;
            }
            else if(map->getTile(ii)->hasRealLink(e,N)) xx+=BIT4;
        }
        else if(map->getTileAt(xpos,ypos-1)->getShrdstate(nt)==0)
        {
            if(map->getTile(ii)->hasRealLink(e,N)) xx+=BIT4;
        }

        switch (xx)
        {
        case 0 : xx=0 ;break;  //none
        case 1 : xx=1 ;break;  //e
        case 2 : xx=2 ;break;  //s
        case 4 : xx=3 ;break;  //w
        case 8 : xx=4 ;break;  //n
        case 3 : xx=5 ;break;  //e+s
        case 5 : xx=6 ;break;  //e+w
        case 9 : xx=7 ;break;  //e+n
        case 6 : xx=8 ;break;  //s+w
        case 10: xx=9 ;break;  //s+n
        case 12: xx=10;break;  //w+n
        case 11: xx=11;break;  //e+s+n
        case 14: xx=12;break;  //w+s+n
        case 7 : xx=13;break;  //e+s+w
        case 13: xx=14;break;  //e+n+w
        default: break;        //e+s+w+n
        }
    }

    switch(e)
    {
    case TILE_FOREST: case TILE_FAKEFOREST:
        {
            switch(map->getTile(ii)->getTerrain())
            {
                case TERRAIN_OPENS:    case TERRAIN_STEPPE: yy=1; break;
                case TERRAIN_SAVANNAH: case TERRAIN_PRAIRIE: yy=2; break;
                case TERRAIN_DESERT:   case TERRAIN_CHAPARRAL: yy=3; break;
                default: yy=0; break;
            }

            //actually draw the tile
            DrawTILE(screen,tilesheetF,x0+n[i][0]-6,y0+n[i][1]-15-6,
                     data->tw,65,data->tilex[xx],data->tiley2[yy]);
            if(map->getTile(ii)->Is(TILE_RAIN))
            {
                DrawTILE(screen,tilesheet1,x0+n[i][0]-6,y0+n[i][1]-6,
                         data->tw,data->th,data->tilex[11],data->tiley[1]);
            }
            if(e==TILE_FAKEFOREST)
            {
                DrawTILE(screen,forestmask,x0+n[i][0]-6,y0+n[i][1]-15-6,
                         data->tw,65,data->tilex[xx],data->tiley2[yy]);
                if(map->getTile(ii)->Is(TILE_RAIN))
                {
                    DrawTILE(screen,mask1,x0+n[i][0]-6,y0+n[i][1]-6,
                             data->tw,data->th,data->tilex[11],data->tiley[1]);
                }
            }
            break;
        }

    case TILE_HILL: case TILE_FAKEHILL:
        DrawTILE(screen,tilesheetM,x0+n[i][0]-3,y0+n[i][1]-15-3,
                 data->tw,65,data->tilex[xx],data->tiley2[0]);
        if(e==TILE_FAKEHILL)
        {
            DrawTILE(screen,Mmask,x0+n[i][0]-3,y0+n[i][1]-15-3,
                     data->tw,65,data->tilex[xx],data->tiley2[0]);
        }
        break;

    case TILE_MOUNTAIN: case TILE_FAKEMOUNTAIN:
        DrawTILE(screen,tilesheetM,x0+n[i][0]-3,y0+n[i][1]-15-3,
                 data->tw,65,data->tilex[xx],data->tiley2[1]);
        if(e==TILE_FAKEMOUNTAIN)
        {
            DrawTILE(screen,Mmask,x0+n[i][0]-3,y0+n[i][1]-15-3,
                     data->tw,65,data->tilex[xx],data->tiley2[1]);
        }
        break;
    
    case TILE_PEAK: case TILE_FAKEPEAK:
        DrawTILE(screen,tilesheetM,x0+n[i][0]-3,y0+n[i][1]-15-3,
                 data->tw,65,data->tilex[xx],data->tiley2[2]);
        if(e==TILE_FAKEPEAK)
        {
            DrawTILE(screen,Mmask,x0+n[i][0]-3,y0+n[i][1]-15-3,
                     data->tw,65,data->tilex[xx],data->tiley2[2]);
        }
        break;

    default: break;
    }
}

/*--------------------------DrawRoad2----------------------------*/
void GraphicsEngine::DrawRoad2(long kx,long ky,int x,long num)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    Uint8 nt = data->nationTurn;

    if(!(map->getTile(num)->Is(TILE_FAKE)))
    {
        DrawTILE(screen,tilesheet1,kx-6,ky-6,data->tw,data->th,data->tilex[x],
                 data->tiley[3]);
        if(map->getTile(num)->getShrdstate(nt)==1)
        {
            DrawTILE(screen,mask1,kx-6,ky-6,data->tw,data->th,data->tilex[x],
                     data->tiley[3]);
        }
    }
}

/*--------------------------DrawRiver----------------------------*/
void GraphicsEngine::DrawRiver(long kx,long ky,int x,long num, int mouth)
{
    GlobalData* data = m_pGame->GetData();
    Map* map = m_pGame->GetMap();
    Uint8 nt = data->nationTurn;

    if(!(map->getTile(num)->Is(TILE_FAKE)))
    {
        DrawTILE(screen,tilesheetR3,kx-6,ky-6,data->tw,data->th,data->tilex[x],
                 data->tiley[mouth]);
        if(map->getTile(num)->getShrdstate(nt)==1)
        {
            DrawTILE(screen,R3mask,kx-6,ky-6,data->tw,data->th,data->tilex[x],
                     data->tiley[mouth]);
        }
    }
}

//
// $Id: Drawcds2.cpp,v 1.10 2004/06/23 15:37:05 sikon Exp $
//

