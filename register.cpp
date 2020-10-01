/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR:
*
*  STUDENT#:
*
*  EMAIL:
*
*  DATE:
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "basketballcourt.h"        // class BasketballCourt
#include "audience.h"        // class Audience
#include "ticketwindow.h"        // class TicketWindow
#include "score.h"        // class Score


void MainSimulator::registerNewAtomics()
{
 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<TicketWindow>(), "TicketWindow" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Audience>(), "Audience" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BasketballCourt>(), "BasketballCourt" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Score>(), "Score" ) ;
}

