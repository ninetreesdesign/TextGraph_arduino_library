/*
 TextGraph - simple vertical graphing using text in monitor or a terminal window.
 Created by David Smith, 2014
 Released into the public domain.
 */
#ifndef TextGraph_h		// avoid invoking more than once
#define TextGraph_h
#include "Arduino.h"	// provide access to core functions

class TextGraph
// Makes simple ascii-based streaming dot and bar graphs to a terminal or IDE's monitor*
//*barGraphSameline doesn't work in Arduino monitor; must be a full terminal program that distinguishes \r and \n as separate entities
{
public:
  TextGraph(int nn);

  void dotGraph(int nn);                 // graph an integer as a '*' (or vertical line)
  void dotGraph(int nn, char dotChar);   // options, set character

  void barGraph(int nn);                 // graph an integer as a horizontal bar
  void barGraph(int nn, char barChar, char dotChar); // options to set characters

  void barGraphSameLine(int nn, char barChar, char dotChar); // options to set characters

  // promoted the spc() function to public section to allow its use as well
  void spc(byte nn);                     // print out N spaces  
  void spc(byte nn, char rowChar);       //  change bar character

private:


};

#endif
