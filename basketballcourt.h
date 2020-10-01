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

#ifndef __BASKETBALLCOURT_H
#define __BASKETBALLCOURT_H


#include "atomic.h"     // class Atomic

class Distribution ;
class BasketballCourt : public Atomic
{
public:
	BasketballCourt( const string &name = "BasketballCourt" );					//Default constructor
	~BasketballCourt();
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &totalRoundNumIn;
	Port &scoreOut;
	Port &totalOut;
	int currentRoundNum;//current attacking round number
	long double totalRoundNum;//total attacking round number
	int score;// 0 means the host team did not get a sore in this round ,1 means the host team got a score in this round.
	int totalScore;
	Time roundTime;
	long double tempPG;//decide if the host team will lose one attack opportunity
	long double tempSF;//influence the ratio of successful shot
	long double tempC;//decides if the team can get another attack opportunity
	long double tempDefence;//influence the ratio of successful shot
	long double temp;
	Distribution * dist;
	Distribution &distribution()
			{return *dist;}
};	// class BasketballCourt

// ** inline ** // 
inline
string BasketballCourt::className() const
{
	return "BasketballCourt" ;
}

#endif   //__BASKETBALLCOURT_H
