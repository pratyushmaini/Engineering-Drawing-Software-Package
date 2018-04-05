#include <string.h>
#include <GL/glui.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <gtk/gtk.h>
#include "../include/File2D_3D.h"
using namespace std;

extern File2D outputFile;
extern int threeViewOrOne;
extern int main_window;
int segments = 4;
int wireframe = 0;
float scale_main = 1.0;
int window_num = 1;
//char *filename;


void draw_axes( float scale_main )
{
  glDisable( GL_LIGHTING );

  glPushMatrix();
  glScalef( scale_main, scale_main, scale_main );

  glBegin( GL_LINES );
 
  glColor3f( 1.0, 0.0, 0.0 );
  glVertex3f( 0.9f, 0.025f, 0.0 );  glVertex3f( 1.0f, 0.125f, 0.0 ); /* Letter X */
  glVertex3f( 0.9f, .125f, 0.0 );  glVertex3f( 1.0f, 0.025f, 0.0 );
  glVertex3f( 0.0, 0.0, 0.0 )  ;  glVertex3f( 1.0, 0.0, 0.0 ); /* X axis      */

  glColor3f( 0.0, 1.0, 0.0 );
  glVertex3f( 0.0, 0.0, 0.0 );    glVertex3f( 0.0, 1.0, 0.0 ); /* Y axis      */

  glColor3f( 0.0, 0.0, 1.0 );
  glVertex3f( 0.0, 0.0, 0.0 );    glVertex3f( 0.0, 0.0, 1.0 ); /* Z axis    */
  glEnd();

  glPopMatrix();

  glEnable( GL_LIGHTING );
}


/***************************************** myGlutDisplay() *****************/

void mainGlutDisplay()
{
  
  if (window_num == 1){

    
    static float rotationX = 0.0, rotationY = 0.0;

    glClearColor( .3f, .3f, .8f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /*** Rotate the object ***/
    rotationX += 1.3f;
    rotationY += 1.3f;

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glRotatef( rotationY, 0.0, 1.0 , 0.0);
    glRotatef( rotationX, 1.0, 0.0 , 0.0);
    if ( wireframe )
      glutWireTorus( .2,.5,16,segments );
    else
      glutSolidTorus( .2,.5,16,segments );

  }

  else if (window_num == 2){
    glClearColor( .4f, .1f, .2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    //draw_axes(scale_main);
  }
  else if (window_num == 3){
    glClearColor( .1f, .5f, .3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  /////////////////////SolidLINES ARRAY
    if(threeViewOrOne==1){
      view_2d_printer();
      }
    else{
    line_2d_printer();
    }
  }
  else if (window_num == 4){
    glClearColor( .2f, .5f, .9f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    view_2d_printer();  
  } 
  else if (window_num == 5){
    glClearColor( .6f, .4f, .1f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    line_3d_printer();
    draw_axes( 1.0 );
  }
  else if (window_num == 6){
    glClearColor( .8f, .3f, .5f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
  }
  else if (window_num == 7){
    glClearColor( .2f, .2f, .2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    line_3d_printer();
    draw_axes( 1.0 );
  }
  else if (window_num == 8){
    glClearColor( .9f, .6f, .6f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    file_3d_printer();
    draw_axes( 1.0 );
  }
  else if (window_num == 9){
    glClearColor( .7f, .8f, .1f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    view_2d_printer();
  }

  glutSwapBuffers(); 
}



/************************************************** draw_axes() **********/
/* Disables lighting, then draws RGB axes                                */



