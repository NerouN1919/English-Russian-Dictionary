#include "Commands.h"
void sviridenko::help(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  if (words.size() != 1)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  ostream << "list - вывод списка словарей\n";
  ostream << "clear {нужный словарь} - очистка словаря\n";
  ostream << "translate {слово} - перевести слово\n";
  ostream << "find {словарь} {слово} - присутствует ли слово в словаре?\n";
  ostream << "search {слово} - поиск словарей, в которых обнаружено слово\n";
  ostream << "change_translation {словарь} {слово} {новый перевод} - замена перевода слова в определенном словаре\n";
  ostream << "print {словарь} - вывести содержимое словаря\n";
  ostream << "delete {словарь} {слово} - удалить слово из словаря\n";
  ostream << "insert {словарь} {слово} {перевод} - добавить новое слово в словарь\n";
  ostream << "compare {первый словарь} {второй словарь} - сравнить первый словарь со вторым\n";
  ostream << "merge {первый словарь} {второй словарь} {название нового словаря}"
    "- объединение первого и второго словаря без повторений\n";
  ostream << "save_result - сохранить словари в файл\n";
  ostream << "history - Вывести историю команд\n";
}

void sviridenko::list(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  if (words.size() != 1)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  for (BinarySearchTree< std::string,
    BinarySearchTree< std::string, ForwardList< std::string > > >::Iterator it = listOfDIcts.begin();
    it != listOfDIcts.end(); it++)
  {
    ostream << it->first;
    BinarySearchTree< std::string,
      BinarySearchTree< std::string, ForwardList< std::string > > >::Iterator its = it;
    if (++its != listOfDIcts.end())
    {
      ostream << " ";
    }
  }
  ostream << "\n";
}

void sviridenko::find(std::ostream& ostream, ForwardList< std::string >& words, BinarySearchTree< std::string,
  BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  if (size != 3 || listOfDIcts.find(words.peekFront()) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string map = words.peekFront();
  words.dropFront();
  std::string word = words.peekFront();
  BinarySearchTree< std::string, ForwardList< std::string > > needMap = listOfDIcts.find(map)->second;
  for (BinarySearchTree< std::string, ForwardList< std::string > >::Iterator
    it = needMap.begin(); it != needMap.end(); it++)
  {
    if (it->first == word)
    {
      printTrue(ostream);
      return;
    }
  }
  printFalse(ostream);
}

void sviridenko::search(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  if (words.size() != 2)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  words.dropFront();
  std::string word = words.peekFront();
  int number = 0;
  for (BinarySearchTree< std::string, BinarySearchTree< std::string,
    ForwardList< std::string > > >::Iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    for (BinarySearchTree<std::string, ForwardList< std::string > >::Iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      if (its->first == word)
      {
        if (number != 0)
        {
          ostream << " ";
        }
        ostream << it->first;
        number++;
      }
    }
  }
  if (number == 0)
  {
    ostream << "Нет словаря с таким содержимым";
  }
  ostream << "\n";
}

void sviridenko::searchWithTranslate(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  if (words.size() != 2)
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  words.dropFront();
  std::string word = words.peekFront();
  bool isFind = false;
  for (BinarySearchTree< std::string, BinarySearchTree< std::string,
    ForwardList< std::string > > >::Iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    for (BinarySearchTree<std::string, ForwardList< std::string > >::Iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      if (its->first == word)
      {
        ostream << "В словаре " << it->first << ": ";
        int number = 0;
        for (ForwardList< std::string >::Iterator vit = its->second.begin(); vit != its->second.end(); vit++)
        {
          if (number != 0)
          {
            ostream << ", ";
          }
          ostream << *vit;
          number++;
        }
        isFind = true;
        ostream << "\n";
      }
    }
  }
  if (isFind == false)
  {
    ostream << "В словарях нет такого слова\n";
  }
}

void sviridenko::changeTranslation(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  std::string needDict = words.peekFront();
  words.dropFront();
  std::string word = words.peekFront();
  words.dropFront();
  if (size < 3 && listOfDIcts.find(needDict) == listOfDIcts.end() ||
    listOfDIcts.find(needDict)->second.find(word) == listOfDIcts.find(needDict)->second.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  listOfDIcts.find(needDict)->second.find(word)->second = words;
}

void sviridenko::print(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  if (size != 2 || listOfDIcts.find(words.peekFront()) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needDict = words.peekFront();
  int num = 0;
  ostream << "В " << listOfDIcts.find(needDict)->first << ":\n";
  BinarySearchTree< std::string, ForwardList< std::string > > b = listOfDIcts.find(needDict)->second;
  int counter = 0;
  for (BinarySearchTree< std::string, ForwardList< std::string > >::Iterator
    it = listOfDIcts.find(needDict)->second.begin();
    it != listOfDIcts.find(needDict)->second.end(); it++)
  {
    ostream << it->first << " - ";
    int number = 0;
    for (ForwardList< std::string >::Iterator vit = it->second.begin(); vit != it->second.end(); vit++)
    {
      if (number != 0)
      {
        ostream << ", ";
      }
      ostream << *vit;
      number++;
    }
    ostream << "\n";
  }
}

void sviridenko::clear(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  if (size != 2 || listOfDIcts.find(words.peekFront()) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  std::string needMap = words.peekFront();
  ForwardList< std::string > temp;
  for (BinarySearchTree< std::string, ForwardList< std::string > >::Iterator
    it = listOfDIcts.find(needMap)->second.begin();
    it != listOfDIcts.find(needMap)->second.end(); it++)
  {
    temp.pushBack(it->first);
  }
  while (!temp.isEmpty())
  {
    listOfDIcts.find(needMap)->second.remove(temp.peekFront());
    temp.dropFront();
  }
}

void sviridenko::deleteWord(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  std::string needDict = words.peekFront();
  words.dropFront();
  std::string word = words.peekFront();
  words.dropFront();
  if (size != 3 || listOfDIcts.find(needDict) == listOfDIcts.end() ||
    listOfDIcts.find(needDict)->second.find(word) == listOfDIcts.find(needDict)->second.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  listOfDIcts.find(needDict)->second.remove(word);
}

void sviridenko::insert(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  std::string needDict = words.peekFront();
  words.dropFront();
  std::string word = words.peekFront();
  words.dropFront();
  if (size < 3 || listOfDIcts.find(needDict) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  listOfDIcts.find(needDict)->second.insert(word, words);
}

void sviridenko::compare(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  std::string firstDict = words.peekFront();
  words.dropFront();
  std::string secondDict = words.peekFront();
  words.dropFront();
  if (size != 3 || listOfDIcts.find(firstDict) == listOfDIcts.end() ||
    listOfDIcts.find(secondDict) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  BinarySearchTree< std::string, ForwardList< std::string > >::Iterator
    itSecond = listOfDIcts.find(secondDict)->second.begin();
  for (BinarySearchTree< std::string,
    ForwardList< std::string > >::Iterator itFirst = listOfDIcts.find(firstDict)->second.begin();
    itFirst != listOfDIcts.find(firstDict)->second.end(); itFirst++)
  {
    bool is = true;
    for (ForwardList< std::string >::Iterator it = itFirst->second.begin(); it != itFirst->second.end(); it++)
    {
      for (ForwardList< std::string >::Iterator its = itSecond->second.begin(); its != itSecond->second.end(); its++)
      {
        if (*it != *its)
        {
          is = false;
          break;
        }
        else
        {
          it++;
        }
      }
      if (is == false)
      {
        break;
      }
    }
    if (is && listOfDIcts.find(firstDict)->second.size() == listOfDIcts.find(secondDict)->second.size())
    {
      itSecond++;
    }
    else
    {
      printFalse(ostream);
      return;
    }
  }
  printTrue(ostream);
}

void sviridenko::merge(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  int size = words.size();
  words.dropFront();
  std::string firstDict = words.peekFront();
  words.dropFront();
  std::string secondDict = words.peekFront();
  words.dropFront();
  std::string newDict = words.peekFront();
  words.dropFront();
  if (size != 4 || listOfDIcts.find(firstDict) == listOfDIcts.end() ||
    listOfDIcts.find(secondDict) == listOfDIcts.end())
  {
    sviridenko::failedEnter(ostream);
    return;
  }
  BinarySearchTree< std::string, ForwardList< std::string > > thirdDict = listOfDIcts.find(firstDict)->second;
  for (BinarySearchTree< std::string,
    ForwardList< std::string > >::Iterator it = listOfDIcts.find(secondDict)->second.begin();
    it != listOfDIcts.find(secondDict)->second.end(); it++)
  {
    if (listOfDIcts.find(secondDict)->second.find(it->first) != listOfDIcts.find(secondDict)->second.end())
    {
      thirdDict.insert(it->first, it->second);
    }
  }
  listOfDIcts.insert(newDict, thirdDict);
}

void sviridenko::history(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  for (BinarySearchTree<int, ForwardList< std::string > >::Iterator it = hist.begin(); it != hist.end(); it++)
  {
    int num = 0;
    for (ForwardList< std::string >::Iterator vit = it->second.begin(); vit != it->second.end(); vit++)
    {
      if (num != 0)
      {
        ostream << " ";
      }
      ostream << *vit;
      num++;
    }
    ostream << "\n";
  }
}

void sviridenko::save(std::ostream& ostream, ForwardList< std::string >& words,
  BinarySearchTree< std::string, BinarySearchTree< std::string, ForwardList< std::string > > >& listOfDIcts, char* arg,
  BinarySearchTree<int, ForwardList< std::string > >& hist, int& numberOfCommand)
{
  hist.insert(numberOfCommand, words);
  numberOfCommand++;
  std::ofstream out;
  out.open(arg, std::ios::trunc);
  out.close();
  out.open(arg, std::ios::app);
  if (!out.is_open())
  {
    sviridenko::failedEnter(ostream);
  }
  for (BinarySearchTree< std::string, BinarySearchTree< std::string,
    ForwardList< std::string > > >::Iterator it = listOfDIcts.begin(); it != listOfDIcts.end(); it++)
  {
    out << "В словаре " << it->first << ":\n";
    for (BinarySearchTree<std::string, ForwardList< std::string > >::Iterator its = it->second.begin();
      its != it->second.end(); its++)
    {
      int number = 0;
      out << its->first << " - ";
      for (ForwardList< std::string >::Iterator vit = its->second.begin(); vit != its->second.end(); vit++)
      {
        if (number != 0)
        {
          out << ", ";
        }
        out << *vit;
        number++;
      }
      out << "\n";
    }
  }
  out << "===================================================\n";
  out.close();
}
