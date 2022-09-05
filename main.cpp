#include <fstream>
#include <string>
#include <Windows.h>
#include <functional>
#include "BinarySearchTree.h"
#include "ForwardList.h"
#include "Commands.h"
#include "Errors.h"
int main(int argc, char* argv[], std::ostream& ostream = std::cout)
{
  if (argc < 3)
  {
    std::cerr << "Incorrect argc\n";
    return 1;
  }
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  sviridenko::BinarySearchTree< int, sviridenko::ForwardList< std::string > > hist;
  int numberOfCommand = 1;
  sviridenko::BinarySearchTree< std::string,
    sviridenko::BinarySearchTree< std::string, sviridenko::ForwardList< std::string > > > listOfDIcts;
  std::string name = "";
  for (std::size_t i = 3; i != argc; i++)
  {
    std::ifstream fstream;
    std::string srcFile = argv[i];
    fstream.open(srcFile);
    if (!fstream.is_open())
    {
      std::cerr << "Incorrect argc\n";
      return 1;
    }
    sviridenko::BinarySearchTree< std::string, sviridenko::ForwardList< std::string > > tree;
    int counter = 1;
    while (!fstream.eof())
    {
      sviridenko::ForwardList< std::string > words;
      sviridenko::ForwardList< std::string > russian;
      std::string line = "";
      std::getline(fstream, line);
      if (counter == 1)
      {
        name = line;
        counter++;
        continue;
      }
      if (line == "")
      {
        std::cerr << "<EMPTY>\n";
      }
      else
      {
        if (line != "\0")
        {
          line += ' ';
          std::string temp = "";
          for (std::size_t i = 0; i < line.size(); i++)
          {
            if (line[i] == ' ')
            {
              words.pushBack(temp);
              temp = "";
            }
            else
            {
              temp += line[i];
            }
          }
        }
        std::string english = words.peekFront();
        words.dropFront();
        for (sviridenko::ForwardList< std::string >::Iterator it = words.begin(); it != words.end(); it++)
        {
          russian.pushBack(*it);
        }
        tree.insert(english, russian);
      }
    }
    fstream.close();
    listOfDIcts.insert(name, tree);
  }
  std::ifstream fstream;
  std::string srcFile = argv[2];
  fstream.open(srcFile);
  if (!fstream.is_open())
  {
    std::cerr << "Incorrect argc\n";
    return 1;
  }
  sviridenko::BinarySearchTree<std::string, sviridenko::ForwardList< std::string > > tree;
  while (!fstream.eof())
  {
    sviridenko::ForwardList< std::string > words;
    std::string line = "";
    std::getline(fstream, line);
    if (line == "")
    {
      std::cerr << "<EMPTY>\n";
    }
    else
    {
      if (line != "\0")
      {
        line += ' ';
        std::string temp = "";
        for (std::size_t i = 0; i < line.size(); i++)
        {
          if (line[i] == ' ')
          {
            words.pushBack(temp);
            temp = "";
          }
          else
          {
            temp += line[i];
          }
        }
      }
      if (words.peekFront() == "save_result")
      {
        sviridenko::save(ostream, words, listOfDIcts, argv[1], hist, numberOfCommand);
      }
      else if (words.peekFront() == "help")
      {
        sviridenko::help(ostream, words, hist, numberOfCommand);
      }
      else if (words.peekFront() == "history")
      {
        sviridenko::history(ostream, words, hist, numberOfCommand);
      }
      else
      {
        sviridenko::BinarySearchTree< std::string, void (*) (std::ostream& ostream,
          sviridenko::ForwardList< std::string >& words, sviridenko::BinarySearchTree< std::string,
          sviridenko::BinarySearchTree< std::string, sviridenko::ForwardList< std::string > > >& listOfDIcts,
          sviridenko::BinarySearchTree<int, sviridenko::ForwardList< std::string > >& hist,
          int& numberOfCommand) > commands;
        commands.insert("list", sviridenko::list);
        commands.insert("find", sviridenko::find);
        commands.insert("search", sviridenko::search);
        commands.insert("clear", sviridenko::clear);
        commands.insert("translate", sviridenko::searchWithTranslate);
        commands.insert("change_translation", sviridenko::changeTranslation);
        commands.insert("print", sviridenko::print);
        commands.insert("delete", sviridenko::deleteWord);
        commands.insert("insert", sviridenko::insert);
        commands.insert("compare", sviridenko::compare);
        commands.insert("merge", sviridenko::merge);
        if (commands.find(words.peekFront()) != commands.end())
        {
          commands.find(words.peekFront())->second(ostream, words, listOfDIcts, hist, numberOfCommand);
        }
        else
        {
          sviridenko::failedEnter(ostream);
        }
      }
    }
  }
}
