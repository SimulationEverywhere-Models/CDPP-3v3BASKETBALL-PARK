/*******************************************************************
*
*  DESCRIPTION: Atomic Model BasketballCourt
*
*  AUTHOR:	Logan	(Shichao Guan)
*
*  EMAIL: sguan049@uottawa.ca
*
*  DATE:12/10/2012
*
*******************************************************************/

/** include files **/
#include "basketballcourt.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution
#include "strutil.h"       // str2float( ... )
#include <stdlib.h>
#include <time.h>
/** public functions **/

/*******************************************************************
*  Function Name:BasketballCourt
*  Description: The Basketball Court component will model how the game goes on.
*  We are mainly focus on the host team’s performance.
*  The host team will have a total attacking round initially.
*  When their current attacking round equals the total attacking round, the game will be over.
*  The host team includes 3 players (Guard, Forward, and Center).
*  Assuming that the grand is the one who controls the pace of the game and its skill decides whether the team is able to find a suitable chance to shot before losing the possession of the ball(lose one attacking round).
*  The forward will mainly focus on shot and its skill plays a dominate role in the ratio of successful shot.
*  The Center, based on its rebound ability, decides whether its team is able to get another attack opportunity if the ball is not in(gain another attacking round).
*  Also, the defend skill of the visit team can reduce the ratio of successful shot of the host team.
*  Game is based on the 24 second rule, which means within 24 seconds, the possession of ball will change between the host team and visit team.
*  That is to say the internal transaction time is 48 seconds for the Basketball Court (the host team is able to get a score during a time period of 48 seconds : the host team attack within 24 seconds, then the visiting team attack as well).
*  With the game going on, the Basketball Court will output the score of the host team’s current attacking round and as well, when game is over, it will output the final score of the host team.
********************************************************************/
BasketballCourt::BasketballCourt( const string &name )
: Atomic( name )
, totalRoundNumIn( addInputPort( "totalRoundNumIn" ) )
, scoreOut( addOutputPort( "scoreOut" ) )
, totalOut( addOutputPort( "totalOut" ) )
{	score = 0;
	totalScore=0;
	currentRoundNum=0;
	tempPG;
	tempSF;
	tempC;
	tempDefence;
	srand((unsigned) time(NULL));
	try
		{
			dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

			MASSERT( dist );

			for ( register int i = 0 ; i < dist->varCount() ; i++ )
			{
				string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
				dist->setVar( i, str2float( parameter ) ) ;
			}
		} catch( InvalidDistribution &e )
		{
			e.addText( "The model " + description() + " has distribution problems!" ) ;
			e.print(cerr);
			MTHROW( e ) ;
		} catch( MException &e )
		{
			MTHROW( e ) ;
		}

}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &BasketballCourt::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &BasketballCourt::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == totalRoundNumIn  && this->state() == passive)
	{	temp=static_cast <  long double > (msg.value());
		totalRoundNum =int( (static_cast < long double > (msg.value())/10000));
		if (totalRoundNum > 0)
		{	currentRoundNum=1;
			tempPG=20*( int((temp-totalRoundNum*10000)/1000));
			tempSF=20*( int((temp-totalRoundNum*10000-tempPG*50)/100));
			tempC=20*( int((temp-totalRoundNum*10000-tempPG*50-tempSF*5)/10));
			tempDefence=20*((temp-totalRoundNum*10000-tempPG*50-tempSF*5-tempC/2));
			if(rand()%100>=tempPG){
				score=0;
				totalScore=0;
				holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) ) );
			}
			else{
				if(rand()%100>=tempSF-tempDefence/2){
					score=0;
					totalScore=0;
					if(rand()%100<tempC/5)
						currentRoundNum--;
					holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) ) );
				}
				else{
					score=1;
					totalScore=1;
					holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) ) );
				}
			}
		}
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &BasketballCourt::internalFunction( const InternalMessage & )
{
		if (currentRoundNum < totalRoundNum)
		{	currentRoundNum ++;
			if(rand()%100>=tempPG)
			{
					score=0;
					holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) )  );
			}
			else
			{
					if(rand()%100>=tempSF-tempDefence/2)
					{
							score=0;
							if(rand()%100<tempC/5)
								currentRoundNum--;
							holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) )  );
					}
					else
					{
							score=1;
							totalScore++;
							holdIn(active,  Time( static_cast<float>( fabs( distribution().get() ) ) )  );
					}
			}
		}
		else
			passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &BasketballCourt::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), scoreOut, score ) ;
	if(currentRoundNum>= totalRoundNum)
		sendOutput( msg.time(), totalOut, totalScore ) ;
	return *this ;
}
BasketballCourt::~BasketballCourt()
{
	delete dist;
}
