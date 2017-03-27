///////////////////////////////////////////////////////////////////////////////
/// @file Graph.cpp
/// @author Ralph Simelus
/// @date 2017-3-25
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////

#include "Graph.h"
#include <list>
#include <iostream>
using namespace std;


Graph::Graph () {}


Graph::~Graph () {

	for ( size_t i = 0; i < allVertices_.size (); ++i )
		delete allVertices_[ i ];
}

// add an edge
void Graph::insertEdge ( const string& source, const string& sourceType, const string& destination, const string& destType, int weight ) {

	if ( source == destination ) // no loop
		return;		

	Vertex* u = getVertex ( source, sourceType );
	Vertex* v = getVertex ( destination, destType );

	u->adjVertex_.push_back ( v );
	u->adjWeight_.push_back ( weight );
}

// Getvertex. If the vertexName is not present, create and add it to vertexMap
// in either case, return the vertex
Graph::Vertex* Graph::getVertex ( const string& vertexName, const string& type ) {

	auto& it = vMap_.find ( vertexName );

	if ( it == vMap_.end () ) {

		Vertex* newVertex = new Vertex ( vertexName, type );
		allVertices_.push_back ( newVertex );

		vMap_.insert ( make_pair ( vertexName, newVertex ) );

		return newVertex;
	}

	return it->second;
}

void Graph::dijkstra ( const string& source, const string& target ) {


	auto& it1 = vMap_.find ( source );
	if ( it1 == vMap_.end () ) {

		cout << source << " is not a vertex in this graph" << endl;
		return;
	}


	auto& it2 = vMap_.find ( target );
	if ( it2 == vMap_.end () ) {

		cout << target << " is not a vertex in this graph" << endl;
		return;
	}

	Vertex* start = it1->second;
	list<Vertex*> vList;
	vector<int> distance ( allVertices_.size (), INT_MAX );
	path_.resize ( allVertices_.size (), -1 );
	//vector<int> previous ( allVertices_.size (), -1 );

	vList.push_back ( start );
	distance[ getVertexIndex ( source ) ] = 0;

	while ( !vList.empty () ) {

		Vertex* u = vList.front ();

		// test permettant d'extraire le graphe resultant aussitot
		// quon arrive a la destination
		if ( u == it2->second ) {

			extractGraph ( path_, source, target );
		}

		vList.pop_front ();

		for ( size_t i = 0; i < u->adjVertex_.size (); ++i ) {

			Vertex* v = u->adjVertex_[ i ];
			int weight = u->adjVertex_[ i ]->adjWeight_[i];

			// if there is a shortest path from u to v
			if ( distance[ getVertexIndex ( v->identifier_ ) ] > distance[ getVertexIndex ( u->identifier_ ) ] + weight ) {

				distance[ getVertexIndex ( v->identifier_ ) ] = distance[ getVertexIndex ( u->identifier_ ) ] + weight;
				path_[ getVertexIndex ( v->identifier_ ) ] = getVertexIndex ( u->identifier_ );
				vList.push_back ( v );
				
			}

		} 
	}
}


void Graph::extractGraph ( const vector<int>& path, const std::string& source, const std::string& target ) {

	/*Reading the shortest path from source to target by reverse iteration*/

	vector<int>tmpPath;
	int v = getVertexIndex ( target ); // v take the index of the target position

	while ( v != getVertexIndex ( source ) ) {
		tmpPath.push_back ( v );
		v = path[ v ];
	}

	tmpPath.push_back ( getVertexIndex ( source ) );
	reverse ( tmpPath.begin (), tmpPath.end () );

	path_.clear ();
	path_ = tmpPath;

}


int Graph::getVertexIndex ( const string& vertexName ) const {

	for ( size_t i = 0; i < allVertices_.size (); ++i )
		if ( allVertices_[ i ]->identifier_ == vertexName )
			return i;

	return -1;
}


void Graph::printGraph () const {

	for ( size_t i = 0; i < allVertices_.size (); ++i ) {

		cout << "( " << allVertices_[ i ]->identifier_ + ", " << allVertices_[ i ]->type_ + ", (";

		for ( size_t j = 0; j < allVertices_[ i ]->adjVertex_.size (); ++j )
			cout << allVertices_[ i ]->adjVertex_[ j ]->identifier_ + ", ";

		cout << "))" << endl;
	}
}


void Graph::printShortestPath () const {


	for ( size_t i = 0; i < path_.size (); ++i ) {


		if ( i > 0 )	// element separator
			cout << " ---> ";

		cout << allVertices_[ path_[ i ] ]->identifier_;

	}

	cout << endl;
}