#include "CSVEditor.hpp"
#include <fstream>
#include <typeinfo>

CSVEditor::CSVEditor(string& inputPath, string& rosterPath, string& outputPath, regex expr, int m) {
    //IMPLEMENT
    input.open(inputPath);
    roster.open(rosterPath);
    output.open(outputPath);
    regexPattern = expr;
    hashTable = new HashTable<string>(m);
}

CSVEditor::~CSVEditor(){
	//IMPLEMENT
	input.close();
	roster.close();
	output.close();
	regexPattern = "";
	(*hashTable).~HashTable();
}

void CSVEditor::readCSVToTable() {
	//IMPLEMENT
	smatch matches;
	string str;
	while(getline(input, str)) {
	    regex_search(str, matches, regexPattern);
	    //cout << matches[1] << " -> " << matches[2] << endl;
        hashTable->insert(std::stoi(matches.str(1)), matches.str(2));
	}
	
}

void CSVEditor::writeCSVToFile() {
	//IMPLEMENT  
	smatch matches;
	string str;
	while(getline(roster, str)) {
		regex_search(str, matches, regexPattern);
		output << matches.str(0);
		if(hashTable->search(std::stoi(matches.str(1)))) {
			output << *(hashTable->search(std::stoi(matches.str(1)))) << endl;
		}
		else {
			output << endl;
		}
		
	}
}

std::tuple<int, int, double> CSVEditor::getStats(){
	//IMPLEMENT
	int minChain = hashTable->minChainLen();
	int maxChain = hashTable->maxChainLen();
	double avgChain = hashTable->averageChainLen();
	
	return std::make_tuple(minChain, maxChain, avgChain);
}

void CSVEditor::print() {
    hashTable->print_table();
}