// Library:     TextGraph
// Functions:   dotGraph, barGraph
//
// @description This example shows the use of barGraph() from the TextGraph library for Arduino
// @language    Wiring (Arduino)
// @author      David Smith
// @version     2014 released for use in Public Domain
// @updated     2019 more comments and tweaks to the examples

// A quick way to visualize a data stream
// generates a vertically scrolling stripchart-style graph
// using text sent to the Monitor or a terminal program
// Program will print the value of a function or input data,
// then pass the value to barGraph() produce a graph of the amplitude.

// usage: tg.bargraph(n)
//     or tg.barGraph(n, '-', '*') to explicitly pick bar and dot characters
//   where n must be a positive integer, scaled to the width you want
//   and tg is the name you assign to the instance of TextGraph
//   dotGraph() is equivalent to bargraph where the "bar" character is a space

// The map() and constrain() functions are often helpful.
// To keep the graph aligned horizontally, the numerical value must be a constant width;
// Using the decimal-to-string function is a good way to format a floating point number for Uno
// or use printf() with Teensy
// @see dtostrf(FLOAT,WIDTH,PRECISION,BUFFER); gist.github.com/2343665

#include <TextGraph.h>

// global variables
char cbuf[16];     // container to hold formatted number

TextGraph tg(1);   // create an instance of TextGraph named "tg"
// -----------------------------------------------------------------------
void setup(void) {
    pinMode(LED_BUILTIN,OUTPUT);

    int t0 = millis();
    Serial.begin(115200);
    while (!Serial && (millis() - t0 < 5000)) {
        ; // wait for port to connect or skip after timeout. Req'd on arduinos with USB port systems
    }
    Serial.println("\nPrint a numerical value and add a graph\n");
}

void loop(void) {
    static float t = 0;
    static float tstep = 0.01;
    float y;
    int y_scaled;
    y = 90*sin(PI*3.0*t) - 50*cos(PI*7.1*t - 1.0) + 40;  // another function to graph
    dtostrf(y, 7, 2, cbuf);                 // -nnn.nn for consistent format
    Serial.print(cbuf);                     // print the actual function's value

    // scale function to fit Monitor window: set window at least as wide as graph range
    y_scaled = map(y, -100, 100, 1, 50);
    tg.barGraph(y_scaled, '-', '+');        // useGraph function, and select chars for bar and dot
    t = t + tstep;
    static bool i = 1;
    digitalWrite(LED_BUILTIN, i);           // toggle led just to see the program running
    i = !i;
    delay(200);                             // set output rate to screen
}
