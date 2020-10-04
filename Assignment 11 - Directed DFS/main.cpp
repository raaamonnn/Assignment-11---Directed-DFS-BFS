#include "graph.h"

// Authors: Kenneth Casimiro, Thea Knasiak
// Class Information: CS1D #14490

// Summary: ASSIGNMENT 11 PART A
//          Modified Assignment 10 Part A to only have directed edges
//			Adds all the city vertices/nodes (DIRECTED EDGES ONLY)
//          12 cities in total.
//          Does the DFS search and output/display it
//          Display the discovery edges
//          Display the back edges
//          Output the total distance of the discovery edges
// 			MODIFICATION - USE ONLY DIRECTED EDGES

int main() {

	Graph graphAdjList; // Graph object.

	cout << "Authors: Kenneth Casimiro, Thea Knasiak" << endl;
	cout << "Class Information: CS1D #14490 Mon/Wed 5PM - 7:20PM" << endl;
	cout << "Summary: This program does a DFS search of flights to 12 cities with weighted DIRECTED edges.\n"
	     << "         Using a graph with a adjacency list structure. DFS starts at Atlanta" << endl << endl;

	cout << "PART A";
	cout << endl << endl;

	cout << "ADDING TO GRAPH/VERTICES " << endl;
	cout << "****************************" << endl;

	// SEATTLE
	graphAdjList.insertEdge("Seattle", "San Francisco", 807);
	graphAdjList.insertEdge("Seattle", "Denver", 1331);

	// SAN FRANCISCO
	graphAdjList.insertEdge("San Francisco", "Los Angeles", 381);

	// LOS ANGELES
	graphAdjList.insertEdge("Los Angeles", "Denver", 1015);

	// DALLAS
	graphAdjList.insertEdge("Dallas", "Los Angeles", 1435);
	graphAdjList.insertEdge("Dallas", "Kansas City", 496);
	graphAdjList.insertEdge("Dallas", "Atlanta", 781);

	// HOUSTON
	graphAdjList.insertEdge("Houston", "Dallas", 239);
	graphAdjList.insertEdge("Houston", "Atlanta", 810);

	// MIAMI
	graphAdjList.insertEdge("Miami", "Houston", 1187);

	// ATLANTA
	graphAdjList.insertEdge("Atlanta", "Miami", 661);

	// NEW YORK
	graphAdjList.insertEdge("New York", "Atlanta", 888);
	graphAdjList.insertEdge("New York", "Chicago", 787);

	// BOSTON
	graphAdjList.insertEdge("Boston", "New York", 214);

	// CHICAGO
	graphAdjList.insertEdge("Chicago", "Boston", 983);
	graphAdjList.insertEdge("Chicago", "Seattle", 2097);

	// DENVER
	graphAdjList.insertEdge("Denver", "San Francisco", 1267);
	graphAdjList.insertEdge("Denver", "Chicago", 1003);

	// KANSAS CITY
	graphAdjList.insertEdge("Kansas City", "Chicago", 533);
	graphAdjList.insertEdge("Kansas City", "Denver", 599);
	graphAdjList.insertEdge("Kansas City", "Los Angeles", 1663);
	graphAdjList.insertEdge("Kansas City", "Atlanta", 864);
	graphAdjList.insertEdge("Kansas City", "New York", 1260);

	// city name (vector string)
	vector<string> searchDFS;

	cout << endl;
	cout << "DFS - STARTING AT ATLANTA";
	cout << endl;
	cout << "****************************" << endl;

	// DFS search + calculate total distance traveled (discovery edges)
	int totalDistance = graphAdjList.DFS("Atlanta", searchDFS);

	for(unsigned int i = 0; i < searchDFS.size(); i++)
	{
		cout << searchDFS.at(i) << endl;
	}

	cout << endl;

	// discovery edges
	vector<string> discEdge = graphAdjList.getDiscoveryEdges(searchDFS);

	cout << endl;
	cout << "DFS DISCOVERY EDGES";
	cout << endl;
	cout << "****************************" << endl;
	for(unsigned int i = 0; i < discEdge.size(); i++)
	{
		cout << discEdge.at(i) << endl;
	}

	// back edges
	vector<string> backEdge = graphAdjList.getBackEdges(searchDFS);

	cout << endl;
	cout << "DFS BACK EDGES";
	cout << endl;
	cout << "****************************" << endl;
	for(unsigned int i = 0; i < backEdge.size(); i++)
	{
		cout << backEdge.at(i) << endl;
	}

	// total distance from discovery edges
	cout << endl;
	cout << "Total Distance Traveled by Discovery Edges: " << totalDistance << endl;


	return 0;
}
