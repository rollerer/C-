#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <set>
#include <fstream>
#include <map>
using namespace std;

struct Node {
  int Id;
  std::string autor;
  std::string name ;
  Node *parentNode;
  Node *leftNode;
  Node *rightNode;
  int NodeColor;
};

typedef Node *NodePtr;

class REDBLACKTREE {
 private:
  NodePtr root;
  NodePtr TNULL;
  

  void INITIALIZENULLNode(NodePtr node, NodePtr parentNode) {
    node->Id = 0;
    node->autor = "None";
    node->name = "None";
    node->parentNode = parentNode;
    node->leftNode = nullptr;
    node->rightNode = nullptr;
    node->NodeColor = 0;
  }

  // The Preorder
  void PREORDERHELPER(NodePtr node) {
    if (node != TNULL) {
      cout << node->Id << " ";
      PREORDERHELPER(node->leftNode);
      PREORDERHELPER(node->rightNode);
    }
  }

  // The Inorder
  void INORDERHELPER(NodePtr node) {
    if (node != TNULL) {
      INORDERHELPER(node->leftNode);
      cout << node->Id << " ";
      INORDERHELPER(node->rightNode);
    }
  }

  // the Post order
  void POSTORDERHELPER(NodePtr node) {
    if (node != TNULL) {
      POSTORDERHELPER(node->leftNode);
      POSTORDERHELPER(node->rightNode);
      cout << node->Id << " ";
    }
  }

  NodePtr SEARCHTREEHELPER(NodePtr node, std::string name) {
    if (node == TNULL || name == node->name) {
      return node;
    }

    if (name < node->name) {
      return SEARCHTREEHELPER(node->leftNode, name);
    }
    return SEARCHTREEHELPER(node->rightNode, name);
  }

  // For balancing the tree after deletion
  void DELETEFIX(NodePtr x) {
    NodePtr s;
    while (x != root && x->NodeColor == 0) {
      if (x == x->parentNode->leftNode) {
        s = x->parentNode->rightNode;
        if (s->NodeColor == 1) {
          s->NodeColor = 0;
          x->parentNode->NodeColor = 1;
          LEFTROTATE(x->parentNode);
          s = x->parentNode->rightNode;
        }

        if (s->leftNode->NodeColor == 0 && s->rightNode->NodeColor == 0) {
          s->NodeColor = 1;
          x = x->parentNode;
        } else {
          if (s->rightNode->NodeColor == 0) {
            s->leftNode->NodeColor = 0;
            s->NodeColor = 1;
            RIGHTNODEROTATE(s);
            s = x->parentNode->rightNode;
          }

          s->NodeColor = x->parentNode->NodeColor;
          x->parentNode->NodeColor = 0;
          s->rightNode->NodeColor = 0;
          LEFTROTATE(x->parentNode);
          x = root;
        }
      } else {
        s = x->parentNode->leftNode;
        if (s->NodeColor == 1) {
          s->NodeColor = 0;
          x->parentNode->NodeColor = 1;
          RIGHTNODEROTATE(x->parentNode);
          s = x->parentNode->leftNode;
        }

        if (s->rightNode->NodeColor == 0 && s->rightNode->NodeColor == 0) {
          s->NodeColor = 1;
          x = x->parentNode;
        } else {
          if (s->leftNode->NodeColor == 0) {
            s->rightNode->NodeColor = 0;
            s->NodeColor = 1;
            LEFTROTATE(s);
            s = x->parentNode->leftNode;
          }

          s->NodeColor = x->parentNode->NodeColor;
          x->parentNode->NodeColor = 0;
          s->leftNode->NodeColor = 0;
          RIGHTNODEROTATE(x->parentNode);
          x = root;
        }
      }
    }
    x->NodeColor = 0;
  }

  void RBTRANSPLANT(NodePtr u, NodePtr v) {
    if (u->parentNode == nullptr) {
      root = v;
    } else if (u == u->parentNode->leftNode) {
      u->parentNode->leftNode = v;
    } else {
      u->parentNode->rightNode = v;
    }
    v->parentNode = u->parentNode;
  }

  void DELETENODEHELPER(NodePtr node, std::string name) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->name == name) {
        z = node;
      }

      if (node->name <= name) {
        node = node->rightNode;
      } else {
        node = node->leftNode;
      }
    }

    if (z == TNULL) {
      cout << "The Key is not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_NodeColor = y->NodeColor;
    if (z->leftNode == TNULL) {
      x = z->rightNode;
      RBTRANSPLANT(z, z->rightNode);
    } else if (z->rightNode == TNULL) {
      x = z->leftNode;
      RBTRANSPLANT(z, z->leftNode);
    } else {
      y = minimum(z->rightNode);
      y_original_NodeColor = y->NodeColor;
      x = y->rightNode;
      if (y->parentNode == z) {
        x->parentNode = y;
      } else {
        RBTRANSPLANT(y, y->rightNode);
        y->rightNode = z->rightNode;
        y->rightNode->parentNode = y;
      }

      RBTRANSPLANT(z, y);
      y->leftNode = z->leftNode;
      y->leftNode->parentNode = y;
      y->NodeColor = z->NodeColor;
    }
    delete z;
    size--;
    if (y_original_NodeColor == 0) {
      DELETEFIX(x);
    }
  }

  // balance the tree after insertion
  void INSERTFIX(NodePtr k) {
    NodePtr u;
    while (k->parentNode->NodeColor == 1) {
      if (k->parentNode == k->parentNode->parentNode->rightNode) {
        u = k->parentNode->parentNode->leftNode;
        if (u->NodeColor == 1) {
          u->NodeColor = 0;
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          k = k->parentNode->parentNode;
        } else {
          if (k == k->parentNode->leftNode) {
            k = k->parentNode;
            RIGHTNODEROTATE(k);
          }
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          LEFTROTATE(k->parentNode->parentNode);
        }
      } else {
        u = k->parentNode->parentNode->rightNode;

        if (u->NodeColor == 1) {
          u->NodeColor = 0;
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          k = k->parentNode->parentNode;
        } else {
          if (k == k->parentNode->rightNode) {
            k = k->parentNode;
            LEFTROTATE(k);
          }
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          RIGHTNODEROTATE(k->parentNode->parentNode);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->NodeColor = 0;
  }

  void PRINTHELPER(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R-----";
        indent += "    ";
      } else {
        cout << "L-----";
        indent += "|   ";
      }

      string sNodeColor = root->NodeColor ? "RED" : "BLACK";
      cout << root->Id<< " Name: " << root->name<< " Autor: " << root->autor << "(" << sNodeColor << ")" << endl;
      PRINTHELPER(root->leftNode, indent, false);
      PRINTHELPER(root->rightNode, indent, true);
    }
  }

 public:
 int size=0;

  REDBLACKTREE() {
    TNULL = new Node;
    TNULL->NodeColor = 0;
    TNULL->leftNode = nullptr;
    TNULL->rightNode = nullptr;
    root = TNULL;
  }

  void preorder() { PREORDERHELPER(this->root); }

  void inorder() { INORDERHELPER(this->root); }

  void postorder() { POSTORDERHELPER(this->root); }

  NodePtr searchTree(std::string k) { return SEARCHTREEHELPER(this->root, k); }

  NodePtr minimum(NodePtr node) {
    while (node->leftNode != TNULL) {
      node = node->leftNode;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->rightNode != TNULL) {
      node = node->rightNode;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->rightNode != TNULL) {
      return minimum(x->rightNode);
    }

    NodePtr y = x->parentNode;
    while (y != TNULL && x == y->rightNode) {
      x = y;
      y = y->parentNode;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->leftNode != TNULL) {
      return maximum(x->leftNode);
    }

    NodePtr y = x->parentNode;
    while (y != TNULL && x == y->leftNode) {
      x = y;
      y = y->parentNode;
    }

    return y;
  }

  void LEFTROTATE(NodePtr x) {
    NodePtr y = x->rightNode;
    x->rightNode = y->leftNode;
    if (y->leftNode != TNULL) {
      y->leftNode->parentNode = x;
    }
    y->parentNode = x->parentNode;
    if (x->parentNode == nullptr) {
      this->root = y;
    } else if (x == x->parentNode->leftNode) {
      x->parentNode->leftNode = y;
    } else {
      x->parentNode->rightNode = y;
    }
    y->leftNode = x;
    x->parentNode = y;
  }

  void RIGHTNODEROTATE(NodePtr x) {
    NodePtr y = x->leftNode;
    x->leftNode = y->rightNode;
    if (y->rightNode != TNULL) {
      y->rightNode->parentNode = x;
    }
    y->parentNode = x->parentNode;
    if (x->parentNode == nullptr) {
      this->root = y;
    } else if (x == x->parentNode->rightNode) {
      x->parentNode->rightNode = y;
    } else {
      x->parentNode->leftNode = y;
    }
    y->rightNode = x;
    x->parentNode = y;
  }

  // Inserting a node
  void INSERTNODE(int key, std::string autor, std::string name) {
    NodePtr node = new Node;
    node->parentNode = nullptr;
    node->Id = key;
    node->autor = autor;
    node->name = name;
    node->leftNode = TNULL;
    node->rightNode = TNULL;
    node->NodeColor = 1;
    size++;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->name < x->name) {
        x = x->leftNode;
      } else {
        x = x->rightNode;
      }
    }

    node->parentNode = y;
    if (y == nullptr) {
      root = node;
    } else if (node->name < y->name) {
      y->leftNode = node;
    } else {
      y->rightNode = node;
    }

    if (node->parentNode == nullptr) {
      node->NodeColor = 0;
      return;
    }

    if (node->parentNode->parentNode == nullptr) {
      return;
    }

    INSERTFIX(node);
  }

  NodePtr getRoot() { return this->root; }

  void DELETENODE(std::string NodeData) { DELETENODEHELPER(this->root, NodeData); }


  void printTree() {
    if (root) {
      PRINTHELPER(this->root, "", true);
    }
  }


  
  void writeTree()
  {
    
    if(root)
    {   
      std::ofstream out_file("Librarry.txt");
      NodePtr x = root;
      NodePtr y;
      std::set<int> ids = {};
      std::set<std::string> d;
      while(ids.size()< size)
      {   
          while(x!=TNULL)
          {
              y = x;
              x = x->leftNode;
          }
          if(y!= root)
          {
            while(ids.find(y->Id) != ids.end())
            {
              y = y->parentNode;
            }    
            out_file<<"Id: "<<y->Id<< "; Name: "<<y->name<<"; Autor: "<<y->autor<<'\n';
            ids.emplace(y->Id);
            x = y->rightNode;
          }
      }
      out_file.close();
    }
    
  }
};

int main() {
    int ind;
    
    std::string name;
    std::string autor;
    REDBLACKTREE LIBRARRY;
    std::map<std::string, std::string> map;

    std::vector<std::string> alphabet = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    std::vector<std::string> Alphabet = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> let(0, alphabet.size()-1);
    std::uniform_int_distribution<int> word(3, 10);
    int size = 10000;
    for (int i = 0; i < size; i++) 
    {   
        name = Alphabet[let(gen)];
        autor = Alphabet[let(gen)];
        for(int j = 0; j < word(gen); j++)
        {
            name += alphabet[let(gen)];
        }
        for(int j = 0; j < word(gen); j++)
        {
            autor += alphabet[let(gen)];
        }
        LIBRARRY.INSERTNODE(i, autor, name);
        map[name] = autor;
    }
    LIBRARRY.writeTree();

    auto start_tree_i = std::chrono::high_resolution_clock::now();
    LIBRARRY.INSERTNODE(10001, "Mdsfd", "Klikli");
    auto end_tree_i = std::chrono::high_resolution_clock::now();
    auto duration_tree_i = std::chrono::duration_cast<std::chrono::microseconds>(end_tree_i - start_tree_i);

    auto start_tree_f = std::chrono::high_resolution_clock::now();
    LIBRARRY.searchTree("Klikli");
    auto end_tree_f = std::chrono::high_resolution_clock::now();
    auto duration_tree_f = std::chrono::duration_cast<std::chrono::microseconds>(end_tree_f - start_tree_f);

    auto start_map_i = std::chrono::high_resolution_clock::now();
    map["Klikli"] = "Mdsfd";
    auto end_map_i = std::chrono::high_resolution_clock::now();
    auto duration_map_i = std::chrono::duration_cast<std::chrono::microseconds>(end_map_i - start_map_i);

    auto start_map_f = std::chrono::high_resolution_clock::now();
    map.find("Klikli");
    auto end_map_f = std::chrono::high_resolution_clock::now();
    auto duration_map_f = std::chrono::duration_cast<std::chrono::microseconds>(end_map_f - start_map_f);

    std::cout<<"Tree insert: "<<duration_tree_i.count() <<"; Tree find: "<<duration_tree_f.count()<<'\n';
    std::cout<<"Map insert: "<<duration_map_i.count()<<"; Map find: "<<duration_map_f.count()<<'\n';

}