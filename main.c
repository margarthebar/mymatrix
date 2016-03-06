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
  ident(transform);
  
  //original rectangle
  add_edge(edges,0,0,0,1,0,0);
  add_edge(edges,0,0,0,0,1,0);
  add_edge(edges,1,0,0,1,1,0);
  add_edge(edges,0,1,0,1,1,0);

  double width,height;
  width = 1;
  height = 1;
  struct matrix *translate = make_translate(250,250,0);
  matrix_mult(translate,edges);
  matrix_mult(translate,transform);
  draw_lines(edges,s,c);

  int i,x,angle,diff;
  angle = 5;
  
  for(i=0; i<150; i++){
    if(c.red == 0){
      c.red = MAX_COLOR;
    }
    diff = ( (i*5) % MAX_COLOR );
    c.red = MAX_COLOR - diff;
    c.blue = 0 + diff;
    if(i%2==0){
      x = width;
    }else{
      x = height;
    }

    struct matrix *scale = make_scale(1.05,1.05,0);
    struct matrix *translate_over = make_translate(x,0,0);
    struct matrix *rotate = make_rotZ(angle);
    struct matrix *translate_back = make_translate(-250,-250,0);

    matrix_mult(translate,scale);
    matrix_mult(scale,rotate);
    matrix_mult(rotate,translate_back);
    copy_matrix(translate_back,transform);

    matrix_mult(transform,edges);
    draw_lines(edges,s,c);

    width = width*1.05;
    height = height*1.05;
    //angle += 5;
  }

  save_extension(s, "lines.png");

  printf("Saved image file\n");

  free_matrix( transform );
  free_matrix( edges );
} 
