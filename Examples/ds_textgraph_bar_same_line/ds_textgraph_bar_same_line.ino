// Library:  TextGraph
// Functions: dotGraph, barGraph, barGraphSameLine
// 
// @language     Wiring (Arduino)
// @description  This example shows the use of barGraphSameLine() 
// @author       David Smith 
// @updated      2014-DEC-30 add barGraphSameLine()
// @updated  2017

// A quick way to visualize a changing data such as analog input
// generates a horizontal moving bar graph of a value on a single line.
// This function cannot be used with Arduino Monitor; it MUST be streamed to a terminal program
// Mac*   MacWise 14, for OS
// Win7   Teraterm
// Linux  xTerm or Terminator

// usage: TG.barGraphSameLine(n, '-', '*') to explicitly pick bar and dot characters
//   where n must be a positive integer, and scaled to the width you want (40 to 100 typical). 
//   and TG is the name assigned in this code to the instance of TextGraph 
// To keep the graph aligned horizontally, the numerical value must be a constant width; 
// Using the decimal-to-string function is a good way to format a floating point number for Uno
// or use printf() with Teensy
// @see dtostrf(FLOAT,WIDTH,PRECISION,BUFFER); gist.github.com/2343665 
 
#include <TextGraph.h>

// global variables
char cbuf[16];     // container to hold formatted number

TextGraph TG(1);   // create an instance of TextGraph named "TG"
// -----------------------------------------------------------------------
void setup(void) {
  Serial.begin(57600);
  char esc = 27;
  int i;
  int t0 = millis();
  while (!Serial && (millis() - t0 < 2000)) {
    ; // wait for serial port to connect. Req'd on some systems, with 2sec timeout
  }
// VT100 terminal allows control of cursor and CR/LF separately; minimal cmds to improve display
// Terminal window width must be wider than max line, or >100 characters as written
// Sometimes window height must be increased as well ~ 20-30 lines
  Serial.print(esc);
  Serial.print("[2J"); // to clr screen for VT100 terminal

  Serial.print(esc);
  Serial.print("[H");  // to screen home for VT100 terminal
  Serial.println("\nPrint a numerical value and add a graph; refreshes one line.\n");

  Serial.print(esc);
  Serial.print("[?25l");  // hide cursor  (ESC [?25h to show)
}

// -----------------------------------------------------------------------
void loop(void) {
  unsigned int i;
  static float tstep = 0.01;
  static float t = 0;
  float y;  
  int y_scaled;

  y = 90*sin(PI*3.0*t)-50*cos(PI*7.1*t-1.0)+40;  // another function to graph
  dtostrf(y, 7, 2, cbuf);               // -nnnn.nn for consistent format   
  Serial.print(cbuf);                   // print the actual function's value
  y_scaled = map(y, -100, 100, 1, 50);  // scale function to fit Monitor window: set window at least as wide as graph range
  TG.barGraphSameLine(y_scaled, '-', '+');  // use Graph refreshing a single line
  t = t + tstep;
  delay(200);                           //control output rate to screen
}


