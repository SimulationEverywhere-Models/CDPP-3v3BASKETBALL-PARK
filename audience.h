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

#ifndef __AUDIENCE_H
#define __AUDIENCE_H

//#include <list>
#include "atomic.h"     // class Atomic

class Audience : public Atomic
{
public:
	Audience( const string &name = "Audience" );					//Default constructor
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &audienceIn;
	Port &out;
	Port &audienceOut;
	int count1;		//if count1 >=3, out=1 ,which means audience behavior: exicetd;
	int count2;		//if count2>=10, out=0 ,which means audience behavior: angry!and 10 audiences will decide to  leave;if audience behavior is not excited and angry, it will be normal.then out=2
	int audienceNum;
};	// class Audience

// ** inline ** // 
inline
string Audience::className() const
{
	return "Audience" ;
}

#endif   //__AUDIENCE_H
