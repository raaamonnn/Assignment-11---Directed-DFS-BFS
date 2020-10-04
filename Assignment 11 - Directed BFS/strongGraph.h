#ifndef STRONGGRAPH_H_
#define STRONGGRAPH_H_

// Authors: Kenneth Casimiro, Mason Godrey
// Class Information: CS1D #14490

#include <iostream>				// input/out stream
#include <string>				// string
#include <vector>				// vector
using namespace std;			// standard library


// Summary: ASSIGNMENT 11 PART B & C
//			This is the graph adjacency list data structure to be used
//          to store the distances between cities
//          It also does a DFS Search of the cities
//          USES ONLY DIRECTED EDGES
//          Determines which edges are discovery edges
//          Determine which edges are back edges
//          Does a total count of how much is traveled through disc edges
//          Determines if the graph has strong connectivity
//          - Normal DFS
//          - Reverse DFS (edges are reversed)

// struct - edge for the list
struct nodeEdge {
	string startCity; 		// start city
	string endCity; 		// end city.
	bool discEdge; 			// determine if its a discovery or back edge
	int weight; 			// distance between cities

	nodeEdge() {
		startCity = "";
		endCity = "";
		discEdge = false;
		weight = 0;
	}
};

// nodeVertex
struct nodeVertex {
	string city; 				// vertex - name of city
	bool visited; 				// determine if it was already visited
	vector<nodeEdge> edgeList; 	// list of edges

	// nodeVertex default constructor.
	nodeVertex() {
		city = "";
		visited = false;
	}
};

// graph - adjacency list structure
class strongGraph {
public:
	strongGraph();													// default constructor
	~strongGraph();													// destructor
	bool empty();													// determine if graph is empty
	int size();														// size of graph
	void insertVertex(string city);									// insert vertex to a city
	int findVertex(string city);									// finds the vertex to a city
	void insertEdge(string startCity, string endCity, int weight);	// insert edge for a city
	vector<string> vertices();										// list of vertices
	vector<string> edges();											// list of edges
	int DFS(string startingCity, vector<string> &dfsGraph);			// DFS search calculation
	vector<string> getDiscoveryEdges(vector<string> &dfsGraph);		// discovery edge list
	vector<string> getBackEdges(vector<string> &dfsGraph);			// back edge list
	void clear();

private:
	int smallestEdgeDFS(int currVertex, vector<string> &dfs);		// finds smallest edge for DFS search
	int verticesVisited();											// checks what vertices has been used already
	int edgesDiscovered(int currVertex);							//  finds edge discovered
	void deleteDuplicates(vector<nodeEdge> &edgeList);				// deletes duplicates
	vector<nodeVertex> graph;										// vertex list graph
	int dfsDistance;												// distance traveled
	string otherVertex(nodeEdge currEdge, string startingCity);		// finds the other vertex to be used
	int distance(nodeVertex * v1, nodeVertex * v2);					// distance between each node
};

// default constructor
strongGraph::strongGraph() {
	dfsDistance = 0;
}

// destructor
strongGraph::~strongGraph() {
}

// checks if its empty
bool strongGraph::empty() {
	return graph.empty();
}

// checks the size
int strongGraph::size() {
	return graph.size();
}

// finds the vertex of the city
int strongGraph::findVertex(string city) {
	int index  = 0;
	bool found = false;

	while(index < graph.size() && !found) {		// finds the city
		if(graph.at(index).city == city) {
			found = true;
		}
		else {
			index++;
		}
	}
	return index;
}

// insert vertex
void strongGraph::insertVertex(string city) {
	if(findVertex(city) == graph.size()) {	// adds the vertex if not added already
		nodeVertex newVertex;

		newVertex.city = city;
		newVertex.visited = false;

		cout <<"CITY: "<< newVertex.city << " - HAS BEEN ADDED."<< endl;

		graph.push_back(newVertex);
	}
}

// insert edge
void strongGraph::insertEdge(string startCity, string endCity, int weight) {
	int index = findVertex(startCity);	// returns the vertex

	if(index == graph.size()) {			// adds the vertex if not added already
		insertVertex(startCity);
		insertEdge(startCity, endCity, weight);
	}
	else {
		nodeEdge newEdge;

		newEdge.startCity = startCity;
		newEdge.endCity   = endCity;
		newEdge.weight    = weight;

		graph.at(index).edgeList.push_back(newEdge);
	}
}

// gets the city nodes
vector<string> strongGraph::vertices() {
	vector<string> cityNames;						// vector of city names

	for(int i = 0; i < graph.size(); i++) {
		cityNames.push_back(graph[i].city);
	}

	return cityNames;
}

// gets the edges
vector<string> strongGraph::edges() {
	vector<string> edgeList; 			// edges

	for(int i = 0; i < graph.size(); i++) {		// adds the edges if node has edges
		if(graph.at(i).edgeList.size() != 0) {
			for(int j = 0; j < graph.at(i).edgeList.size(); j++) {	// adds it in (startCity, endCity) format
				edgeList.push_back("(" + graph.at(i).edgeList.at(j).startCity + ", "
									   + graph.at(i).edgeList.at(j).endCity + ")");
			}
		}
	}
	return edgeList;
}

// DFS search
int strongGraph::DFS(string startingCity, vector<string> &dfsGraph) {
	int currVertex = findVertex(startingCity);		// gets the vertex

	graph.at(currVertex).visited = true;			// marks it as visited

	vector<string>::iterator nextCityIt = find(dfsGraph.begin(), dfsGraph.end(), startingCity);	// gets the cities visited

	if(nextCityIt == dfsGraph.end()) {
		dfsGraph.push_back(startingCity);
	}

	if(verticesVisited() != graph.size()) {								// recursive call
		int nextVertex = smallestEdgeDFS(currVertex, dfsGraph);
		DFS(graph.at(nextVertex).city, dfsGraph);
	}
	return dfsDistance;
}

// get the discovery edges
vector<string> strongGraph::getDiscoveryEdges(vector<string> &dfsGraph)
{
	vector<nodeEdge> discEdges;					// vector of discovery edges

	for(int i = 0; i < graph.size(); i++) {		// gets all the disc edges
		int dfsIndex = findVertex(dfsGraph.at(i));

		for(int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++) {
			if(graph.at(dfsIndex).edgeList.at(j).discEdge) {
				discEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
			}
		}
	}

	deleteDuplicates(discEdges);		// delete duplicates

	vector<nodeEdge>::iterator edgeIt = discEdges.begin();	// goes to the beginning disc edges

	vector<string> discoveryEdges; 							// disc edge pairs

	while(edgeIt != discEdges.end()) {
		discoveryEdges.push_back("(" + edgeIt->startCity + ", " + edgeIt->endCity + ")");

		edgeIt++;
	}

	return discoveryEdges;
}

vector<string> strongGraph::getBackEdges(vector<string> &dfsGraph) {
	vector<nodeEdge> backEdges; 					// vector - back edges

	for(int i = 0; i < graph.size(); i++) {				// adds back edges
		int dfsIndex = findVertex(dfsGraph.at(i));

		for(unsigned int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++) {
			if(!(graph.at(dfsIndex).edgeList.at(j).discEdge)) {					// adds only if its a back edge
				backEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
			}
		}
	}

	deleteDuplicates(backEdges);		// delete duplicates

	vector<nodeEdge>::iterator edgeIt = backEdges.begin();	// starts at begin of vector

	vector<string> backEdgeList; // back edge pairs

	while(edgeIt != backEdges.end()) {	// (startCity, endCity)
		backEdgeList.push_back("(" + edgeIt->startCity + ", " + edgeIt->endCity + ")");

		edgeIt++;
	}

	return backEdgeList;
}

// goes to the smallest edge for DFS search
int strongGraph::smallestEdgeDFS(int currVertex, vector<string> &dfsGraph) {
	if(edgesDiscovered(currVertex) != graph.at(currVertex).edgeList.size()) {
		int smallestIndex = 0;
		int compIndex = smallestIndex + 1;

		int size = graph.at(currVertex).edgeList.size();		// get current size

		while(compIndex < size) {
			int smallestVertex = findVertex(graph.at(currVertex).edgeList.at(smallestIndex).endCity);
			int compVertex = findVertex(graph.at(currVertex).edgeList.at(compIndex).endCity);

			if(graph.at(smallestVertex).visited) {
				smallestIndex++;
			}
			else {
				if(!(graph.at(compVertex).visited)) {
					if(graph.at(currVertex).edgeList.at(smallestIndex).weight >=
					   graph.at(currVertex).edgeList.at(compIndex).weight) {
						smallestIndex = compIndex;
					}
				}
			}
			compIndex++;
		}
		graph.at(currVertex).edgeList.at(smallestIndex).discEdge = true;
		dfsDistance += graph.at(currVertex).edgeList.at(smallestIndex).weight;
		string nextCity = graph.at(currVertex).edgeList.at(smallestIndex).endCity;
		smallestIndex = findVertex(nextCity);

		for(int i = 0; i < graph.at(smallestIndex).edgeList.size(); i++) {
			if(graph.at(currVertex).city == graph.at(smallestIndex).edgeList.at(i).endCity) {
				graph.at(smallestIndex).edgeList.at(i).discEdge = true;
			}
		}
		return smallestIndex;
	}
	else {
		vector<string>::iterator dfsIt = find(dfsGraph.begin(), dfsGraph.end(),
										 	  graph.at(currVertex).city);
		dfsIt--;

		int backIndex = findVertex(*dfsIt);

		return smallestEdgeDFS(backIndex, dfsGraph);
	}
}

// distance/weight
int strongGraph::distance(nodeVertex * v1, nodeVertex * v2) {
    for (int i=0; i<v1->edgeList.size(); i++) {			// get connecting edge
        if (v1->edgeList.at(i).startCity == v2->city || v1->edgeList.at(i).endCity == v2->city)
            return v1->edgeList.at(i).weight;
    }
    return -1;
}

// find other vertex of the node
string strongGraph::otherVertex(nodeEdge currEdge, string startingCity) {
    if(currEdge.startCity == startingCity) {
        return currEdge.endCity;
    }
    else {
        return currEdge.startCity;
    }
}

// get all the vertices visited
int strongGraph::verticesVisited() {
	int numVisited = 0;

	vector<nodeVertex>::iterator graphIt = graph.begin();

	while(graphIt != graph.end()) {
		if(graphIt->visited)
		{
			numVisited++;
		}

		graphIt++;
	}
	return numVisited;
}

// finds how many edges discovered
int strongGraph::edgesDiscovered(int currVertex) {
	int numVisited = 0;

	for(int i = 0; i < graph.at(currVertex).edgeList.size(); i++) {
		if(graph.at(findVertex(graph.at(currVertex).edgeList.at(i).endCity)).visited) {
			numVisited++;
		}
	}

	return numVisited;
}

// delete duplicates
void strongGraph::deleteDuplicates(vector<nodeEdge> &edgeList)
{
	vector<nodeEdge>::iterator listIt = edgeList.begin();

	while(listIt != edgeList.end()) {
		vector<nodeEdge>::iterator compIt = listIt + 1;

		bool deleted = false;

		while(compIt != edgeList.end() && !deleted) {
			if(listIt->startCity == compIt->endCity && listIt->endCity == compIt->startCity) {
				edgeList.erase(compIt);

				deleted = true;
			}
			else {
				compIt++;
			}
		}
		listIt++;
	}
}

void strongGraph::clear() {
	graph.clear();
}

#endif /* STRONGGRAPH_H_ */
