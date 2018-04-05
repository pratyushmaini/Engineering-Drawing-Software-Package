#include <vector>
// #include "File2D.h"
#include <string.h>
#include <fstream>
#include <GL/glui.h>
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "../include/File2D_3D.h"
#include <gtk/gtk.h>
using namespace std;
extern char* filename;
extern int main_window;
File3D outputFile3D;
File3D previous3D;
extern float scale;
extern float view_rotate[];

extern float lights_rotation3D[];
// extern int window_num;
extern int main2DSave(int argc, char* argv[]);

PlaneNode3D plane_node_temp;

int wire_frame = 0;

#define Done_Plane_node3D 		700
#define Done_Plane        		701
#define Done_Edge3D   	  		702
#define Done_Node3D       		703
#define Undo3D            		704
#define Done_Overall3D    		707
#define DeleteCall3D     		708
#define TransTo2D         		709
#define LIGHT0_ENABLED3D_ID     710
#define LIGHT1_ENABLED3D_ID     711
#define RotateCall3D     		712
#define LIGHT0_INTENSITY3D_ID   750
#define LIGHT1_INTENSITY3D_ID   760
#define Save3D_7				761
#define	Back7 					762
#define	Reset 					763

float x_3D = 0.0, y_3D = 0.0, z_3D =0.0, label3D = 0.0, node_delete_label3D = 0.0, rotate_x_3D = 0.0, rotate_y_3D=0.0, rotate_z_3D=0.0;
float node_solid1_3D = 0.0, node_solid2_3D = 0.0, node_plane_3D = 0.0;
GLUI *glui_LineOptions3D, *glui2_line3D;
GLUI_Panel      *obj_panel3D, *delete_panel3D, *rotate_panel3D, *edge_panel, *plane_panel;
extern float obj_pos[];

/********** Miscellaneous global variables **********/

int   light0_enabled3D = 1;
int   light1_enabled3D = 1;
float light0_intensity3D = 1.0;
float light1_intensity3D = .4;
GLUI_Spinner    *light0_spinner3D, *light1_spinner3D;

extern GLfloat light0_ambient3D[];
extern GLfloat light0_diffuse3D[];
extern GLfloat light0_position3D[];
extern float lights_rotation3D1[];
extern float light0_position3D1[];

extern GLfloat light1_ambient3D[];
extern GLfloat light1_diffuse3D[];
extern GLfloat light1_position3D[];

GLfloat lights_rotation3D[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

void Save3D_7view(){
	///Makes a text File that contains the 3D array
	cout<< "kafhahfakhf"<<endl;
	cout<< filename << endl;
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

void rotateFile(float rotate_x, float rotate_y,float rotate_z);
void control_cb_line3D( int control ){
	if (control == Done_Node3D){
		int label_int3D = (int)label3D;
  		string label_str3D = std::to_string(label_int3D);
		outputFile3D.Makenode3D(x_3D,y_3D, z_3D, label_str3D);
		cout  <<   outputFile3D.Node_array.size() << endl;
	}
	else if (control == DeleteCall3D ){
		string node_delete_str3D = std::to_string((int)node_delete_label3D);
  	
	  	outputFile3D.deleteNode3D(node_delete_str3D);
	  	line_3d_printer();

	}
	else if (control == Done_Overall3D ){
		window_num = 9;
	    glui_LineOptions3D -> close();
	    glui2_line3D -> close();
	    File2D out2DFile = Start2DTrans(outputFile3D);
	    View2DWindow(out2DFile, outputFile3D);

	}
	else if (control == Done_Plane_node3D ){

		vector3 temp_vec3D;
		string node_plane_3D_str = std::to_string((int)node_plane_3D);
		for(int i=0; i<outputFile3D.Node_array.size(); i++){
			if(outputFile3D.Node_array[i].coord3D.name==node_plane_3D_str){
				temp_vec3D = outputFile3D.Node_array[i].coord3D;
			}
		}
		plane_node_temp.circ_neighbour.push_back(temp_vec3D);
		// cout<< "Circ Ngb Size " << plane_node_temp.circ_neighbour.size() <<endl;
	}
	else if (control == Done_Plane ){
		outputFile3D.Plane_array.push_back(plane_node_temp);
		vector<vector3> circ_temp;
		plane_node_temp.circ_neighbour = circ_temp;
		// cout<< "No. of Planes " << outputFile3D.Plane_array.size() <<endl;

	}
	else if (control == Done_Edge3D ){
		string node_edge1_str = std::to_string((int)node_solid1_3D);
	  	string node_edge2_str = std::to_string((int)node_solid2_3D);
	  	
	  	outputFile3D.MakeEdge3D(node_edge1_str, node_edge2_str);
	  	line_3d_printer();
	}
	else if ( control == LIGHT0_ENABLED3D_ID ) {
    if ( light0_enabled3D ) {
      glEnable( GL_LIGHT0 );
      light0_spinner3D->enable();
    }
    else {
      glDisable( GL_LIGHT0 ); 
      light0_spinner3D->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED3D_ID ) {
    if ( light1_enabled3D ) {
      glEnable( GL_LIGHT1 );
      light1_spinner3D->enable();
    }
    else {
      glDisable( GL_LIGHT1 ); 
      light1_spinner3D->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY3D_ID ) {
    float v[] = { 
      light0_diffuse3D[0],  light0_diffuse3D[1],
      light0_diffuse3D[2],  light0_diffuse3D[3] };
    
    v[0] *= light0_intensity3D;
    v[1] *= light0_intensity3D;
    v[2] *= light0_intensity3D;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY3D_ID ) {
    float v[] = { 
      light1_diffuse3D[0],  light1_diffuse3D[1],
      light1_diffuse3D[2],  light1_diffuse3D[3] };
    
    v[0] *= light1_intensity3D;
    v[1] *= light1_intensity3D;
    v[2] *= light1_intensity3D;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  else if ( control == Save3D_7 ){
  	int zero =	main2DSave(NULL, NULL);
    Save3D_7view();
  }
  else if ( control == Back7 ){
  	glui_LineOptions3D -> close();
	glui2_line3D -> close();
	window_num = 6;
    C3DFile();
  }
  else if (control == RotateCall3D){
  	cout << 832098423940 << endl;
  	rotateFile (rotate_x_3D, rotate_y_3D, rotate_z_3D);
  	
  }
  else if (control == Reset){
  	cout << "RESET" << endl;
  	float temp_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  	for (int i=0; i<16; i++)
  		{view_rotate[i] = temp_rotate[i];}
  	
  }
}

vector3 rotatex(float angle, vector3 points){
    angle = angle * M_PI / 180.0;
    float temp = points.b;
    points.b = points.b * cos(angle) - points.c * sin(angle);
    points.c = temp * sin(angle) + points.c * cos(angle);
    return points;
} 
 
vector3 rotatey(float angle, vector3 points){
    angle = (angle * M_PI) / 180.0;
    float temp = points.c;
    points.c = points.c * cos(angle) - points.a * sin(angle);
    points.a = temp * sin(angle) + points.a * cos(angle);
    return points; 
} 
 
vector3 rotatez(float angle, vector3 points){
    angle = angle * M_PI / 180.0;
    float temp = points.a;
    points.a = points.a * cos(angle) - points.b * sin(angle);
    points.b = temp * sin(angle) + points.b *cos(angle);
    return points;
} 
void rotateFile(float rotate_x, float rotate_y,float rotate_z){
	cout << "Rotate: " << rotate_x << ", " << rotate_y << ", " << rotate_z << endl;
	//First Node Array
	for (int i = 0; i< outputFile3D.Node_array.size(); i++){
		outputFile3D.Node_array[i].coord3D = rotatex(rotate_x, outputFile3D.Node_array[i].coord3D);
		outputFile3D.Node_array[i].coord3D = rotatey(rotate_y, outputFile3D.Node_array[i].coord3D);
		outputFile3D.Node_array[i].coord3D = rotatez(rotate_z, outputFile3D.Node_array[i].coord3D);
		for (int j=0; j< outputFile3D.Node_array[i].array_neighbour.size(); j++){
			outputFile3D.Node_array[i].array_neighbour[j] = rotatex(rotate_x, outputFile3D.Node_array[i].array_neighbour[j]);
			outputFile3D.Node_array[i].array_neighbour[j] = rotatey(rotate_y, outputFile3D.Node_array[i].array_neighbour[j]);
			outputFile3D.Node_array[i].array_neighbour[j] = rotatez(rotate_z, outputFile3D.Node_array[i].array_neighbour[j]);	
		}
		cout<< "rotate here" << endl;
	}
	//Plane Array
    for (int i = 0; i< outputFile3D.Plane_array.size(); i++){
            for (int j = 0; j< outputFile3D.Plane_array[i].circ_neighbour.size(); j++){
                    outputFile3D.Plane_array[i].circ_neighbour[j] = rotatex(rotate_x, outputFile3D.Plane_array[i].circ_neighbour[j]);
                    outputFile3D.Plane_array[i].circ_neighbour[j] = rotatey(rotate_y, outputFile3D.Plane_array[i].circ_neighbour[j]);
                    outputFile3D.Plane_array[i].circ_neighbour[j] = rotatez(rotate_z, outputFile3D.Plane_array[i].circ_neighbour[j]);
            }
    }
}



void translate3D (){
	///pan around by entering percentage movement for translation along each direction
	  GLUI_Translation *trans_xy = 
	    new GLUI_Translation(glui2_line3D, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
	  trans_xy->set_speed( .005 );
	  new GLUI_Column( glui2_line3D, false );
	  GLUI_Translation *trans_x = 
	    new GLUI_Translation(glui2_line3D, "Objects X", GLUI_TRANSLATION_X, obj_pos );
	  trans_x->set_speed( .005 );
	  new GLUI_Column( glui2_line3D, false );
	  GLUI_Translation *trans_y = 
	    new GLUI_Translation( glui2_line3D, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
	  trans_y->set_speed( .005 );
	  new GLUI_Column( glui2_line3D, false );
	  GLUI_Translation *trans_z = 
	    new GLUI_Translation( glui2_line3D, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
	  trans_z->set_speed( .005 );
}

void zoom3D (int zoom_amount){
	///zoom in/out by entering percentage
}

bool isEqual(View_Node3D n1, View_Node3D n2){
	if(n1.coord3D.a==n2.coord3D.a && n1.coord3D.b==n2.coord3D.b && n1.coord3D.c==n2.coord3D.c){
		return true;
	}
	else return false;
}

bool File3D::Makenode3D(float x, float y, float z, string nam){
	//Make a new Node in a 3D File
	vector3 v(x,y,z,nam);

	vector<vector3> array_neighbour;
	View_Node3D node(v, array_neighbour);

	for(int i=0; i<Node_array.size(); i++){
		if(isEqual(node, Node_array[i])){
			return false;
		}
	}

	Node_array.push_back(node);
	return true;

} 
bool File3D::MakeEdge3D(string node1, string node2){
	//Make solid line between two nodes
	int n1,n2,i;
	for(i=0; i< Node_array.size(); i++){
		if(Node_array[i].coord3D.name==node1){
			n1 = i;
			for(int j=0; j<Node_array[i].array_neighbour.size(); j++){
				if(Node_array[i].array_neighbour[j].name==node2){
					return false;
				}
			}
		}
		if(Node_array[i].coord3D.name==node2){
			n2 = i;
		}
	}


	if(i==0)
		return false;

	vector3 c1(Node_array[n1].coord3D.a,Node_array[n1].coord3D.b,Node_array[n1].coord3D.c,node1);
	vector3 c2(Node_array[n2].coord3D.a,Node_array[n2].coord3D.b,Node_array[n2].coord3D.c,node2);
	
	Node_array[n1].array_neighbour.push_back(c2);
	Node_array[n2].array_neighbour.push_back(c1);

	return true;

}

void File3D::deleteNode3D(string n1){
	// Remove a particular node and the dependent lines from the file
	vector<vector3> array_neighbour1;
	vector<vector3> array_neighbour_temp;

	for(int i=0; i<Node_array.size(); i++){
		if(n1 == Node_array[i].coord3D.name){
			array_neighbour1 = Node_array[i].array_neighbour;
			Node_array.erase(Node_array.begin() + i);
			break;
		}
	}

	for (int i=0; i< array_neighbour1.size(); i++){
		vector3 temp_neighbour = array_neighbour1[i];
		for (int j =0; j< Node_array.size(); j++){
			if(temp_neighbour.name == Node_array[j].coord3D.name){
				array_neighbour_temp = Node_array[j].array_neighbour;
				for(int k=0; k<array_neighbour_temp.size(); k++){
					if(n1 == array_neighbour_temp[k].name){
						Node_array[j].array_neighbour.erase(Node_array[j].array_neighbour.begin() + k);
						break;
					}
				}
			break;
			}
		}
	}

	for (int i=0; i< Plane_array.size(); i++){
		for (int j=0; j< Plane_array[i].circ_neighbour.size(); j++){
			if (Plane_array[i].circ_neighbour[j].name == n1){
				Plane_array.erase(Plane_array.begin() + i);
				break;
			}
		}
		
	}

}

void File3D::getSolidSurfaceLabels(){
	//Label Solid Surfaces on the given 3D object
}

void SetView3D(){
	///Set view as done
}

void NextStep3D(){
	///Choose between going to Next View or Completing the drawing
}


File3D editView(File3D initialView){
	///Functional Specification: 
	///Translate Plane
	///Make node
	///pan around
	///make solid line
	///undo or go back
	///zoom in/out
	///Set Done view
	///Next View or Complete
	///Label Solid Surfaces
}

void line_3d_printer(){
	//outputFile3D.Node_array
	//printf("Reached line_2d_Printer1\n");

	glClearColor( .3f, .1f, .1f, 1.0f );
	glLoadIdentity();
	glMultMatrixf( lights_rotation3D1 );
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position3D1);

    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );
    // glScalef(abs(obj_pos[2]), abs(obj_pos[2]), abs(obj_pos[2])); 
    glMultMatrixf( view_rotate );

	// cout<< outputFile3D.Node_array.size()<<endl;
	for (int q=0; q< outputFile3D.Node_array.size(); q++){
		glPointSize(6);
		glBegin( GL_POINTS );
		
		glVertex3f(outputFile3D.Node_array[q].coord3D.a*abs(obj_pos[2]), outputFile3D.Node_array[q].coord3D.b*abs(obj_pos[2]), outputFile3D.Node_array[q].coord3D.c*abs(obj_pos[2]));
		glEnd();
		vector3 coord_base3D = outputFile3D.Node_array[q].coord3D;
		for (int r=0; r< outputFile3D.Node_array[q].array_neighbour.size(); r++){
			  vector3 coord_solid_temp3D = outputFile3D.Node_array[q].array_neighbour[r];
			  float temp_draw_array[] = {coord_base3D.a, coord_base3D.b, coord_base3D.c, coord_solid_temp3D.a, coord_solid_temp3D.b, coord_solid_temp3D.c};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );
			  
			  glPushMatrix();
			  glScalef( scale, scale, scale );
			  glLineWidth (3);
			  glBegin( GL_LINES );
			  
			  // cout<< "aojfoajf"<<endl;
			  // cout << coord_base3D.a << "next" << coord_base3D.b << "next" << temp_draw_array[3] << "next" << temp_draw_array[4] <<endl;
			  glColor3f( 1.0, 1.0, 1.0 );
			  glVertex3f( temp_draw_array[0]*abs(obj_pos[2]), temp_draw_array[1]*abs(obj_pos[2]), temp_draw_array[2]*abs(obj_pos[2]));  glVertex3f( temp_draw_array[3]*abs(obj_pos[2]), temp_draw_array[4]*abs(obj_pos[2]), temp_draw_array[5]*abs(obj_pos[2]) );
			  glEnd();

			  glPopMatrix();
			  glLineWidth (1);

			  glEnable( GL_LIGHTING );
		}
		
	}
	
	if(wire_frame != 1){
		for (int w=0; w< outputFile3D.Plane_array.size(); w++){
			vector<vector3> circ_neighbour_temp = outputFile3D.Plane_array[w].circ_neighbour;
			for (int q =0; q< circ_neighbour_temp.size() ; q++ ){

				glEnable( GL_NORMALIZE );
			    float vect_A[] = {circ_neighbour_temp[0].a-circ_neighbour_temp[1].a, circ_neighbour_temp[0].b-circ_neighbour_temp[1].b, circ_neighbour_temp[0].c-circ_neighbour_temp[1].c};
			    float vect_B[] = {circ_neighbour_temp[2].a-circ_neighbour_temp[1].a, circ_neighbour_temp[2].b-circ_neighbour_temp[1].b, circ_neighbour_temp[2].c-circ_neighbour_temp[1].c};
			    
			    float cross_P[3];
				    cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
				    cross_P[1] = vect_A[0] * vect_B[2] - vect_A[2] * vect_B[0];
				    cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];

				glColor3f(0.0, 0.0, 1.0);
			    glBegin(GL_POLYGON);

			    glNormal3f(cross_P[0], cross_P[1], cross_P[2]);
					
			    	for (int r=0; r<circ_neighbour_temp.size(); r++){
			    		glVertex3f(circ_neighbour_temp[r].a*abs(obj_pos[2]), circ_neighbour_temp[r].b*abs(obj_pos[2]), circ_neighbour_temp[r].c*abs(obj_pos[2]));
			    	}
			        
			        
			    glEnd();
			} 
		}
	}
}


File3D Line3DInput(File3D inputFile){

	obj_pos[2] = 0.2f;
	outputFile3D = inputFile;	
	
	glui_LineOptions3D = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );


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

        //////////////////Create Node////////////////////////

    obj_panel3D = new GLUI_Rollout(glui_LineOptions3D, "Make Node", false );
    GLUI_Spinner *x_coord3D = 
    new GLUI_Spinner( obj_panel3D, "X Coord:", &x_3D);
    x_coord3D->set_int_limits( -40.0, 40.0 );
    x_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *y_coord3D = 
    new GLUI_Spinner( obj_panel3D, "Y Coord:", &y_3D);
    y_coord3D->set_float_limits( -40.0, 40.0 );
    y_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *z_coord3D = 
    new GLUI_Spinner( obj_panel3D, "Z Coord:", &z_3D);
    z_coord3D->set_float_limits( -40.0, 40.0 );
    z_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *label_text3D = 
    new GLUI_Spinner( obj_panel3D, "Node Number:", &label3D);
    label_text3D->set_float_limits( 0, 100 );
    label_text3D->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( obj_panel3D, "Done", Done_Node3D, control_cb_line3D );


    //////////////////Create Edge////////////////////////

    edge_panel = new GLUI_Rollout(glui_LineOptions3D, "Make Edge", false );
    

    GLUI_Spinner *solid_label_1 = 
    new GLUI_Spinner( edge_panel, "Node 1:", &node_solid1_3D);
    solid_label_1->set_float_limits( 0, 100 );
    solid_label_1->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *solid_label_2 = 
    new GLUI_Spinner( edge_panel, "Node 2:", &node_solid2_3D);
    solid_label_2->set_float_limits( 0, 100 );
    solid_label_2->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( edge_panel, "Done", Done_Edge3D, control_cb_line3D );


    //////////////////Create Plane////////////////////////

    plane_panel = new GLUI_Rollout(glui_LineOptions3D, "Make Plane", false );
    

    GLUI_Spinner *plane_label_1 = 
    new GLUI_Spinner( plane_panel, "Add Node:", &node_plane_3D);
    plane_label_1->set_float_limits( 0, 100 );
    plane_label_1->set_alignment( GLUI_ALIGN_RIGHT );

    
    new GLUI_Button( plane_panel, "Add Node", Done_Plane_node3D, control_cb_line3D );
    new GLUI_Button( plane_panel, "Done", Done_Plane, control_cb_line3D );

    new GLUI_Checkbox( glui_LineOptions3D, "Wire Frame", &wire_frame, 1, control_cb_line3D );

    ///////////////Rotate Projection/////////////////
 	rotate_panel3D = new GLUI_Rollout(glui_LineOptions3D, "Rotate Plane", false );

    GLUI_Spinner *rotateX3D = 
    new GLUI_Spinner(rotate_panel3D, "Rotate X:", &rotate_x_3D);
    rotateX3D->set_float_limits( -180, 180 );
    rotateX3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *rotateY3D = 
    new GLUI_Spinner( rotate_panel3D, "Rotate Y:", &rotate_y_3D);
    rotateY3D->set_float_limits( -180, 180 );
    rotateY3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *rotateZ3D = 
    new GLUI_Spinner( rotate_panel3D, "Rotate Z:", &rotate_z_3D);
    rotateZ3D->set_float_limits( -180, 180 );
    rotateZ3D->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( rotate_panel3D, "Rotate", RotateCall3D, control_cb_line3D );



  		
 	//////////////////////////Delete///////////////////////////////

    delete_panel3D = new GLUI_Rollout(glui_LineOptions3D, "Delete Node", false );

    GLUI_Spinner *delete_label3D = 
    new GLUI_Spinner( delete_panel3D, "Node Label:", &node_delete_label3D);
    delete_label3D->set_float_limits( 0, 100 );
    delete_label3D->set_alignment( GLUI_ALIGN_RIGHT );
    new GLUI_Button( delete_panel3D, "Delete", DeleteCall3D, control_cb_line3D );

    new GLUI_Button( glui_LineOptions3D, "Done", Done_Overall3D, control_cb_line3D );

 	new GLUI_Button( glui_LineOptions3D, "Save3D File", Save3D_7, control_cb_line3D );

 	new GLUI_Button( glui_LineOptions3D, "Back", Back7, control_cb_line3D );

 	
    /*** Create the bottom subwindow ***/
	  glui2_line3D = GLUI_Master.create_glui_subwindow( main_window, 
	                                             GLUI_SUBWINDOW_BOTTOM );
	  glui2_line3D->set_main_gfx_window( main_window );

  	  
	  GLUI_Rotation *view_rot = new GLUI_Rotation(glui2_line3D, "Objects", view_rotate );
	  view_rot->set_spin( 1.0 );
	  new GLUI_Column( glui2_line3D, false );
	  GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2_line3D, "Blue Light", lights_rotation3D );
	  lights_rot->set_spin( .82 );
	  new GLUI_Column( glui2_line3D, false );
	  translate3D();
	  new GLUI_Column( glui2_line3D, false );
	  new GLUI_Button( glui2_line3D, "Reset Rotation", Reset, control_cb_line3D );
	  return outputFile3D;
	
}
