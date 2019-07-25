// Library:  TextGraph
// Functions: dotGraph, barGraph
//
// @description  This example shows the use of barGraph() from the TextGraph library for Arduino 
// @language Wiring (Arduino)
// @author   David Smith 
// @version  1.0	2014 released for use in Public Domain
// @updated  2017

// A quick way to visualize a data stream
// generates a vertically scrolling stripchart-style graph 
// using text sent to the Monitor or a terminal program
// Program will print the value of a function or input data,
// then pass the value to barGraph() produce a graph of the amplitude.

// usage: TG.bargraph(n) 
//     or TG.barGraph(n, '-', '*') to explicitly pick bar and dot characters
//   where n must be a positive integer, scaled to the width you want  
//   and TG is the name you assign to the instance of TextGraph 
//   dotGraph() is equivalent to bargraph where the "bar" character is a space
// The map() and constrain() functions are often helpful.
// To keep the graph aligned horizontally, the numerical value must be a constant width; 
// Using the decimal-to-string function is a good way to format a floating point number for Uno
// or use printf() with Teensy
// @see dtostrf(FLOAT,WIDTH,PRECISION,BUFFER); gist.github.com/2343665 

#include <TextGraph.h>

// global variables
char cbuf[16];	   // container to hold formatted number

TextGraph TG(1);   // create an instance of TextGraph named "TG"
// -----------------------------------------------------------------------
void setup(void) {
  Serial.begin(57600);
  Serial.println("\nPrint a numerical value and add a graph\n");
}

void loop(void) {
  unsigned int i;
  static float tstep = 0.01;
  static float t = 0;
  float y;  
  int y_scaled;
  y = 90*sin(PI*3.0*t)-50*cos(PI*7.1*t-1.0)+40;  // another function to graph
  dtostrf(y, 7, 2, cbuf);               // -nnn.nn for consistent format   
  Serial.print(cbuf);                   // print the actual function's value
  
  y_scaled = map(y, -100, 100, 1, 50);  // scale function to fit Monitor window: set window at least as wide as graph range
  TG.barGraph(y_scaled, '-', '+');      // useGraph function, and select chars for bar and dot
  t = t + tstep;
  delay(200);                           //control output rate to screen
}




