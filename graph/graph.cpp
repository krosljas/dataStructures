#include "graph.h"
#include <sstream>
#include <iostream>

using namespace std;

// to be implemented



Graph::~Graph() {
    node_list.erase(node_list.begin(), node_list.end());
    adj_list.erase(adj_list.begin(), adj_list.end());
}

void Graph::buildGraph(ifstream &input) {
    string str;
    
    while(getline(input, str)) {
        istringstream ss(str);
        int label;
        ss >> label;
        Vertex node(label, 0);
        node_list.push_back(node);
        list<int> * adjList = new list<int>;
        while(ss >> label) {
            if(label != -1) {
                adjList->push_back(label);
            }
        }
        adj_list.push_back(adjList);
            
    }
    
}

void Graph::displayGraph() {
    cout << "Printing graph: " << endl;
    for(int i = 0; i < node_list.size(); i++) {
        cout << node_list[i].label << " : ";
        for(auto it = adj_list[i]->begin(); it != adj_list[i]->end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
    }
}


