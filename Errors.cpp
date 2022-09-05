#include "Errors.h"
void sviridenko::failedEnter(std::ostream& ostream)
{
  ostream << "Incorrect command. Enter 'help'\n";
}

void sviridenko::printTrue(std::ostream& ostream)
{
  ostream << "<TRUE>\n";
}

void sviridenko::printFalse(std::ostream& ostream)
{
  ostream << "<FALSE>\n";
}
