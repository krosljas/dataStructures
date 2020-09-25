#include <iostream>
#include <fstream>
#include "BSTree.h"

using namespace std;


BSTree read_file(string file_name)
{
  /*
    open the file and use the input operator (operator>>)
    to construct a new tree
  */
    
  BSTree new_tree;
  ifstream infile(file_name); 
  // use >> to read in to new_tree
  infile >> new_tree;
  return new_tree;
}

void write_file(string file_name, BSTree& printTree) {
  ofstream outfile(file_name);
  printTree.inorder(outfile);
  outfile.close();
  outfile.flush();
}


int main()
{
  
  for(int i = 1; i <= 12; i++) {
    string dir= "data-files/"+std::to_string(i);
    string output = "output-files/"+std::to_string(i);
    
    BSTree l = read_file(dir+"l");
    cout << "average search time linear " << i << " " << l.get_average_search_time() << endl;
    if(l.get_size() <= 16) {
      l.inorder(cout);
    }
    cout << "Size: " << l.get_size() << endl;
    write_file(output+"l", l);
    
    
    BSTree p = read_file(dir+"p");
    cout << "average search time perfect "<< i << " " << p.get_average_search_time() << endl;
    if(p.get_size() <= 16) {
      p.inorder(cout);
      cout << endl;
    }
    write_file(output+"p", p);
    
    
    BSTree r = read_file(dir+"r");
    cout << "average search time random "<< i << " " << r.get_average_search_time() << endl;
    if(r.get_size() <= 16) {
      r.inorder(cout);
      cout << endl;
    }
    write_file(output+"r", r);

    if(i <= 4) {
      cout << "Size: " << p.get_size() << endl;
      cout << "perfect tree " << i << endl << p;
    }

    cout << endl;
    
  }
    
}