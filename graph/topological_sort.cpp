// topological sort

#include <iostream>
#include <queue>
#include "graph.h"

using namespace std;


void Graph::compute_indegree()
{
  for(int i = 0; i < node_list.size(); i++) {
    node_list[i].indegree = 0;
  }
  
  for(int i = 0; i < adj_list.size(); i++) {
    for(auto it = adj_list[i]->begin(); it != adj_list[i]->end(); ++it) {
        node_list[(*it)-1].indegree++;
    }
  }

}

void Graph::topological_sort()
{
  // to be implemented
  queue<int> q;
  int counter = 0;
  
  for(int i = 0; i < node_list.size(); i++) {
    if(node_list[i].indegree == 0) {
      q.push(node_list[i].label);
    }
  }
  
  while(!q.empty()) {
     int current_label = q.front();
     q.pop();
     node_list[current_label - 1].top_num = ++counter;
     
     for(auto it = adj_list[current_label - 1]->begin(); it != adj_list[current_label -1]->end(); ++it) {
       if(--(node_list[(*it)-1].indegree) == 0) {
         //cout << "Pushing " << node_list[(*it)-1].label << "to the queue" << endl;
         q.push(node_list[(*it)-1].label);
         
       }
     }
  }
  
  if(counter != node_list.size()) {
    throw CycleFoundException();
  }
  
  compute_indegree();
}

void Graph::print_top_sort()
{
  cout << "Graph printed in topological order: " << endl;
  for(int j = 0; j <= node_list.size() + 1; j++) {
    for(int i = 0; i < node_list.size(); i++) {
      if(node_list[i].top_num == j) {
        cout << node_list[i].label << endl;
      }
    }
  }
}
