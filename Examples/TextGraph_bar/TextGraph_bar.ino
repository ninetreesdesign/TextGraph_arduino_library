// Library:     TextGraph
/*
    Generates a vertically scrolling stripchart-style graph
    using text sent to the Monitor or a terminal program
    The function will print the value of a function or input data and then
    pass the value to barGraph() produce a graph of the amplitude.

    Functions:   dotGraph, barGraph, barGraphSameLine
    @description This example shows the use of barGraph() in the TextGraph library for Arduino
    @language    Wiring (Arduino)
    @author      David Smith
    @version     2014 released for use in Public Domain
    @updated     2019 more comments and tweaks to the examples

    usage: tg.bargraph(n)              [applies default bar and dot characters]
      or   tg.barGraph(n, '-', '*')    [to choose bar and dot characters]
      where n must be a positive integer, scaled to the width you want

    The map() and constrain() functions are usually helpful.
    To keep the graph aligned horizontally, the numerical value must be a constant width;
    to do so, use dtostrf()* for Uno and other AVR boards, or use printf() with Teensy.
    * http://gist.github.com/2343665
*/

#include <TextGraph.h>

// global variables
char cbuf[16];          // container to hold formatted number

TextGraph tg(1);        // create an instance of TextGraph named "tg"


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
    static bool i = 1;
    static float t = 0;
    static float tstep = 0.01;
    float y;
    int y_scaled;
    y = 9*sin(PI*3.0*t) - 5*cos(PI*7.1*t - 1.0) + 4;  // another function to graph
    dtostrf(y, 7, 2, cbuf);                 // -nnn.nn for consistent format
    Serial.print(cbuf);                     // print the actual function's value

    // scale function to fit Monitor window: set window at least as wide as graph range
    y_scaled = map(y, -10, 10, 1, 50);
    tg.barGraph(y_scaled, '-', '+');        // useGraph function, and select chars for bar and dot
    t = t + tstep;

    digitalWrite(LED_BUILTIN, i);           // toggle led just to see the program running
    i = !i;
    delay(200);                             // set update rate to screen
}

