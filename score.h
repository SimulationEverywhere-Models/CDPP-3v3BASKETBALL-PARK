/*******************************************************************
*
*  DESCRIPTION: Atomic Model
*
*  AUTHOR:
*
*  EMAIL:
*
*  DATE:
*
*******************************************************************/

#ifndef __Score_H
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
#define __Score_H

//#include <list>
#include "atomic.h"     // class Atomic

class Score : public Atomic
{
public:
	Score( const string &name = "Score" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &totalScoreIn;
	Port &totalScoreOut;

	int finalScore;


};	// class Score

// ** inline ** // 
inline
string Score::className() const
{
	return "Score" ;
}

#endif   //__Score_H
