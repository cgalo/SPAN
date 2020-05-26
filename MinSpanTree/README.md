# MinSpanTree Class
This class handles all the logic for the program, and it's only called by the [main file](../main.cpp).

## Overview
1. Initiating the MinSpanTree, _MST_ for short, required a char array that will contain the location of a text file. The constructor will attempt to open the text file and build a graph using a 2D character array.
2. Then the [main file](../main.cpp) will call the public method _getKruskalMSP_ within this class, which outputs the results from the private method _KruskalMST_.
