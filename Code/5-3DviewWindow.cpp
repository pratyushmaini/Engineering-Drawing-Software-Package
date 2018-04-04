#include <string.h>
#include <GL/glui.h>
#include <vector>
#include <fstream> 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "File2D_3D.h"
using namespace std;

extern int main_window;
extern void home();
extern File3D outputFile3D;
// extern int window_num;
extern float view_rotate[] ;
extern float obj_pos[] ;
extern int main2DSave(int argc, char* argv[]); 

File2D outputFile2D;
extern GLfloat lights_rotation3D[];
extern char *filename;
GLUI *glui_view3D1, *glui_view3D;
extern OrthographicView editView(OrthographicView initialView);

#define Home2D             500
#define Edit2D   		       502
#define Save3D             503
#define Save2D   		       504
#define Reset              505

void view_3d_printer();
void Save3D_3Dview();
void Save2D_3Dview();

void control_cb_view3D( int control )
{  

  if ( control == Home2D )
  {
    window_num = 1;
    glui_view3D1 -> close();
    glui_view3D -> close();
    home();
  }
  else if ( control == Edit2D )
  {
    window_num = 3;
    glui_view3D1 -> close();
    glui_view3D -> close();
    Line2DInput(outputFile2D);
  }
  else if ( control == Save3D )
  {
   int zero = main2DSave(NULL, NULL);
   Save3D_3Dview();
  }
  else if ( control == Save2D )
  {
   int zero = main2DSave(NULL, NULL);
   Save2D_3Dview(); 
  }
  else if (control == Reset){
    cout << "RESET" << endl;
    float temp_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    for (int i=0; i<16; i++)
      {view_rotate[i] = temp_rotate[i];}
    
  }

}

void translate3Dview (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom3Dview(int zoom_amount){
	///zoom in/out by entering percentage
}

void Rotate3Dview (float x_rotate, float y_rotate, float z_rotate){
	///Rotate XYZ by entering degree rotation along each axis
}

void Edit3Dview (File2D inputFile){
	///Edit 2D Model
	File2D input = Line2DInput(inputFile);
}

void BackToModeSelectionUI3Dview(){
	///BackToModeSelectionUI after having seen the 3D object

}

void Save3D_3Dview(){
	///Makes a text File that contains the 3D array
  ofstream outfile3D (filename);
  outfile3D << "Node Array:" << endl;
  outfile3D << outputFile3D.Node_array.size() << endl;

  for(int i=0; i< outputFile3D.Node_array.size(); i++){
    outfile3D << outputFile3D.Node_array[i].coord3D.a << " " << outputFile3D.Node_array[i].coord3D.b << " " << outputFile3D.Node_array[i].coord3D.c << " " << outputFile3D.Node_array[i].coord3D.name << endl;
    for(int j=0; j< outputFile3D.Node_array[i].array_neighbour.size(); j++){
      outfile3D << outputFile3D.Node_array[i].array_neighbour[j].a << " ";
      outfile3D << outputFile3D.Node_array[i].array_neighbour[j].b << " ";
      outfile3D << outputFile3D.Node_array[i].array_neighbour[j].c << " ";
      outfile3D << outputFile3D.Node_array[i].array_neighbour[j].name << " ";
      }
    outfile3D << endl;
  }

  outfile3D << "Plane Array:" << endl;  
  outfile3D << outputFile3D.Plane_array.size() << endl;

  for(int i=0; i< outputFile3D.Plane_array.size(); i++){
      for(int j=0; j< outputFile3D.Plane_array[i].circ_neighbour.size(); j++){
        outfile3D << outputFile3D.Plane_array[i].circ_neighbour[j].a << " ";
        outfile3D << outputFile3D.Plane_array[i].circ_neighbour[j].b << " ";
        outfile3D << outputFile3D.Plane_array[i].circ_neighbour[j].c << " ";
        outfile3D << outputFile3D.Plane_array[i].circ_neighbour[j].name << " ";
        }
      outfile3D << endl;
    }

  outfile3D.close();
}

void Save2D_3Dview(){
  ///Makes a text File that contains the 3D array
  ofstream outfile3D (filename);
  outfile3D << "Front View:" << endl;
  outfile3D << outputFile2D.Frontview.node_array.size() << endl;

  for(int i=0; i< outputFile2D.Frontview.node_array.size(); i++){
    outfile3D << outputFile2D.Frontview.node_array[i].coord.a << " " << outputFile2D.Frontview.node_array[i].coord.b << " " << outputFile2D.Frontview.node_array[i].coord.name << endl;
    outfile3D << outputFile2D.Frontview.node_array[i].solid_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Frontview.node_array[i].solid_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Frontview.node_array[i].solid_array_neighbour[j].a << " " << outputFile2D.Frontview.node_array[i].solid_array_neighbour[j].b << " " << outputFile2D.Frontview.node_array[i].solid_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Frontview.node_array[i].solid_array_neighbour.size()!=0)
    outfile3D << endl;
    outfile3D << outputFile2D.Frontview.node_array[i].dashed_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Frontview.node_array[i].dashed_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Frontview.node_array[i].dashed_array_neighbour[j].a << " " << outputFile2D.Frontview.node_array[i].dashed_array_neighbour[j].b << " " << outputFile2D.Frontview.node_array[i].dashed_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Frontview.node_array[i].dashed_array_neighbour.size()!=0)
    outfile3D << endl;
  }

  outfile3D << "Side View:" << endl;
  outfile3D << outputFile2D.Sideview.node_array.size() << endl;

  for(int i=0; i< outputFile2D.Sideview.node_array.size(); i++){
    outfile3D << outputFile2D.Sideview.node_array[i].coord.a << " " << outputFile2D.Sideview.node_array[i].coord.b << " " << outputFile2D.Sideview.node_array[i].coord.name << endl;
    outfile3D << outputFile2D.Sideview.node_array[i].solid_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Sideview.node_array[i].solid_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Sideview.node_array[i].solid_array_neighbour[j].a << " " << outputFile2D.Sideview.node_array[i].solid_array_neighbour[j].b << " " << outputFile2D.Sideview.node_array[i].solid_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Sideview.node_array[i].solid_array_neighbour.size()!=0)
    outfile3D << endl;
    outfile3D << outputFile2D.Sideview.node_array[i].dashed_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Sideview.node_array[i].dashed_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Sideview.node_array[i].dashed_array_neighbour[j].a << " " << outputFile2D.Sideview.node_array[i].dashed_array_neighbour[j].b << " " << outputFile2D.Sideview.node_array[i].dashed_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Sideview.node_array[i].dashed_array_neighbour.size()!=0)
    outfile3D << endl;
  }

  outfile3D << "Top View:" << endl;
  outfile3D << outputFile2D.Topview.node_array.size() << endl;

  for(int i=0; i< outputFile2D.Topview.node_array.size(); i++){
    outfile3D << outputFile2D.Topview.node_array[i].coord.a << " " << outputFile2D.Topview.node_array[i].coord.b << " " << outputFile2D.Topview.node_array[i].coord.name << endl;
    outfile3D << outputFile2D.Topview.node_array[i].solid_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Topview.node_array[i].solid_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Topview.node_array[i].solid_array_neighbour[j].a << " " << outputFile2D.Topview.node_array[i].solid_array_neighbour[j].b << " " << outputFile2D.Topview.node_array[i].solid_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Topview.node_array[i].solid_array_neighbour.size()!=0)
    outfile3D << endl;
    outfile3D << outputFile2D.Topview.node_array[i].dashed_array_neighbour.size() << endl;
    for(int j=0; j< outputFile2D.Topview.node_array[i].dashed_array_neighbour.size(); j++){
      outfile3D << outputFile2D.Topview.node_array[i].dashed_array_neighbour[j].a << " " << outputFile2D.Topview.node_array[i].dashed_array_neighbour[j].b << " " << outputFile2D.Topview.node_array[i].dashed_array_neighbour[j].name << " ";
    }
    if(outputFile2D.Topview.node_array[i].dashed_array_neighbour.size()!=0)
    outfile3D << endl;
  }

  outfile3D.close();

}


void View3DWindow(File3D outFile, File2D inputFile){
	///Manages all actions depending on mouse and keyboard input
	/*** Create the bottom subwindow ***/
  obj_pos[2] = 0.2f;
   glui_view3D1 = GLUI_Master.create_glui_subwindow( main_window, 
					    GLUI_SUBWINDOW_RIGHT );
   glui_view3D1->set_main_gfx_window( main_window );

   outputFile3D = outFile;
   outputFile2D = inputFile;
   /*** Disable/Enable buttons ***/
   	new GLUI_Button( glui_view3D1, "Home", Home2D, control_cb_view3D );
  	new GLUI_Button( glui_view3D1, "Edit File", Edit2D, control_cb_view3D );
 	new GLUI_Button( glui_view3D1, "Save3D File", Save3D, control_cb_view3D );
  	new GLUI_Button( glui_view3D1, "Save2D File", Save2D, control_cb_view3D );




  glui_view3D = GLUI_Master.create_glui_subwindow( main_window, 
                                             GLUI_SUBWINDOW_BOTTOM );
  glui_view3D->set_main_gfx_window( main_window );

  GLUI_Rotation *view_rot = new GLUI_Rotation(glui_view3D, "Objects", view_rotate );
  view_rot->set_spin( 1.0 );
  new GLUI_Column( glui_view3D, false );
  GLUI_Rotation *lights_rot = new GLUI_Rotation(glui_view3D, "Blue Light", lights_rotation3D );
  lights_rot->set_spin( .82 );
  new GLUI_Column( glui_view3D, false );
  GLUI_Translation *trans_xy = 
    new GLUI_Translation(glui_view3D, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
  trans_xy->set_speed( .005 );
  new GLUI_Column( glui_view3D, false );
  GLUI_Translation *trans_x = 
    new GLUI_Translation(glui_view3D, "Objects X", GLUI_TRANSLATION_X, obj_pos );
  trans_x->set_speed( .005 );
  new GLUI_Column( glui_view3D, false );
  GLUI_Translation *trans_y = 
    new GLUI_Translation( glui_view3D, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
  trans_y->set_speed( .005 );
  new GLUI_Column( glui_view3D, false );
  GLUI_Translation *trans_z = 
    new GLUI_Translation( glui_view3D, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
  trans_z->set_speed( .005 );
    new GLUI_Column( glui_view3D, false );
  new GLUI_Button( glui_view3D, "Reset Rotation", Reset, control_cb_view3D );

}
