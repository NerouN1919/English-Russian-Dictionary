#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"
#include "ForwardList.h"
#include "Errors.h"
namespace sviridenko
{
  void help(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void list(std::ostream& ostream, ForwardList< std::string >& words, BinarySearchTree< std::string,
    BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void find(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void search(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void clear(std::ostream& ostream, ForwardList< std::string >& words, BinarySearchTree< std::string,
    BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void searchWithTranslate(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void changeTranslation(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void print(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void deleteWord(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void insert(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void compare(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void merge(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void history(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
  void save(std::ostream& ostream, ForwardList< std::string >& words,
    BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
    char* arg, BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand);
}
