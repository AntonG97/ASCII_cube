# About
A lightweight C program that renders a rotating **3D ASCII cube** directly in the terminal using ANSI escape codes.The cube is projected with perspective projection (3D to 2D), vectors, dot-and cross products.
The program requires user specified input arguments in a specified order

# Usage
The program requires **at least** two input arguments in the **following order**
*./ascii_cube **<rows> <coloumns>** [scale | [-c | -color]] [-c | -color]*
*Rows and coloums* determine the windows size in the terminal and *scale* applies a scaling factor to the cube. The default value is 20.
*Color* activates unique coloring of each of the cube faces.
**NOTE** The value of *coloums* should be twice that of rows for a correct window resolution 

# Example
*./cube_ascii 30 60*
*./cube_ascii 30 60 10*
*./cube_asci 40 80 30 -c*

<img width="612" height="505" alt="Screenshot from 2025-12-15 15-58-53" src="https://github.com/user-attachments/assets/9c30cee2-fde7-4ec0-90b7-22ec8a67a2e8" />
*./cube_ascii 40 80 -color*

<img width="612" height="505" alt="Screenshot from 2025-12-15 15-59-13" src="https://github.com/user-attachments/assets/59501722-9bed-4721-bf05-587c630b650a" />
*./cube_ascii 40 80*


# Controls
To terminate the program, type either **'q'** or **'clear'** into the terminal running the program, or use 
**CTRL+C** to force exit. The program uses ANSI-escape codes as auxillary to render the cube and the program
resets any settings before termination. 

# Build
The program depend on **math.h** to include **-lm** when compiling using GCC
*gcc -o ascii_cube ascii_cube.c -lm -Wextra -Wall -ggdb*
