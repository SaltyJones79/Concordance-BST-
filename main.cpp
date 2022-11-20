#include "BST.h"
#include "wordEntry.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void stringRead(ifstream &in, wordEntry *word, bstClass *tree);

void buildTree(wordEntry *word, bstClass *tree, int line);

void print(wordEntry &words);

void topDisplay();

int main() {

  bstClass *bst;
  bst = new bstClass;
  wordEntry *foundWord;
  foundWord = new wordEntry;
  ifstream myIn;
  treeNode *bstNode;

  myIn.open("text1.dat");
  assert(myIn);
  stringRead(myIn, foundWord, bst);
  myIn.close();
  topDisplay();
  bst->InorderTraverse(print);
  foundWord = new wordEntry;
  bst = new bstClass;
  
  myIn.open("text2.dat");
  assert(myIn);
  stringRead(myIn, foundWord, bst);
  myIn.close();
  cout << endl;
  topDisplay();
  bst->InorderTraverse(print);

  delete bst;
  delete foundWord;

  return 0;
}

void stringRead(ifstream &in, wordEntry *word, bstClass *tree) {
  string line, one_word;
  int lineNum = 0, lastLine;

  while (getline(in, line)) {
    // Convert the string to lowercase
    transform(line.begin(), line.end(), line.begin(),
              ptr_fun<int, int>(tolower));
    // Replace everything that is not an alphanumeric with a space
    replace_if(line.begin(), line.end(), not1(ptr_fun<int, int>(isalnum)), ' ');
    stringstream single_word(line);
    lineNum++;
    while (single_word >> one_word) {
      word->wordOfText = one_word;
      buildTree(word, tree, lineNum);
      word = new wordEntry;
    }
  }
}

void buildTree(wordEntry *word, bstClass *tree, int line) {
  bool test;

  if (tree->SearchTreeIsEmpty()) {
    word->frequCount++;
    word->lineNums.push_back(line);
    word->lastLineNum = line;
    tree->SearchTreeInsert(*word, test);
    word = new wordEntry;
  } else {
    tree->SearchTreeRetrieve(word->wordOfText, *word, test);
    if (test) {
      if (word->lastLineNum == line) {
        word->frequCount++;
        tree->SearchTreeDelete(word->wordOfText, test);
        tree->SearchTreeInsert(*word, test);
        word = new wordEntry;
      } else {
        word->frequCount++;
        word->lineNums.push_back(line);
        word->lastLineNum = line;
        tree->SearchTreeDelete(word->wordOfText, test);
        tree->SearchTreeInsert(*word, test);
        word = new wordEntry;
      }
    } else {
      word->frequCount++;
      word->lineNums.push_back(line);
      word->lastLineNum = line;
      tree->SearchTreeInsert(*word, test);
      word = new wordEntry;
    }
  }
}

void print(wordEntry &words) {
  list<int>::iterator i;
  cout << words.wordOfText << setw(16 - words.wordOfText.size())
       << words.frequCount << setw(15);
  for (i = words.lineNums.begin(); i != words.lineNums.end(); i++) {
    if(i != words.lineNums.end())
      cout << *i << ",";
    else
      cout << *i;
  }
  cout << endl;
}

void topDisplay() {
  cout << "Word" << setw(20) << "Frequency" << setw(23) << "Occurs on lines:\n";
  for (int i = 0; i < 50; i++)
    cout << "-";
  cout << endl;
}