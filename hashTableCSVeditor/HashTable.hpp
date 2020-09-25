#pragma once
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <list>
#include <iterator>
#include <utility>
#include <iostream>

using namespace std;

template<typename T>
class HashTable {
private:
	int size;
	//IMPLEMENT	
	vector< list< pair<const int, T> > > table;
	//Vector of linked lists, list nodes are key-value pairs
	
    int hash(const int _key) {
        return _key % size;
    }
public:
    HashTable(const int _size) {
		//IMPLEMENT
		size = _size;
		table.resize(size);
    }
	
	~HashTable(){
		table.erase(table.begin(), table.end());
		size = 0;
	}
    
    void insert(const int _key, T _value) {
		//IMPLEMENT
		int h = hash(_key);
		pair <const int, T> new_pair(_key, _value);
		table[h].push_back(new_pair);
    }
	
	int minChainLen(){
		int currentMin = 100;
		typename list<pair<const int, T>>::iterator it;
		//IMPLEMENT
		for(int i = 0; i < table.size(); i++) {
			int temp = 0;
			for(it = table[i].begin(); it != table[i].end(); ++it) {
				temp++;
			}
			if (temp < currentMin) {
				currentMin = temp;
			}
		}
		return currentMin;
	}
	
	int maxChainLen(){
		int currentMax = 0;
		typename list<pair<const int, T>>::iterator it;
		//IMPLEMENT
		for(int i = 0; i < table.size(); i++) {
			int temp = 0;
			for(it = table[i].begin(); it != table[i].end(); ++it) {
				temp++;
			}
			if (temp > currentMax) {
				currentMax = temp;
			}
		}
		return currentMax;
	}
	
	double averageChainLen(){
		double total = 0;
		typename list<pair<const int, T>>::iterator it;
		//IMPLEMENT
		for(int i = 0; i < table.size(); i++) {
			for(it = table[i].begin(); it != table[i].end(); ++it) {
				total++;
			}
		}
		return (total / size);
	}
    
    T* search(int _key) {
		//IMPLEMENT
		T* val = nullptr;
		int h_index = hash(_key);
		
		
		typename list<pair<const int, T>>::iterator it;
		for(it = table[h_index].begin(); it != table[h_index].end(); ++it) {
			if(it->first == _key) {
				val = &(it->second);
			}
		}
		
		return val;
    }
    
    void print_table() {
    	typename list<pair<const int, T>>::iterator it;
		//IMPLEMENT
		for(int i = 0; i < table.size(); i++) {
			cout << "Index " << i << " : ";
			for(it = table[i].begin(); it != table[i].end(); ++it) {
				cout << it->first << ", " << it->second << " -> ";
			}
			cout << endl;
		}
    }
    
};

#endif