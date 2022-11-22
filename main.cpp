/*
Programmer: Jeremy Saltz M00420942
Program Description:
This program creates a concordance for a text file. The program uses a BST to
keep track of the fequency of a words appearance and what lines the word apears
on. The program then prints out the concordance for each file and shows the word it's frequency and which lines the words appear on in a table. 
*/

#include "BST.h"
#include "wordEntry.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

//this fuction reads each line and then seperates each word and sends it to the build tree function to build the tree
void stringRead(ifstream &in, wordEntry *word, bstClass *tree);

//build the BST 
void buildTree(wordEntry *word, bstClass *tree, int line);

//prints the concordance 
void print(wordEntry &words);

//the top display for the concordance 
void topDisplay();

int main() {

  bstClass *bst;//pointer to the BST 
  bst = new bstClass;
  wordEntry *foundWord;//pointer to the sord entry struct
  foundWord = new wordEntry;
  ifstream myIn;//for reading the file
  

  myIn.open("text1.dat");//opens first file
  assert(myIn);//checks for vailid file
  stringRead(myIn, foundWord, bst);//calls the function to read each line
  myIn.close();//closes the file
  topDisplay();//display for the concordence table
  bst->InorderTraverse(print);//prints the concordance
  foundWord = new wordEntry;//sets the pointer to new
  delete bst;//deallowcates the ponter
  bst = new bstClass;//sets the pointer to a new ptr to start a new tree

  myIn.open("text2.dat");//opens the next file
  assert(myIn);//checks the file
  stringRead(myIn, foundWord, bst);//calls the function to read each line
  myIn.close();//closes the file
  cout << endl;//formats so the two concordances are easier to read
  topDisplay();//display for the top of the concordance
  bst->InorderTraverse(print);//prints the concordance

  delete bst;//deallowcates the ponter
  delete foundWord;//see above

  return 0;
}

//this function takes the file and reads each line one at a time and makes all the words lower case so that they will count as the same words. It then sends each word to the function that builds the binary tree.
void stringRead(ifstream &in, wordEntry *word, bstClass *tree) {
  string line, one_word;
  int lineNum = 0;

  while (getline(in, line)) {
    // Convert the string to lowercase
    transform(line.begin(), line.end(), line.begin(),
              ptr_fun<int, int>(tolower));
    // Replace everything that is not an alphanumeric with a space
    replace_if(line.begin(), line.end(), not1(ptr_fun<int, int>(isalnum)), ' ');
    
    stringstream single_word(line);
    lineNum++;

    //loops through each line breaking off each word to be added to the BST
    while (single_word >> one_word) {
      word->wordOfText = one_word;
      buildTree(word, tree, lineNum);
      word = new wordEntry;
    }
  }
}

//this function builds the binary tree using the word as the key for the tree. 
void buildTree(wordEntry *word, bstClass *tree, int line) {
  bool test;

  //if the tree is empty then this will start the root node
  if (tree->SearchTreeIsEmpty()) {
    word->frequCount++;
    word->lineNums.push_back(line);
    word->lastLineNum = line;
    tree->SearchTreeInsert(*word, test);
    word = new wordEntry;
  } else {
    //else look to see if the word is already on the tree and if not add it or update it
    tree->SearchTreeRetrieve(word->wordOfText, *word, test);
    if (test) {
      //if the last line count is the same then don't add the line count to the list
      if (word->lastLineNum == line) {
        word->frequCount++;
        tree->SearchTreeDelete(word->wordOfText, test);
        tree->SearchTreeInsert(*word, test);
        word = new wordEntry;
      } else {
        //else if it's a different line then add the line to the list
        word->frequCount++;
        word->lineNums.push_back(line);
        word->lastLineNum = line;
        tree->SearchTreeDelete(word->wordOfText, test);
        tree->SearchTreeInsert(*word, test);
        word = new wordEntry;
      }
    } else {
      //else it's a new word and is add to the BST
      word->frequCount++;
      word->lineNums.push_back(line);
      word->lastLineNum = line;
      tree->SearchTreeInsert(*word, test);
      word = new wordEntry;
    }
  }
}

//prints out the concordance 
void print(wordEntry &words) {
  list<int>::iterator i;
  cout << words.wordOfText << setw(16 - words.wordOfText.size())
       << words.frequCount << setw(15);
  for (i = words.lineNums.begin(); i != words.lineNums.end(); i++) {
    if (i == words.lineNums.begin())
      cout << *i;
    else
      cout << "," << *i;
  }
  cout << endl;
}

//top diplay for the concordance
void topDisplay() {
  cout << "Word" << setw(20) << "Frequency" << setw(23) << "Occurs on lines:\n";
  for (int i = 0; i < 50; i++)
    cout << "-";
  cout << endl;
}