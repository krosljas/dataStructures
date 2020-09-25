#include <string>
#include <regex>

#include "HashTable.hpp"
#include "CSVEditor.hpp"
#include "CSVEditor.cpp"

int main() {
    
    HashTable<int> h(3);
    h.insert(3, 1);
    h.insert(4, 2);
    h.insert(5, 3);
    h.insert(6, 11);
    h.print_table();
    
    cout << "Max chain length: " << h.maxChainLen() << endl;
    cout << "Avg chain length: " << h.averageChainLen() << endl;
    cout << "Min chain length: " << h.minChainLen() << endl;
    
    cout << "The value of the node with key 6 is " << *(h.search(6)) << endl;
    
    h.~HashTable();
    h.print_table();
    
    /*
    regex expr(".*,.*,(.*),(.*)");
	
    string inputPath = "./input.csv";
    string rosterPath = "./roster.csv";
    string outputPath = "./output.csv";
	
	int m = 100; 
	
	//OBTAIN M HERE

    CSVEditor editor(inputPath, rosterPath, outputPath, expr, m);
    editor.readCSVToTable();
    editor.print();
    editor.writeCSVToFile();
    
    std::tuple<int, int, double> stats = editor.getStats();
	
	cout << "minimum chain len = " << std::get<0>(stats) << endl;
	cout << "maximum chain len = " << std::get<1>(stats) << endl;
	cout << "average chain len = " << std::get<2>(stats) << endl;
    */
    
}