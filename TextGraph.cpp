/*arduino library "TextGraph" is a class
  - has a definition portion in .h file
  - has code in the .cpp file
  - and keywords in keywords.txt file
*/
// @language Wiring (Arduino)
// @author   David Smith
// @version  1.0
// @released 2014   for use in Public Domain
// @updated  2017
// A quick way to visualize a data stream
// generates a vertically scrolling stripchart-style graph


#include "Arduino.h"
#include "TextGraph.h"

// mini ascii vertical "dot" graph
TextGraph::TextGraph(int nn) {     // <<constructor>>
  ;
}
// <<NO destructor>>

// The multiple instances of the same name function with different input arguments
// allows option to omit an argument and use the default value.
// This technique is referred to as "overloading"

/// draw a horizontal line graph
void TextGraph::dotGraph(int nn) {
  char dotChar = '*';
  Serial.print(" ");             // a gap before the graph starts
  spc(byte(nn));                 // local fctn prints a row of n chars
  Serial.print(dotChar);         // character for the graph data point
  Serial.print("\n");            // newline
}

void TextGraph::dotGraph(int nn, char dotChar) {
  Serial.print(" ");             // a gap before the graph starts
  spc(byte(nn));                 // local fctn prints a row of n spaces
  Serial.print(dotChar);         // character for the graph data point
  Serial.print("\n");
}

void TextGraph::barGraph(int nn) { // default chars
  char barChar = '-';
  char dotChar = '+';
  Serial.print(" ");             // a gap before the graph starts
  spc(byte(nn), barChar);        // row of bar chars
  Serial.print(dotChar);         // character for the graph data point
  Serial.print("\n");            // newline
}

/// the most general version accommodates all options of dot/bar graph
void TextGraph::barGraph(int nn, char barChar, char dotChar) {
  Serial.print(" ");             // a gap before the graph starts
  spc(byte(nn), barChar);        // row of bar chars
  Serial.print(dotChar);         // character for the graph data point
  Serial.print("\n");            // newline
}

/// Prints a single animated (refreshed) horizontal line; output must go to terminal program.
//  It will not work in IDE Monitor.
//  Screen must be wide enough to avoid wrap, or it will look like LF are still generated
void TextGraph::barGraphSameLine(int nn, char barChar, char dotChar) {
  byte maxWidth = 111;           // this can be adjusted as desired
  Serial.print(" ");             // a gap before the graph starts
  spc(byte(nn), barChar);        // row of bar chars
  Serial.print(dotChar);         // character for the graph data point
  Serial.print("\n");            // newline
  spc(byte(maxWidth - nn));      // clear the rest of the line
  Serial.print("\r");            // carriage return only
}

/// Print n characters in a row (spaces usually)
void TextGraph::spc(byte numChars) {
  char rowChar = ' ';
  byte maxWidth = 111;           // this can be adjusted as desired
  if (numChars >= 0 && numChars < maxWidth) {  // constrain
    for (byte i = 0; i < numChars; i++) {
      Serial.print(rowChar);
    }
  }
  else {
    numChars = constrain(numChars, 5,maxWidth);
    Serial.print("warning: length out of range; constrained.");
  }
}

// optional argument to change default space to another char (used to draw a row of n chars)
void TextGraph::spc(byte numChars, char rowChar) {
  byte maxWidth = 111;  // this can be adjusted as desired
  if (numChars > 0 && numChars < maxWidth) {  // constrain
    for (byte i = 0; i < numChars; i++) {
      Serial.print(rowChar);
    }
  }
  else {
    Serial.print("err: length out of range");
  }
}

