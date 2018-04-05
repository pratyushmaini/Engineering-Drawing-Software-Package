#include <vector>
// #include "File2D.h"
#include <string.h>
#include <GL/glui.h>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "../include/File2D_3D.h"
using namespace std;


#define Front          100
#define Top            101
#define Side           102
#define Done_Node      103
#define Undo           104
#define Done_Solid     105
#define Done_Dashed    106
#define Done_Overall   107
#define DeleteCall     108
#define TransTo3D      109
#define Back3		   110

extern float obj_pos_view2D[];
extern GLUI *glui_view2D;
extern void getUIView2D();
extern int main_window; 
extern int view = 3;
OrthographicView curr;
File2D outputFile;
extern File2D printFile;
File2D previous;
//1 for three ortho and 0 for one ortho
int threeViewOrOne = 0;
// extern int window_num;

float xy_aspect;
float   horiz = 0.0;
float   vert = 0.0;
float   label = 0;
float node_solid1 = 0, node_dashed1 = 0;
float node_solid2 = 0, node_dashed2 = 0, node_delete_label = 0;

float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float sphere_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float torus_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
GLfloat light0_position[] = {.5f, .5f, 1.0f, 0.0f};
GLfloat lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float scale = 1.0;
int total_nodes = 0;

GLUI_TextBox *label_box, *solid_label_box1, *solid_label_box2, *dashed_label_box1, *dashed_label_box2;
GLUI *glui_OrthSelection, *glui_LineOptions, *glui2_line;
GLUI_Panel      *obj_panel, *dashed_panel, *solid_panel, *delete_panel;
OrthographicView editView(OrthographicView initialView);
// void line_2d_printer();
// bool File2D::Makenode2D(vector2 v);


void undo2D (){
	outputFile = previous;
	///Undo previous Move
}

void control_cb_line( int control )
{	OrthographicView initialView;
  if ( control == Front )
  {
    view = 0;
    curr = outputFile.Frontview;
    threeViewOrOne = 0;
    glui_OrthSelection -> close();
    glui_view2D -> close();
    editView(initialView);
  }
  else if ( control == Top )
  {
    view = 1;
    curr = outputFile.Topview;
    threeViewOrOne = 0;
    glui_OrthSelection -> close();
    glui_view2D -> close();
    editView(initialView);
  }
  else if ( control == Side )
  {
    view = 2;
    curr = outputFile.Sideview;
    threeViewOrOne = 0;
    glui_OrthSelection -> close();
    glui_view2D -> close();
    editView(initialView);
  }
  else if ( control == TransTo3D )
  {
    window_num = 5;
    glui_OrthSelection -> close();
    glui_view2D -> close();
    File3D out3DFile = Start3DTrans(outputFile);
    File3D cube3;
    
    View3DWindow(out3DFile, outputFile);

  }
  else if (control == Done_Node){
  	vector2 Node_temp;
  	
  	float node_num = label;
  	
  	Node_temp.a = horiz;
  	Node_temp.b = vert;
  	int label_int = (int)label;
  	string label_str = std::to_string(label_int);
  	// std::ostringstream ss;
  	// ss << label;
  	// std::string label_str(ss.str());
  	Node_temp.name = label_str;
  	// cout << horiz << "space" <<  vert << endl;

  	outputFile.Makenode2D(Node_temp);
  }

  else if (control == Done_Solid){
  	//node_solid1, node_solid2
  	string node_solid1_str = std::to_string((int)node_solid1);
  	string node_solid2_str = std::to_string((int)node_solid2);
  	
  	outputFile.SolidLine2D(node_solid1_str, node_solid2_str);
  	line_2d_printer();
  }
  else if (control == Done_Dashed){
  	//node_solid1, node_solid2
  	string node_dashed1_str = std::to_string((int)node_dashed1);
  	string node_dashed2_str = std::to_string((int)node_dashed2);
  	
  	outputFile.DashedLine2D(node_dashed1_str, node_dashed2_str);
  	line_2d_printer();
  }
  else if (control == DeleteCall){
  	//node_solid1, node_solid2
  	string node_delete_str = std::to_string((int)node_delete_label);
  	
  	outputFile.deleteNode(node_delete_str);
  	line_2d_printer();
  }
  else if (control == Undo){
  	//node_solid1, node_solid2
  	undo2D();
  	line_2d_printer();
  }
  else if (control == Done_Overall){
  	if(view==0){
		outputFile.Frontview = curr;
	}
	else if(view==1){
		outputFile.Topview = curr;
	}
	else{
		outputFile.Sideview = curr;
	}
	threeViewOrOne = 1;
	printFile = outputFile;
	glui_LineOptions -> close();
	glui2_line -> close();

	Line2DInput(outputFile);
  }
  else if (control == Back3 ){
  	window_num = 2;
    glui_OrthSelection -> close();
    glui_view2D -> close();
    C2DFile();
  }


}

bool equalForVector2(vector2 node1, vector2 node2){
	if(node1.a == node2.a && node1.b == node2.b){
		return true;
	}
	else false;
}

bool File2D::Makenode2D(vector2 v){

	///The first linked adjacency list is of those neighbours connected via a solid line
	vector<vector2> solid_array;
	///The second linked adjacency list is of those neighbours connected via a dashed line
	vector<vector2> dashed_array;

	View_Node2D node(v, solid_array, dashed_array);

	curr.node_array.push_back(node);
	// cout << v.a << v.b << v.name << endl;
	// cout << node.coord.a << node.coord.b << node.coord.name << endl;
	// for (int m = 0; m< curr.node_array.size(); m++){
	// 	// cout << curr.node_array[m].coord.a << curr.node_array[m].coord.b << curr.node_array[m].coord.name << endl;

	// }
	return true;
} 



//make solid line
bool File2D::SolidLine2D(string node1, string node2){

	vector2 coord1, coord2;
	
	for(int i=0; i<curr.node_array.size(); i++){
		if(node1 == curr.node_array[i].coord.name){
			coord1 = curr.node_array[i].coord;
		}
		if(node2 == curr.node_array[i].coord.name){
			coord2 = curr.node_array[i].coord;
		}
	}	

	for(int i=0; i<curr.node_array.size(); i++){
		if(node1 == curr.node_array[i].coord.name){			
			for(int j=0; j<curr.node_array[i].solid_array_neighbour.size();j++){
				if(node2 == curr.node_array[i].solid_array_neighbour[j].name){
					return false;
				}
			}
			curr.node_array[i].solid_array_neighbour.push_back(coord2);

		}
		if(node2 == curr.node_array[i].coord.name){
			for(int j=0; j<curr.node_array[i].solid_array_neighbour.size();j++){
				if(node1 == curr.node_array[i].solid_array_neighbour[j].name){
					return false;
				}
			}

			curr.node_array[i].solid_array_neighbour.push_back(coord1);
		}
	}

	return true;

}

//make dashed line
bool File2D::DashedLine2D(string node1, string node2){

	vector2 coord1, coord2;
	
	for(int i=0; i<curr.node_array.size(); i++){
		if(node1 == curr.node_array[i].coord.name){
			coord1 = curr.node_array[i].coord;
		}
		if(node2 == curr.node_array[i].coord.name){
			coord2 = curr.node_array[i].coord;
		}
	}	

	for(int i=0; i<curr.node_array.size(); i++){
		if(node1 == curr.node_array[i].coord.name){			
			for(int j=0; j<curr.node_array[i].dashed_array_neighbour.size();j++){
				if(node2 == curr.node_array[i].dashed_array_neighbour[j].name){
					return false;
				}
			}
			curr.node_array[i].dashed_array_neighbour.push_back(coord2);

		}
		if(node2 == curr.node_array[i].coord.name){
			for(int j=0; j<curr.node_array[i].dashed_array_neighbour.size();j++){
				if(node1 == curr.node_array[i].dashed_array_neighbour[j].name){
					return false;
				}
			}

			curr.node_array[i].dashed_array_neighbour.push_back(coord1);
		}
	}

	return true;

}




///not completed
void File2D::deleteNode(string node){

	vector<vector2> solid , dashed;
	int i;
	for(i=0; i<curr.node_array.size(); i++){
		if(node==curr.node_array[i].coord.name){
   			solid = curr.node_array[i].solid_array_neighbour , dashed = curr.node_array[i].dashed_array_neighbour;
			curr.node_array.erase(curr.node_array.begin() + i);
			break;
		}
	}

	for(int j=0; j<solid.size(); j++){
		for(int k=0; k<curr.node_array.size(); k++){
			if(solid[j].name==curr.node_array[k].coord.name){
				for(int l=0; l<curr.node_array[k].solid_array_neighbour.size();l++){
					if(curr.node_array[k].solid_array_neighbour[l].name==node){
						curr.node_array[k].solid_array_neighbour.erase(curr.node_array[k].solid_array_neighbour.begin() + l);
						break;	
					}
				}
				break;
			}
		}
	}


	for(int j=0; j<dashed.size(); j++){
		for(int k=0; k<curr.node_array.size(); k++){
			if(dashed[j].name==curr.node_array[k].coord.name){
				for(int l=0; l<curr.node_array[k].dashed_array_neighbour.size();l++){
					if(curr.node_array[k].dashed_array_neighbour[l].name==node){
						curr.node_array[k].dashed_array_neighbour.erase(curr.node_array[k].dashed_array_neighbour.begin() + l);	
						break;
					}
				}
				break;
			}
		}
	}


}

OrthographicView editView(OrthographicView initialView){
	OrthographicView view_orth;
	glClearColor( .1f, .1f, .3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    glutSwapBuffers(); 


    obj_pos_view2D[2] = 0.2f;

    glui_LineOptions = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );

        //////////////////Create Node////////////////////////

    obj_panel = new GLUI_Rollout(glui_LineOptions, "Make Node", false );
    GLUI_Spinner *horiz_coord = 
    new GLUI_Spinner( obj_panel, "Horiz Coord:", &horiz);
    horiz_coord->set_int_limits( -40.0, 40.0 );
    horiz_coord->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *vert_coord = 
    new GLUI_Spinner( obj_panel, "Vert Coord:", &vert);
    vert_coord->set_float_limits( -40.0, 40.0 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );

    // new GLUI_StaticText (obj_panel, "   Label:");

    // label_box = new GLUI_EditText(obj_panel, true, 1);
    // // const char initial[] = "Enter Label Here:";
    // // label_box -> set_text(initial);
    // label_box -> set_h(20);
    // label_box -> set_w(75);
    GLUI_Spinner *label_text = 
    new GLUI_Spinner( obj_panel, "Node Number:", &label);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( obj_panel, "Done", Done_Node, control_cb_line );

    	    //////////////////Create Solid Line////////////////////////
    
    solid_panel = new GLUI_Rollout(glui_LineOptions, "Solid Line", false );
    

    GLUI_Spinner *solid_label_1 = 
    new GLUI_Spinner( solid_panel, "Node 1:", &node_solid1);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *solid_label_2 = 
    new GLUI_Spinner( solid_panel, "Node 2:", &node_solid2);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( solid_panel, "Done", Done_Solid, control_cb_line );

    		//////////////////Create Dashed Line////////////////////////

    dashed_panel = new GLUI_Rollout(glui_LineOptions, "Dashed Line", false );
    

    GLUI_Spinner *dashed_label_1 = 
    new GLUI_Spinner( dashed_panel, "Node 1:", &node_dashed1);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *dashed_label_2 = 
    new GLUI_Spinner( dashed_panel, "Node 2:", &node_dashed2);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );


    new GLUI_Button( dashed_panel, "Done", Done_Dashed, control_cb_line );
//////////////////////////Undo///////////////////////////////

    delete_panel = new GLUI_Rollout(glui_LineOptions, "Delete Node", false );

    GLUI_Spinner *delete_label = 
    new GLUI_Spinner( delete_panel, "Node Label:", &node_delete_label);
    vert_coord->set_float_limits( 0, 100 );
    vert_coord->set_alignment( GLUI_ALIGN_RIGHT );
    new GLUI_Button( delete_panel, "Delete", DeleteCall, control_cb_line );


    new GLUI_Button( glui_LineOptions, "Undo", Undo, control_cb_line );

    new GLUI_Button( glui_LineOptions, "Done", Done_Overall, control_cb_line );


    /*** Create the bottom subwindow ***/
  glui2_line = GLUI_Master.create_glui_subwindow( main_window, 
                                             GLUI_SUBWINDOW_BOTTOM );
  glui2_line->set_main_gfx_window( main_window );

  
  GLUI_Translation *trans_xy = 
    new GLUI_Translation(glui2_line, "Objects XY", GLUI_TRANSLATION_XY, obj_pos_view2D );
  trans_xy->set_speed( .005 );
  new GLUI_Column( glui2_line, false );
  GLUI_Translation *trans_x = 
    new GLUI_Translation(glui2_line, "Objects X", GLUI_TRANSLATION_X, obj_pos_view2D );
  trans_x->set_speed( .005 );
  new GLUI_Column( glui2_line, false );
  GLUI_Translation *trans_y = 
    new GLUI_Translation( glui2_line, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos_view2D[1] );
  trans_y->set_speed( .005 );
  new GLUI_Column( glui2_line, false );
  GLUI_Translation *trans_z = 
    new GLUI_Translation( glui2_line, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos_view2D[2] );
  trans_z->set_speed( .005 );


    // GLUI_TextBox *label = 
    // new GLUI_Spinner( obj_panel, "Label", &label);
    // label->set_alignment( GLUI_ALIGN_RIGHT );

    
	///Functional Specification: 
	///Make node
	///pan around
	///make solid line
	///make dashhed line
	///undo or go back
	///zoom in/out
	///Set view
	///Next View or Complete
	return view_orth;
}

void line_2d_printer(){
	// cout<<curr.node_array.size();
	//curr.node_array
	//printf("Reached line_2d_Printer1\n");
	glClearColor( .5f, .9f, .3f, 1.0f );
	glLoadIdentity();


	glTranslatef( obj_pos_view2D[0], obj_pos_view2D[1], -obj_pos_view2D[2] );
	// glScalef( abs(obj_pos_view2D[2]) , abs(obj_pos_view2D[2]) , abs(obj_pos_view2D[2]) );
	// cout<< curr.node_array.size()<<endl;
	for (int q=0; q< curr.node_array.size(); q++){

		vector2 coord_base = curr.node_array[q].coord;
		glPointSize(6);
		glBegin( GL_POINTS );
		
		glVertex2f(coord_base.a*abs(obj_pos_view2D[2]), coord_base.b*abs(obj_pos_view2D[2]));
		glEnd();
		for (int r=0; r< curr.node_array[q].solid_array_neighbour.size(); r++){
			vector2 coord_solid_temp = curr.node_array[q].solid_array_neighbour[r];
			float temp_draw_array[] = {coord_base.a*abs(obj_pos_view2D[2]), coord_base.b*abs(obj_pos_view2D[2]), coord_solid_temp.a*abs(obj_pos_view2D[2]), coord_solid_temp.b*abs(obj_pos_view2D[2])};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );

			  glLineWidth (3);
			  glBegin( GL_LINES );
			  
			  // cout<< "aojfoajf"<<endl;
			  // cout << coord_base3D.a << "next" << coord_base3D.b << "next" << temp_draw_array[3] << "next" << temp_draw_array[4] <<endl;
			  glColor3f( 1.0, 1.0, 1.0 );
			  glVertex3f( temp_draw_array[0], temp_draw_array[1], 0.0 );  glVertex3f( temp_draw_array[2], temp_draw_array[3], 0.0 );
			  glEnd();

			  // glPopMatrix();

			  glEnable( GL_LIGHTING );
		}
		for (int s=0; s< curr.node_array[q].dashed_array_neighbour.size(); s++){
			vector2 coord_dashed_temp = curr.node_array[q].dashed_array_neighbour[s];
			GLfloat temp_draw_array_dashed[] = {coord_base.a*abs(obj_pos_view2D[2]), coord_base.b*abs(obj_pos_view2D[2]), coord_dashed_temp.a*abs(obj_pos_view2D[2]), coord_dashed_temp.b*abs(obj_pos_view2D[2])};
			 glLineStipple(3, 0x1C47);
			 glEnable(GL_LINE_STIPPLE);
			 glDisable( GL_LIGHTING );

			  // glPushMatrix();
			  // glScalef( scale, scale, scale );
			  glLineWidth (3);
			  glBegin( GL_LINES );
			 
			  glColor3f( 1.0, 1.0, 1.0 );
			  glVertex3f( temp_draw_array_dashed[0], temp_draw_array_dashed[1], 0.0 );  glVertex3f( temp_draw_array_dashed[2], temp_draw_array_dashed[3], 0.0 );
			  glEnd();

			  glPopMatrix();
			  glDisable(GL_LINE_STIPPLE);
			  // glEnable( GL_LIGHTING );
		}
		
	}
}


File2D Line2DInput(File2D inputFile){
	
	obj_pos_view2D[2] = 0.2f;
	outputFile = inputFile;
  	glui_OrthSelection = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_TOP );

  	

  	/*** Disable/Enable buttons ***/
 	new GLUI_Button( glui_OrthSelection, "Front View", Front, control_cb_line );
 	new GLUI_Column( glui_OrthSelection, false );
  	new GLUI_Button( glui_OrthSelection, "Top View",   Top, control_cb_line );
  	new GLUI_Column( glui_OrthSelection, false );
  	new GLUI_Button( glui_OrthSelection, "Side View",  Side, control_cb_line );
  	new GLUI_Column( glui_OrthSelection, false );
  	new GLUI_Button( glui_OrthSelection, "Start Transform",  TransTo3D, control_cb_line );
  	new GLUI_Column( glui_OrthSelection, false );
  	new GLUI_Button( glui_OrthSelection, "Back",  Back3, control_cb_line );


  	getUIView2D();

	 return outputFile;
}
