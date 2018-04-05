#include <vector>
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

/*! \addtogroup Module Module for 2D window
   *  All the functions related to 2D file are available here.
   *  @{
   */

 /*! \fn void Start3DTrans(input)
 * \param input
 * \brief Gives the option for Line Drawing and File Input.
 */
/********** User IDs for callbacks ********/

#define Line             200
#define FileIn           201
#define Back  			 202
int mode2D = 2;
extern int main_window;
// extern int window_num;
extern void home();

GLUI *glui_2dSelection;
extern GLUI *glui;
extern bool isInside(float polygon[], int n, float p[]);

vector3 find_vec_in_node_array3d(string find_name, vector<View_Node3D> Node_array_output){
	vector3 temp_vec3D;
	for (int i = 0; i< Node_array_output.size(); i++){
		if (Node_array_output[i].coord3D.name == find_name){
			temp_vec3D = Node_array_output[i].coord3D;
			break;
		}
	}
	return temp_vec3D;
}

bool isEqual_Plane(PlaneNode3D plane1, PlaneNode3D plane2){
	cout<< "Checking Equal "<< plane1.circ_neighbour.size()<< endl;
	if (plane1.circ_neighbour.size() == plane2.circ_neighbour.size()){
		cout<< "Checking Equal1"<<endl;
		for (int i = 0; i< plane1.circ_neighbour.size() ; i++){
			cout<< "Checking Equal2  i = "<< i <<endl;
			int k; 
			for (k= 0; k< plane2.circ_neighbour.size() ; k++){
				cout<< "Checking Equal3. k= "<< k<<endl;
				if (plane1.circ_neighbour[i].name == plane2.circ_neighbour[k].name){
					break;
				}
			}
			if (k == plane2.circ_neighbour.size()){
				cout<< "Checking Equal4"<<endl;
				return false;
			}
		}
		cout<< "Checking Equal5"<<endl;
		return true;
	}
	else{
		cout<< "Checking Equal6"<<endl;
		return false;
	}
		
}

int present_in_plane_list_temp(vector3 vec, PlaneNode3D plane_list_temp){
	for (int q =0; q< plane_list_temp.circ_neighbour.size(); q++){
		if (plane_list_temp.circ_neighbour[q].name == vec.name){
			return q;
		}
	}
	return -1;	
}

int lookup_node_in_array(vector3 vec, File3D outFile){
	int d;
	for ( d = 0; d< outFile.Node_array.size(); d++){
		if (outFile.Node_array[d].coord3D.name == vec.name){
			break;
		}
	}
	return d;
}

void twoDmodeSelection(){
  
///Two Sub Files: Line Drawing , Direct Input
	File2D input;
	if (mode2D == 0) {
		File2D nulls;
		window_num = 3;
		
		input = Line2DInput(nulls);
		mode2D = 2;
	}
	else if (mode2D == 1) {
		window_num = 4;
			cout<<1207248<<endl;

		input = File2DInput();
		mode2D = 2;
	}
	
}


/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb_2D( int control )
{  printf("HEy\n");

  if ( control == Line )
  {
    mode2D = 0;
    // printf("Apple1\n");
    glui_2dSelection -> close();
    twoDmodeSelection();
  }
  else if ( control == FileIn )
  {
    mode2D = 1;
    glui_2dSelection -> close();
    twoDmodeSelection();
  }
  else if ( control == Back )
  {
	mode2D  = 2;
	glui_2dSelection -> close();
	window_num = 1;
	home();
  } 
}


File3D Start3DTrans(File2D input){
	///Starts the 3D Transformation of the given 2D projections
	///Algorithm for 2D to 3D is inserted here
	File3D outFile;

	vector<PlaneNode3D> Plane_array_out;
	vector<View_Node3D> Node_array_out;
	vector <float> vector_of_plane_parameters;

	OrthographicView currentView = input.Frontview;

	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		
		vector3 coordi(nod.coord.a,nod.coord.b,0,nod.coord.name);
		vector<vector3> arr;
		View_Node3D v(coordi,arr);
		Node_array_out.push_back(v);
	}
	cout <<"Frontview scanned" <<endl;
	currentView = input.Sideview;

	//Coordinate mapping for SideView
	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		int j;
		for (j = 0; j< Node_array_out.size(); j++){
			if (Node_array_out[j].coord3D.name == nod.coord.name){
				break;
			}
		}

		Node_array_out[j].coord3D.c = (-nod.coord.a);
	}
	cout <<"Sideview scanned" <<endl;
	
	//Now all the nodes have the correct coordinates. We can start to work on Node Array

	for (int i=0; i<Node_array_out.size(); i++){
		View_Node3D temp_vec3D = Node_array_out[i];
		string temp_name = temp_vec3D.coord3D.name;

		int j;
		//FrontScan
		for (j= 0; j<input.Frontview.node_array.size(); j++){
			if (input.Frontview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Frontview.node_array[j].solid_array_neighbour.size(); k++){
			int p;
			for(p=0; p< Node_array_out.size(); p++){
				if(Node_array_out[p].coord3D.name == input.Frontview.node_array[j].solid_array_neighbour[k].name){
					break;
				}
			}
			vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
			temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
		}
		//For Dashed ngb
		for(int k=0; k< input.Frontview.node_array[j].dashed_array_neighbour.size(); k++){
			int p;
			for(p=0; p< Node_array_out.size(); p++){
				if(Node_array_out[p].coord3D.name == input.Frontview.node_array[j].dashed_array_neighbour[k].name){
					break;
				}
			}
			vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
			temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
		}



		//Top Scan

		for (j= 0; j<input.Topview.node_array.size(); j++){
			if (input.Topview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Topview.node_array[j].solid_array_neighbour.size(); k++){
			int q;
			for ( q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Topview.node_array[j].solid_array_neighbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				int p;
				for(p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Topview.node_array[j].solid_array_neighbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
			}

			
		}
		//For Dashed ngb
		for(int k=0; k< input.Topview.node_array[j].dashed_array_neighbour.size(); k++){
			int q;
			for (q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Topview.node_array[j].dashed_array_neighbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				int p;
				for(p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Topview.node_array[j].dashed_array_neighbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
			}
			
		}

		//Side Scan
		for (j= 0; j<input.Sideview.node_array.size(); j++){
			if (input.Sideview.node_array[j].coord.name == temp_name){
				break;
			}
		}
		//For Solid ngb
		for(int k=0; k< input.Sideview.node_array[j].solid_array_neighbour.size(); k++){
			int q;
			for ( q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Sideview.node_array[j].solid_array_neighbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				int p;
				for( p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Sideview.node_array[j].solid_array_neighbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
			}			
		}
		//For Dashed ngb
		for(int k=0; k< input.Sideview.node_array[j].dashed_array_neighbour.size(); k++){
			int q;
			for ( q =0; q< temp_vec3D.array_neighbour.size(); q++){
				if (temp_vec3D.array_neighbour[q].name ==  input.Sideview.node_array[j].dashed_array_neighbour[k].name){
					break;
				}
			}

			if (q == temp_vec3D.array_neighbour.size()){
				int p;
				for( p=0; p< Node_array_out.size(); p++){
					if(Node_array_out[p].coord3D.name == input.Sideview.node_array[j].dashed_array_neighbour[k].name){
						break;
					}
				}
				vector3 temp_vec3_ngb = Node_array_out[p].coord3D;
				temp_vec3D.array_neighbour.push_back(temp_vec3_ngb);
			}	
		}
		Node_array_out[i] = temp_vec3D;


	}
	outFile.Node_array =  Node_array_out;

	//For Planes
	cout << "Finding Planes: "<<endl;

	//Step 1: Pick a node
	for (int i = 0; i< outFile.Node_array.size(); i++){
		
		cout << "Node number 1: " << outFile.Node_array[i].coord3D.name <<endl;
		float vec0[] = {outFile.Node_array[i].coord3D.a, outFile.Node_array[i].coord3D.b, outFile.Node_array[i].coord3D.c};
		//Step 2: For every neighbour:  
		for (int h = 0; h< outFile.Node_array[i].array_neighbour.size(); h++){
			//Step 3: Look for every third neighbour from second neighbour
			int d = lookup_node_in_array(outFile.Node_array[i].array_neighbour[h], outFile);
			cout << "Node number 2: " << outFile.Node_array[d].coord3D.name <<endl;
			float vec1[] = {outFile.Node_array[d].coord3D.a, outFile.Node_array[d].coord3D.b, outFile.Node_array[d].coord3D.c};
			for (int k =0; k< outFile.Node_array[d].array_neighbour.size(); k++){

				if (outFile.Node_array[d].array_neighbour[k].name != outFile.Node_array[i].coord3D.name){
					
					//Step 4: Construct a Plane using these 3
					float vec2[] = {outFile.Node_array[d].array_neighbour[k].a, outFile.Node_array[d].array_neighbour[k].b, outFile.Node_array[d].array_neighbour[k].c};
					float dir0[] = {vec0[0]-vec1[0], vec0[1]-vec1[1], vec0[2]-vec1[2]};
					float dir1[] = {vec2[0]-vec1[0], vec2[1]-vec1[1], vec2[2]-vec1[2]};
					float normal[] = { (dir0[1]*dir1[2] - dir0[2]*dir1[1]), (dir0[2]*dir1[0] - dir0[0]*dir1[2]), (dir0[0]*dir1[1] - dir0[1]*dir1[0])};
					float plane_parameters[] = {normal[0], normal[1], normal[2], -(normal[0]*vec0[0] + normal[1]*vec0[1] + normal[2]*vec0[2])}; //ax+by+cz+d=0

					int l = lookup_node_in_array(outFile.Node_array[d].array_neighbour[k], outFile);
					
					cout << "Node number 3: " << outFile.Node_array[l].coord3D.name <<endl;
					PlaneNode3D plane_list_temp;
					plane_list_temp.circ_neighbour.push_back(outFile.Node_array[i].coord3D);
					plane_list_temp.circ_neighbour.push_back(outFile.Node_array[d].coord3D);
					plane_list_temp.circ_neighbour.push_back(outFile.Node_array[l].coord3D);
					//Step 5: See if there is another node on the same plane from the third node //Step 6: Continue this way till we reach source node
					int flag = 0;

					//present_in_plane_list_temp(vec, plane_list_temp)
					while (flag == 0){
						//cout<<"Inside While" <<endl;
						flag = 2;
						for (int s =0; s< outFile.Node_array[l].array_neighbour.size(); s++){
							int pres_num = present_in_plane_list_temp(outFile.Node_array[l].array_neighbour[s], plane_list_temp);
							if ( pres_num == -1){
								float vec3[] = {outFile.Node_array[l].array_neighbour[s].a, outFile.Node_array[l].array_neighbour[s].b, outFile.Node_array[l].array_neighbour[s].c};
								float value = vec3[0]*plane_parameters[0] + vec3[1]*plane_parameters[1] + vec3[2]*plane_parameters[2] +  plane_parameters[3];
								if (value == 0){
									int e = lookup_node_in_array(outFile.Node_array[l].array_neighbour[s], outFile);
									plane_list_temp.circ_neighbour.push_back(outFile.Node_array[e].coord3D);
									l=e;
									cout << "Enter Again" <<endl;
									flag = 0;
									break;
								}
							}
							else if (pres_num == 0){
								flag = 1;
								break;
							}
							
						}
						cout<<"Inside While" <<endl;
					}
					if (flag == 1){
						//Step 7: If yes, declare the plane -- else False
						Plane_array_out.push_back(plane_list_temp);
						vector_of_plane_parameters.push_back(plane_parameters[0]);
						vector_of_plane_parameters.push_back(plane_parameters[1]);
						vector_of_plane_parameters.push_back(plane_parameters[2]);
						vector_of_plane_parameters.push_back(plane_parameters[3]);
					}
				}
				
			}
		}
	}
	//Step 8: Remove extra planes
	for (int i=0; i< Plane_array_out.size(); i++){
		for (int j= i + 1; j< Plane_array_out.size(); j++){
			if (isEqual_Plane(Plane_array_out[i], Plane_array_out[j])){
				Plane_array_out.erase(Plane_array_out.begin()+j);
				vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+4*j);
				vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+4*j);
				vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+4*j);
				vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+4*j);
				j--;
				cout <<"Elements left"<<Plane_array_out.size() <<endl;;
			}
		}
	}
	cout << "vector_of_plane_parameters size: "<<vector_of_plane_parameters.size()<<endl;
	for (int i=0; i< Plane_array_out.size(); i++){

		cout << "Plane No.: " << i << ", " <<  endl;
		cout << "vector_of_plane_parameters size: "<<vector_of_plane_parameters[4*i]<<", "<<vector_of_plane_parameters[4*i + 1]<<", "<<vector_of_plane_parameters[4*i + 2]<<", "<<vector_of_plane_parameters[4*i + 3]<<", "<<endl;
		for (int j=0; j<Plane_array_out[i].circ_neighbour.size(); j++){
			cout << Plane_array_out[i].circ_neighbour[j].a << ", " << Plane_array_out[i].circ_neighbour[j].b << ", " << Plane_array_out[i].circ_neighbour[j].c << ", " << Plane_array_out[i].circ_neighbour[j].name << endl;
		}
		
	}



	// Step 9: See if any plane makes a solid lines -> dashed: if yes, remove that plane.
	// Front View
	currentView = input.Frontview;
	//FrontScan
		for (int j= 0; j<input.Frontview.node_array.size(); j++){
			vector3 coord_xyz = find_vec_in_node_array3d(input.Frontview.node_array[j].coord.name, Node_array_out);
			//For Solid ngb
			for(int k=0; k< input.Frontview.node_array[j].solid_array_neighbour.size(); k++){
				vector3 coord_xyz_ngb = find_vec_in_node_array3d(input.Frontview.node_array[j].solid_array_neighbour[k].name, Node_array_out);
				for (int d=0; d< vector_of_plane_parameters.size(); d= d+4){
					bool visible_ngb_p = true;
					float value_point = (coord_xyz.a + coord_xyz_ngb.a)*vector_of_plane_parameters[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*vector_of_plane_parameters[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*vector_of_plane_parameters[d + 2]/2 + vector_of_plane_parameters[d + 3];
					value_point = round( value_point * 1000.0 ) / 1000.0;
					if ((value_point>0 && vector_of_plane_parameters[d + 2] > 0) || (value_point<0 && vector_of_plane_parameters[d + 2] < 0) || value_point==0 || (vector_of_plane_parameters[d + 0]==0 && vector_of_plane_parameters[d + 2] == 0)|| (vector_of_plane_parameters[d + 2]==0 && vector_of_plane_parameters[d + 1] == 0)){
						visible_ngb_p = true;
					}
					else {
						cout<< "Check2" <<endl;
						int num_node = Plane_array_out[d/4].circ_neighbour.size();
						float polygon_plane_proj[2*num_node] ;
						for (int c=0; c< 2*num_node; c=c+2){
							polygon_plane_proj[c] = Plane_array_out[d/4].circ_neighbour[c/2].a;
							polygon_plane_proj[c+1] = Plane_array_out[d/4].circ_neighbour[c/2].b;
							cout << "Polygon: {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;
						}
						float points_proj[2] = {(coord_xyz.a + coord_xyz_ngb.a)/2, (coord_xyz.b + coord_xyz_ngb.b)/2};
						if(isInside(polygon_plane_proj, num_node, points_proj)){
							visible_ngb_p = false;
							cout<< "false front" <<endl;
						}
					}
					if (!visible_ngb_p ){
						Plane_array_out.erase(Plane_array_out.begin()+d/4);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);

						break;
					}


				}
				
			}
		}

		//Top View
	currentView = input.Topview;
	
	//Top
		for (int j= 0; j<input.Topview.node_array.size(); j++){
			vector3 coord_xyz = find_vec_in_node_array3d(input.Topview.node_array[j].coord.name, Node_array_out);
			cout << "Base Node: " <<  coord_xyz.a << ", " << coord_xyz.b<<", "<< coord_xyz.c << endl;
			//For Solid ngb
			for(int k=0; k< input.Topview.node_array[j].solid_array_neighbour.size(); k++){
				vector3 coord_xyz_ngb = find_vec_in_node_array3d(input.Topview.node_array[j].solid_array_neighbour[k].name, Node_array_out);
				cout << "Neighbour No: " <<k<< " Coord: "<<  coord_xyz_ngb.a << ", " << coord_xyz_ngb.b<<", "<< coord_xyz_ngb.c << endl;
				for (int d=0; d< vector_of_plane_parameters.size(); d= d+4){
					bool visible_ngb_p = true;
					float value_point = (coord_xyz.a + coord_xyz_ngb.a)*vector_of_plane_parameters[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*vector_of_plane_parameters[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*vector_of_plane_parameters[d + 2]/2 + vector_of_plane_parameters[d + 3];
					value_point = round( value_point * 1000.0 ) / 1000.0;

					cout << "Plane Parameters : " << vector_of_plane_parameters[d] << ", " << vector_of_plane_parameters[d+1] << ", " << vector_of_plane_parameters[d+2] << ", " << vector_of_plane_parameters[d+3] << endl;
 					if ((value_point>0 && vector_of_plane_parameters[d + 1] > 0) || (value_point<0 && vector_of_plane_parameters[d + 1] < 0) || value_point==0 || (vector_of_plane_parameters[d + 0]==0 && vector_of_plane_parameters[d + 1] == 0) || (vector_of_plane_parameters[d + 2]==0 && vector_of_plane_parameters[d + 1] == 0)){
						visible_ngb_p = true;
					}
					else {
						cout<< "Check2, value_point: " <<value_point<<endl;
						int num_node = Plane_array_out[d/4].circ_neighbour.size();
						float polygon_plane_proj[2*num_node] ;
						for (int c=0; c< 2*num_node; c=c+2){
							polygon_plane_proj[c] = Plane_array_out[d/4].circ_neighbour[c/2].a;
							polygon_plane_proj[c+1] = -Plane_array_out[d/4].circ_neighbour[c/2].c;
							cout << "Polygon Coord: "<<c/2 << " Member Name: "<< Plane_array_out[d/4].circ_neighbour[c/2].name <<" {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;
						}
						float points_proj[2] = {(coord_xyz.a + coord_xyz_ngb.a)/2, -(coord_xyz.c + coord_xyz_ngb.c)/2};
						cout << "Point : "<<(coord_xyz.a + coord_xyz_ngb.a)/2 <<", "<< (coord_xyz.b + coord_xyz_ngb.b)/2 << ", "<< (coord_xyz.c + coord_xyz_ngb.c)/2<< endl; 
						cout << "Point Proj: "<<points_proj[0] <<", "<< points_proj[1] <<endl; 
						if(isInside(polygon_plane_proj, num_node, points_proj)){
							visible_ngb_p = false;
							cout<< "false top" <<endl;
						}
					}
					if (!visible_ngb_p ){
						Plane_array_out.erase(Plane_array_out.begin()+d/4);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						cout << "vector_of_plane_parameters size: "<<vector_of_plane_parameters.size()<<endl;
						for (int i=0; i< Plane_array_out.size(); i++){

							cout << "Plane No.: " << i << ", " <<  endl;
							cout << "vector_of_plane_parameters size: "<<vector_of_plane_parameters[4*i]<<", "<<vector_of_plane_parameters[4*i + 1]<<", "<<vector_of_plane_parameters[4*i + 2]<<", "<<vector_of_plane_parameters[4*i + 3]<<", "<<endl;
							for (int j=0; j<Plane_array_out[i].circ_neighbour.size(); j++){
								cout << Plane_array_out[i].circ_neighbour[j].a << ", " << Plane_array_out[i].circ_neighbour[j].b << ", " << Plane_array_out[i].circ_neighbour[j].c << ", " << Plane_array_out[i].circ_neighbour[j].name << endl;
							}
							
						}
						break;
					}


				}
				
			}
		}

		//Side View
	currentView = input.Sideview;
	//Side
		for (int j= 0; j<input.Sideview.node_array.size(); j++){
			vector3 coord_xyz = find_vec_in_node_array3d(input.Sideview.node_array[j].coord.name, Node_array_out);
			//For Solid ngb
			for(int k=0; k< input.Sideview.node_array[j].solid_array_neighbour.size(); k++){
				vector3 coord_xyz_ngb = find_vec_in_node_array3d(input.Sideview.node_array[j].solid_array_neighbour[k].name, Node_array_out);
				for (int d=0; d< vector_of_plane_parameters.size(); d= d+4){
					bool visible_ngb_p = true;
					float value_point = (coord_xyz.a + coord_xyz_ngb.a)*vector_of_plane_parameters[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*vector_of_plane_parameters[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*vector_of_plane_parameters[d + 2]/2 + vector_of_plane_parameters[d + 3];
					value_point = round( value_point * 1000.0 ) / 1000.0;
					if ((value_point>0 && vector_of_plane_parameters[d + 0] > 0) || (value_point<0 && vector_of_plane_parameters[d + 0] < 0) || value_point==0 || (vector_of_plane_parameters[d + 1]==0 && vector_of_plane_parameters[d + 0] == 0) || (vector_of_plane_parameters[d + 0]==0 && vector_of_plane_parameters[d + 2] == 0)){
							visible_ngb_p = true;
						}
					else {
						cout<< "Check2" <<endl;
						int num_node = Plane_array_out[d/4].circ_neighbour.size();
						float polygon_plane_proj[2*num_node] ;
						for (int c=0; c< 2*num_node; c=c+2){
							polygon_plane_proj[c] = -Plane_array_out[d/4].circ_neighbour[c/2].c;
							polygon_plane_proj[c+1] = Plane_array_out[d/4].circ_neighbour[c/2].b;
							cout << "Polygon: {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;
						}
						float points_proj[2] = {-(coord_xyz.c + coord_xyz_ngb.c)/2, (coord_xyz.b + coord_xyz_ngb.b)/2};
						if(isInside(polygon_plane_proj, num_node, points_proj)){
							visible_ngb_p = false;
							cout<< "false side" <<endl;
							
						}
					}
					if (!visible_ngb_p ){
						Plane_array_out.erase(Plane_array_out.begin()+d/4);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);
						vector_of_plane_parameters.erase(vector_of_plane_parameters.begin()+ d);

						break;
					}
				}
				
			}
		}
		


	

	

	outFile.Plane_array  = Plane_array_out;

	cout<< "Output Ready" <<endl;

	cout << "No. of Nodes" << outFile.Node_array.size() <<endl;
	for (int r = 0; r< outFile.Node_array.size(); r++){
		cout << "Node number" << outFile.Node_array[r].coord3D.name <<endl;
		cout << "Neighbours: ";
		for (int w=0; w< outFile.Node_array[r].array_neighbour.size(); w++){
			cout << outFile.Node_array[r].array_neighbour[w].name << ", ";
		}
		cout << " " <<endl;
	}

	cout << "No. of Planes" << outFile.Plane_array.size() <<endl;
	for (int r = 0; r< outFile.Plane_array.size(); r++){
		cout << "Plane number : " << r  <<endl;
		cout << "Members: ";
		for (int w=0; w< outFile.Plane_array[r].circ_neighbour.size(); w++){
			cout << outFile.Plane_array[r].circ_neighbour[w].name << ", ";
		}
		cout << " " <<endl;
	}
	

		//View3DWindow();
	return outFile;
}
/*! \fn void C2DFile()
 * \brief This is the mode selection function for the 2D interface, gives a choice between line drawing and file input.
 * \brief Gives the option for Line Drawing and File Input.
 */


void C2DFile(){
	
	/// int mode2D represents the mode for 2D to 3D resconstruction
	/// 0 for Line Drawing
	/// 1 for File Input

	//Selection2dDisplay();
  	//glutDisplayFunc( Selection2dDisplay );
  	glui_2dSelection = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );

  	/*** Disable/Enable buttons ***/
 	new GLUI_Button( glui_2dSelection, "Line Drawing", Line, control_cb_2D );
  	new GLUI_Button( glui_2dSelection, "File Input", FileIn, control_cb_2D );
    new GLUI_Button( glui_2dSelection, "Back", Back, control_cb_2D ); 
  	//GLUI_Master.set_glutMouseFunc( myGlutMouse );
	//glutMainLoop();

}
