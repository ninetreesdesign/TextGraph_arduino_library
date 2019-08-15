Textgraph_arduino_library
=========================
a simple library to make text-based stripchart graphs printed to the Arduino monitor or a terminal program.
The width is whatever your range of output values is. Typically I scale to around 50 or so. You just need to drag the output window wide enough to show a complete row.

The basic functions with defaults are:
```
    dotGraph(n)    
    barGraph(n)
```
There is the option to specify which character is printed for arguments "bar" and "dot"
```
    dotGraph(n,"*")    
    barGraph(n,"-","+")
```
There is also a bargraph to refresh on a single line instead of scrolling. (This works in a terminal program, but *not* in the Arduino monitor window.)
```  
    bargraphSameLine(n)
```
You can also call the spc() function to generate a row of N spaces or other characters
```
    spc(n)    
    spc(n,"=")
```
An example snippet for bargraph():
```
    y_scaled = map(y, -10.0, 10.0, 1, 50);  // scale function 
    Serial.print(y_scaled);
    TG.barGraph(y_scaled, '-', '+');      // use barGraph function, and select chars for bar and dot

output:
    -5.4 ----------+
    -3.2 --------------+
```
