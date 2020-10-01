/*******************************************************************
*
*  DESCRIPTION: Atomic Model TicketWindow
*
*  AUTHOR:	Logan	(Shichao Guan)
*
*  EMAIL: sguan049@uottawa.ca
*
*  DATE:12/10/2012
*
*******************************************************************/

/** include files **/
#include "ticketwindow.h"      // class TicketWindow
#include "message.h"    	// class ExternalMessage, InternalMessage
#include "mainsimu.h"   	// MainSimulator::Instance().getParameter( ... )
#include "distri.h"      	  // class Distribution
#include "strutil.h"      	 // str2float( ... )
#include <stdlib.h>


/** public functions **/

/*******************************************************************
* Function Name: TicketWindow
* Description: Ticket Window is the entrance to the park, through which audiences and workers can get into the park.
* Workers will come first to prepare for the game.
* After they finish preparing, audiences will be able to come in.
* There will be no fee for workers, bur each Audience should be charged 3 dollars as entrance fee.
* It will output the total amount of money earned as well as the current audience number.
********************************************************************/
TicketWindow::TicketWindow( const string &name )
: Atomic( name )
, audienceIn( addInputPort( "audienceIn" ) )
, workerIn( addInputPort( "workerIn" ) )
, moneyOut( addOutputPort( "moneyOut" ) )
, audienceOut( addOutputPort( "audienceOut" ) )
, timeForAudience( 0, 0, 3, 0 )	//time for audience
, timeForworker(0, 0, 2, 0)	//time for worker
{	currentQueue1Num=0; 	//the current queue1 length for audience
	currentQueue2Num=0;		//the current queue2 length for worker
	totalQueue1Num=0;		// total audienceIn number, if the accumulated audience number is equal or //larger than 500, the TicketWindow will not work at all because audience seats are full!
	totalQueue2Num=0;		//total workerIn number
	money=0; 				//money =3*audience number
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &TicketWindow::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &TicketWindow::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == audienceIn  && this->state() == passive)
	{	totalQueue1Num = static_cast < int > (msg.value());
		if (totalQueue1Num > 0)
		{	currentQueue1Num = totalQueue1Num ;
			money=3;
			holdIn(active, timeForAudience );
		}
	}
	if( msg.port() == workerIn  && this->state() == passive)
	{	totalQueue2Num = static_cast < int > (msg.value());
			if (totalQueue2Num > 0)
			{	currentQueue2Num = totalQueue2Num ;
				holdIn(active, timeForworker );
			}
		}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &TicketWindow::internalFunction( const InternalMessage & )
{
	if (currentQueue1Num > 0)
		{
			money=money+3;
			if(money>1500)
				currentQueue1Num=1;
			currentQueue1Num--;
			holdIn( active, timeForAudience );
		}
	if (currentQueue2Num > 0 )
		{
			currentQueue2Num--;
			holdIn(active, timeForworker);
		}
	if(currentQueue1Num==0 && currentQueue2Num==0)
		passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &TicketWindow::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), moneyOut, money ) ;
	sendOutput( msg.time(), audienceOut, money/3 ) ;
	return *this ;
}
