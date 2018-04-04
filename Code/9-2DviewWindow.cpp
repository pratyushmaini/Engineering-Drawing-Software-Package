#include <vector>
// #include "File2D.h"
#include <string.h>
#include <GL/glui.h>
#include <gtk/gtk.h>
#include <fstream> 
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "File2D_3D.h"
using namespace std;

File3D viewFile;
File2D printFile;

// extern int window_num;
extern float scale;
extern int main_window;
extern int main2DSave(int argc, char* argv[]);
float obj_pos_view2D[] = { 0.0, 0.0, 0.0 }; 
GLUI *glui_view2D1, *glui_view2D;
extern  char *filename;

#define Home3Dto2D             900
#define LabelShow3Dto2D        901
#define Edit3Dto2D   		   902
#define Save3D_9               903
#define Save2D_9   		       904

File3D inputFile3D; 
extern int home();
extern File3D input3D;

void BackToModeSelectionUI_2Dview();
void Save3D_2Dview();
void Save2D_2Dview();

string saveDirectory;



void control_cb_view2D( int control )
{  

  if ( control == Home3Dto2D )
  {
    window_num = 1;
    glui_view2D -> close();
    glui_view2D1 -> close();
    BackToModeSelectionUI_2Dview();
  }
  else if ( control == LabelShow3Dto2D )
  {
  	
    
  }
  else if ( control == Edit3Dto2D )
  {
    glui_view2D -> close();
    glui_view2D1 -> close();
    window_num = 7;
    Line3DInput(inputFile3D);

  }
  else if ( control == Save3D_9 )
  {
  	cout << "Here0" <<endl;
    int zero =	main2DSave(NULL, NULL);
    Save3D_2Dview();
    
  }
  else if ( control == Save2D_9 )
  {
    int zero =	main2DSave(NULL, NULL);
    Save2D_2Dview();
  }

}

void translate2Dview (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom2Dview(int zoom_amount){
	///zoom in/out by entering percentage
}

void LabelShow2Dview(int show){
	//View or Hide Labels
}

void Edit3Dto2D_2Dview (File3D inputFile){
	///Edit 3D Model
	File3D input = Line3DInput(inputFile);
}


void BackToModeSelectionUI_2Dview(){
	///BackToModeSelectionUI after having seen the 3D object
	home();
}

void Save3D_2Dview(){
	///Makes a text File that contains the 3D array
	cout<< "kafhahfakhf"<<endl;
	cout<< filename << endl;
  ofstream outfile3D (filename);
  outfile3D << "Node Array:" << endl;
  outfile3D << input3D.Node_array.size() << endl;

  for(int i=0; i< input3D.Node_array.size(); i++){
    outfile3D << input3D.Node_array[i].coord3D.a << " " << input3D.Node_array[i].coord3D.b << " " << input3D.Node_array[i].coord3D.c << " " << input3D.Node_array[i].coord3D.name << endl;
    for(int j=0; j< input3D.Node_array[i].array_neighbour.size(); j++){
      outfile3D << input3D.Node_array[i].array_neighbour[j].a << " ";
      outfile3D << input3D.Node_array[i].array_neighbour[j].b << " ";
      outfile3D << input3D.Node_array[i].array_neighbour[j].c << " ";
      outfile3D << input3D.Node_array[i].array_neighbour[j].name << " ";
      }
    outfile3D << endl;
  }

  outfile3D << "Plane Array:" << endl;  
  outfile3D << input3D.Plane_array.size() << endl;

  for(int i=0; i< input3D.Plane_array.size(); i++){
      for(int j=0; j< input3D.Plane_array[i].circ_neighbour.size(); j++){
        outfile3D << input3D.Plane_array[i].circ_neighbour[j].a << " ";
        outfile3D << input3D.Plane_array[i].circ_neighbour[j].b << " ";
        outfile3D << input3D.Plane_array[i].circ_neighbour[j].c << " ";
        outfile3D << input3D.Plane_array[i].circ_neighbour[j].name << " ";
        }
      outfile3D << endl;
    }

  outfile3D.close();
}

void Save2D_2Dview(){
	///Makes a text File that contains the 3D array
	ofstream outfile3D (filename);
	outfile3D << "Front View:" << endl;
	outfile3D << printFile.Frontview.node_array.size() << endl;

	for(int i=0; i< printFile.Frontview.node_array.size(); i++){
		outfile3D << printFile.Frontview.node_array[i].coord.a << " " << printFile.Frontview.node_array[i].coord.b << " " << printFile.Frontview.node_array[i].coord.name << endl;
		outfile3D << printFile.Frontview.node_array[i].solid_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Frontview.node_array[i].solid_array_neighbour.size(); j++){
			outfile3D << printFile.Frontview.node_array[i].solid_array_neighbour[j].a << " " << printFile.Frontview.node_array[i].solid_array_neighbour[j].b << " " << printFile.Frontview.node_array[i].solid_array_neighbour[j].name << " ";
		}
		if(printFile.Frontview.node_array[i].solid_array_neighbour.size()!=0)
		outfile3D << endl;
		outfile3D << printFile.Frontview.node_array[i].dashed_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Frontview.node_array[i].dashed_array_neighbour.size(); j++){
			outfile3D << printFile.Frontview.node_array[i].dashed_array_neighbour[j].a << " " << printFile.Frontview.node_array[i].dashed_array_neighbour[j].b << " " << printFile.Frontview.node_array[i].dashed_array_neighbour[j].name << " ";
		}
		if(printFile.Frontview.node_array[i].dashed_array_neighbour.size()!=0)
		outfile3D << endl;
	}

	outfile3D << "Side View:" << endl;
	outfile3D << printFile.Sideview.node_array.size() << endl;

	for(int i=0; i< printFile.Sideview.node_array.size(); i++){
		outfile3D << printFile.Sideview.node_array[i].coord.a << " " << printFile.Sideview.node_array[i].coord.b << " " << printFile.Sideview.node_array[i].coord.name << endl;
		outfile3D << printFile.Sideview.node_array[i].solid_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Sideview.node_array[i].solid_array_neighbour.size(); j++){
			outfile3D << printFile.Sideview.node_array[i].solid_array_neighbour[j].a << " " << printFile.Sideview.node_array[i].solid_array_neighbour[j].b << " " << printFile.Sideview.node_array[i].solid_array_neighbour[j].name << " ";
		}
		if(printFile.Sideview.node_array[i].solid_array_neighbour.size()!=0)
		outfile3D << endl;
		outfile3D << printFile.Sideview.node_array[i].dashed_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Sideview.node_array[i].dashed_array_neighbour.size(); j++){
			outfile3D << printFile.Sideview.node_array[i].dashed_array_neighbour[j].a << " " << printFile.Sideview.node_array[i].dashed_array_neighbour[j].b << " " << printFile.Sideview.node_array[i].dashed_array_neighbour[j].name << " ";
		}
		if(printFile.Sideview.node_array[i].dashed_array_neighbour.size()!=0)
		outfile3D << endl;
	}

	outfile3D << "Top View:" << endl;
	outfile3D << printFile.Topview.node_array.size() << endl;

	for(int i=0; i< printFile.Topview.node_array.size(); i++){
		outfile3D << printFile.Topview.node_array[i].coord.a << " " << printFile.Topview.node_array[i].coord.b << " " << printFile.Topview.node_array[i].coord.name << endl;
		outfile3D << printFile.Topview.node_array[i].solid_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Topview.node_array[i].solid_array_neighbour.size(); j++){
			outfile3D << printFile.Topview.node_array[i].solid_array_neighbour[j].a << " " << printFile.Topview.node_array[i].solid_array_neighbour[j].b << " " << printFile.Topview.node_array[i].solid_array_neighbour[j].name << " ";
		}
		if(printFile.Topview.node_array[i].solid_array_neighbour.size()!=0)
		outfile3D << endl;
		outfile3D << printFile.Topview.node_array[i].dashed_array_neighbour.size() << endl;
		for(int j=0; j< printFile.Topview.node_array[i].dashed_array_neighbour.size(); j++){
			outfile3D << printFile.Topview.node_array[i].dashed_array_neighbour[j].a << " " << printFile.Topview.node_array[i].dashed_array_neighbour[j].b << " " << printFile.Topview.node_array[i].dashed_array_neighbour[j].name << " ";
		}
		if(printFile.Topview.node_array[i].dashed_array_neighbour.size()!=0)
		outfile3D << endl;
	}

	outfile3D.close();
}
void view_2d_printer(){

	//curr_printing.node_array
	//printf("Reached line_2d_Printer1\n");
	OrthographicView curr_printing = printFile.Frontview;
	glClearColor( .5f, .9f, .3f, 1.0f );
	glLoadIdentity();
	glTranslatef( obj_pos_view2D[0], obj_pos_view2D[1], -obj_pos_view2D[2] ); 
	// glScalef(abs(obj_pos_view2D[2]), abs(obj_pos_view2D[2]), abs(obj_pos_view2D[2]));
	// cout<< obj_pos_view2D[2]<<endl;
	// cout <<"Frontview"<<endl;
	// cout<< curr_printing.node_array.size()<<endl;
	for (int q=0; q< curr_printing.node_array.size(); q++){
		vector2 coord_base = curr_printing.node_array[q].coord;
		for (int r=0; r< curr_printing.node_array[q].solid_array_neighbour.size(); r++){
			vector2 coord_solid_temp = curr_printing.node_array[q].solid_array_neighbour[r];
			float temp_draw_array[] = {coord_base.a, coord_base.b, coord_solid_temp.a, coord_solid_temp.b};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 // cout << coord_base.a << "next" << coord_base.b << "next" << coord_solid_temp.a << "next" << coord_solid_temp.b <<endl;
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( (temp_draw_array[0] - 3)*abs(obj_pos_view2D[2]) , (temp_draw_array[1] - 3)*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( (temp_draw_array[2] - 3)*abs(obj_pos_view2D[2]), (temp_draw_array[3] - 3)*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();

			  glEnable( GL_LIGHTING );
		}
		for (int s=0; s< curr_printing.node_array[q].dashed_array_neighbour.size(); s++){
			vector2 coord_dashed_temp = curr_printing.node_array[q].dashed_array_neighbour[s];
			GLfloat temp_draw_array_dashed[] = {coord_base.a, coord_base.b, coord_dashed_temp.a, coord_dashed_temp.b};
			 glLineStipple(3, 0x1C47);
			 glEnable(GL_LINE_STIPPLE);
			 glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( (temp_draw_array_dashed[0] - 3)*abs(obj_pos_view2D[2]), (temp_draw_array_dashed[1] - 3)*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( (temp_draw_array_dashed[2] - 3)*abs(obj_pos_view2D[2]), (temp_draw_array_dashed[3] - 3)*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();
			  glDisable(GL_LINE_STIPPLE);
			  glEnable( GL_LIGHTING );
		}
		
	}
	curr_printing = printFile.Topview;
	// cout <<"Topview"<<endl;
	// cout<< curr_printing.node_array.size()<<endl;
	for (int q=0; q< curr_printing.node_array.size(); q++){
		vector2 coord_base = curr_printing.node_array[q].coord;
		for (int r=0; r< curr_printing.node_array[q].solid_array_neighbour.size(); r++){
			vector2 coord_solid_temp = curr_printing.node_array[q].solid_array_neighbour[r];
			float temp_draw_array[] = {coord_base.a, coord_base.b, coord_solid_temp.a, coord_solid_temp.b};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 // cout << coord_base.a << "next" << coord_base.b << "next" << coord_solid_temp.a << "next" << coord_solid_temp.b <<endl;
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( (temp_draw_array[0] - 3)*abs(obj_pos_view2D[2]), temp_draw_array[1]*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( (temp_draw_array[2] - 3)*abs(obj_pos_view2D[2]), temp_draw_array[3]*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();

			  glEnable( GL_LIGHTING );
		}
		for (int s=0; s< curr_printing.node_array[q].dashed_array_neighbour.size(); s++){
			vector2 coord_dashed_temp = curr_printing.node_array[q].dashed_array_neighbour[s];
			GLfloat temp_draw_array_dashed[] = {coord_base.a, coord_base.b, coord_dashed_temp.a, coord_dashed_temp.b};
			 glLineStipple(3, 0x1C47);
			 glEnable(GL_LINE_STIPPLE);
			glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( (temp_draw_array_dashed[0] - 3)*abs(obj_pos_view2D[2]), temp_draw_array_dashed[1]*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( (temp_draw_array_dashed[2] - 3)*abs(obj_pos_view2D[2]), temp_draw_array_dashed[3]*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();
			  glDisable(GL_LINE_STIPPLE);
			  glEnable( GL_LIGHTING );
		}
		
	}
	curr_printing = printFile.Sideview;
	// cout <<"Sideview"<<endl;
	// cout<< curr_printing.node_array.size()<<endl;
	for (int q=0; q< curr_printing.node_array.size(); q++){
		vector2 coord_base = curr_printing.node_array[q].coord;
		for (int r=0; r< curr_printing.node_array[q].solid_array_neighbour.size(); r++){
			vector2 coord_solid_temp = curr_printing.node_array[q].solid_array_neighbour[r];
			float temp_draw_array[] = {coord_base.a, coord_base.b, coord_solid_temp.a, coord_solid_temp.b};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 // cout << coord_base.a << "next" << coord_base.b << "next" << coord_solid_temp.a << "next" << coord_solid_temp.b <<endl;
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( temp_draw_array[0]*abs(obj_pos_view2D[2]), (temp_draw_array[1] - 3)*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( temp_draw_array[2]*abs(obj_pos_view2D[2]), (temp_draw_array[3] - 3)*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();

			  glEnable( GL_LIGHTING );
		}
		for (int s=0; s< curr_printing.node_array[q].dashed_array_neighbour.size(); s++){
			vector2 coord_dashed_temp = curr_printing.node_array[q].dashed_array_neighbour[s];
			GLfloat temp_draw_array_dashed[] = {coord_base.a, coord_base.b, coord_dashed_temp.a, coord_dashed_temp.b};
			 glLineStipple(3, 0x1C47);
			 glEnable(GL_LINE_STIPPLE);
			glDisable( GL_LIGHTING );

			  glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glBegin( GL_LINES );
			 
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( temp_draw_array_dashed[0]*abs(obj_pos_view2D[2]), (temp_draw_array_dashed[1] - 3)*abs(obj_pos_view2D[2]), 0.0 );  glVertex3f( temp_draw_array_dashed[2]*abs(obj_pos_view2D[2]), (temp_draw_array_dashed[3] - 3)*abs(obj_pos_view2D[2]), 0.0 );
			  glEnd();

			  // glPopMatrix();
			  glDisable(GL_LINE_STIPPLE);
			  glEnable( GL_LIGHTING );
		}
		
	}
}

void getUIView2D(){
	  glui_view2D = GLUI_Master.create_glui_subwindow( main_window, 
                                             GLUI_SUBWINDOW_BOTTOM );
  glui_view2D->set_main_gfx_window( main_window );

  obj_pos_view2D[2] = 0.2f;
  
  GLUI_Translation *trans_xy = 
    new GLUI_Translation(glui_view2D, "Objects XY", GLUI_TRANSLATION_XY, obj_pos_view2D );
  trans_xy->set_speed( .005 );
  new GLUI_Column( glui_view2D, false );
  GLUI_Translation *trans_x = 
    new GLUI_Translation(glui_view2D, "Objects X", GLUI_TRANSLATION_X, obj_pos_view2D );
  trans_x->set_speed( .005 );
  new GLUI_Column( glui_view2D, false );
  GLUI_Translation *trans_y = 
    new GLUI_Translation( glui_view2D, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos_view2D[1] );
  trans_y->set_speed( .005 );
  new GLUI_Column( glui_view2D, false );
  GLUI_Translation *trans_z = 
    new GLUI_Translation( glui_view2D, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos_view2D[2] );
  trans_z->set_speed( .005 );
}

void View2DWindow(File2D outFile, File3D inputFile){
	///Manages all actions depending on mouse and keyboard input
	printFile = outFile;
	inputFile3D = inputFile;
	glui_view2D1 = GLUI_Master.create_glui_subwindow( main_window, 
					    GLUI_SUBWINDOW_RIGHT );
   glui_view2D1->set_main_gfx_window( main_window );

   /*** Disable/Enable buttons ***/
   	new GLUI_Button( glui_view2D1, "Home", Home3Dto2D, control_cb_view2D );
   	new GLUI_Button( glui_view2D1, "Show Labels", LabelShow3Dto2D, control_cb_view2D );
  	new GLUI_Button( glui_view2D1, "Edit File", Edit3Dto2D, control_cb_view2D );
 	new GLUI_Button( glui_view2D1, "Save3D File", Save3D_9, control_cb_view2D );
  	new GLUI_Button( glui_view2D1, "Save2D File", Save2D_9, control_cb_view2D );




  	getUIView2D();
}
