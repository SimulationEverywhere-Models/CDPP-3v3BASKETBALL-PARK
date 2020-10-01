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

#ifndef __TICKETWINDOW_H
#define __TICKETWINDOW_H


#include "atomic.h"     // class Atomic

class TicketWindow : public Atomic
{
public:
	TicketWindow( const string &name = "TicketWindow" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &audienceIn;
	const Port &workerIn;
	Port &moneyOut;
	Port &audienceOut;

	Time timeForAudience;
	Time timeForworker;
	int currentQueue1Num; 	//the current queue1 length for audience
	int currentQueue2Num;	//the current queue2 length for worker
	int totalQueue1Num;		//total audienceIn number, if the accumulated audience number is equal or //larger than 500, the TicketWindow will not work at all because audience seats are full!
	int totalQueue2Num;		//total workerIn number
	int money; 				//money =3*audience number



};	// class TicketWindow

// ** inline ** // 
inline
string TicketWindow::className() const
{
	return "TicketWindow" ;
}

#endif   //__TicketWindow_H
