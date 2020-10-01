/*******************************************************************
*
*  DESCRIPTION: Atomic Model Audience
*
*  AUTHOR:	Logan	(Shichao Guan)
*
*  EMAIL: sguan049@uottawa.ca
*
*  DATE:12/10/2012
*
*******************************************************************/

/** include files **/
#include "audience.h"      // class Audience
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name:Audience
* Description: As to the Audience part, audiences have three behaviors:
* 'Excited', if the host team wins 3 scores consecutively in their 3 attacking rounds;
* 'Angry', if the host team cannot get any score consecutively in their 10 attacking rounds;
* else, the behavior is 'normal'.
* Some of them will decide to leave the park if they are angry.
* The total amount of audiences who still want to watch the game will be shown as an output.
* Another output is the audience’s behavior.
********************************************************************/
Audience::Audience( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, audienceIn( addInputPort( "audienceIn" ) )
, out( addOutputPort( "out" ) )
, audienceOut( addOutputPort( "audienceOut" ) )
{	count1=0;
	count2=0;
	audienceNum=0;

}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition:
********************************************************************/
Model &Audience::initFunction()
{
	this-> passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Audience::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == audienceIn )
	{
		audienceNum = static_cast < int > (msg.value());
		holdIn( active, Time::Zero );
	}
	if(msg.port() == in)
	{
		if(static_cast < int > (msg.value())==1){
			count1++;
			count2=0;
			holdIn(active,Time::Zero );
		}
		if( static_cast < int > (msg.value())==0){
			count1=0;
			count2++;
			if(count2>=10){
				if(audienceNum<10)
					audienceNum=0;
				if(audienceNum>=10)
					audienceNum= audienceNum-10;
			}
			holdIn(active,Time::Zero );
		}

	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Audience::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Audience::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), audienceOut, audienceNum) ;
	if(count1>=3)
		sendOutput( msg.time(), out, 1);
	if(count2>=10)
		sendOutput( msg.time(), out, 0);
	if(count1<3 && count2<10 && (count1!=0 || count2!=0))
		sendOutput(msg.time(), out, 2);
	return *this ;
}
