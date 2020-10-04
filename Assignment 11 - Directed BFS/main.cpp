#include "Graph.h"
#include "strongGraph.h"

// Authors: Kenneth Casimiro, Mason Godrey
// Class Information: CS1D #14490

// Summary: ASSIGNMENT 11 PART B & C
//			This is the graph adjacency list data structure to be used
//          to store the distances between cities
//          It also does a BFS & DFS Search of the cities ( start: Atlanta)
//          USES ONLY DIRECTED EDGES
//          Determines which edges are discovery edges
//          Determine which edges are back edges
//          Does a total count of how much is traveled through disc edges
//			OUTPUT:
//			---------
//			Adds all vertices (cities)
//			BFS and outputs the order
// 			Determines the edges (discovery, back, and cross)
//			Outputs the total distance by disc edges
//          Determines if the graph has strong connectivity
//          - Normal DFS
//          - Reverse DFS (edges are reversed)

int main()
{
	Graph graphAdjList; // Graph object.

	cout << "Authors: Kenneth Casimiro, Mason Godrey" << endl;
	cout << "Class Information: CS1D #14490 Mon/Wed 5PM - 7:20PM" << endl << endl;
	cout << "Summary: This program does a BFS search of flights to 12 cities with weighted DIRECTED edges.\n"
	     << "         Using a graph with a adjacency list structure. BFS starts at Atlanta" << endl
		 << "         Program then checks the connectivity and determines if its strong or" << endl
		 << "         or not by doing a DFS search and then reverse its edges and DFS     " << endl
		 << "         search again and checks if all 12 cities were visited from the two."  << endl;

	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "Part B - BFS with a digraph" << endl;
	cout << "------------------------------------------------------" << endl;


	cout << "ADDING TO GRAPH/VERTICES " << endl;
	cout << "******************************************************" << endl;

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

    vector<string> bfs;

    cout << endl;

    cout << "Performing a BFS starting at Atlanta" << endl;
    cout << "******************************************************" << endl;
    int bfsDistance = graphAdjList.BFS("Atlanta",bfs);

    for(int i = 0; i < bfs.size(); i++) {
        cout << i+ 1 << ": " << bfs.at(i) << endl;
    }

    cout << endl;
    cout << "Total Distance (Discovery Edge): " << bfsDistance << endl;

    vector<string> bfsDiscEdges;
    vector<string> bfsBackEdges;
    vector<string> bfsCrossEdges;
    graphAdjList.bfsLabelEdges(bfsBackEdges,bfsDiscEdges,bfsCrossEdges);

    cout << endl;
    cout << "BFS DISCOVERY EDGES" << endl;
    cout << "******************************************************" << endl;
    for(int i = 0; i < bfsDiscEdges.size(); i++) {
        cout << bfsDiscEdges.at(i) << endl;
    }

    cout << endl;
    cout << "BFS BACK EDGES" << endl;
    cout << "******************************************************" << endl;
    for(int i = 0; i < bfsBackEdges.size(); i++) {
        cout << bfsBackEdges.at(i) << endl;
    }

    cout << endl;
    cout << "BFS CROSS EDGES" << endl;
    cout << "******************************************************" << endl;
    for(int i = 0; i < bfsCrossEdges.size(); i++) {
        cout << bfsCrossEdges.at(i) << endl;
    }

    cout << endl;
	cout << "------------------------------------------------------" << endl;
    cout << "PART C - Strong Connectivity" << endl;
	cout << "------------------------------------------------------" << endl;

	strongGraph test; // Graph object.

	cout << "ADDING TO GRAPH/VERTICES " << endl;
	cout << "****************************" << endl;

	// SEATTLE
	test.insertEdge("Seattle", "San Francisco", 807);
	test.insertEdge("Seattle", "Denver", 1331);

	// SAN FRANCISCO
	test.insertEdge("San Francisco", "Los Angeles", 381);

	// LOS ANGELES
	test.insertEdge("Los Angeles", "Denver", 1015);

	// DALLAS
	test.insertEdge("Dallas", "Los Angeles", 1435);
	test.insertEdge("Dallas", "Kansas City", 496);
	test.insertEdge("Dallas", "Atlanta", 781);

	// HOUSTON
	test.insertEdge("Houston", "Dallas", 239);
	test.insertEdge("Houston", "Atlanta", 810);

	// MIAMI
	test.insertEdge("Miami", "Houston", 1187);

	// ATLANTA
	test.insertEdge("Atlanta", "Miami", 661);

	// NEW YORK
	test.insertEdge("New York", "Atlanta", 888);
	test.insertEdge("New York", "Chicago", 787);

	// BOSTON
	test.insertEdge("Boston", "New York", 214);

	// CHICAGO
	test.insertEdge("Chicago", "Boston", 983);
	test.insertEdge("Chicago", "Seattle", 2097);

	// DENVER
	test.insertEdge("Denver", "San Francisco", 1267);
	test.insertEdge("Denver", "Chicago", 1003);

	// KANSAS CITY
	test.insertEdge("Kansas City", "Chicago", 533);
	test.insertEdge("Kansas City", "Denver", 599);
	test.insertEdge("Kansas City", "Los Angeles", 1663);
	test.insertEdge("Kansas City", "Atlanta", 864);
	test.insertEdge("Kansas City", "New York", 1260);

	// city name (vector string)
	vector<string> searchDFS;

	cout << endl;
	cout << "DFS - STARTING AT ATLANTA";
	cout << endl;
	cout << "****************************" << endl;

	// DFS search + calculate total distance traveled (discovery edges)
	int totalDistance = test.DFS("Atlanta", searchDFS);

	for(int i = 0; i < searchDFS.size(); i++) {
		cout << searchDFS.at(i) << endl;
	}

	cout << endl;
	cout << "REVERSE DFS - STARTING AT ATLANTA";
	cout << endl;
	cout << "****************************" << endl;

	strongGraph reverseTest; // Graph object.

	cout << "ADDING TO GRAPH/VERTICES " << endl;
	cout << "****************************" << endl;

	// SEATTLE - REVERSED
	reverseTest.insertEdge("Seattle", "Chicago", 2097);

	// SAN FRANCISCO - REVERSED
	reverseTest.insertEdge("San Francisco", "Seattle", 807);
	reverseTest.insertEdge("San Francisco", "Denver", 1267);

	// LOS ANGELES - REVERSED
	reverseTest.insertEdge("Los Angeles", "San Francisco", 381);
	reverseTest.insertEdge("Los Angeles", "Kansas City", 1663);
	reverseTest.insertEdge("Los Angeles", "Dallas", 1435);

	// DALLAS - REVERSED
	reverseTest.insertEdge("Dallas", "Houston", 239);

	// HOUSTON - REVERSED
	reverseTest.insertEdge("Houston", "Miami", 1187);

	// MIAMI - REVERSED
	reverseTest.insertEdge("Miami", "Atlanta", 661);

	// ATLANTA - REVERSED
	reverseTest.insertEdge("Atlanta", "Houston", 810);
	reverseTest.insertEdge("Atlanta", "Dallas", 781);
	reverseTest.insertEdge("Atlanta", "Kansas City", 864);
	reverseTest.insertEdge("Atlanta", "New York", 888);

	// NEW YORK - REVERSED
	reverseTest.insertEdge("New York", "Boston", 214);
	reverseTest.insertEdge("New York", "Kansas City", 864);

	// BOSTON - REVERSED
	reverseTest.insertEdge("Boston", "Chicago", 983);

	// CHICAGO - REVERSED
	reverseTest.insertEdge("Chicago", "New York", 787);
	reverseTest.insertEdge("Chicago", "Kansas City", 533);
	reverseTest.insertEdge("Chicago", "Denver", 1003);


	// DENVER - REVERSED
	reverseTest.insertEdge("Denver", "Seattle", 1331);
	reverseTest.insertEdge("Denver", "Los Angeles", 1015);
	reverseTest.insertEdge("Denver", "Kansas City", 599);

	// KANSAS CITY - REVERSED
	reverseTest.insertEdge("Kansas City", "Dallas", 496);


	vector<string> searchDFS2;

	cout << endl;
	cout << "DFS - STARTING AT ATLANTA";
	cout << endl;
	cout << "****************************" << endl;

	// DFS search + calculate total distance traveled (discovery edges)
	int totalDistance2 = reverseTest.DFS("Atlanta", searchDFS2);

	for(int i = 0; i < searchDFS2.size(); i++) {
		cout << searchDFS2.at(i) << endl;
	}


	cout << endl;


	cout << "TOTAL VISITED (DFS): " << test.size() << endl;
	cout << "TOTAL VISITED (REVERSE DFS): " << reverseTest.size() << endl;

	if(test.size() == reverseTest.size()) {
		cout << "Graph is strongly connected: When the edge directions are\n"
		                "reversed the DFS can still visit all vertices.";
	} else {
        cout << "Graph is not strongly connected: When the edge directions are"
                "reversed the DFS did not visit all vertices.";
	}

    return 0;
}


