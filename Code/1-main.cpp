#include <string.h>
#include <GL/glui.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "File2D_3D.h"
#include <gtk/gtk.h>
#include <vector>
#include <fstream> 
#include <cmath>
#include <iostream>




using namespace std;

/*! \mainpage Engineering Drawing Software aka ED
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
/** These are the live variables passed into GLUI ***/
 char *filename;
int mode = 0;
int file_num = 0;
int main_window;
extern int main_window;
// extern int window_num;

//int segments = 4;
//int wireframe = 0;
float xy_aspect_main;
// float scale_main = 1.0;
GLfloat light0_ambient3D[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse3D[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position3D[] = {1.5f*100, 6.5f*100, 5.0f*100, 1.0f};

GLfloat light1_ambient3D[] =  {0.6f, 0.5f, 0.8f, 1.0f};
GLfloat light1_diffuse3D[] =  {.9f, .3f, 0.5f, 1.0f};
GLfloat light1_position3D[] = {-2.0f*100, -5.0f*100, 2.0f*100, 1.0f};

/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;


/********** User IDs for callbacks ********/
#define Mode2D           300
#define Mode3D           301



void modeSelection(){
  
  if (mode == 2) {
    // printf("Apple\n");
    window_num = 2;
    C2DFile();
    // printf("Ball\n");
    mode = 0;
  }
  else if (mode == 3) {
    window_num = 6;
    C3DFile();
    mode = 0;
  }

}

static void open_dialogSave3D(GtkWidget* button, gpointer window)
{
    GtkWidget *dialog;
    cout << "Here" <<endl;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Save File", GTK_WINDOW(window), action, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
  chooser = GTK_FILE_CHOOSER (dialog);
  cout << "Here2" <<endl;

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  // if (user_edited_a_new_document)
    gtk_file_chooser_set_current_name (chooser, "untitled.txt");
  // else
  //  gtk_file_chooser_set_filename (chooser, existing_filename);
  cout << "Here3" <<endl;
  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
   {

      filename = gtk_file_chooser_get_filename (chooser);
      cout << filename << endl;
      
      // save_to_file (filename);
      // g_free (filename);
    }

  gtk_widget_destroy (dialog);
}

int main2DSave(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    cout << "Here9" <<endl;
    GtkWidget *window, *button;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    cout << "Here11" <<endl;
    button = gtk_button_new_with_label("Save File");
    cout << "Here11" <<endl;
    g_signal_connect(button, "clicked", G_CALLBACK(open_dialogSave3D), window);
    cout << "Here11" <<endl;
    gtk_container_set_border_width(GTK_CONTAINER(window), 100);
    cout << "Here11" <<endl;
    gtk_container_add(GTK_CONTAINER(window), button);
  cout << "Here11" <<endl;
    gtk_widget_show_all(window);
  cout << "Here11" <<endl;
  gtk_main();
  cout << "save3d" << endl;

    return 0;
}


/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb( int control )
{  
  // printf("HEy\n");

  if ( control == Mode2D )
  {
    mode = 2;
    // printf("Apple1\n");
    glui -> close();
    modeSelection();
  }
  else if ( control == Mode3D )
  {
    mode = 3;
    glui -> close();

    modeSelection();
  }

}

/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 27: 
  case 'q':
    exit(0);
    break;
  };
  
  glutPostRedisplay();
}


/***************************************** myGlutMenu() ***********/

void myGlutMenu( int value )
{
  myGlutKeyboard( value, 0, 0 );
}


/***************************************** myGlutIdle() ***********/

void myGlutIdle()
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */

  glutPostRedisplay();
}

/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int button_state, int x, int y )
{
}

void myGlutReshape( int x, int y )
{
  int tx, ty, tw, th;
  GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
  glViewport( tx, ty, tw, th );

  xy_aspect_main = (float)tw / (float)th;

  glutPostRedisplay();
}


// 


/***************************************** myGlutDisplay() *****************/

// void myGlutDisplay()
// {
//   static float rotationX = 0.0, rotationY = 0.0;

//   glClearColor( .3f, .3f, .8f, 1.0f );
//   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//   /*** Rotate the object ***/
//   rotationX += 1.3f;
//   rotationY += 1.3f;

//   glMatrixMode( GL_MODELVIEW );
//   glLoadIdentity();
//   glTranslatef( 0.0, 0.0, -1.0 );
//   glRotatef( rotationY, 0.0, 1.0, 0.0 );
//   glRotatef( rotationX, 1.0, 0.0, 0.0 );

//   /*** Now we render object, using the variables 'segments' and
//     'wireframe'.  These are _live_ variables, which are transparently 
//     updated by GLUI ***/
  
//   if ( wireframe )
//     glutWireTorus( .2,.5,16,segments );
//   else
//     glutSolidTorus( .2,.5,16,segments );

//   //draw_axes(scale_main);
//   line_2d_printer();

//   glutSwapBuffers(); 
// }

void mainGlutDisplay();

void home(){
  /*** Create the side subwindow ***/
  glui = GLUI_Master.create_glui_subwindow( main_window, 
              GLUI_SUBWINDOW_TOP );

  /*** Disable/Enable buttons ***/
  new GLUI_Button( glui, "Mode2D", Mode2D, control_cb );
  new GLUI_Column( glui, false );
  new GLUI_Button( glui, "Mode3D", Mode3D, control_cb );

  new GLUI_StaticText( glui, "" );


}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  /****************************************/
  /*   Initialize GLUT and create window  */
  /****************************************/

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
 
  main_window = glutCreateWindow( "Auto CAD" );
  glutDisplayFunc( mainGlutDisplay );
  GLUI_Master.set_glutReshapeFunc( myGlutReshape );  
  GLUI_Master.set_glutKeyboardFunc( myGlutKeyboard );
  GLUI_Master.set_glutSpecialFunc( NULL );
  GLUI_Master.set_glutMouseFunc( myGlutMouse );



  /****************************************/
  /*          Enable z-buferring          */
  /****************************************/

  glEnable(GL_DEPTH_TEST);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

  home(); 
    glEnable(GL_LIGHTING);
    glEnable( GL_NORMALIZE );

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient3D);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse3D);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position3D);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient3D);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse3D);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position3D);

    // glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
    // glEnable ( GL_COLOR_MATERIAL ) ;


  /****** A 'quit' button *****/
  

  glui2 = GLUI_Master.create_glui_subwindow( main_window, 
              GLUI_SUBWINDOW_BOTTOM );

  new GLUI_Button( glui2, "Quit", 0,(GLUI_Update_CB)exit );
  /**** Link windows to GLUI, and register idle callback ******/
  
  glui->set_main_gfx_window( main_window );
  glui2->set_main_gfx_window( main_window );

  /* We register the idle callback with GLUI, *not* with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle ); 
 

 
  glutMainLoop();

  return EXIT_SUCCESS;
}

