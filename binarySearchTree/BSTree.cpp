#include "BSTree.h"

using namespace std;

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream& operator<<(ostream& out, Node node)
{
  return out << "( " << node.value << ", " << node.search_time << " )";
}

istream& operator>>(istream& in, BSTree& tree)
{
  /*
    take input from the in stream, and build your tree
    input will look like
    4 
    2 
    6 
    1 
    3 
    5 
    7
  */
  int next;
  while(in >> next) 
    tree.insert(next);
  return in;
}

///////////// Implementation To Do ////////////////////

// copy constructor
BSTree::BSTree(const BSTree& other)
{
  size = other.get_size();
  root = other.root;
  copy_helper(root, other.root);
  /*
    complete this copy constructor
    make sure when copying nodes to copy
    the value and left and right children
  */
}

// move constructor
BSTree::BSTree(BSTree&& tree)
{
  size = tree.get_size();
  if(root == nullptr) {
    root = new Node();
    root->search_time = 1;
  }
  
  if(tree.root != nullptr) {
    root->value = tree.root->value;
    root->left = tree.root->left;
    root->right = tree.root->right;
    copy_helper(root, tree.root);
    tree.~BSTree();
  }
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
  size = other.get_size();
  /*
    complete this assignment operator
    make sure when copying nodes to copy
    the value
    and left and right children
    not important for this part but will be used later
  */
  if(&other != this) {
    root = other.root;
    copy_helper(root, other.root);
  }
  
  return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& tree)
{
    size = tree.get_size();
    
    if(&tree == this) {
       return *this;
    }
    
    if(root == nullptr) {
      root = new Node();
      root->search_time = 1;
    }
        
    if(tree.root != nullptr) {
        root->value = tree.root->value;
        root->left = tree.root->left;
        root->right = tree.root->right;
        copy_helper(root, tree.root);
        tree.~BSTree();
    }
        
    return *this;
}

void BSTree::destructHelp(Node *node) {
  if(node != nullptr) {
    if(node->left != nullptr) {
      destructHelp(node->left);
    }
    if(node->right != nullptr) {
      destructHelp(node->right);
    }
    delete node;

  }
}

// destructor
BSTree::~BSTree()
{
  size = 0;
  // use a helper function
  destructHelp(root);
  root = nullptr;
}
    
// recursive
void BSTree::copy_helper(Node* copy_to, const Node* copy_from) const
{
  if(copy_from == nullptr)
    return;

  if(copy_from->left != nullptr) {
    copy_to->left = new Node(*copy_from->left);
    copy_helper(copy_to->left, copy_from->left);
  } else {
    copy_to->left = nullptr;
  }

  if(copy_from->right != nullptr) {
    copy_to->right = new Node(*copy_from->right);
    copy_helper(copy_to->right, copy_from->right);
  } else {
    copy_to->right = nullptr;
  }
}

int sTime = 1;

Node* BSTree::insertHelp(int val, Node* & node) {
    if(node == nullptr) {
        size++;
        Node* newNode = new Node();
        newNode->value = val;
        newNode->search_time = sTime;
        node = newNode;
        sTime = 1;
        return newNode;
    }
    else {
        if(val < node->value) {
          sTime++;
          insertHelp(val, node->left);
        }
        else {
          sTime++;
          insertHelp(val, node->right);
        }
    }
}

Node* BSTree::insert(int obj)
{
  /*
    insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node 
  */
  Node* newNode = insertHelp(obj, root);
  return newNode;
}

Node* BSTree::searchHelp(int obj, Node* node) {
  if(node == nullptr) {
    return nullptr;
  }
  
  if(node->value == obj) {
    return node;
  }
  else {
    if(node->value < obj) {
      return searchHelp(obj, node->right);
    }
    else {
      return searchHelp(obj, node->left);
    }
  }
}

Node* BSTree::search(int obj)
{
  /*
    recursivly search down the tree to find the node that contains obj
    if you dont find anything return null
  */
  Node* searchNode = searchHelp(obj, root);
  return searchNode;
}

void BSTree::updateHelp(Node *node, int n) {
  if(node == nullptr) {
    return;
  }
  updateHelp(node->left, n+1);
  node->search_time=n;
  updateHelp(node->right, n+1);
}

void BSTree::update_search_times()
{
  updateHelp(root, 1);
}

void BSTree::infixHelp(Node* node, ostream& out) {
  if(node != nullptr) {
    infixHelp(node->left, out);
    pretty_print_node(out, node);
    infixHelp(node->right, out);
  }
}

ostream& BSTree::inorder(ostream& out)
{
  /*
    print your nodes in infix order
    if our tree looks like 

    4
    2 6
    1 3 5 7

    we should get

    1 2 3 4 5 6 7 
  */
  infixHelp(root, out);
  
  return out;
  
  
}

// implemented
void BSTree::pretty_print_node(ostream& out,Node* node)
{
  out << node->value << "["<<node->search_time<<"] ";
}

// implemented
ostream& BSTree::print_level_by_level(ostream& out)
{
  /*
    print the tree using a BFS 
    output should look like this if we dont have a full tree

    4
    2 6
    1 X 5 7
    X X X X X X X 9

    it will be helpfull to do this part iterativly, 
    so do the BFS with the std stack data structure.

    it may also be helpfull to put the entire tree into a vector 
    (probably google this if you dont know how to do it)
  */

  if(root == nullptr)
    return out;

  bool hasNodes = true;
  vector<Node*> current_level;
  vector<Node*> next_level;
  current_level.push_back(root);
  while(hasNodes) {
    hasNodes = false;
    for(auto node : current_level) {
      if(node != nullptr) {
	pretty_print_node(out, node);
	if(node->left != nullptr)
	  hasNodes = true;
	if(node->right != nullptr)
	  hasNodes = true;
	
	next_level.push_back(node->left);
	next_level.push_back(node->right);
      } else {
	out << "X ";
	next_level.push_back(nullptr);
	next_level.push_back(nullptr);
      }
    }
    out << endl;
    current_level.clear();
    current_level = next_level;
    next_level.clear();
  }

  return out;
}

// implemented
int BSTree::get_total_search_time(Node* node)
{
  if(node == nullptr)
    return 0;

  return get_total_search_time(node->left) +
    get_total_search_time(node->right) + node->search_time;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}
