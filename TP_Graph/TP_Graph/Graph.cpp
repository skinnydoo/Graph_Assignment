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

	for ( int i = 0; i < allVertices_.size (); ++i )
		delete allVertices_[ i ];
}

// add an edge
void Graph::insertEdge ( const string& source, const string& sourceType, const string& destination, const string& destType, int weight ) {

	if ( source == destination ) // no loop
		return;		

	Vertex* u = getVertex ( source, sourceType );
	u->weight_ = weight;
	Vertex* v = getVertex ( destination, destType );

	u->adjVertex_.push_back ( v );
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

Graph& Graph::dijkstra ( const string& source, const string& target ) {


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
	vector<int> previous ( allVertices_.size (), -1 );

	vList.push_back ( start );
	distance[ getVertexIndex ( source ) ] = 0;

	while ( !vList.empty () ) {

		Vertex* u = vList.front ();

		// test permettant d'extraire le graphe resultant aussitot
		// quon arrive a la destination
		if ( u == it2->second ) {

			return extractGraph ( previous, source, target );
		}

		vList.pop_front ();

		for ( size_t i = 0; i < u->adjVertex_.size (); ++i ) {

			Vertex* v = u->adjVertex_[ i ];
			int weight = u->weight_;

			// if there is a shortest path from u to v
			if ( distance[ getVertexIndex ( v->identifier_ ) ] > distance[ getVertexIndex ( u->identifier_ ) ] + weight ) {

				distance[ getVertexIndex ( v->identifier_ ) ] = distance[ getVertexIndex ( u->identifier_ ) ] + weight;
				previous[ getVertexIndex ( v->identifier_ ) ] = getVertexIndex ( u->identifier_ );
				vList.push_back ( v );
				
			}

		} 
	}

	return;
}


Graph& Graph::extractGraph ( std::vector<int> path, const std::string& source, const std::string& target ) {

	/*Reading the shortest path from source to target by reverse iteration*/

	vector<int>tmpPath;
	int v = getVertexIndex ( target ); // v take the index of the target position

	while ( v != getVertexIndex ( source ) ) {
		tmpPath.push_back ( v );
		v = path[ v ];
	}

	tmpPath.push_back ( getVertexIndex ( source ) );
	reverse ( tmpPath.begin (), tmpPath.end () );


	Graph g;

	for ( size_t i = 0; i < tmpPath.size () - 1; ++i )
		g.insertEdge ( allVertices_[ i ]->identifier_, allVertices_[ i ]->type_, allVertices_[ i + 1 ]->identifier_, allVertices_[ i + 1 ]->type_, allVertices_[i]->weight_ );

	return g;


	// NOT TESTED. I HAVE NO IDEA WHETHER THIS MAKES SENSES

}
