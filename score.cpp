/*******************************************************************
*
*  DESCRIPTION: Atomic Model Score
*
*  AUTHOR:	Logan	(Shichao Guan)
*
*  EMAIL: sguan049@uottawa.ca
*
*  DATE:12/10/2012
*
*******************************************************************/

/** include files **/
#include "score.h"      // class Score
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name:
* Description: 
********************************************************************/
Score::Score( const string &name )
: Atomic( name )
, totalScoreIn( addInputPort( "totalScoreIn" ) )
, totalScoreOut( addOutputPort( "totalScoreOut" ) )
{
	finalScore=0;
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Score::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Score::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == totalScoreIn )
	{
		finalScore = static_cast < int > (msg.value());
		holdIn( active, Time::Zero );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Score::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Score::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), totalScoreOut, finalScore) ;
	return *this ;
}
