#include <GLUT/glut.h>
#include <GL/glui.h>
#include <iostream>
// #include "File2D.h"
// #include "File3D.h"
#include "File2D_3D.h"
/*! \mainpage Engineering Drawing Software
 *
 * \section intro_sec Description
 *
 * Engineering Drawing Software is a tool for generating orhotgraphic views of a 3D model and for generating 3D model from the orthographic views.
 
 *This a documentation for Engineering Drawing Software Package 
  
  *Work by Pratyush Maini and Pranav Baurasia
  
  *The Code has been Modularised into 9 C++ files and two header files.

  *1-main.cpp:: The first file that is compiled and is basically used for mode selection and calling sub-functions. This enables users selection of a 2D window or 3D window.

  *This also the point where we make use of th rendering libraries in OpenGL and GLUT to draw objects and provide graphic user interface for the user. The same have been included in the libraries.

  *File2D.h:: Contains all the classes that we require for the two dimensional interface, and also the window that is seen upon 2D transformation into a 3D object. The functions associated with each class are also flagged herein.

  *2-twoDmain.cpp:: Functions in this file are called when the user decides to draw 2D orthographic projections of an object or import a file from his local database. The basic purpose of the functions in this file is to make a user select between drawing/importing a file.

  *3-LineDrawing.cpp:: Contains all the functions that enable a user to create new nodes, join two nodes, delete nodes etc. while making a 2D diagram. 
	
  *4-InputFor2D.cpp:: The user is given two choices of either loading a labeled file, or an unlabeled one, in whic case he is supposed to Add Labels through getLabels().

  *5-3DviewWindow.cpp:: The basic UI for viewing the 3D object in different ways as per the user's convenience.

  *File3D.h:: Contains all the classes that we require for the three dimensional interface, and also the window that is seen upon 3D transformation into a 2D object. The functions associated with each class are also flagged herein.

  *6-threeDmain.cpp:: Functions in this file are called when the user decides to draw 3D view of an object or import a file from his local database. The basic purpose of the functions in this file is to make a user select between drawing/importing a file.

  *7-LineDrawingFor3Dto2D.cpp:: Contains all the functions that enable a user to create new nodes, join two nodes, delete nodes etc. while making a 3D diagram.

  *8-InputFor3Dto2D.cpp:: The user is given two choices of either loading a labeled file, or an unlabeled one, in whic case he is supposed to Add Labels through getLabels(), and mark all the Solid Planes.

  *9-2DviewWindow.cpp:: The basic UI for viewing the orthographic projections of the object in different ways as per the user's convenience.


 */

using namespace std;

///Mode Selection and basic IO
int TwoDmode, ThreeDmode; 

GLuint main_window;
//  The id of the main window
GLUI * glui_window;
// extern void C2DFile();
// extern void C3DFile();

void render(void);
 
void keyboard(unsigned char c, int x, int y);
 
void mouse(int button, int state, int x, int y);

///Selects between 2DMode and 3Dmode
void modeSelection();

void setup() 
{ 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	///Any other requirement at the time of setup
}
void display() { 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* drawing commands would go here, if we had any yet... */
	/*Displays a simple rectangle as of now
	glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-0.75f,0.75f, 0.75f, -0.75f);*/
    modeSelection();
    glutSwapBuffers();
    
 }

void setupGLUI ();
//  Idle callack function
void idle ();

int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(400, 200);
        glutInitWindowSize(640, 480);
        main_window = glutCreateWindow("Engineering Drawing Software Package");
        TwoDmode = 0; ThreeDmode =0;
        glutDisplayFunc(render);       
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);

        //GLUI
        setupGLUI();

        glutMainLoop();
}	

void keyboard(unsigned char c, int x, int y) {
        if (c == 27) {
                exit(0);
        }
}

void mouse(int button, int state, int x, int y) {
        if (button == GLUT_RIGHT_BUTTON) {
                exit(0);
        }
}
 
void render(void) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        glBegin(GL_TRIANGLES);
                glColor3f(1, 0, 0);
                glVertex2f(-0.5, -0.5);
                glColor3f(0, 1, 0);
                glVertex2f(0.5, -0.5);
                glColor3f(0, 0, 1);
                glVertex2f(0.0, 0.5);
        glEnd();
 
        glutSwapBuffers();
}

void modeSelection(){
  
  if (TwoDmode == 1) {
    C2DFile();
    TwoDmode = 0;
  }
  else if (ThreeDmode == 1) {
    C3DFile();
    ThreeDmode = 0;
  }

}

void setupGLUI (){
  //  Set idle function
  GLUI_Master.set_glutIdleFunc (idle);
  //  Create GLUI window
  glui_window = GLUI_Master.create_glui ("Options", 0, 1000, 1000);
}

void idle ()
{
  glutSetWindow (main_window);
  glutPostRedisplay ();
  //Sleep (50);
}