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
#include <SDL.h>

#include "graphicsEngine.h" //should be placed in MouseHandler??
#include "gameEngine.h"
#include "globalData.h"

/*---------------------------CDSmousecheck-------------------------*/
int GraphicsEngine::CDSMouseCheck(int xM,int yM)
{
    GlobalData* data = m_pGame->GetData();

    int x,y,x0,bckgds[2],xMold=0,yMold=0,x1;
    short drag=0;//,n,tonsold; looks unused (Brett 13.11.03)
    SDL_Surface *bckgoods;

    /*market*/
    x=325;y=681;
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

    /*counter*/
    x=256;y=620;
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

    /*selected ship pass. left arrow*/  
    x=325+211;y=620;
    if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {  
        HCSArrowButtons(x,y,0,0,17,55,799,89,4,20,7,13,67,132);
        UpdateScreen1(x,y,17,55);

        SDL_Delay(100);    
        HCSArrowButtons(x,y,0,0,17,55,781,89,5,21,7,13,67,132);
        UpdateScreen1(x,y,17,55);
    }

    /*selected ship pass right arrow*/  
    x+=223;
    if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {
        HCSArrowButtons(x,y,0,0,17,55,799,89,5,20,7,13,75,132);
        UpdateScreen1(x,y,17,55);

        SDL_Delay(100);
        HCSArrowButtons(x,y,0,0,17,55,781,89,6,21,7,13,75,132);
        UpdateScreen1(x,y,17,55);
    }

    /*selected cargo left arrow*/  
    x=325+211+240;y=620;
    if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {
        HCSArrowButtons(x,y,0,0,17,55,799,89,4,20,7,13,67,132);
        UpdateScreen1(x,y,17,55);

        SDL_Delay(100);    
        HCSArrowButtons(x,y,0,0,17,55,781,89,5,21,7,13,67,132);
        UpdateScreen1(x,y,17,55);
    }

    /*selected cargo right arrow*/   
    x+=223;
    if(xM>x&&xM<x+17&&yM>y&&yM<y+55)
    {
        HCSArrowButtons(x,y,0,0,17,55,799,89,5,20,7,13,75,132);
        UpdateScreen1(x,y,17,55);

        SDL_Delay(100);    
        HCSArrowButtons(x,y,0,0,17,55,781,89,6,21,7,13,75,132);
        UpdateScreen1(x,y,17,55);
    }

    /*  Under Orders left arrow*/
    x=256;y=34+480;
    if(xM>x&&xM<x+52&&yM>y&&yM<y+17)
    {        
        HCSArrowButtons(x,y,0,0,52,17,116,96,16,5,14,7,37,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,0,0,52,17,63,96,17,6,14,7,37,136);
        return 0;       
    }

    /*  Under Orders right arrow*/  
    if(xM>x+177&&xM<x+177+52&&yM>y&&yM<y+17)
    {    
        HCSArrowButtons(x,y,177,0,52,17,116,96,197,5,14,7,52,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,177,0,52,17,63,96,198,6,14,7,52,136);   
        return 0;
    }

    /*  unassigned left arrow*/
    x=256+265;
    if(xM>x&&xM<x+52&&yM>y&&yM<y+17)
    {        
        HCSArrowButtons(x,y,0,0,52,17,116,96,16,5,14,7,37,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,0,0,52,17,63,96,17,6,14,7,37,136);
        return 0;        
    }

    /*  unassigned right arrow*/  
    if(xM>x+177&&xM<x+177+52&&yM>y&&yM<y+17)
    {    
        HCSArrowButtons(x,y,177,0,52,17,116,96,197,5,14,7,52,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,177,0,52,17,63,96,198,6,14,7,52,136);   
        return 0;
    }

    /*  transports left arrow*/
    x=256+531;
    if(xM>x&&xM<x+52&&yM>y&&yM<y+17)
    {        
        HCSArrowButtons(x,y,0,0,52,17,116,96,16,5,14,7,37,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,0,0,52,17,63,96,17,6,14,7,37,136);
        return 0;       
    }  

    /*  transports right arrow*/  
    if(xM>x+177&&xM<x+177+52&&yM>y&&yM<y+17)
    {    
        HCSArrowButtons(x,y,177,0,52,17,116,96,197,5,14,7,52,136);

        SDL_Delay(100);
        HCSArrowButtons(x,y,177,0,52,17,63,96,198,6,14,7,52,136);
        return 0;
    }

    /*load cargo*/
    x0=325;y=681;  
    if(yM>y&&yM<y+53)
    {
        x1=1;
        for(x=x0+18;x<x0+674;x+=41)
        {
            if(xM>x&&xM<x+40)
            {
//                bckgoods=CreateSurface(40,50);
                bckgoods=CreateSurface(screen,40,50);
                bckgds[0]=xM-20;bckgds[1]=yM-26;
                DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
//                SDL_ShowCursor(0);
                while(!drag)
                {
                    if(yM < 27) yM = 27;
                    if(xM!=xMold || yM!=yMold)
                    {   
                        DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
                        //SDL_UpdateRect(screen,bckgds[0],bckgds[1],40,50);
                        bckgds[0]=xM-20;bckgds[1]=yM-26;

                        DrawTILE(bckgoods,screen,0,0,40,50,bckgds[0],bckgds[1]);
                        DrawTILE(screen,extra1,xM-20,yM-26,40,50,x1+5,1);
                        //SDL_UpdateRect(screen,xM-20,yM-26,40,50);  
                        xMold=xM;yMold=yM;
                    }
                    drag=CheckMouseButton();
                    if(drag)
                    {
                        DrawSURF(screen,bckgoods,bckgds[0],bckgds[1]);
                        //SDL_UpdateRect(screen,bckgds[0],bckgds[1],40,50);
                    }

                    SDL_GetMouseState(&xM,&yM);
                }
                SDL_FreeSurface(bckgoods);
                SDL_ShowCursor(1);
            }
            x1+=51;
        }
    }       
    return 0;  
}


//
// $Id: CDSmouse.cpp,v 1.4 2004/06/23 15:37:05 sikon Exp $
//

