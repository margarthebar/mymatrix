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

  struct matrix *edges = new_matrix(4, 4);
  struct matrix *transform = new_matrix(4, 4);
  /*
  add_edge(edges,1,2,3,4,5,6);

  add_edge(transform,0,1,0,-1,0,0);
  add_edge(transform,0,0,1,0,0,0);
  transform->m[3][0] = 0;
  transform->m[3][1] = 0;
  transform->m[3][2] = 0;

  printf("edges\n");
  print_matrix(edges);
  printf("transform\n");
  print_matrix(transform);

  matrix_mult(transform,edges);
  printf("transformed\n");
  print_matrix(edges);
  */

  printf("Declared edges and transform matrices\n");

  //original rectangle
  add_edge(edges,100,100,0,300,100,0);
  add_edge(edges,100,100,0,100,150,0);
  add_edge(edges,300,100,0,300,150,0);
  add_edge(edges,100,150,0,300,150,0);
  printf("Added edges to edge matrix\n");
  
  draw_lines(edges,s,c);

  printf("Drew original rectangle\n");
  print_matrix(edges);

  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;
  ////translate rectangle
  //create translation matrix
  struct matrix *translate = make_translate(-100,-100,0);
  printf("Translation matrix\n");
  print_matrix(translate);

  //apply translation to transform matrix
  copy_matrix(translate,transform);
  //apply translation to edges
  matrix_mult(translate,edges);
  draw_lines(edges,s,c);

  printf("Translated rectangle\n");
  print_matrix(edges);

  c.red = 0;
  c.green = 0;
  c.blue = MAX_COLOR;
  ////scale rectangle
  //create scale matrix
  struct matrix *scale = make_scale(1.5,1.5,1);
  //apply scale to transform matrix
  matrix_mult(scale,transform);
  //apply scale to edges
  matrix_mult(scale,edges);
  draw_lines(edges,s,c);

  //scale = make_scale(1,2,1);
  //matrix_mult(scale,transform);
  //matrix_mult(scale,edges);
  //draw_lines(edges,s,c);

  printf("Scaled rectangle\n");
  print_matrix(edges);

  c.red = MAX_COLOR;
  ////rotate rectangle 45 degrees around z axis
  //create rotation matrix
  struct matrix *rotate = make_rotZ(90);
  //apply rotation to transform matrix
  matrix_mult(rotate,transform);
  //apply rotation to edges
  matrix_mult(rotate,edges);
  draw_lines(edges,s,c);

  printf("Rotated rectangle\n");
  print_matrix(edges);

  struct matrix *trans = make_translate(75,0,0);
  matrix_mult(trans,transform);
  matrix_mult(trans,edges);
  draw_lines(edges,s,c);
  printf("Translated again\n");
  print_matrix(edges);   
  

  save_extension(s, "lines.png");

  printf("Saved image file\n");

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
