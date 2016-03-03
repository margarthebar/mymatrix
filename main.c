#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
//#include "parser.h"

int main() {

  screen s;
  color c;
  c.red = MAX_COLOR;
  c.green = 0;
  c.blue = 0;
  clear_screen(s);
  struct matrix *edges;
  struct matrix *transform;

  edges = new_matrix(4, 4);
  transform = new_matrix(4, 4);

  add_edge(edges,100,100,0,300,100,0);
  add_edge(edges,100,100,0,100,150,0);
  add_edge(edges,300,100,0,300,150,0);
  add_edge(edges,100,150,0,300,150,0);

  draw_lines(edges,s,c);
  
  save_extension(s, "lines.png");

  free_matrix( transform );
  free_matrix( edges );
}  

/*
Write code to set up a point matrix with the following functionality:
add a point to a point matrix
add an edge to a point matrix (should call your add point routine)
go through a point matrix and draw the lines stored in the matrix (should call your draw line routine)
Write code to work with matrices:
print out a matrix
scalar matrix multiplication
creation of an identity matrix
matrix multiplication
create a translation matrix
create a scale matrix
create a rotation matrix about the x-axis
create a rotation matrix about the y-axis
create a rotation matrix about the z-axis
Note: The trig functions in java, python and c take radians as parameters, but you should assume degree input, make sure to convert or things won't look right.
*/
