///////////////////////////////////////////////////////////////////////////////
/// @file Vehicle.h
/// @author Ralph Simelus
/// @date 2017-3-25
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef VEHICULE_H
#define VEHICULE_H

#include<string>


class Vehicle {
public:
	Vehicle (const std::string&, int, int );
	~Vehicle ();

	void setVehiculeType ( const std::string& );
	void setMaxMileage ( int );
	void setCurrentMileage ( int );

	std::string getVehiculeType () const;
	int getMaxMileage () const;
	int getCurrentMileage () const;


private:
	std::string vehiculeType_;	// essence, electric or hybrid
	int maxMileage_;	// max mileage
	int currentMileage_; // current mileage
};

#endif // !VEHICULE_H
