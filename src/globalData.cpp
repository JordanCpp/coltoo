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
// FILE		: globalData.cpp
//
// VERSION	: 0.1
//
// AUTHOR	: Goose Bonis,  November 2003
//
// CLASS	: GlobalData
//
// DESCRIPTION	: storage data class for global data.
//

#include "globalData.h"
#include <SDL.h>
#include <string.h>
#include "graphicsEngine.h"
#include "unit.h"
// >>>
#include "message.h"
#include "skill.h"
#include "tinyxml.h"
// <<<

//using namespace std;

//Constructors, destructor
GlobalData::GlobalData()
{
    m_pGame      = NULL;

    zl=0;flag=0;scrmax=153;mapmax=29999;
    red=255;green=0;turnnum=1;x_res=1024;y_res=768;

    tilex[0] =  1; tilex[1] = 77; tilex[2] = 153; tilex[3] = 229;
    tilex[4] =305; tilex[5] =381; tilex[6] = 457; tilex[7] = 533;
    tilex[8] =609; tilex[9] =685; tilex[10]= 761; tilex[11]= 837;
    tilex[12]=913; tilex[13]=989; tilex[14]=1065; tilex[15]=1141;

    gdstilesX[0] =  1; gdstilesX[1] = 52; gdstilesX[2] =103; gdstilesX[3] =154;
    gdstilesX[4] =205; gdstilesX[5] =256; gdstilesX[6] =307; gdstilesX[7] =358;
    gdstilesX[8] =409; gdstilesX[9] =460; gdstilesX[10]=511; gdstilesX[11]=562;
    gdstilesX[12]=613; gdstilesX[13]=664; gdstilesX[14]=715; gdstilesX[15]=766;

    tiley[0]=1;tiley[1]=52;tiley[2]=103;tiley[3]=154;tiley[4]=205;tiley[5]=256;

    tiley2[0]=1; tiley2[1]=67; tiley2[2]=156; tiley2[3]=222;

    shiptypenum[0]=shiptypenum[2]=shiptypenum[3]= 0;
    shiptypenum[1]=1;
    shiptypenum[4]=shiptypenum[5]=shiptypenum[6]= 0;

    HLCheckOld[0]=HLCheckOld[1]=HLCheckOld[2]=0;

    oldloc=55;scrnum=71;tw=75;th=50;rows=200;cols=150;
    JobCount=0; visible=1;yextra=9;
    scrndsply = 0; grid = 0; HCSradio1 = 0; Pstart = 0;
    Tstart=1;shipnum=0;
      
                    /*screen directions*/
    sNE=10;sE=1;sSE=12;sS=11;sSW=10;sW=1;sNW=12;sN=11;
                      /*map directions*/
    mNE=149;mE=1;mSE=151;mS=150;mSW=149;mW=1;mNW=151;mN=150;

    gold=1000000;RumorFlag=0;

    ReCenFlag=BIT1;MoveFlag=BIT2;UpDateFlag=BIT3;
    NoMoveFlag=BIT4;VillageFlag=BIT5;SpaceFlag=BIT6;
    RoadFlag=BIT7;//horz=0;vert=1;

    counterbutton=2;counterspace=0;

    caravel=1;//merchantman=2;galleon=3;privateer=4;frigate=5;manowar=6;
    tons=100;counter=100;//nation=0;

	rHL=0;
	pHL=0;
	tHL=0;

//added 6/2
//sets number of colonies and colony names to 0
//assigns a number to each power	
	colonyCount=0;
	colNameCount[0]=0;colNameCount[1]=0;colNameCount[2]=0;colNameCount[3]=0;
//  england=0;france=1;spain=2;dutch=3;tribe=4;
}

GlobalData::GlobalData(GameEngine* game)
: m_pGame(game)
{
    zl=0;flag=0;scrmax=153;mapmax=29999;
    red=255;green=0;turnnum=1;x_res=1024;y_res=768;

    tilex[0] =  1; tilex[1] = 77; tilex[2] = 153; tilex[3] = 229;
    tilex[4] =305; tilex[5] =381; tilex[6] = 457; tilex[7] = 533;
    tilex[8] =609; tilex[9] =685; tilex[10]= 761; tilex[11]= 837;
    tilex[12]=913; tilex[13]=989; tilex[14]=1065; tilex[15]=1141;

    gdstilesX[0] =  1; gdstilesX[1] = 52; gdstilesX[2] =103; gdstilesX[3] =154;
    gdstilesX[4] =205; gdstilesX[5] =256; gdstilesX[6] =307; gdstilesX[7] =358;
    gdstilesX[8] =409; gdstilesX[9] =460; gdstilesX[10]=511; gdstilesX[11]=562;
    gdstilesX[12]=613; gdstilesX[13]=664; gdstilesX[14]=715; gdstilesX[15]=766;

    tiley[0]=1;tiley[1]=52;tiley[2]=103;tiley[3]=154;tiley[4]=205;tiley[5]=256;

    tiley2[0]=1; tiley2[1]=67; tiley2[2]=156; tiley2[3]=222;

    shiptypenum[0]=shiptypenum[2]=shiptypenum[3]= 0;
    shiptypenum[1]=1;
    shiptypenum[4]=shiptypenum[5]=shiptypenum[6]= 0;

    HLCheckOld[0]=HLCheckOld[1]=HLCheckOld[2]=0;

    oldloc=55;scrnum=71;tw=75;th=50;rows=200;cols=150;
    JobCount=0; visible=1; yextra=2;
    scrndsply = 0; grid = 0; HCSradio1 = 0; Pstart = 0;
    Tstart=1;shipnum=0;
      
                    /*screen directions*/
    sNE=10;sE=1;sSE=12;sS=11;sSW=10;sW=1;sNW=12;sN=11;
                      /*map directions*/
    mNE=149;mE=1;mSE=151;mS=150;mSW=149;mW=1;mNW=151;mN=150;

    gold=1000000;RumorFlag=0;

    ReCenFlag=BIT1;MoveFlag=BIT2;UpDateFlag=BIT3;
    NoMoveFlag=BIT4;VillageFlag=BIT5;SpaceFlag=BIT6;
    RoadFlag=BIT7;//horz=0;vert=1;

    counterbutton=2;counterspace=0;

    caravel=1;//merchantman=2;galleon=3;privateer=4;frigate=5;manowar=6;
    tons=100;counter=100;//nation=0;

	rHL=0;
	pHL=0;
	tHL=0;

//added 6/2
//sets number of colonies and colony names to 0
//assigns a number to each power	
	colonyCount=0;
	colNameCount[0]=0;colNameCount[1]=0;colNameCount[2]=0;colNameCount[3]=0;
//  england=0;france=1;spain=2;dutch=3;tribe=4; 	
}

GlobalData::~GlobalData()
{
  #ifdef DEBUG
  cout<<"deleting unitlist"<<endl;
  #endif
  vector<Unit*>::iterator it = unitList.begin();
  for( it = unitList.begin(); it != unitList.end(); it++ )
  {
    if (*it) delete (*it);
  }
  unitList.clear();
  #ifdef DEBUG
  cout << "deleting playerlist" << endl;
  #endif
/*  vector<Player*>::iterator p = playerlist.begin();
  for(p = playerlist.begin(); p != playerlist.end(); p++)
  {
      if(*p) delete (*p);
  }
*/
  playerlist.clear();
}


//
//Methods
//
bool GlobalData::Init(void)
{
    char buffer[255],filename[255];
    int k,i,done=0,temp,num=0,k2=0;
    unsigned int temp0,temp1,temp2,temp3,temp4,temp5;
    FILE *fp = NULL;
    OptionList *opts = m_pGame->GetOptions();
    
    #ifdef DEBUG
    cout<<"  Init GlobalData {"<<endl;
    #endif
    msg = new Message;
    #ifdef DEBUG
    cout<<"    Natives"<<endl;
    #endif
    nativeOnTile = new short[30000];
    memset(nextColName, 0, sizeof(nextColName));
    #ifdef DEBUG
    cout<<"    Loading skills"<<endl;
    #endif
    Skill::loadSkills(&skillList);
/*    for(k=0;k<3;k++)
    {
        switch(k)
        {
            case(0):{sprintf(filename,"data/text/village.txt");break;}
            case(1):{sprintf(filename,"data/text/rumor.txt");break;}
            default:{sprintf(filename,"data/text/errors.txt");}
        }
      
        if((fp=fopen(filename, "r")) == NULL)
        {
             cout << "ERROR opening file " << filename << "\n\n" ;
             return false;
        }

        while(!feof(fp))
        {
             fgets(buffer, 255, fp); //Get a line from the file
             if(buffer[0]=='@')
             {  
                  switch(k)
                  {
                    case(0): 
                    {
                      for(i=0;i<4;i++)
                        {fgets(VillMess[VillCount][i],40,fp);}
                        VillCount++;
                        break;
                    }
                    case(1): 
                    {
                      for(i=0;i<4;i++)
                        {fgets(RumMess[RumCount][i],40,fp);}
                      RumCount++;
                      break;
                    }
//added 6/2
//reads error messages                    
                    case(2): 
                    {
                      for(i=0;i<3;i++)
                        {fgets(Errors[ErrorCount][i],40,fp);}
                      ErrorCount++;
                      break;
                    }
                  }
             }
        }
        fclose(fp);
    }
*/

    #ifdef DEBUG
    cout<<"    Loading labels"<<endl;
    #endif
    strcpy(filename, "data/text/labels.txt");

    //Check to see if the file opened
    if((fp=fopen(filename, "r")) == NULL)
    {
        cout << "ERROR opening file " << filename << "\n\n" ;
        return false;
    }

    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        if(buffer[0]=='@'&&buffer[1]=='J'&&buffer[2]=='o')
        {
             while(done==0)
             {
                  fgets(Jobs[JobCount], 25, fp);
                  if(Jobs[JobCount][0]=='@'){done=1;break;}
                  JobCount++;
             }
        }

        //orders    
        if(buffer[0]=='@'&&buffer[1]=='O'&&buffer[2]=='r')
        {
             for(i=0;i<10;i++){fgets(Order[i],25,fp);}
        }

        //game  
        if(buffer[0]=='@'&&buffer[1]=='G'&&buffer[2]=='a')
        {
             for(i=0;i<9;i++){fgets(Game[i],25,fp);}       
        }

        //view
        if(buffer[0]=='@'&&buffer[1]=='V'&&buffer[2]=='i')
        {
             for(i=0;i<2;i++){fgets(View[i],25,fp);}       
        }

        //buy
        if(buffer[0]=='@'&&buffer[1]=='B'&&buffer[2]=='u')
        {
             for(i=0;i<6;i++){fgets(Buy[i],25,fp);}       
        }

        //buycost
        if(buffer[0]=='@'&&buffer[1]=='B'&&buffer[2]=='C')
        {
             for(i=0;i<6;i++){fgets(BuyCost[i],25,fp);}       
        }

        //jobcost
        if(buffer[0]=='@'&&buffer[1]=='J'&&buffer[2]=='C')
        {
             for(i=0;i<JobCount+1;i++){fgets(JobsCost[i],25,fp);}       
        }

        //labels
        if(buffer[0]=='@'&&buffer[1]=='L'&&buffer[2]=='a')
        {
             i=0;done=0;
             while(done==0)
             {
                  fgets(Labels[i], 25, fp);
                  if(Labels[i][0]=='@'){done=1;}
                  i++;
             }       
        }      
    }
    fclose(fp);    

//New xml file reading
//This section reads the job list and their respective cost
//Not used for now, but works, tested
/*
    string tmpString;
	Job	   tmpJob;
 
    TiXmlBase::SetCondenseWhiteSpace( false );
    
    TiXmlDocument labelFile( "data/text/datalabels.xml" );
    
    bool loadOkay = labelFile.LoadFile();

	if ( !loadOkay )
	{
		cout << "Could not load file 'datalabels.xml'. Error= " << labelFile.ErrorDesc() << ".\nExiting...\n";
		return false;
	}
    
    TiXmlNode*	node				= 0;
    TiXmlElement* jobListElement	= 0;
	TiXmlElement* jobElement		= 0;
	
	node = labelFile.FirstChild( "joblist" );
	jobListElement = node->ToElement();
	
	node = jobListElement->FirstChildElement();
	jobElement = node->ToElement();
	
	do{
		node = jobElement->FirstChild("name");
		tmpJob.name = (node->FirstChild())->Value();

		node = jobElement->FirstChild("cost");
		tmpString = (node->FirstChild())->Value();
		tmpJob.cost = atoi(tmpString.c_str());
		jobList.push_back(tmpJob);
		
		jobElement = jobElement->NextSiblingElement();
	}while(jobElement != 0);
*/

    #ifdef DEBUG
    cout<<"    Loading TextColors"<<endl;
    #endif
    strcpy(filename,"data/text/TextColors.txt");

    if((fp = fopen(filename,"r"))==NULL)
    {
        cout << "ERROR opening file " << filename << "\n\n";
        return false;
    }

    for(i=0;i<18;i+=6)
    {
        fscanf(fp,"%lu,%lu,%lu,%lu,%lu,%lu",&temp0,&temp1,&temp2,&temp3,
                                            &temp4,&temp5);
        text1color[i]=temp0;
        text1color[i+1]=temp1;
        text1color[i+2]=temp2;

        text1color[i+3]=temp3;
        text1color[i+4]=temp4;
        text1color[i+5]=temp5;
    }

    fclose(fp);
    

    #ifdef DEBUG
    cout<<"    Loading pricelist"<<endl;
    #endif
    sprintf(filename,"data/text/pricelist.txt");

    if((fp=fopen(filename,"r"))==NULL)
    {
        cout << "ERROR opening file " << filename << "\n\n";
        return false;
    }

    for(i=0,k=0;i<32;i++)
    {
        fscanf(fp,"%d",&temp);
        if(k==0){price[num][0]=temp;k=1;}
        else{price[num][1]=temp;k=0;num++;}
        k2++;
    }

    fclose(fp);

//from initarrays1.cpp - begin
    int x, y;
    for(y=25, i=0; y<725; y+=50)
    {
        for(x=8;x<833;x+=75, i++)
        {
            stile[i][XPOS]=x;
            stile[i][YPOS]=y;
        }
    }

    for(y = 1, i = 0; y < 257; y += 51)
    {
        for(x = 1; x < 838; x += 76, i++)
        {
            tile50[i][XPOS] = x;
            tile50[i][YPOS] = y;
        }
    }

    for(y = 1, i = 0; y < 132; y += 26)
    {
        for(x = 1; x < 365; x += 33, i++)
        {
            tile26[i][XPOS] = x;
            tile26[i][YPOS] = y;
        }
    }

    #ifdef DEBUG
    cout<<"    Create the Caravel"<<endl;
    #endif
    /*put the data for the ship on the map into the shipstruct array.*/
    DefaultShipName(shiptypenum[caravel],Buy,caravel);
    strcpy(units_ships[shipnum].type,Buy[caravel]);
    units_ships[shipnum].typenum=caravel;
    ShipCharacteristics(units_ships[shipnum].typenum);

    #ifdef DEBUG
    cout<<"    Create the Merchantman"<<endl;
    #endif
    /*put the data for the ship on the map into the shipstruct array.*/
    DefaultShipName(shiptypenum[merchantman],Buy,merchantman);
    strcpy(units_ships[shipnum].type,Buy[merchantman]);
    units_ships[shipnum].typenum=merchantman;
    ShipCharacteristics(units_ships[shipnum].typenum);

    /*zero the value of the SelectedShipstart & 
      SelectedShipCargo arrays;*/
    for(i=0;i<100;i++)
    {
        SSstart[i]=0;
        SSCstart[i]=0;
    }

//added 6/2
//sets native flag to zero    
    for(x=0;x<30000;x++)
    {
      nativeOnTile[x]=0;
    }
//added 6/2
//sets up colony struct for placing buildings
/*    for(x=0;x<1000;x++)
    {
      colony[x].colonyLoc=0;
      colony[x].colDock=-1;
      for(i=0;i<18;i++)
      {
        colony[x].colSmBuilding[i]=-1;
      }
    } */

//added 6/2
//reads colony names
    #ifdef DEBUG
    cout<<"    Loading Colony data"<<endl;
    #endif
    strcpy(filename, "data/text/colony.txt");

    //Check to see if the file opened
    if((fp=fopen(filename, "r")) == NULL)
    {
        cout << "ERROR opening file " << filename << "\n\n" ;
        return false;
    }

    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        done=0;
        if(buffer[0]=='@'&&buffer[1]=='E'&&buffer[2]=='N')
        {
             while(done==0)
             {
                  fgets(colName[0][colNameCount[0]], 30, fp);
                  if(colName[0][colNameCount[0]][0]=='@'){done=1;break;}
                  colNameCount[0]++;
             }
        }
        if(buffer[0]=='@'&&buffer[1]=='F'&&buffer[2]=='R')
        {
             while(done==0)
             {
                  fgets(colName[1][colNameCount[1]], 30, fp);
                  if(colName[1][colNameCount[1]][0]=='@'){done=1;break;}
                  colNameCount[1]++;
             }
        }
        if(buffer[0]=='@'&&buffer[1]=='S'&&buffer[2]=='P')
        {
             while(done==0)
             {
                  fgets(colName[2][colNameCount[2]], 30, fp);
                  if(colName[2][colNameCount[2]][0]=='@'){done=1;break;}
                  colNameCount[2]++;
             }
        }
        if(buffer[0]=='@'&&buffer[1]=='D'&&buffer[2]=='U')
        {
             while(done==0)
             {
                  fgets(colName[3][colNameCount[3]], 30, fp);
                  if(colName[3][colNameCount[3]][0]=='@'){done=1;break;}
                  colNameCount[3]++;
             }
        }        
    }
    fclose(fp);

    
//from initarrays1.cpp - end
    
    #ifdef DEBUG
    cout<<"    Loading Players {"<<endl;
    #endif
    InitPlayers();
    #ifdef DEBUG
    cout<<"    } Players"<<endl;
    #endif
    
    #ifdef DEBUG
    cout<<"  } GlobalData"<<endl;
    #endif
    return true; //global
}

bool GlobalData::InitPlayers()
{
    /*Player format
	    <country>
	  		    <name>England</name>
	  		    <color>255,0,0</color>
	  		    <nationality>English</nationality>
	  		    <abbrev>Eng.</abbrev>
	  		    <homeport>London</homeport>
	  		    <colonyname>New England</colonyname>
	  		    <independant>United States of America</independant>
	  		    <leader>
	  		             <name>Walter Raleigh</name>
	  		             <attitude> 1,-1, 0</attitude>
         	    </leader>
         	    <mission>Church of</mission>
	    </country>*/
	string tmp = "";
	
	TiXmlBase::SetCondenseWhiteSpace( false );
	
    #ifdef DEBUG
	cout<<"      Loading names"<<endl;
    #endif
    TiXmlDocument pFile("data/text/names.xml");
    
    bool loadOkay = pFile.LoadFile();
	
	if ( !loadOkay )
	{
		printf( "Could not load file 'names.xml'. Error='%s'. Exiting.\n", pFile.ErrorDesc() );
		exit( 1 );
	}
	
	TiXmlNode *node = 0;
	TiXmlNode *pNodeList = 0;
	TiXmlNode *pNode = 0;
	
    #ifdef DEBUG
	cout<<"      Getting Names list"<<endl;
    #endif
	node = pFile.FirstChild("names");
	pNodeList = node->ToElement();
	
    #ifdef DEBUG
	cout<<"      Getting Countries {"<<endl;
    #endif
	node = pNodeList->FirstChild("country");
	//pNodeList = node->ToElement();
	
	while(node)
	{
	    Player *p = new Player();
	    if(!p->Init()) break;
	    
        #ifdef DEBUG
	    cout<<"        Set nodelist"<<endl;
        #endif
	    pNodeList = node->ToElement();	    

        #ifdef DEBUG
	    cout<<"        Creating Player "<<playerlist.size()<<" {"<<endl;
        #endif
	    p->setNationID(playerlist.size());
	    
        #ifdef DEBUG
	    cout<<"          Get Country Data {"<<endl;
        #endif
	    //Get Country Data
	    tmp = pNodeList->FirstChild("name")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->country.name = tmp;
	    tmp = pNodeList->FirstChild("color")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->Color->SetColor(tmp.c_str());
	    tmp = pNodeList->FirstChild("nationality")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->country.nationality = tmp;
	    tmp = pNodeList->FirstChild("abbrev")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->country.abbrev = tmp;
	    tmp = pNodeList->FirstChild("homeport")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->country.homeport = tmp;
        #ifdef DEBUG
	    cout<<"          } Country Data"<<endl;
        #endif
	    
        #ifdef DEBUG
	    cout<<"          Get Colony Data {"<<endl;
        #endif
	    //Get Colony Data
	    tmp = pNodeList->FirstChild("colonyname")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->NewWorld.name = tmp;
	    tmp = pNodeList->FirstChild("independent")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->NewWorld.independent = tmp;
	    tmp = pNodeList->FirstChild("mission")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"            Got "<<tmp<<endl;
        #endif
	    p->NewWorld.mission = tmp;
	    #ifdef DEBUG
	    cout<<"        } Colony Data"<<endl;
	    #endif
	    
        #ifdef DEBUG
	    cout<<"        Get Leader Data {"<<endl;
        #endif
	    //Get Leader Data
	    tmp = pNodeList->FirstChild("leaderName")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"          Got "<<tmp<<endl;
        #endif
	    p->setName(tmp.c_str());
	    tmp = pNodeList->FirstChild("leaderAttitude")->FirstChild()->Value();
        #ifdef DEBUG
	    cout<<"          Got "<<tmp<<endl;
        #endif
	    p->setAttitude(tmp.c_str());
	    #ifdef DEBUG
	    cout<<"        } Leader Data"<<endl;
	    #endif
	    
	    #ifdef DEBUG
	    cout<<"        Setting "<<p->getName()<<"'s gold"<<endl;
        #endif
        p->setGold(gold);
        
        #ifdef DEBUG
	    cout<<"        Push Player into the Players list"<<endl;
        #endif
	    playerlist.push_back(p);
	    
        #ifdef DEBUG
	    cout<<"      } Player"<<endl;
        #endif
	    node = pNodeList->NextSibling("country");
	}
	//TODO: where's the return?
};

/*const char *GlobalData::GetDataValue(TiXmlNode *node, char *nodeName)
{
    string tmp = "";
    
    TiXmlNode *elem = node->FirstChild(nodeName);
    if(elem)
    {
        TiXmlNode *txt = elem->FirstChild();
        if(txt)
        {
            tmp = txt->Value();
        }
    }
    return tmp.data();
}

*/
//
// $Id: globalData.cpp,v 1.19 2004/06/23 15:37:05 sikon Exp $
//
