#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glui.h>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// #include "File3D.h"
#include "../include/File2D_3D.h"
using namespace std;


extern int main2Dinput(int argc, char** argv);
extern string inputDirectory;

void file_3d_printer();
File3D *fileLabelled3D;
File3D input;
int wire_frame_file = 0;

extern float obj_pos_view2D[];
extern int main_window;
extern float scale;
extern float view_rotate[];
extern float sphere_rotate[];
extern float torus_rotate[];
extern float lights_rotation3D1[];
// extern int window_num;

PlaneNode3D plane_node_temp1;


#define Done_Planefile_node3D_file 		800
#define Done_Planefile        		801
#define Done_Edge3Dfile   	  		802
#define Done_Node3D_file       		803
#define Undo3D_file            		804
#define Done_Overall3D_file    		807
#define DeleteCall3D_file     		808
#define TransTo2D_file         		809
#define LIGHT0_ENABLED3D1_ID_file     810
#define LIGHT1_ENABLED3D1_ID_file     811
#define LIGHT0_INTENSITY3D1_ID_file   850
#define LIGHT1_INTENSITY3D1_ID_file   860
#define Back8						  861
#define Reset						  862

float x_3D1 = 0.0, y_3D1 = 0.0, z_3D1 =0.0, label3D1 = 0.0, node_delete_label3D1 = 0.0;
float node_solid1_3D1 = 0.0, node_solid2_3D1 = 0.0, node_plane_3D1 = 0.0;
GLUI *glui_FileOptions3D, *glui2_file3D;
GLUI_Panel      *obj_panel3D1, *delete_panel3D1, *edge_panel1, *plane_panel1;
extern float obj_pos[];

/********** Miscellaneous global variables **********/

int   light0_enabled3D1 = 1;
int   light1_enabled3D1 = 1;
float light0_intensity3D1 = 1.0;
float light1_intensity3D1 = .4;
GLUI_Spinner    *light0_spinner3D1, *light1_spinner3D1;

GLfloat light0_ambient3D1[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse3D1[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position3D1[] = {.5f, .5f, 1.0f, 0.0f};

GLfloat light1_ambient3D1[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse3D1[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat light1_position3D1[] = {-1.0f, -1.0f, 1.0f, 0.0f};

GLfloat lights_rotation3D1[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };


void control_cb_line3D1( int control ){
	if (control == Done_Node3D_file){
		int label_int3D = (int)label3D1;
  		string label_str3D = std::to_string(label_int3D);
		input.Makenode3D(x_3D1,y_3D1, z_3D1, label_str3D);
		// cout  <<   input.Node_array.size() << endl;
	}
	else if (control == DeleteCall3D_file ){
		string node_delete_str3D = std::to_string((int)node_delete_label3D1);
  	
	  	input.deleteNode3D(node_delete_str3D);
	  	file_3d_printer();

	}
	else if (control == Done_Overall3D_file ){
		window_num = 9;
		obj_pos_view2D[2] = 1.0;
	    glui_FileOptions3D -> close();
	    glui2_file3D -> close();
	    File2D out2DFile = Start2DTrans(input);
	    View2DWindow(out2DFile, input);

	}
	else if (control == Done_Planefile_node3D_file ){

		vector3 temp_vec3D;
		string node_plane_3D1_str = std::to_string((int)node_plane_3D1);
		for(int i=0; i<input.Node_array.size(); i++){
			if(input.Node_array[i].coord3D.name==node_plane_3D1_str){
				temp_vec3D = input.Node_array[i].coord3D;
			}
		}
		plane_node_temp1.circ_neighbour.push_back(temp_vec3D);
		// cout<< "Circ Ngb Size " << plane_node_temp1.circ_neighbour.size() <<endl;
	}
	else if (control == Done_Planefile ){
		input.Plane_array.push_back(plane_node_temp1);
		vector<vector3> circ_temp;
		plane_node_temp1.circ_neighbour = circ_temp;
		// cout<< "No. of Planes " << input.Plane_array.size() <<endl;

	}
	else if (control == Done_Edge3Dfile ){
		string node_edge1_str = std::to_string((int)node_solid1_3D1);
	  	string node_edge2_str = std::to_string((int)node_solid2_3D1);
	  	
	  	input.MakeEdge3D(node_edge1_str, node_edge2_str);
	  	file_3d_printer();
	}
	else if ( control == LIGHT0_ENABLED3D1_ID_file ) {
    if ( light0_enabled3D1 ) {
      glEnable( GL_LIGHT0 );
      light0_spinner3D1->enable();
    }
    else {
      glDisable( GL_LIGHT0 ); 
      light0_spinner3D1->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED3D1_ID_file ) {
    if ( light1_enabled3D1 ) {
      glEnable( GL_LIGHT1 );
      light1_spinner3D1->enable();
    }
    else {
      glDisable( GL_LIGHT1 ); 
      light1_spinner3D1->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY3D1_ID_file ) {
    float v[] = { 
      light0_diffuse3D1[0],  light0_diffuse3D1[1],
      light0_diffuse3D1[2],  light0_diffuse3D1[3] };
    
    v[0] *= light0_intensity3D1;
    v[1] *= light0_intensity3D1;
    v[2] *= light0_intensity3D1;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY3D1_ID_file ) {
    float v[] = { 
      light1_diffuse3D1[0],  light1_diffuse3D1[1],
      light1_diffuse3D1[2],  light1_diffuse3D1[3] };
    
    v[0] *= light1_intensity3D1;
    v[1] *= light1_intensity3D1;
    v[2] *= light1_intensity3D1;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  else if( control == Back8 ){
	glui_FileOptions3D -> close();
	glui2_file3D -> close();    
  	window_num = 6;
  	C3DFile();
  }
  else if (control == Reset){
  	cout << "RESET" << endl;
  	float temp_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
  	for (int i=0; i<16; i++)
  		{view_rotate[i] = temp_rotate[i];}
  	
  }
}



///Labeled File
///Unlabeled File 
///Get users to label it.
int chooseMode3D(){
	/// 0 for labeled and 1 for unlabeled
}

void file_3d_printer(){
	//input.Node_array
	//printf("Reached line_2d_Printer1\n");

	glClearColor( .5f, .9f, .3f, 1.0f );
	glLoadIdentity();
	glMultMatrixf( lights_rotation3D1 );
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position3D1);

    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] ); 
    // glScalef(abs(obj_pos[2]), abs(obj_pos[2]), abs(obj_pos[2]));
    glMultMatrixf( view_rotate );

	// cout<< input.Node_array.size()<<endl;
	for (int q=0; q< input.Node_array.size(); q++){
		glPointSize(6);
		glBegin( GL_POINTS );
		
		glVertex3f(input.Node_array[q].coord3D.a*abs(obj_pos[2]), input.Node_array[q].coord3D.b*abs(obj_pos[2]), input.Node_array[q].coord3D.c*abs(obj_pos[2]));
		glEnd();
		vector3 coord_base3D = input.Node_array[q].coord3D;
		for (int r=0; r< input.Node_array[q].array_neighbour.size(); r++){
			  vector3 coord_solid_temp3D = input.Node_array[q].array_neighbour[r];
			  float temp_draw_array[] = {coord_base3D.a*abs(obj_pos[2]), coord_base3D.b*abs(obj_pos[2]), coord_base3D.c*abs(obj_pos[2]), coord_solid_temp3D.a*abs(obj_pos[2]), coord_solid_temp3D.b*abs(obj_pos[2]), coord_solid_temp3D.c*abs(obj_pos[2])};
				// cout << temp_draw_array <<endl;
			  glDisable( GL_LIGHTING );

			  glPushMatrix();
			  glScalef( scale, scale, scale );
			  glLineWidth (3);
			  glBegin( GL_LINES );
			  // cout << coord_base.a << "next" << coord_base.b << "next" << coord_solid_temp.a << "next" << coord_solid_temp.b <<endl;
			  glColor3f( 1.0, 0.0, 0.0 );
			  glVertex3f( temp_draw_array[0], temp_draw_array[1], temp_draw_array[2]);  glVertex3f( temp_draw_array[3], temp_draw_array[4], temp_draw_array[5] );
			  glEnd();

			  glPopMatrix();
			  glLineWidth (1);

			  glEnable( GL_LIGHTING );
		}
		
	}
	
	if(wire_frame_file != 1){
		for (int w=0; w< input.Plane_array.size(); w++){
			vector<vector3> circ_neighbour_temp = input.Plane_array[w].circ_neighbour;
			for (int q =0; q< circ_neighbour_temp.size() ; q++ ){

				glEnable( GL_NORMALIZE );
			    float vect_A[] = {circ_neighbour_temp[0].a-circ_neighbour_temp[1].a, circ_neighbour_temp[0].b-circ_neighbour_temp[1].b, circ_neighbour_temp[0].c-circ_neighbour_temp[1].c};
			    float vect_B[] = {circ_neighbour_temp[2].a-circ_neighbour_temp[1].a, circ_neighbour_temp[2].b-circ_neighbour_temp[1].b, circ_neighbour_temp[2].c-circ_neighbour_temp[1].c};
			    
			    float cross_P[3];
				    cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
				    cross_P[1] = vect_A[0] * vect_B[2] - vect_A[2] * vect_B[0];
				    cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];


				glColor3f(0.0f, 0.0f, 1.0f);
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



File3D Takeinput3D(){
	///Browse from directory
	fileLabelled3D = new File3D;
	int zero =main2Dinput(NULL, NULL);
  	ifstream inFile;
  	inFile.open(inputDirectory);
  	if (!inFile) {
    	cerr << "Unable to open file datafile.txt";
    	exit(1);   // call system to stop
	}

	int no_of_nodes;
	float a,b,c;
	string str,s;

	getline(inFile, str);
	inFile >> no_of_nodes;
	getline(inFile, str);


	vector<View_Node3D> Node_array1;

	for(int i=0; i<no_of_nodes; i++){
		getline(inFile, str);
		cout<< str << endl;
        istringstream ss(str);

		ss >> a;
		ss >> b;
		ss >> c;
		ss >> s;
		// cout<< s<< " name" <<endl;
		vector3 nod1(a,b,c,s);

		getline(inFile, str);
		istringstream ss1(str);

		vector<vector3> nod1_array;

		while(ss1>>a){
			ss1>>b;
			ss1>>c;
			ss1>>s;

			vector3 coord31(a,b,c,s);
			nod1_array.push_back(coord31);
		}

		View_Node3D vn3D(nod1, nod1_array);
		Node_array1.push_back(vn3D);

	}

	vector<PlaneNode3D> Plane_array1;

	getline(inFile, str);
	int no_of_planes;
	inFile >> no_of_planes;

	getline(inFile, str);
	for(int i=0; i<no_of_planes; i++){
		getline(inFile, str);
		istringstream ss(str);
		vector<vector3> circ_nei2;
		while(ss>>a){
			ss>>b;
			ss>>c;
			ss>>s;
			vector3 nod2(a,b,c,s);
			circ_nei2.push_back(nod2);
		}
		PlaneNode3D plane3D1(circ_nei2);
		Plane_array1.push_back(plane3D1);
	}
	cout << Plane_array1.size() << endl;
	cout<< "cool"<< endl;
	fileLabelled3D = new File3D;
	fileLabelled3D -> Plane_array = Plane_array1;
	fileLabelled3D -> Node_array = Node_array1;	

	return *fileLabelled3D;
}


File3D File3DInput(){


	// input = inputFile;
	
	glui_FileOptions3D = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );

	  obj_pos[2] = 0.2f;
	  glEnable(GL_DEPTH_TEST);
   	  glEnable(GL_COLOR_MATERIAL);
	  glEnable(GL_LIGHTING);
	  glEnable( GL_NORMALIZE );

	  glEnable(GL_LIGHT0);
	  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient3D1);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse3D1);
	  glLightfv(GL_LIGHT0, GL_POSITION, light0_position3D1);

	  glEnable(GL_LIGHT1);
	  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient3D1);
	  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse3D1);
	  glLightfv(GL_LIGHT1, GL_POSITION, light1_position3D1);

        //////////////////Create Node////////////////////////

    obj_panel3D1 = new GLUI_Rollout(glui_FileOptions3D, "Make Node", false );
    GLUI_Spinner *x_coord3D = 
    new GLUI_Spinner( obj_panel3D1, "X Coord:", &x_3D1);
    x_coord3D->set_int_limits( -40.0, 40.0 );
    x_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *y_coord3D = 
    new GLUI_Spinner( obj_panel3D1, "Y Coord:", &y_3D1);
    y_coord3D->set_float_limits( -40.0, 40.0 );
    y_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *z_coord3D = 
    new GLUI_Spinner( obj_panel3D1, "Z Coord:", &z_3D1);
    z_coord3D->set_float_limits( -40.0, 40.0 );
    z_coord3D->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *label_text3D = 
    new GLUI_Spinner( obj_panel3D1, "Node Number:", &label3D1);
    label_text3D->set_float_limits( 0, 100 );
    label_text3D->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( obj_panel3D1, "Done", Done_Node3D_file, control_cb_line3D1 );


    //////////////////Create Edge////////////////////////

    edge_panel1 = new GLUI_Rollout(glui_FileOptions3D, "Make Edge", false );
    

    GLUI_Spinner *solid_label_1 = 
    new GLUI_Spinner( edge_panel1, "Node 1:", &node_solid1_3D1);
    solid_label_1->set_float_limits( 0, 100 );
    solid_label_1->set_alignment( GLUI_ALIGN_RIGHT );

    GLUI_Spinner *solid_label_2 = 
    new GLUI_Spinner( edge_panel1, "Node 2:", &node_solid2_3D1);
    solid_label_2->set_float_limits( 0, 100 );
    solid_label_2->set_alignment( GLUI_ALIGN_RIGHT );

    new GLUI_Button( edge_panel1, "Done", Done_Edge3Dfile, control_cb_line3D1 );


    //////////////////Create Plane////////////////////////

    plane_panel1 = new GLUI_Rollout(glui_FileOptions3D, "Make Plane", false );
    

    GLUI_Spinner *plane_label_1 = 
    new GLUI_Spinner( plane_panel1, "Add Node:", &node_plane_3D1);
    plane_label_1->set_float_limits( 0, 100 );
    plane_label_1->set_alignment( GLUI_ALIGN_RIGHT );

    
    new GLUI_Button( plane_panel1, "Add Node", Done_Planefile_node3D_file, control_cb_line3D1 );
    new GLUI_Button( plane_panel1, "Done", Done_Planefile, control_cb_line3D1 );

  		
 	//////////////////////////Undo///////////////////////////////

    delete_panel3D1 = new GLUI_Rollout(glui_FileOptions3D, "Delete Node", false );

    GLUI_Spinner *delete_label3D1 = 
    new GLUI_Spinner( delete_panel3D1, "Node Label:", &node_delete_label3D1);
    delete_label3D1->set_float_limits( 0, 100 );
    delete_label3D1->set_alignment( GLUI_ALIGN_RIGHT );
    new GLUI_Button( delete_panel3D1, "Delete", DeleteCall3D_file, control_cb_line3D1 );

    new GLUI_Button( glui_FileOptions3D, "Done", Done_Overall3D_file, control_cb_line3D1 );

    new GLUI_Button( glui_FileOptions3D, "Back", Back8, control_cb_line3D1 );

    new GLUI_Checkbox( glui_FileOptions3D, "Wire Frame", &wire_frame_file, 1,control_cb_line3D1 );

    /*** Create the bottom subwindow ***/
	  glui2_file3D = GLUI_Master.create_glui_subwindow( main_window, 
	                                             GLUI_SUBWINDOW_BOTTOM );
	  glui2_file3D->set_main_gfx_window( main_window );

  	  
	  GLUI_Rotation *view_rot = new GLUI_Rotation(glui2_file3D, "Objects", view_rotate );
	  view_rot->set_spin( 1.0 );
	  new GLUI_Column( glui2_file3D, false );
	  // GLUI_Rotation *sph_rot = new GLUI_Rotation(glui2_file3D, "Sphere", sphere_rotate );
	  // sph_rot->set_spin( .98 );
	  // new GLUI_Column( glui2_file3D, false );
	  // GLUI_Rotation *tor_rot = new GLUI_Rotation(glui2_file3D, "Torus", torus_rotate );
	  // tor_rot->set_spin( .98 );
	  new GLUI_Column( glui2_file3D, false );
	  GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2_file3D, "Blue Light", lights_rotation3D1 );
	  lights_rot->set_spin( .82 );
	  new GLUI_Column( glui2_file3D, false );
	  GLUI_Translation *trans_xy = 
	    new GLUI_Translation(glui2_file3D, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
	  trans_xy->set_speed( .005 );
	  new GLUI_Column( glui2_file3D, false );
	  GLUI_Translation *trans_x = 
	    new GLUI_Translation(glui2_file3D, "Objects X", GLUI_TRANSLATION_X, obj_pos );
	  trans_x->set_speed( .005 );
	  new GLUI_Column( glui2_file3D, false );
	  GLUI_Translation *trans_y = 
	    new GLUI_Translation( glui2_file3D, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
	  trans_y->set_speed( .005 );
	  new GLUI_Column( glui2_file3D, false );
	  GLUI_Translation *trans_z = 
	    new GLUI_Translation( glui2_file3D, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
	  trans_z->set_speed( .005 );
	  	  new GLUI_Column( glui2_file3D, false );
	  new GLUI_Button( glui2_file3D, "Reset Rotation", Reset, control_cb_line3D1 );

	  // return input;


	///Manages the further action depending on mode selected	
	int mode = chooseMode3D();
	// File3D input;
	if(mode == 0){
		input = Takeinput3D();
	}
	else {
		input = Takeinput3D();
		// input.getLabels3D();			
	}

	return input;
}