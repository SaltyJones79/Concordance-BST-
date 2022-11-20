#ifndef WORDENTRY_H
#define WORDENTRY_H
#include <list>
#include <string>

using namespace std;

struct wordEntry {

  string wordOfText;
  int frequCount =0;
  list<int> lineNums;
  int lastLineNum;

  string Key() const;
};

#endif