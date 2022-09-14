//============================================================================
// Name        : main.cpp
// Author      : RWHasker
// Assignment  : CS 2040, Lab 5
// Description : Main for raider the robot
//============================================================================

#include "robot.h"
#include "map.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// Given an integer number of arguments and an array of argument
//   strings (as passed to main()), checks if there is at least
//   one string in argv[]. If there is, this code treats it as
//   the name of a file and attempts to open as standard input.
//   If no name is specified, does nothing (leaving cin unchanged).
//   Prints an error if a name is specified but the name cannot
//   be opened as a file.
//   This function must be called at most once.
void set_input(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  set_input(argc, argv);

  Map *map = new Map();
  map->load();
  int startx, starty;
  cin >> startx >> starty;
  bool ok = true;
  Robot *mainRobot = new Robot(map, startx, starty);
  string cmd;
  cout << "Initial state: ";
  mainRobot->displayStatus();
  cout << endl;
  while (ok && cin >> cmd) {
    cout << "Executing " << cmd << endl;
    if (mainRobot->move(cmd)) {
      mainRobot->displayStatus();
      cout << endl;
      map->write();
    } else {
      cout << endl;
      cout << "Error: robot with current status of ";
      mainRobot->displayStatus();
      cout << " broke while executing " << cmd << endl;
      map->write();
      ok = false;
    }
  }
  cout << endl;
  if ( ok )
    cout << "Robot has completed its task." << endl;

  return 0;
}

void set_input(int argc, char *argv[]) {
  static bool called = false;
  if (called) {
    cerr << "programming error: set_input cannot be called twice." << endl;
    exit(1);
  }
  called = true;
  static ifstream alternative_input; // used if have filename on command line
  if (argc > 0 && argv[1] != nullptr && argv[1][0] != 0) {
    alternative_input.open(argv[1]);
    if (!alternative_input) {
      cerr << "Could not open " << argv[1] << " for input." << endl;
      exit(1);
    }
    // this magic sets the read buffer for cin to the read buffer for
    //   the input stream (redirecting input from the named file)
    cin.rdbuf(alternative_input.rdbuf());
  }
}
