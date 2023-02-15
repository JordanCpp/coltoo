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
// >>>
#include "message.h"
#include "unit.h"
// <<<

/*---------------------------MessageWindow-----------------------*/
void GraphicsEngine::MessageWindow(int k)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    int xM,yM,swidth,x0,y0;
	string text;

    /*Display the message window
    Then clear it on a mouse click or return key*/

//modified 6/1

	x0 = ( screenResX / 2 ) - messagenew->w /2;
	y0 = ( screenResY / 2 ) - messagenew->h / 2;
    DrawTILE(messageold,screen,0,0,messagenew->w,messagenew->h,x0,y0);
//???    DrawSURF(screen,messagenew,x0,y0);
    
    switch (k)
    {
      case MSG_RUMOR:
      {
//???        Message(data->RumCount,1);
        text = data->msg->GetRumorMessage(map->getTile(data->RumorFlag));
        DisplayMessage(text, fontInformation);
        break;
      }
      case MSG_NEWRECRUIT:
      {
      /*for proper English. If skill starts with a vowel use 'an' instead of 'a'*/
        if(data->Jobs[data->recruit[0]][0]=='A'||
              data->Jobs[data->recruit[0]][0]=='E'||
              data->Jobs[data->recruit[0]][0]=='I'||
              data->Jobs[data->recruit[0]][0]=='O'||
              data->Jobs[data->recruit[0]][0]=='U')
        {
				  text = "An ";
				  text.append(data->Jobs[data->recruit[0]]);
				  text = text.substr(0,text.size()-1); //Remove the carriage return
				  text += " is now Waiting on the Docks.";
				  
				  DisplayMessage(text,fontInformation);

        }
        else
        {
				  text = "A ";
				  text.append(data->Jobs[data->recruit[0]]);
				  text = text.substr(0,text.size()-1); //Remove the carriage return
				  text += " is now Waiting on the Docks.";

				  DisplayMessage(text,fontInformation);

        }
        break;
      }
      case MSG_VILLAGE:
      {
//???        Message(data->VillCount,0);
        text = data->msg->GetVillageMessage(map->getTile(data->VillageFlag));
        DisplayMessage(text, fontInformation);
        break;
      }
      case MSG_NOROOMPASS:
      {
        ShowSysMessage(SYS_NOROOMPASS);
        break;
      }
      case MSG_NOROOMCARGO:
      {
        ShowSysMessage(SYS_NOROOMCARGO);
        break;
      }
//not implemented yet
      case MSG_NOTIMPLEMENTED:
      {
//???        Message(data->ErrorCount,99);
        ShowSysMessage(SYS_NOTIMPLEMENTED);
        break;
      }
//already cleared      
      case MSG_ALREADYCLEARED:
      {
//???        Message(data->ErrorCount,3);
        ShowSysMessage(SYS_ALREADYCLEARED);
        break;
      }
//already plowed      
      case MSG_ALREADYPLOWED:
      {
//???        Message(data->ErrorCount,4);
        ShowSysMessage(SYS_ALREADYPLOWED);
        break;
      }
//already road      
      case MSG_ALREADYROAD:
      {
//???        Message(data->ErrorCount,5);
        ShowSysMessage(SYS_ALREADYROAD);
        break;
      }
//already colony      
      case MSG_ALREADYCOLONY:
      {
//???        Message(data->ErrorCount,6);
        ShowSysMessage(SYS_ALREADYCOLONY);
        break;
      }                         
      case MSG_TIMESCALE:
      {
        ShowSysMessage(SYS_TIMESCALE);
        break;
      }                         
      case MSG_CANTATTACK:
      {
        ShowSysMessage(SYS_CANTATTACK);
        break;
      }                         
      case MSG_COMBAT:
      {
        ShowSysMessage(SYS_COMBAT);
        break;
      }                         
      case MSG_ENDOFTURN:
      {
        ShowSysMessage(SYS_ENDOFTURN);
        break;
      }                         
      case MSG_NOCDS:
      {
        ShowSysMessage(SYS_NOCDS);
        break;
      }                         
      default : {return;}
    }

    UpdateScreen();

    /*wait for a mouse click or the return key*/  
    while(SDL_WaitEvent(&data->event))
    {
        if(SDL_GetMouseState(&xM,&yM)&SDL_BUTTON(1))
        {
            if(k<2 || k>2){break;}
            else
            {
                /* if message is a village, click must be on box*/
                if(xM>x0&&xM<x0+400&&yM>y0&&yM<y0+150&&k==2){break;}
            }          
        }
        if ( data->event.type == SDL_KEYDOWN )
        {
            if (data->event.key.keysym.sym == SDLK_RETURN ||
                data->event.key.keysym.sym == SDLK_KP_ENTER ||
                data->event.key.keysym.sym == SDLK_ESCAPE)
                break;
        }
    }

    DrawSURF(screen,messageold,x0,y0);
    UpdateScreen();
}

/*---------------------------RemoveRumor--------------------------*/
void GraphicsEngine::RemoveRumor(void)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;
    /*Clear the rumor flag for the tile
      Replace the unit icon with stored background
      Redraw the display (SetTerrain)
      Update the stored background (bck1)
      Put the unit icon back on the screen*/

    map->getTile(data->mapnum)->setFlags(TILE_RUMOR, false);
    DrawSURF(screen,bck1,data->stile[data->oldloc][XPOS],
             data->stile[data->oldloc][YPOS]-data->yextra-5);
    SetTerrain();
    UpdateScreen1(data->stile[data->scrnum][XPOS]-25,
                  data->stile[data->scrnum][YPOS]-25,
                  data->tw+50,data->th+50);
    DrawTILE(bck1,screen,0,0,data->tw,data->th,data->stile[data->scrnum][XPOS],
             data->stile[data->scrnum][YPOS]-data->yextra-5);
/*    DrawTILE(screen,tilesheet1,data->stile[data->scrnum][XPOS],
             data->stile[data->scrnum][YPOS]-data->yextra-5,
             data->tw,data->th,data->tilex[3],data->tiley[1]); */
    UpdateScreen1(data->stile[data->scrnum][XPOS],
                  data->stile[data->scrnum][YPOS]-data->yextra-5,
                  data->tw,data->th);
}

/*---------------------------Message------------------------------*/

/*void GraphicsEngine::Message(short count,short mess)
{
    GlobalData* data = m_pGame->GetData();
    //Randomly select rumor or village message to display

    short k,j,i, strings;
    k=rand()%(count);
    j=334;
    
      switch (mess)
      {
        case (0) :
        {
         strings = 4;
         j = 334;
       
          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->VillMess[k][i]);
            j+=25;
          }
          break;
        }
        case (1) :
        {
         strings = 4;
         j = 334;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->RumMess[k][i]);
            j+=25;
          }            
          break;
        }
        case (3) :
        {
//already cleared        
         strings = 3;
         j = 346;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->Errors[10][i]);
            j+=25;
          }            
          break;
        }
//already plowed        
        case (4) :
        {
         strings = 3;
         j = 346;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->Errors[8][i]);
            j+=25;
          }            
          break;
        }
//already road
        case (5) :
        {
         strings = 3;
         j = 346;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->Errors[7][i]);
            j+=25;
          }            
          break;
        }
//already colony
        case (6) :
        {
         strings = 3;
         j = 346;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->Errors[9][i]);
            j+=25;
          }            
          break;
        }
//not yet implemented                        
        default : 
        {
         strings = 2;
         j = 359;

          for(i=0;i<strings;i++)
          {
            drawString(screen,fontInformation,354,j,false,data->Errors[6][i]);
            j+=25;
          }
        }        
      }
} */

/*---------------------------DisplayMessage------------------------------*/
void GraphicsEngine::DisplayMessage(string text,SDLFont *font,SDL_Surface* surf,
                                      SDL_Rect* pos){
		
	SDL_Rect destinationRect;
	SDL_Surface *text_surface,*messageSurface;

	//The offset on the background image where to start the text
	int xOffset = 15;
	int yOffset = 15;

	//If not specified, default message background image
	if(surf == NULL)
		messageSurface  = messagenew;

	//If not specified, center the image on screen
	if(pos == NULL){
		//Search the center of the screen for the current message bgnd image
		destinationRect.x = ( screenResX / 2 ) - messageSurface->w /2;
		destinationRect.y = ( screenResY / 2 ) - messageSurface->h / 2;
	}
	//Otherwise, use specified destination
	else {
		destinationRect = *pos;
	}
	
	//Blit the background image, without text for now
	SDL_BlitSurface(messagenew,NULL,screen,&destinationRect);
	

	//Retreive space needed for the text according to font size
	int renderW, renderH, numberOfLinesNeeded = 0;
	char *cbegin = (char *)text.c_str(), *temp = cbegin;
	
	while(1)
	{
	 for(; *temp && *temp != ' '; temp++);
	 if(*temp == ' ')
	 {
	  *temp = 0;
      TTF_SizeText(font->font, cbegin, &renderW, &renderH);
      *temp = ' ';
     }
     else
      TTF_SizeText(font->font, cbegin, &renderW, &renderH);

     if(renderW / (messageSurface->w-(2*xOffset)))
     {
		numberOfLinesNeeded++;
		char *cend = temp - 1;
		for(; cend != cbegin && *cend != ' '; cend--);
		if(cend == cbegin)
		 cend = temp;
	    if(!*cend) break;
	    temp = cbegin = cend + 1;
	 }
	 else if(!*temp)
	 {
      numberOfLinesNeeded++;
	  break;
     }
     else
     {
      temp++;
     }
	}
	#ifdef DEBUG
	cout << "NOLN: " << numberOfLinesNeeded<<endl;
	#endif
/*	TTF_SizeText(font->font,(char *)text.c_str(),&renderW,&renderH);

	//How many line needed ?
	int numberOfLinesNeeded = renderW / (messageSurface->w-(2*xOffset));
	
	if( (renderW % (messageSurface->w-(2*xOffset))) > 0){
		numberOfLinesNeeded++;
	} 

// >>>
	int numberOfCharsPerLine = (messageSurface->w-(2*xOffset)) * text.size() / 
        renderW;
// <<< */

	//Starting point for text rendering
	if(numberOfLinesNeeded==1)
	{
	  destinationRect.x += (messageSurface->w - renderW) / 2;
	}
	else
	{
	  destinationRect.x += xOffset;
    }
    destinationRect.y += (messageSurface->h - (numberOfLinesNeeded*renderH))/2;

    temp = cbegin = (char *)text.c_str();
    
	while(1)
	{
	 for(; *temp && *temp != ' '; temp++);
	 if(*temp == ' ')
	 {
	  *temp = 0;
      TTF_SizeText(font->font, cbegin, &renderW, &renderH);
      *temp = ' ';
     }
     else
      TTF_SizeText(font->font, cbegin, &renderW, &renderH);

     if(renderW / (messageSurface->w-(2*xOffset)))
     {
		char *cend = temp - 1;
		for(; cend != cbegin && *cend != ' '; cend--);
		if(cend == cbegin)
		 cend = temp;
		
        if(*cend == ' ')
        { 
		 *cend = 0;
         text_surface = TTF_RenderText_Blended(font->font,cbegin,font->color);
		 SDL_BlitSurface(text_surface,NULL,screen,&destinationRect);
		 SDL_FreeSurface(text_surface);
   		 destinationRect.y += renderH;
		 *cend = ' ';
	    }
	    else
	    {
         text_surface = TTF_RenderText_Blended(font->font,cbegin,font->color);
		 SDL_BlitSurface(text_surface,NULL,screen,&destinationRect);
		 SDL_FreeSurface(text_surface);
		 destinationRect.y += renderH;
	    }
		 
	    if(!*cend) break;
	    temp = cbegin = cend + 1;
	 }
	 else if(!*temp)
	 {
      text_surface = TTF_RenderText_Blended(font->font,cbegin,font->color);
      SDL_BlitSurface(text_surface,NULL,screen,&destinationRect);
      SDL_FreeSurface(text_surface);
      destinationRect.y += renderH;
	  break;
     }
     else
     {
      temp++;
     }
	}

/*	int begin	= 0;
	int end		= 1;

	string line;

	//Render the text
	while(end < text.size()){

		line = text.substr(end-1,numberOfCharsPerLine);

		//Return back to first space (we don't want to split words)
		if( !(begin+numberOfCharsPerLine >= text.size()))
		{
			end += line.find_last_of(" ");
		}
			
		else
			end = text.size(); 

		line = text.substr(begin,end-begin);

		text_surface = TTF_RenderText_Blended(font->font,line.c_str(),font->color);
		SDL_BlitSurface(text_surface,NULL,screen,&destinationRect);
		destinationRect.y += renderH;

		begin = end;
	} */

	UpdateScreen();
	
	return;
}

// >>>

void GraphicsEngine::ShowSysMessage(int message)
{
    GlobalData* data = _GlobalData;
    Map* map = _Map;

    string text = data->msg->GetSysMessage(message);
    DisplayMessage(text, fontInformation);
}

Message::Message()
{
    SysMsg = new vector<string>;
    VillMsg = new vector<string>;
    RumorMsg = new vector<string>;
    ReadMessages();
}

Message::~Message()
{
}

void Message::ParseXml(string xmlFile, vector<string> *array, string root, string item)
{
    string tmpString;
 
    TiXmlBase::SetCondenseWhiteSpace(true);
    TiXmlDocument labelFile(xmlFile.c_str());
    
    bool loadOkay = labelFile.LoadFile();

	if(!loadOkay)
	{
		cerr << "Could not load file '" << xmlFile << "'. Error= " <<
         labelFile.ErrorDesc() << ".\nExiting...\n";
		return;
	}
    
    TiXmlNode*	node			= 0;
    TiXmlElement* listElement	= 0;
	TiXmlElement* element		= 0;
	
	node = labelFile.FirstChild(root.c_str());
	listElement = node->ToElement();
	
	node = listElement->FirstChild(item.c_str());
	element = node->ToElement();
	
	do {
		node = element->FirstChild("text");
		tmpString = node->FirstChild()->Value();
		
		array->push_back(tmpString);
		
		element = element->NextSiblingElement();
	} while(element);
}

void Message::ReadMessages()
{
    ParseXml("data/text/datarumors.xml", RumorMsg, "rumorlist", "rumor");
    ParseXml("data/text/datavillage.xml", VillMsg, "villagemessagelist", "message");
    ParseXml("data/text/datasys.xml", SysMsg, "sysmessagelist", "message");
}

string Message::GetVillageMessage(Tile *village)
{
    int k = rand() % VillMsg->size();
    return (*VillMsg)[k];
}

string Message::GetRumorMessage(Tile *rumor)
{
    int k = rand() % RumorMsg->size();
    return (*RumorMsg)[k];
}

string Message::GetSysMessage(int message)
{
    string s;
    if(message >= SysMsg->size())
    {
         cerr << "Message::GetSysMessage: invalid message ID " << message << endl;
         return "Invalid message";
    }
    return (*SysMsg)[message];
}

char *Message::GetShortNation(int nation)
{
    switch(nation)
    {
        case NATION_ENG:
                return "Eng.";
        case NATION_FR:
                return "Fr.";
        case NATION_SPAN:
                return "Span.";
        case NATION_DUT:
                return "Dut.";
    }
    return "Err.";
}

char Message::GetOrderLetter(Uint8 order)
{
    switch(order)
    {
        case ORD_NONE:
                return '-';
        case ORD_CLEAR:
                return 'C';
        case ORD_PLOW:
                return 'P';
        case ORD_ROAD:
                return 'R';
        case ORD_FORTIFY: case ORD_FORTIFIED:
                return 'F';
        case ORD_SENTRY:
                return 'S';
    }
    return 'X';
}

//
// $Id: message.cpp,v 1.13 2004/06/23 15:37:05 sikon Exp $
//

