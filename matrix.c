#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int r,c;
  for(r=0; r<4; r++){
    for(c=0; c < m->lastcol; c++){
      printf("%G\t",m->m[r][c]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int r,c,columns;
  columns = m->lastcol;
  if(m->lastcol==0){//if matrix is empty, create it
    columns = m->cols;
    //m->m[0][lastcol] = 1;
    //m->m[1][lastcol
    //add_edge(m,1,0,0,0,1,0);
    //add_edge(m,0,0,1,0,0,0);
  }
  for(c=0; c< columns; c++){
    for(r=0; r< m->rows; r++){
      //printf("row: %d, col: %d\n",r,c);
      if(c==r){
	//printf("here 1\n");
	m->m[r][c]=1;
      }else{
	//printf("here 0\n");
	m->m[r][c]=0;
      }
    }
    m->lastcol++;
  }
  //printf("ident called\n");
  //print_matrix(m);
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m 
Returns: 

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int r,c;
  for(r=0; r< m->rows; r++){
    for(c=0; c< m->lastcol; c++){
      m->m[r][c] *= x;
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  struct matrix *c = new_matrix(a->rows,b->lastcol);
  int a_row,a_col,b_col;
  double a_el,b_el;
  double sum;
  //for each row in matrix a
  for(a_row=0; a_row< a->rows; a_row++){
    //for each column in matrix B
    for(b_col=0; b_col< b->lastcol; b_col++){
      sum = 0;
      //for each column in this row of matrix a
      for(a_col=0; a_col< a->lastcol; a_col++){
	a_el = a->m[a_row][a_col];
	b_el = b->m[a_col][b_col];
	sum += (a_el*b_el);
      }
      //add sum to matrix b
      c->m[a_row][b_col] = sum;
      if(c->lastcol < c->cols){
	c->lastcol++;
      }
    }
  }
  copy_matrix(c,b);
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix created using x, y and z 
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix *trans = new_matrix(4,4);
  ident(trans);
  trans->m[0][3] = x;
  trans->m[1][3] = y;
  trans->m[2][3] = z;
  return trans;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z 
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix *make_scale(double x, double y, double z) {
  struct matrix *scale = new_matrix(4,4);
  ident(scale);
  scale->m[0][0] = x;
  scale->m[1][1] = y;
  scale->m[2][2] = z;
  return scale;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  theta = fmod(theta,360);
  theta = theta * (M_PI/180);
  double cosine,sine;
  if(theta == (90 * (M_PI/180) ) ){
    cosine = 0;
    sine = sin(theta);
  }else if(theta == 0){
    sine = 0;
    cosine = cos(theta);
  }else{
    sine = sin(theta);
    cosine = cos(theta);
  }

  struct matrix *rot = new_matrix(4,4);
  ident(rot);
  rot->m[1][1] = cosine;
  rot->m[1][2] = -sine;
  rot->m[2][1] = sine;
  rot->m[2][2] = cosine;
  return rot;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  theta = fmod(theta,360);
  theta = theta * (M_PI/180);
  double cosine,sine;
  if(theta == (90 * (M_PI/180) ) ){
    cosine = 0;
    sine = sin(theta);
  }else if(theta == 0){
    sine = 0;
    cosine = cos(theta);
  }else{
    sine = sin(theta);
    cosine = cos(theta);
  }

  struct matrix *rot = new_matrix(4,4);
  ident(rot);
  rot->m[0][0] = cosine;
  rot->m[0][2] = -sine;
  rot->m[2][0] = sine;
  rot->m[2][2] = cosine;
  return rot;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the 
angle of rotation and Z as the axis of rotation.
====================*/
struct matrix * make_rotZ(double theta) {
  theta = fmod(theta,360);
  theta = theta * (M_PI/180);
  double cosine,sine;
  if(theta == (90 * (M_PI/180) ) ){
    cosine = 0;
    sine = sin(theta);
  }else if(theta == 0){
    sine = 0;
    cosine = cos(theta);
  }else{
    sine = sin(theta);
    cosine = cos(theta);
  }

  struct matrix *rot = new_matrix(4,4);
  ident(rot);
  rot->m[0][0] = cosine;
  rot->m[0][1] = -sine;
  rot->m[1][0] = sine;
  rot->m[1][1] = cosine;
  return rot;
}
