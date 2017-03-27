///////////////////////////////////////////////////////////////////////////////
/// @file Vehicle.cpp
/// @author Ralph Simelus
/// @date 2017-3-25
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#include "Vehicle.h"
using namespace std;



Vehicle::Vehicle (const string& vehiculeType, int current, int max)
	: vehiculeType_ ( vehiculeType ), currentMileage_ { current }, maxMileage_ {max}
{}


Vehicle::~Vehicle () {}


void Vehicle::setVehiculeType ( const string& type ) {

	if ( type != "essence" || type != "hybrid" || type != "eletric" )
		throw invalid_argument ( "vehicle type must either be 'essence', 'hybrid' or 'electric'" );

	vehiculeType_ = type;
}

void Vehicle::setCurrentMileage ( int current ) {

	/*if ( current <= 0 )
		throw invalid_argument ( "Current mileage must be > 0" );*/

	currentMileage_ = current;
}

void Vehicle::setMaxMileage ( int max ) {

	/*if ( max < 0 )
		throw invalid_argument ( "Max mileage must be > 0" );*/

	maxMileage_ = max;

}

string Vehicle::getVehiculeType () const {

	return vehiculeType_;
}


int Vehicle::getCurrentMileage () const {

	return currentMileage_;
}


int Vehicle::getMaxMileage () const {

	return maxMileage_;
}
