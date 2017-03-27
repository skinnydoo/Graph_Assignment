#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include "Graph.h"
#include "Vehicle.h"
using namespace std;

int enterChoice ();	// Prototype
Graph* createGraph ( const string& );
void readGraph ( Graph* );
void shortestPath ( Graph*, Vehicle*, const string&, const string& );

enum Choices { CAR_SPECS = 1, READMAP, SHORTESTPATH, EXIT };


int main () {

	Graph* graph = nullptr;
	Vehicle* car = nullptr;
	bool optionA = false;

	int choice; // store the user's choice
	while ( (choice = enterChoice() ) != EXIT ) {

		switch ( choice ) {

			case CAR_SPECS: {

					string carType;
					int maxAutonomy, currentAutonomy;
					bool ChoiceOk = false;

					/**
					* CAR TYPE
					*/
					do {

						cout << "\nInserer le type du vehicule.\nLes options sont : " << endl
							<< "\t - essence" << endl
							<< "\t - hybrid" << endl
							<< "\t - electrique" << endl;

						cout << "? : ";
						cin >> carType;
						cin.ignore ();

						if ( ( carType == "essence" ) || ( carType == "hybrid" ) || ( carType == "electrique" ) ) {
							cout << "Votre choix : " << carType << endl;
							ChoiceOk = true;
						} else
							cout << "Votre choix '" << carType << "' est invalide. Assurez vous de bien ecrire votre choix." << endl;


					} while ( !ChoiceOk );

				
					/**
					* MAX AUTONOMY
					*/
					do {

						cout << "\nInserer un chiffre indiquant l'autonomie maximale du vehicule." << endl;
						cout << "? : ";
						cin >> maxAutonomy;

						if ( cin.fail () ) {

							cout << "Error. Not an integer" << endl;
							cin.clear ();
							cin.ignore ( 256, '\n' );
						} else
							cout << "Max mileage inserted : " << maxAutonomy << endl;


					} while ( cin.fail () );



					/**
					* CURRENT AUTONOMY
					*/
					do {

						cout << "\nInserer un chiffre indiquant l'autonomie courrante du vehicule." << endl;
						cout << "? : ";
						cin >> currentAutonomy;

						if ( cin.fail () ) {

							cout << "Error. Not an integer" << endl;
							cin.clear ();
							cin.ignore ( 256, '\n' );
						} else
							cout << "Current mileage inserted : " << currentAutonomy << endl;


					} while ( cin.fail () );


					// Creation of the vehicule
					car = new Vehicle ( carType, currentAutonomy, maxAutonomy );
					optionA = true;

					break;
				}

			case READMAP: {

					string fileName;
					cout << "\nEntrez le nom du ficher(sans extension) : ";
					cin >> fileName;
					cin.ignore ();

					graph = createGraph ( fileName );
					readGraph ( graph );

					break;
				}


			case SHORTESTPATH: {

					if ( optionA ) {

						cout << "\nPoint de depart (un seul caractere en MAJ): ";
						string source;

						while ( !( cin >> source ) ) {

							cin.clear ();
							cin.ignore ( 256, '\n' );
							cout << "\n\nERROR! Expecting a character" << endl
								<< "Insert your starting point again : ";
						}


						cout << "\nDestination (un seul caractere en MAJ): ";
						string target;

						while ( !( cin >> target ) ) {

							cin.clear ();
							cin.ignore ( 256, '\n' );
							cerr << "\n\nERROR! Expecting a character" << endl
								<< "Insert your destination again : ";
						}

						/// check if graph exist
						if ( graph == nullptr ) {

							cerr << "\n\nErreur! Aucune carte predefinie" << endl;
							break;
						}

						// Find the shortest path
						shortestPath ( graph, car, source, target );

					} else

						cout << "\n\nERROR! L'option 1 'Caracteristiques du vehicule' est necessaire a la recherche d'un itineraire" << endl;

					break;
				}

			default: cerr << "invalid choice" << endl;
				break;
		}

	} // end outter while

	cout << "Program terminated!" << endl << endl;
}


// enable menu choice
int enterChoice () {

	// Display available options
	cout << "\nChoose one of the following options" << endl
		<< "(1) - Caracteristiques du vehicule" << endl
		<< "(2) - Lire la carte" << endl
		<< "(3) - Obtenir le plus court chemin" << endl
		<< "(4) - Quitter" << endl;

	cout << "\nEnter your choice : ";

	int choice;
	while ( !( cin >> choice ) ) {

		cin.clear ();
		cin.ignore ( 256, '\n' );
		cout << "\nERROR! Expecting an integer!" << endl
			<< "Enter your choice again : ";
	}

	return choice;
}




Graph* createGraph ( const string& fileName ) {


	ifstream inMapFile ( fileName + ".txt" );
	Graph* graph { new Graph() };

	// exit program if ifstream can't open the file
	if ( !inMapFile ) {

		cerr << "\nERROR! The map file could not be opened!" << endl;
		exit ( EXIT_FAILURE );
	}


	/*VERTICES SECTION*/
	string verticesLine;
	getline ( inMapFile, verticesLine ); // read the first line containing the vertices
	istringstream inputVertexString ( verticesLine );
	string identifier;
	string type;
	
	vector<pair<string, string>> vertices;
	
	while ( !inputVertexString.eof () ) {

		getline ( inputVertexString, identifier, ',' );
		getline ( inputVertexString, type, ';' );

		if ( identifier == "" )
			break;

		vertices.push_back ( make_pair( identifier, type) );
	}


	/*EDGES SECTION*/
	string edgesLine;
	getline ( inMapFile, edgesLine ); // read the second line containing the the edges
	istringstream inputEdgesString ( edgesLine );
	string sourceVertex, targetVertex;
	string weight;


	while ( !inputEdgesString.eof () ) {

		getline ( inputEdgesString, sourceVertex, ',' );
		getline ( inputEdgesString, targetVertex, ',' );
		getline ( inputEdgesString, weight, ';' );

		if ( sourceVertex == "" )
			break;

		auto& it1 = find_if ( vertices.begin (), vertices.end (), [&sourceVertex]( const pair<string, string>& element ) {return element.first == sourceVertex; } );
		auto& it2 = find_if ( vertices.begin (), vertices.end (), [&targetVertex]( const pair<string, string>& element ) {return element.first == targetVertex; } );

		if ( it1 != vertices.end () && it2 != vertices.end () )
			graph->insertEdge ( sourceVertex, it1->second, targetVertex, it2->second, stoi(weight) );
	}


	cout << "\nGraph Created!" << endl;
	return graph;
}



// enable graph reading
void readGraph ( Graph* graph ) {

	cout << "\nReading Graph..." << endl;
	graph->printGraph ();
}

// enable finding shortest path 
void shortestPath ( Graph* graph, Vehicle* myCar, const string& source, const string& target ) {

	if ( graph->dijkstra ( source, target ) ) {

		if ( graph->getDestinationType () == myCar->getVehiculeType () ) {


			if ( myCar->getCurrentMileage () >= graph->getTotalDistanceToStation () ) {

				cout << "\nTotal distance length : " << graph->getTotalDistanceToStation () << endl
					<< "Current autonomy of your vehicule : " << myCar->getCurrentMileage () << endl;

				// Printing the shortest path
				graph->printShortestPath ();

				int newCurrAutonomy = myCar->getCurrentMileage () - graph->getTotalDistanceToStation ();
				myCar->setCurrentMileage ( newCurrAutonomy );
				cout << "\nYour current autonomy is now : " << myCar->getCurrentMileage () << endl;
			} else {

				cout << "\nYou won't be able to get to that station" << endl
					<< "Total distance length : " << graph->getTotalDistanceToStation () << endl
					<< "Your current autonomy is : " << myCar->getCurrentMileage () << endl
					<< "Your max autonomy is : " << myCar->getMaxMileage () << endl;
			}

		} else {

			cout << "This station has no fuel type compatible with your vehicule." << endl
				<< "Station fuel type : " << graph->getDestinationType() << endl
				<< "Your vehicule fuel type : " << myCar->getVehiculeType() << endl;

		}
	
	}else
		cout << "\n\nERROR! No path exist from " << source << " to " << target << endl;
}