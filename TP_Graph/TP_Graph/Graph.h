///////////////////////////////////////////////////////////////////////////////
/// @file Graph.h
/// @author Ralph Simelus
/// @date 2017-3-25
/// @version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<string>
#include <map>


class Graph {
public:
	Graph ();
	~Graph ();

	void insertEdge ( const std::string&, const std::string&, const std::string&, const std::string&, int weight );
	Graph& dijkstra ( const std::string& , const std::string& );

	void printGraph ( ) const;
	void printShortestPath ( const std::string& ) const;

private:

	struct Vertex {

		std::string			 identifier_;	// station name (vertex)
		std::string			 type_;			// station type (vertex)
		int					 weight_;		// weight to adj vertex
		std::vector<Vertex*> adjVertex_;	// adjacent vertex
		//Vertex*				 path_;			// hold the previous vertex on shortest path


		Vertex ( const std::string& id, const std::string& type )
			:identifier_ ( identifier_ ), type_ ( type ) 
		{}
	};

	using vertexMap = std::map<std::string, Vertex*>;
	vertexMap vMap_;
	std::vector<Vertex*> allVertices_;

	Graph& extractGraph ( std::vector<int>, const std::string&, const std::string& );
	Vertex* getVertex ( const std::string&, const std::string& type );
	int getVertexIndex ( const std::string& );
	void printPath ( const Vertex& ) const;
	void clear ();
};

///////////////////////////////////////////////////////////////////////////////
//@}
//////////////////////////////////////////////////////////////////////////////


#endif // !GRAPH_H
