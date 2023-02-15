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

/*---------------------------HCSMouseCheck-----------------------*/
int GraphicsEngine::HCSMouseCheck(int xM,int yM,char RFlag)
{
    GlobalData* data = _GlobalData;

int x,y,x1,x0=640,y0=244,i,/*dx,*/y1,w,/*ii,xx,*/cost,/*swidth,*/k,bckgds[2],
    xMold=0,yMold=0,SSCa;
static char NewUnits[100],NUIndex=0,Dstart=0,
            Ships1[100],Ships1Index=0,IPstart=0,
            SailedShips1[100],SailedShips1Index=0,Sailedstart=0;
static short IPshipnum[100],SSshipnum[100];
char yes=1,no=0,start;
short n,drag=0,tonsold;
int SSx=410,SSy=535,SSxx,SSCx=410,SSCy=604;//,SSCxx;
SDL_Surface *bckgoods;

n=IPshipnum[IPstart];

/*market*/
x=166;y=676;
  if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
  {
    HCSArrowButtons(x,y,0,0,17,55,799,89,4,20,7,13,67,132);
    UpdateScreen1(x,y,17,55);
    SDL_Delay(100);
    HCSArrowButtons(x,y,0,0,17,55,781,89,5,21,7,13,67,132);
    UpdateScreen1(x,y,17,55);
  }
  if(xM>x+674&&xM<x+674+17&&yM>y&&yM<y+55)
  {
    HCSArrowButtons(x,y,674,0,17,55,799,89,674+5,20,7,13,75,132);
    UpdateScreen1(x+674,y,17,55);
    SDL_Delay(100);
    HCSArrowButtons(x,y,674,0,17,55,781,89,674+6,21,7,13,75,132);
    UpdateScreen1(x+674,y,17,55);
  }

/*selected ship pass. left arrow*/  
x=392;y=478+57;
  if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
  {
    if(data->units_ships[n].passengernum>0&&Ships1Index>0)
    {  
      HCSArrowButtons(x,y,0,0,17,55,799,89,4,20,7,13,67,132);
      UpdateScreen1(x,y,17,55);
    
      while(xM>x&&xM<x+17&&yM>y&&yM<y+55)
      {        
        data->SSstart[n]--;
        if(data->SSstart[n]<0){data->SSstart[n]=0;}
        SelectedShipPassengers(n,data->SSstart[n]);
        SDL_Delay(250);    
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }    
      HCSArrowButtons(x,y,0,0,17,55,781,89,5,21,7,13,67,132);
      UpdateScreen1(x,y,17,55);
    }
  }

/*selected ship pass right arrow*/  
x+=223;
  if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
  {
    if(data->units_ships[n].passengernum!=0&&Ships1Index>0)
    {
      HCSArrowButtons(x,y,0,0,17,55,799,89,5,20,7,13,75,132);
      UpdateScreen1(x,y,17,55);
    
      while(xM>x&&xM<x+17&&yM>y&&yM<y+55)
      {        
        data->SSstart[n]++;SSxx=SSx;
        if(data->SSstart[n]>data->units_ships[n].passengernum-1)
        {data->SSstart[n]=data->units_ships[n].passengernum-1;}
        SelectedShipPassengers(n,data->SSstart[n]);    
        SDL_Delay(250);        
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }
      HCSArrowButtons(x,y,0,0,17,55,781,89,6,21,7,13,75,132);
      UpdateScreen1(x,y,17,55);
    }
  }

/*selected ship cargo left arrow*/  
x=392;y=478+70+56;
  if(xM>x&&xM<x+17&&yM>y&&yM<y+55&&Ships1Index>0)
  {
    HCSArrowButtons(x,y,0,0,17,55,799,89,4,20,7,13,67,132);
    UpdateScreen1(x,y,17,55);
    
    while(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {        
      data->SSCstart[n]--;
      if(data->SSCstart[n]<0)
      {data->SSCstart[n]=0;}
      SelectedShipCargo(n,data->SSCstart[n],data->SSCstart[n]);
      SDL_Delay(250);        
      if(CheckMouseButton()){break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    
    HCSArrowButtons(x,y,0,0,17,55,781,89,5,21,7,13,67,132);
    UpdateScreen1(x,y,17,55);
  }

/*selected ship cargo right arrow*/   
  x+=223;
  if(xM>x&&xM<x+17&&yM>y&&yM<y+55&&Ships1Index>0)
  {
    HCSArrowButtons(x,y,0,0,17,55,799,89,5,20,7,13,75,132);
    UpdateScreen1(x,y,17,55);
    
    while(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {        
      data->SSCstart[n]++;
      if(data->SSCstart[n]>data->units_ships[n].cargonum-1)
      {data->SSCstart[n]=data->units_ships[n].cargonum-1;}
      SelectedShipCargo(n,data->SSCstart[n],data->SSCstart[n]);
      SDL_Delay(250);        
      if(CheckMouseButton()){break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    
    HCSArrowButtons(x,y,0,0,17,55,781,89,6,21,7,13,75,132);
    UpdateScreen1(x,y,17,55);
  }
  
/*  P/T left arrow*/
  if(xM>x0+3&&xM<x0+3+52&&yM>y0+91&&yM<y0+91+17&&data->HCSradio1>0)
  {
    HCSArrowButtons(x0,y0,3,91,52,17,116,96,19,96,14,7,37,136);
    
    while(xM>x0+3&&xM<x0+3+52&&yM>y0+91&&yM<y0+91+17)
    {    
      if(data->HCSradio1==1)
      {
        PTArrowShift(data->Pstart,data->pHL,1,2,data->Buy,data->BuyCost,0,x0,y0,
                     229,88,0,-1,0);
      }
      else
      {
        PTArrowShift(data->Tstart,data->tHL,2,3,data->Jobs,data->JobsCost,1,
                     x0,y0,229,88,1,-1,0);
      }
      SDL_Delay(250);        
      if(CheckMouseButton()){break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    HCSArrowButtons(x0,y0,3,91,52,17,63,96,20,97,14,7,37,136);
    return 0;
  }

/*  P/T right arrow*/
  if(xM>x0+3+177&&xM<x0+3+52+177&&yM>y0+91&&yM<y0+91+17&&
      data->HCSradio1>0)
  {
    HCSArrowButtons(x0,y0,180,91,52,17,116,96,200,96,14,7,52,136);
    
    while(xM>x0+3+177&&xM<x0+3+52+177&&yM>y0+91&&yM<y0+91+17)
    {        
      if(data->HCSradio1==1)
      {
        PTArrowShift(data->Pstart,data->pHL,1,2,data->Buy,data->BuyCost,0,
                     x0,y0,229,88,3,1,2);
      }
      else
      {
        PTArrowShift(data->Tstart,data->tHL,2,3,data->Jobs,data->JobsCost,1,
                     x0,y0,229,88,15,1,2);
      }
      SDL_Delay(250);            
      if(CheckMouseButton()){break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    HCSArrowButtons(x0,y0,180,91,52,17,63,96,201,97,14,7,52,136);
    return 0;
  }

/*  P/T buy/hire button*/  
  if(xM>x0+3+52&&xM<x0+3+52+125&&yM>y0+91&&yM<y0+91+17&&
      data->HCSradio1>0)
  {
    if(data->HCSradio1==1)
    {
      i=21;
      if(data->Pstart+data->pHL==0)
      {
        NewUnits[NUIndex]=36;
        cost=atoi(data->BuyCost[0]);
        SubtractGold(cost);
        cost+=100;
        sprintf(data->BuyCost[0],"%d",cost);

        HCSDNewUnitHL(data->pHL,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
        DrawSURF(screen,HCSWin[2],x0,y0);
        UpdateScreen1(x0,y0,229,138);
        
        NUIndex++;
        if(NUIndex>99){NUIndex=99;}
          
x=643;y1=368;
        BuyHireButton(NUIndex,Dstart,NewUnits,x,y1+17,screen,n);
      }
      else
      {
        Ships1[Ships1Index]=data->Pstart+data->pHL+36;

        data->shipnum++;
        data->shiptypenum[data->Pstart+data->pHL]++;
        data->DefaultShipName(data->shiptypenum[data->Pstart+data->pHL],data->Buy,
                        data->Pstart+data->pHL);
        strcpy(data->units_ships[data->shipnum].type,data->Buy[data->Pstart+data->pHL]);
        data->units_ships[data->shipnum].typenum=data->Pstart+data->pHL;

        data->ShipCharacteristics(data->units_ships[data->shipnum].typenum);
        IPshipnum[Ships1Index]=data->shipnum;
        Ships1Index++;
        if(Ships1Index>99){Ships1Index=99;}   
    
        cost=atoi(data->BuyCost[data->Pstart+data->pHL]);
        SubtractGold(cost);
        
        x=398;y1=368;
        BuyHireButton(Ships1Index,IPstart,Ships1,x,y1+17,screen,n);
        SelectedShipName(IPshipnum[IPstart],yes);
      }
    }
    else
    {
      i=22;
      NewUnits[NUIndex]=data->Tstart+data->tHL;
    
      if(NewUnits[NUIndex]==17)
      {
        k=rand()%7;
        if(k==4){NewUnits[NUIndex]=18;}
      }
    
      cost=atoi(data->JobsCost[data->Tstart+data->tHL]);
      SubtractGold(cost);
      
      NUIndex++;
      if(NUIndex>99){NUIndex=99;}
    
      x=643;y1=368;
      BuyHireButton(NUIndex,Dstart,NewUnits,x,y1+17,screen,n);
    }
    Buttons4(data->SoLfont1[1],x0+3+52,4,y0+91,4,i,547,52,421,125,17);
    return 0;
  }

/* recruit sign up button*/  
  if(xM>x0+3&&xM<x0+3+229&&yM>y0+91&&yM<y0+91+17&&
      data->HCSradio1==0)
  {
    if(RFlag==0){NewUnits[NUIndex]=data->recruit[data->rHL];}
    else{NewUnits[NUIndex]=data->recruit[0];}
  
    if(NewUnits[NUIndex]==17)
    {
      k=rand()%7;
      if(k==4){NewUnits[NUIndex]=18;}
    }

    NUIndex++;
    if(NUIndex>99){NUIndex=99;}

    x=643;y1=368;
    if(RFlag==0)
    {BuyHireButton(NUIndex,Dstart,NewUnits,x,y1+17,screen,n);}
    else{BuyHireButton(NUIndex,Dstart,NewUnits,x,y1+17,hcs1,n);}
  
    if(data->rHL==2&&RFlag==0){data->recruit[2]=RecruitSelection1();}
    if(data->rHL==1&&RFlag==0)
    {data->recruit[1]=data->recruit[2];data->recruit[2]=RecruitSelection1();}
    if(data->rHL==0||RFlag==1)
    {
      data->recruit[0]=data->recruit[1];
      data->recruit[1]=data->recruit[2];
      data->recruit[2]=RecruitSelection1();
    }

    if(RFlag==0){SubtractGold(data->recruitcost);}
    data->recruitcost=(rand()%25)+data->turnnum+data->recruitcostold;
    data->recruitcostold=data->recruitcost;

    HCSDRecruitHL(data->rHL);
  
    if(RFlag==0)
    {  
      DrawSURF(screen,HCSWin[1],x0,y0);
      UpdateScreen1(x0,y0,232,91);
      Buttons4(data->SoLfont1[1],x0+3,4,y0+91,4,23,557,71,327,229,17);
    }
    else{DrawSURF(hcs1,HCSWin[1],x0,y0);}

    return 0;
  }

/*  R/P/T radio buttons*/
x0=640;y0=224;
  if(xM>x0+3&&xM<x0+3+76&&yM>y0&&yM<y0+18)
  {data->HCSradio1=0;HCSRadioButtons1();data->HLCheckOld[0]=-1;return 0;}
  if(xM>x0+3+76&&xM<x0+3+152&&yM>y0&&yM<y0+18)
  {data->HCSradio1=1;HCSRadioButtons1();data->HLCheckOld[1]=-1;return 0;}
  if(xM>x0+3+152&&xM<x0+3+228&&yM>y0&&yM<y0+18)
  {data->HCSradio1=2;HCSRadioButtons1();data->HLCheckOld[2]=-1;data->tHL=0;return 0;}

/*  Port left arrow*/
x=398;y1=368+17;
  if(xM>x&&xM<x+52&&yM>y1+60&&yM<y1+60+17)
  {    
    
    if(Ships1Index>0)
    {
      HCSArrowButtons(x,y1,0,60,52,17,116,96,16,65,14,7,37,136);
    
      while(xM>x&&xM<x+52&&yM>y1+60&&yM<y1+60+17)
      {        
        IPstart--;
        if(IPstart<0){IPstart=0;}
        data->SSstart[IPshipnum[IPstart]]=0;
        data->SSCstart[IPshipnum[IPstart]]=0;
        SelectedShipName(IPshipnum[IPstart],yes);
        SelectedShipPassengers(IPshipnum[IPstart],0);
        SelectedShipCargo(IPshipnum[IPstart],0,0);
        ShipsInPortDisplay(x,y1,IPstart,Ships1Index,Ships1,
                                IPshipnum);
        SDL_Delay(250);
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);    
      }
      HCSArrowButtons(x,y1,0,60,52,17,63,96,17,66,14,7,37,136);
      return 0;    
    }    
  }

/*  Port set sail button*/  
  if(xM>x+52&&xM<x+52+125&&yM>y1+60&&yM<y1+60+17)
  {  
    if(Ships1Index>0)
    {  
      SailedShips1[SailedShips1Index]=Ships1[IPstart];
      SSshipnum[SailedShips1Index]=IPshipnum[IPstart];
      SailedShips1Index++;
      if(SailedShips1Index>99){SailedShips1Index=99;}     
                  
x=153;y1=368;
      if(SailedShips1Index>3){Sailedstart=SailedShips1Index-3;}  
      ShipsInPortDisplay(x,y1+17,Sailedstart,SailedShips1Index,
                SailedShips1,SSshipnum);

x=398;y1=368+17;  
      for(i=IPstart;i<Ships1Index-1;i++)
      {
        Ships1[i]=Ships1[i+1];
        IPshipnum[i]=IPshipnum[i+1];
      }
      Ships1Index--;
      if(IPstart>=Ships1Index){IPstart--;if(IPstart<0){IPstart=0;}}
      ShipsInPortDisplay(x,y1,IPstart,Ships1Index,Ships1,
                              IPshipnum);    
    
      if(Ships1Index>0)
      {
        data->SSstart[IPshipnum[IPstart]]=0;
        data->SSCstart[IPshipnum[IPstart]]=0;
        SelectedShipName(IPshipnum[IPstart],yes);
        SelectedShipPassengers(IPshipnum[IPstart],0);
        SelectedShipCargo(IPshipnum[IPstart],0,0);    
      }
      else
      {
        SelectedShipName(IPshipnum[IPstart],no);
        FillRect(screen,SSx,SSy,193,55,16,80,32);
        FillRect(screen,SSx,SSy+69,203,55,64,64,64);
        UpdateScreen1(SSx,SSy,204,125);
        DrawTILE(hcs1,screen,SSx,SSy,204,125,SSx,SSy);
      }        
      Buttons4(data->SoLfont1[1],x+52,5,y1+60,4,24,547,52,421,125,17);
    }
    return 0;  
  }

/*  Port right arrow*/  
  if(xM>x+177&&xM<x+177+52&&yM>y1+60&&yM<y1+60+17)
  {
x=398;y1=368+17;    
    if(Ships1Index!=0)
    {
      HCSArrowButtons(x,y1,177,60,52,17,116,96,197,65,14,7,52,136);
    
      while(xM>x+177&&xM<x+177+52&&yM>y1+60&&yM<y1+60+17)
      {        
        IPstart++;
        if(IPstart>Ships1Index-1){IPstart=Ships1Index-1;}
        data->SSstart[IPshipnum[IPstart]]=0;
        data->SSCstart[IPshipnum[IPstart]]=0;
        SelectedShipName(IPshipnum[IPstart],yes);
        SelectedShipPassengers(IPshipnum[IPstart],0);
        SelectedShipCargo(IPshipnum[IPstart],0,0);
        ShipsInPortDisplay(x,y1,IPstart,Ships1Index,Ships1,
                IPshipnum);    
        SDL_Delay(250);    
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);    
      }
      HCSArrowButtons(x,y1,177,60,52,17,63,96,198,66,14,7,52,136);
    }
    return 0;
  }

/*  Docks left arrow*/  
x=643;y1=368+17;
  if(xM>x&&xM<x+52&&yM>y1+60&&yM<y1+60+17)
  {        
    if(NUIndex>0)
    {
      HCSArrowButtons(x,y1,0,60,52,17,116,96,16,65,14,7,37,136);  
        
      while(xM>x&&xM<x+52&&yM>y1+60&&yM<y1+60+17)
      {        
        Dstart--;
        if(Dstart<0){Dstart=0;}
        DocksWaitingDisplay(x,y1,Dstart,NUIndex,NewUnits);
        SDL_Delay(250);
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }
      HCSArrowButtons(x,y1,0,60,52,17,63,96,17,66,14,7,37,136);    
    }
    return 0;
  }

/*  Docks auto button*/  
  if(xM>x+52&&xM<x+52+63&&yM>y1+60&&yM<y1+60+17)
  {Buttons4(data->SoLfont1[1],x+52,5,y1+60,4,25,129,114,65,63,17);return 0;}

/*  Dock board button*/  
  if(xM>x+52+63&&xM<x+52+63+63&&yM>y1+60&&yM<y1+60+17)
  {  
    if(NUIndex>0&&Ships1Index>0)
    {
      Buttons4(data->SoLfont1[1],x+52+63,5,y1+60,4,26,129,114,65,63,17);

      if(((data->units_ships[n].passengernum*100)+
            data->units_ships[n].cargototal)<=data->units_ships[n].capacity-100)
      {
        data->units_ships[n].passengernum++;
        SelectedShipName(n,yes);
        data->units_ships[n].passenger[data->units_ships[n].passengernum-1]=
                    NewUnits[Dstart];
        SelectedShipPassengers(IPshipnum[IPstart],data->SSstart[n]);
   
        for(i=Dstart;i<NUIndex-1;i++){NewUnits[i]=NewUnits[i+1];}
        NUIndex--;
        if(Dstart>=NUIndex){Dstart--;if(Dstart<0){Dstart=0;}}
        DocksWaitingDisplay(x,y1,Dstart,NUIndex,NewUnits);    
      }
      else{MessageWindow(3);}
    }
    return 0;  
  }

/*  Dock right arrow*/  
  if(xM>x+178&&xM<x+178+52&&yM>y1+60&&yM<y1+60+17)
  {    
    if(NUIndex>0)
    {
      HCSArrowButtons(x,y1,178,60,52,17,116,96,198,65,14,7,52,136);
    
      while(xM>x+178&&xM<x+178+52&&yM>y1+60&&yM<y1+60+17)
      {        
        Dstart++;
        if(Dstart>NUIndex-1){Dstart=NUIndex-1;}
        DocksWaitingDisplay(x,y1,Dstart,NUIndex,NewUnits);
        SDL_Delay(250);
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }    
      HCSArrowButtons(x,y1,178,60,52,17,63,96,199,66,14,7,52,136);
    }
    return 0;
  }
  
/*  Sailed left arrow*/
x=153;y1=368;
  if(xM>x&&xM<x+52&&yM>y1&&yM<y1+17)
  {        
    if(SailedShips1Index>0)
    {
      HCSArrowButtons(x,y1,0,0,52,17,116,96,16,5,14,7,37,136);
    
      while(xM>x&&xM<x+52&&yM>y1&&yM<y1+17)
      {        
        Sailedstart--;
        if(Sailedstart<0){Sailedstart=0;}
        ShipsInPortDisplay(x,y1+17,Sailedstart,SailedShips1Index,
                SailedShips1,SSshipnum);
        SDL_Delay(250);    
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }
      HCSArrowButtons(x,y1,0,0,52,17,63,96,17,6,14,7,37,136);
      return 0;    
    }    
  }  

/*  Sailed right arrow*/  
  if(xM>x+177&&xM<x+177+52&&yM>y1&&yM<y1+17)
  {    
    if(SailedShips1Index!=0)
    {
      HCSArrowButtons(x,y1,177,0,52,17,116,96,197,5,14,7,52,136);
    
      while(xM>x+177&&xM<x+177+52&&yM>y1&&yM<y1+17)
      {        
        Sailedstart++;
        if(Sailedstart>SailedShips1Index-1)
        {Sailedstart=SailedShips1Index-1;}
        ShipsInPortDisplay(x,y1+17,Sailedstart,SailedShips1Index,
                SailedShips1,SSshipnum);        
        SDL_Delay(250);        
        if(CheckMouseButton()){break;} 
        SDL_GetMouseState(&xM,&yM);
      }
      HCSArrowButtons(x,y1,177,0,52,17,63,96,198,6,14,7,52,136);   
    }
    return 0;
  }
  
/*counter*/
x=648;y=544;
  if(xM>x+4&&xM<x+4+13&&yM>y+5&&yM<y+5+13)
  {
    Counter2(1,data->counterspace,x,y);
    data->tons=50;data->counterbutton=1;
  }
  if(xM>x+4&&xM<x+4+13&&yM>y+23&&yM<y+23+13)
  {
    Counter2(2,data->counterspace,x,y);
    data->tons=100;data->counterbutton=2;
  }
  if(xM>x+4&&xM<x+4+13&&yM>y+44&&yM<y+44+13)
  {
    Counter2(3,data->counterspace,x,y);
    data->tons=-1;data->counterbutton=3;
  }
  if(xM>x+4&&xM<x+4+13&&yM>y+59&&yM<y+59+13)
  {
    Counter2(4,data->counterspace,x,y);
    data->tons=data->counter;data->counterbutton=4;
  }
  
  if(xM>x+46&&xM<x+46+12&&yM>y+80&&yM<y+80+12&&data->counterbutton==4)
  {
    HCSArrowButtons(x,y,46,80,12,12,50,109,46,80,12,12,37,96);
    
    while(xM>x+46&&xM<x+46+12&&yM>y+80&&yM<y+80+12)
    {        
      data->counter++;
      if(data->counter>999){data->counter=999;}
      data->counterspace=Counter3();
      Counter4(x,y,data->counterspace);       
      if(CheckMouseButton()){data->tons=data->counter;break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    HCSArrowButtons(x,y,46,80,12,12,37,109,47,81,12,12,37,96);
  }
  
  if(xM>x+46&&xM<x+46+12&&yM>y+92&&yM<y+92+12&&data->counterbutton==4)
  {
    HCSArrowButtons(x,y,46,92,12,12,50,109,46,92,12,12,50,96);
    
    while(xM>x+46&&xM<x+46+12&&yM>y+92&&yM<y+92+12)
    {
      data->counter--;
      if(data->counter<1){data->counter=1;}
      data->counterspace=Counter3();
      Counter4(x,y,data->counterspace);
      if(CheckMouseButton()){data->tons=data->counter;break;} 
      SDL_GetMouseState(&xM,&yM);
    }
    HCSArrowButtons(x,y,46,92,12,12,37,109,47,93,12,12,50,96);
  }

/*load cargo*/
x0=166;y=676;  
  if(yM>y&&yM<y+53)
  {
    x1=1;
    for(x=x0+18;x<x0+674;x+=41)
    {
      if(xM>x&&xM<x+40)
      {
        bckgoods=CreateSurface(screen,40,50);
        bckgds[0]=xM-20;bckgds[1]=yM-26;
        DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
        SDL_ShowCursor(0);

        while(!drag)
        {
          if(yM < 27) yM = 27;
          if(xM!=xMold||yM!=yMold)
          {  
            DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
            UpdateScreen1(bckgds[0],bckgds[1],40,50);
            bckgds[0]=xM-20;bckgds[1]=yM-26;

            DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
            DrawTILE(screen,extra1,xM-20,yM-26,40,50,x1+5,1);
  
            UpdateScreen1(xM-20,yM-26,40,50);  
            xMold=xM;yMold=yM;
          }  
          drag=CheckMouseButton();
          if(drag)
          {
            DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
            UpdateScreen1(bckgds[0],bckgds[1],40,50);
  
            if(xM>SSCx&&xM<SSCx+204&&yM>SSCy&&yM<SSCy+55&&
                        Ships1Index>0)
            {
              tonsold=data->tons;
              if(data->tons==-1){data->tons=100;}
              if(((data->units_ships[n].passengernum*100)+
                      data->units_ships[n].cargototal)<=
                      data->units_ships[n].capacity-data->tons)
              {
                data->units_ships[n].cargototal+=data->tons;
                for(i=0;i<20;i++)
                {
                  if(data->units_ships[n].cargo[i][0]==x1||
                                      data->units_ships[n].cargo[i][0]==0)
                  {
                    if(data->units_ships[n].cargo[i][0]==0)
                    {data->units_ships[n].cargonum++;}
                    
                    data->units_ships[n].cargo[i][0]=x1;
                    data->units_ships[n].cargo[i][1]+=data->tons;
                    SSCa=i;
                    break;
                  }
                }
          
                if(SSCa<5){data->SSCstart[n]=0;}else{data->SSCstart[n]=SSCa-4;}
                SelectedShipName(n,yes);
                SelectedShipCargo(IPshipnum[IPstart],data->SSCstart[n],
                                SSCa);
          
                for(i=0;i<16;i++)
                {
                  if(data->units_ships[n].cargo[SSCa][0]==data->gdstilesX[i])
                  {cost=data->tons*data->price[i][1];break;}
                }
                SubtractGold(cost);
                x=398;y1=368+17;          
                ShipsInPortDisplay(x,y1,IPstart,Ships1Index,Ships1,
                                IPshipnum);   
              }
              else{MessageWindow(4);}
              data->tons=tonsold;
              return 0;
            }
          }
  
          SDL_GetMouseState(&xM,&yM);
        }
        SDL_FreeSurface(bckgoods);
        SDL_ShowCursor(1);
      }
      x1+=51;
    }
  }    
   
/*unload ship*/  
  if(yM>SSCy&&yM<SSCy+55&&Ships1Index>0&&data->units_ships[n].cargonum>0)
  {
    start=data->SSCstart[n];
    x1=data->units_ships[n].cargo[start][0];
    for(x=SSx;x<SSx+205;x+=41)
    {
      if(xM>x&&xM<x+40)
      {
        bckgoods=CreateSurface(screen,40,50);
        bckgds[0]=xM-20;bckgds[1]=yM-26;
        DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
        SDL_ShowCursor(0);

        while(!drag)
        {
          if(yM < 27) yM = 27;
          if(xM!=xMold||yM!=yMold)
          {  
            DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
            UpdateScreen1(bckgds[0],bckgds[1],40,50);
            bckgds[0]=xM-20;bckgds[1]=yM-26;

            DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
            DrawTILE(screen,extra1,xM-20,yM-26,40,50,x1+5,1);
  
            UpdateScreen1(xM-20,yM-26,40,50);  
            xMold=xM;yMold=yM;
          }  
          drag=CheckMouseButton();
          if(drag)
          {
            DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
            UpdateScreen1(bckgds[0],bckgds[1],40,50);
  
            if(xM>166+18&&xM<166+674&&yM>676&&yM<676+53)
            {
              tonsold=data->tons;
              if(data->tons==-1||data->tons>data->units_ships[n].cargo[start][1])
              {data->tons=data->units_ships[n].cargo[start][1];}

              data->units_ships[n].cargototal-=data->tons;
              data->units_ships[n].cargo[start][1]-=data->tons;
          
              for(i=0;i<16;i++)
              {
                if(data->units_ships[n].cargo[start][0]==data->gdstilesX[i])
                {cost=-(data->tons*data->price[i][0]);break;}
              }
              SubtractGold(cost);
          
              if(data->units_ships[n].cargo[start][1]==0)
              {
          
                for(i=start;i<data->units_ships[n].cargonum;i++)
                {
                  data->units_ships[n].cargo[i][0]=
                                    data->units_ships[n].cargo[i+1][0];
                  data->units_ships[n].cargo[i][1]=
                                    data->units_ships[n].cargo[i+1][1];
                }
                data->units_ships[n].cargonum--;
              }
          
              if(start<5){data->SSCstart[n]=0;}else{data->SSCstart[n]=SSCa-4;}
              SelectedShipName(n,yes);
              SelectedShipCargo(IPshipnum[IPstart],
                                          data->SSCstart[n],start);

              data->tons=tonsold;
              return 0;
            }
          }
          SDL_GetMouseState(&xM,&yM);
        }
        SDL_FreeSurface(bckgoods);
        SDL_ShowCursor(1);
      }
      start++;
      x1=data->units_ships[n].cargo[start][0];
    }
  }
  
/*disembark unit*/  
  if(yM>SSy&&yM<SSy+55&&Ships1Index>0&&
                data->units_ships[n].passengernum>0)
  {

    RemoveExtraSpaceH(uniticons,
        data->tile50[data->units_ships[n].passenger[data->SSstart[n]]][0],
        data->tile50[data->units_ships[n].passenger[data->SSstart[n]]][1],75,50);
    w=75-data->leftspace-data->rightspace;

    if(xM>SSx&&xM<SSx+w)
    {
      bckgoods=CreateSurface(screen,w,50);
      bckgds[0]=xM-(w/2);bckgds[1]=yM-26;
      DrawTILE(bckgoods,screen,0,0,w,50,bckgds[0],bckgds[1]);
      SDL_ShowCursor(0);

      while(!drag)
      {
        if(yM < 27) yM = 27;
        if(xM!=xMold||yM!=yMold)
        {  
          DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
          UpdateScreen1(bckgds[0],bckgds[1],w,50);
          bckgds[0]=xM-(w/2);bckgds[1]=yM-26;

          DrawTILE(bckgoods,screen,0,0,w,50,bckgds[0],bckgds[1]);
          DrawTILE(screen,uniticons,xM-(w/2),yM-26,w,50,
                  data->tile50[data->units_ships[n].passenger[data->SSstart[n]]][0]+
                  data->leftspace,data->tile50[data->units_ships[n].passenger
                  [data->SSstart[n]]][1]);
  
          UpdateScreen1(xM-(w/2),yM-26,w,50);  
          xMold=xM;yMold=yM;
        }  
        drag=CheckMouseButton();
        if(drag)
        {
          DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
          UpdateScreen1(bckgds[0],bckgds[1],w,50);
  
          if(xM>643&&xM<643+230&&yM>368&&yM<368+60+34)
          {
            NewUnits[NUIndex]=data->units_ships[n].passenger[data->SSstart[n]];
    
            NUIndex++;
            if(NUIndex>99){NUIndex=99;}
    
x=643;y1=368;    
            BuyHireButton(NUIndex,Dstart,NewUnits,x,y1+17,screen,n);

            for(i=data->SSstart[n];i<data->units_ships[n].passengernum;i++)
            {
              data->units_ships[n].passenger[i]=
                            data->units_ships[n].passenger[i+1];
            }
    
            data->units_ships[n].passengernum--;
          
            SelectedShipName(n,yes);
            SelectedShipPassengers(IPshipnum[IPstart],data->SSstart[n]);
          }
        }  
        SDL_GetMouseState(&xM,&yM);
      }
      SDL_FreeSurface(bckgoods);
      SDL_ShowCursor(1);
    }
  }       
  return 0;
}

/*---------------------------HCSMouseOverSort--------------------*/
void GraphicsEngine::HCSMouseOverSort(void)
{
    GlobalData* data = _GlobalData;

int xM,yM,x0=640,y0=244,HLCheck[3]={-2,-2,-2};
SDL_Surface *temp;

  SDL_GetMouseState(&xM,&yM);

  if(xM>x0&&xM<x0+228&&yM>y0&&yM<y0+62)
  {
    switch(data->HCSradio1)
    {
      case(0):
      {
        temp=HCSWin[1];
        if(xM>x0&&xM<x0+76)
        {
          HCSDRecruitHL(0);
          HLCheck[0]=0;
          data->rHL=0;
        }
        if(xM>x0+76&&xM<x0+152)
        {
          HCSDRecruitHL(1);
          HLCheck[0]=1;
          data->rHL=1;
        }
        if(xM>x0+152&&xM<x0+228)
        {
          HCSDRecruitHL(2);
          HLCheck[0]=2;
          data->rHL=2;
        }
        break;
      }
      case(1):
      {
        temp=HCSWin[2];
        if(xM>x0&&xM<x0+76)
        {
          HCSDNewUnitHL(0,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
          HLCheck[1]=0;
          data->pHL=0;
        }
        if(xM>x0+76&&xM<x0+152)
        {
          HCSDNewUnitHL(1,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
          HLCheck[1]=1;
          data->pHL=1;
        }
        if(xM>x0+152&&xM<x0+228)
        {
          HCSDNewUnitHL(2,HCSWin[2],data->Pstart,data->Buy,data->BuyCost,0);
          HLCheck[1]=2;
          data->pHL=2;
        }
        break;
      }
      default:
      {
        temp=HCSWin[3];
        if(xM>x0&&xM<x0+76)
        {
          HCSDNewUnitHL(0,HCSWin[3],data->Tstart,data->Jobs,data->JobsCost,1);
          HLCheck[2]=0;
          data->tHL=0;
        }
        if(xM>x0+76&&xM<x0+152)
        {
          HCSDNewUnitHL(1,HCSWin[3],data->Tstart,data->Jobs,data->JobsCost,1);
          HLCheck[2]=1;
          data->tHL=1;
        }
        if(xM>x0+152&&xM<x0+228)
        {
          HCSDNewUnitHL(2,HCSWin[3],data->Tstart,data->Jobs,data->JobsCost,1);
          HLCheck[2]=2;
          data->tHL=2;
        }
      }
    }

    if(data->HLCheckOld[data->HCSradio1]!=HLCheck[data->HCSradio1])
    {
      DrawSURF(screen,temp,x0,y0);
      UpdateScreen1(x0,y0,229,104);
      data->HLCheckOld[data->HCSradio1]=HLCheck[data->HCSradio1];
    }
  }
}


//
// $Id: HCSmouse.cpp,v 1.6 2004/06/23 15:37:05 sikon Exp $
//

