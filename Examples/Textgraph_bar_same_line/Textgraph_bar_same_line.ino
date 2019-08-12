//  Library:     TextGraph
/*
    The barGraphSameLine() lets you visualize a changing data such as analog input
    as a horizontal moving bar graph of a value on a single line.
    This function **cannot be used with Arduino Monitor**; it **must** be streamed to a terminal program.
    Examaples:
      Mac*   MacWise 14
      Win7   Teraterm
      Linux  xTerm or Terminator

    Functions:   dotGraph, barGraph, barGraphSameLine
    @description This example shows the use of barGraphSameLine()
    @language    Wiring (Arduino)
    @author      David Smith
    @version     2014 released for use in Public Domain
    @updated     2019 more comments and tweaks to the examples

    usage: tg.barGraphSameLine(n, '-', '*') [to choose bar and dot characters]
      where n must be a positive integer, and scaled to the width you want (40 to 100 typical).
      and tg is the name assigned in this code to the instance of TextGraph

    The map() and constrain() functions are usually helpful.
    To keep the graph aligned horizontally, the numerical value must be a constant width;
    to do so, usedtostrf()* for Uno and other AVR boards, or use printf() with Teensy.
    * http://gist.github.com/2343665
*/


#include <TextGraph.h>

TextGraph tg(1);   // create an instance of TextGraph named "tg"


void setup(void) {
    const char ESC = 27;
    int t0 = millis();
    Serial.begin(115200);
    while (!Serial && (millis() - t0 < 5000)) {
        ; // wait for port to connect or skip after timeout. Req'd on arduinos with USB port systems
    }
    // VT100 terminal allows control of cursor and CR/LF separately; minimal cmds to improve display
    // Terminal window width must be wider than max line length.
    // Sometimes window height must be increased as well ~ 20-30 lines
    Serial.print(ESC);
    Serial.print("[2J");                    // to clr screen for VT100 terminal

    Serial.print(ESC);
    Serial.print("[H");                     // to screen home (upper left) for VT100 terminal
    Serial.println("\nPrint a numerical value and add a graph; refreshes one line.\n");

    Serial.print(ESC);
    Serial.print("[?25l");                  // hide cursor  (ESC [?25h to show)
}


void loop(void) {
    char cbuf[16];                          // container to hold formatted number
    static float tstep = 0.01;
    static float t = 0;
    float y;
    int y_scaled;

    y = 90*sin(PI*3.0*t) - 50*cos(PI*7.1*t - 1.0) + 40;   // a function to graph
    dtostrf(y, 7, 2, cbuf);                 // -nnnn.nn for consistent format
    Serial.print(cbuf);                     // print the actual function's value

    // set window at least as wide as graph range
    y_scaled = map(y, -100, 100, 1, 50);    // scale function to fit Monitor window:
    tg.barGraphSameLine(y_scaled, '-', '+');  // use Graph refreshing a single line
    t = t + tstep;
    delay(200);                             // set the update rate to screen
}

