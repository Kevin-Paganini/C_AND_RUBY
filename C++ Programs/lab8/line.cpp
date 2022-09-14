// line.cpp
// Author: Kevin Paganini
// CS 2040, Spring 2022
//

#include "line.h"
#include "words.h"
#include <sstream>

using namespace std;

// break source into words and store each in contents
Line::Line(string source) {
  stringstream iss(source);
  string next;
  iss >> next;
  while ( iss ) {
    Word* word_from_pool = WordPool::instance()->get(next);

    contents.push_back(word_from_pool);

    iss >> next;
  }
}

// Does the line contain the target word
bool Line::contains(string target) const {
  for(auto wp : contents) {
      if (wp->value() == target) {
        return true;
      }
  }
  return false;

}
// Turning the line into a nice string
string Line::to_string() const {
  string result = "";
  for(auto wp : contents) {
    if ( !result.empty() )
      result += ' ';
    result += wp->value();
  }
  return result;
}

