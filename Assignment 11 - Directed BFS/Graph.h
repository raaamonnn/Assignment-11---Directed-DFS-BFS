#ifndef GRAPH_H_
#define GRAPH_H_

// Authors: Kenneth Casimiro, Mason Godrey
// Class Information: CS1D #14490

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Summary: ASSIGNMENT 11 PART B & C
//			This is the graph adjacency list data structure to be used
//          to store the distances between cities
//          It also does a BFS Search of the cities
//          USES ONLY DIRECTED EDGES
//          Determines which edges are discovery edges
//          Determine which edges are back edges
//          Does a total count of how much is traveled through disc edges


// edge
struct Edge {
	string startCity; 			// start city.
	string endCity; 			// end city.
	bool discoveryEdge; 		// discovery edge or not

	int edgeType;				// back edge (0)
								// disc      (1)
								// cross     (2)

	int weight; 				// distance from each city

	Edge() {					// edge default constructor
		startCity     = "";
		endCity       = "";
		discoveryEdge = false;
		edgeType      = 0;
		weight        = 0;
	}
};

// vertex struct
struct Vertex
{
	string city; 				// vertex city name
	bool visited; 				// visited or not
	vector<Edge> edgeList;		// edges
	int bfsLevel;
	Vertex() {					// vertex default constructor
		city = "";
		visited = false;
		bfsLevel = 0;
	}
};

// adjacency  list graph
class Graph {
public:
	Graph();							// graph default constructor
	~Graph();							// destructor
	bool empty();						// check if graph is empty
	int size();							// size of graph
	void insertVertex(string city);		// insert vertex (city)
	int findVertex(string city);		// find vertex (city)
	void insertEdge(string startCity, string endCity, int weight);	// add edge to vertex
	vector<string> vertices();										// vertex vector
	vector<string> edges();											// edges of vertex
	void bfsLabelEdges(vector<string> &backEdges, 		// edges (cross/disc/back)
					   vector<string> &discEdges,
					   vector<string> &crossEdges);
	int BFS(string startingCity, vector<string> &bfs);	// BFS

private:
	int verticesVisited();					// vertices that were visited
	int edgesDiscovered(int currVertex);	// determine edges
	vector<Vertex> graph;					// graph of vertices
	int dfsDistance;						// distance
	int BFSRecur(vector<string> &bfs, 		// BFS (levels)
				 vector<int> previousLevel,
				 int bfsLevel);
	string otherVertex(Edge currEdge, string startingCity);	// find other vertex
	int distance(Vertex * v1, Vertex * v2);					// distance between 2 vertices
};

// default constructor
Graph::Graph() {
	dfsDistance = 0;
}

// destructor
Graph::~Graph() {
}

// checks if graph is empty
bool Graph::empty() {
	return graph.empty();
}

// size of graph
int Graph::size() {
	return graph.size();
}

// vertex (city)
int Graph::findVertex(string city) {
	unsigned int index = 0;
	bool found = false;

	while(index < graph.size() && !found) {
		if(graph.at(index).city == city) {
			found = true;
		}
		else {
			index++;
		}
	}
	return index;
}

// add vertex
void Graph::insertVertex(string city) {
	if(findVertex(city) == graph.size()) {
		Vertex newVertex;

		newVertex.city = city;
		newVertex.visited = false;

		cout << newVertex.city << endl;

		graph.push_back(newVertex);
	}
}

// add edge to vertex
void Graph::insertEdge(string startCity, string endCity, int weight) {
	int index = findVertex(startCity);

	if(index == graph.size()) {
		insertVertex(startCity);

		insertEdge(startCity, endCity, weight);
	}
	else {
		Edge newEdge;

		newEdge.startCity = startCity;
		newEdge.endCity = endCity;
		newEdge.weight = weight;

		graph.at(index).edgeList.push_back(newEdge);
	}
}

// vertex vector
vector<string> Graph::vertices() {
	vector<string> cityNames;

	for(int i = 0; i < graph.size(); i++) {
		cityNames.push_back(graph[i].city);
	}

	return cityNames;
}

// edges of the vertex
vector<string> Graph::edges()
{
	vector<string> edgeList;

	for(int i = 0; i < graph.size(); i++) {
		if(graph.at(i).edgeList.size() != 0) {
			for(int j = 0; j < graph.at(i).edgeList.size(); j++) {
				edgeList.push_back("(" + graph.at(i).edgeList.at(j).startCity + ", "
									   + graph.at(i).edgeList.at(j).endCity + ")");
			}
		}
	}
	return edgeList;
}

// determine if edge is discovery, cross, or back edge
void Graph::bfsLabelEdges(vector<string> &backEdges, vector<string> &discEdges, vector<string> &crossEdges) {
    Edge * currEdge;
    string currString;

	for(int i = 0; i < graph.size(); i++) {
		for (int j=0; j<graph.at(i).edgeList.size(); j++) {
			currEdge = &graph.at(i).edgeList.at(j);
			currString = "(" + currEdge->startCity + ", " + currEdge->endCity + ")";
			if (currEdge->edgeType != 1) {
                if(graph.at(findVertex(currEdge->startCity)).bfsLevel > graph.at(findVertex(currEdge->endCity)).bfsLevel) {
                    currEdge->edgeType = 0;
                    backEdges.push_back(currString);
                }
                else {
                    currEdge->edgeType = 2;
                    crossEdges.push_back(currString);
                }
			}
			else {
                discEdges.push_back(currString);
			}
		}
	}
}

// Breadth First Search
int Graph::BFS(string startingCity, vector<string> &bfs) {
    // Reset the graph, this should be its own function
    for (int i=0; i<graph.size(); i++) {
        graph.at(i).visited = false;
        graph.at(i).bfsLevel = 0;
        for (int j=0; j< graph.at(i).edgeList.size(); j++) {
            graph.at(i).edgeList.at(j).edgeType = 1;
        }
    }
	int currVertex = findVertex(startingCity);

	graph.at(currVertex).visited = true;
	graph.at(currVertex).bfsLevel = 0;

	vector<int> newLevel;
	newLevel.push_back(currVertex);
	bfs.push_back(startingCity);

	return BFSRecur(bfs, newLevel, 0);
}

// Recursive BFS
int Graph::BFSRecur(vector<string> &bfs, vector<int> previousLevel, int bfsLevel) {
    vector<int> newLevel;
    vector<int> currLevel;
    int levelDistance = 0;

    vector<Edge> * currEdgeList;
    Vertex * startingVertex;
    Vertex * currVertex;
    int currVertexID;

    for (int i=0; i<previousLevel.size(); i++) {
        startingVertex = &graph.at(previousLevel.at(i));
        currEdgeList = &startingVertex->edgeList;

        for (int j=0; j<currEdgeList->size(); j++) {
            currVertexID = findVertex(currEdgeList->at(j).endCity);
            currVertex = &graph.at(currVertexID);
            if (!currVertex->visited) {
                levelDistance += currEdgeList->at(j).weight;

                currVertex->visited = true;
                currVertex->bfsLevel = bfsLevel;
                currEdgeList->at(j).edgeType = 1;

                bool inserted = false;
                for (int k=0; k<currLevel.size() && !inserted; k++) {
                    if (currEdgeList->at(j).weight < distance(startingVertex, &graph.at(currLevel.at(k)))) {
                        currLevel.insert(currLevel.begin()+k,currVertexID);
                        inserted = true;
                    }
                }
                if (!inserted) {
                    currLevel.push_back(findVertex(currVertex->city));
                }
            }
            else {
                currEdgeList->at(j).edgeType = 0;
            }
        }
        for (unsigned int m=0; m<currLevel.size(); m++) {
            bfs.push_back(graph.at(currLevel.at(m)).city);
        }

        newLevel.insert(newLevel.end(),currLevel.begin(),currLevel.end());
        currLevel.clear();
    }

    if (newLevel.size() > 0) {
        return levelDistance + BFSRecur(bfs, newLevel, bfsLevel+1);
    }
    else {
        return levelDistance;
    }
}

// Distance between two vertex
int Graph::distance(Vertex * v1, Vertex * v2) {
    // find connecting edge
    for (unsigned int i=0; i<v1->edgeList.size(); i++) {
        if (v1->edgeList.at(i).endCity == v2->city)
            return v1->edgeList.at(i).weight;
    }
    return -1;
}

// Find other vertex
string Graph::otherVertex(Edge currEdge, string startingCity) {
    if(currEdge.startCity == startingCity) {
        return currEdge.endCity;
    }
    else {
        return currEdge.startCity;
    }
}

// Determine how many vertices were visited
int Graph::verticesVisited() {
	int numVisited = 0;

	vector<Vertex>::iterator graphIt = graph.begin();

	while(graphIt != graph.end()) {
		if(graphIt->visited) {
			numVisited++;
		}
		graphIt++;
	}
	return numVisited;
}

// Edges discovered
int Graph::edgesDiscovered(int currVertex) {
	int numVisited = 0;

	for(int i = 0; i < graph.at(currVertex).edgeList.size(); i++) {
		if(graph.at(findVertex(graph.at(currVertex).edgeList.at(i).endCity)).visited) {
			numVisited++;
		}
	}

	return numVisited;
}

#endif /* GRAPH_H_ */
