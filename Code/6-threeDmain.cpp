#include <vector>
#include <array>
// #include "File2D.h"
#include <string.h>
#include <GL/glui.h>
#include <fstream>
#include <sstream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "File2D_3D.h"
using namespace std;

#define Line3D             600
#define FileIn3D           601
#define Back6 			   602

extern int main_window;
// extern int window_num;
int mode3D = 2; 
GLUI *glui_3dSelection;
extern GLUI *glui;
File3D input3D;
extern void home();

/*! \addtogroup Module1 Module for 3D window
   *  All the functions related to 3D file are available here.
   *  @{
   */

 /*! \fn void Start2DTrans(input)
 * \param input
 * \brief Gives the option for Line Drawing and File Input.
 */
bool isInside(float polygon[], int n, float p[]);
void threeDmodeSelection(){
  
///Two Sub Files: Line Drawing , Direct Input
	
	/// This represents the mode for 2D to 3D resconstruction
	/// 0 for Line Drawing
	/// 1 for File Input
	
	if (mode3D == 0) {
		File3D null_array;
		window_num = 7;
		
		input3D = Line3DInput(null_array);
		mode3D = 2;
	}
	else if (mode3D == 1) {
		window_num = 8;
		input3D = File3DInput();
		mode3D = 2;
	}
	// File2D outFile = Start2DTrans(input);
	//View2DWindow(outFile, input);
	
}


void control_cb_3D( int control )
{  

  if ( control == Line3D )
  {
    mode3D = 0;
    // printf("Apple1\n");
    glui_3dSelection -> close();
    threeDmodeSelection();
  }
  else if ( control == FileIn3D )
  {
    mode3D = 1;

    glui_3dSelection -> close();
    threeDmodeSelection();
  }
  else if ( control == Back6 )
  {
  	glui_3dSelection -> close();
  	window_num = 1;
  	home();
  }
}

///Start 2D Transformation()
File2D Start2DTrans(File3D input){
	///Algorithm for 3D to 2D
	File2D outFile;
	//This contains the Orthographic View of the Frontview_outfile of the object.
	OrthographicView Frontview_outfile;
	//This contains the Orthographic View of the Sideview_outfile of the object
	OrthographicView Sideview_outfile;
	//This contains the Orthographic View of the Topview_outfile of the object
	OrthographicView Topview_outfile;
	cout << "Total No. of planes " <<input.Plane_array.size()<<endl;
	vector<View_Node3D> nodelist = input.Node_array;
	vector<PlaneNode3D> planelist = input.Plane_array;
	int num_size = planelist.size()*4 ;
	vector<float> plane_parameters_list; //float plane_parameters_list[num_size];

	//FINDING EQUATION OF ALL PLANES

	for(int r=0; r<planelist.size(); r++){
		PlaneNode3D planenode3D_list = planelist[r];
		vector<vector3>  planevec_list = planenode3D_list.circ_neighbour;
		float vec0[] = {planevec_list[0].a, planevec_list[0].b, planevec_list[0].c};
		float vec1[] = {planevec_list[1].a, planevec_list[1].b, planevec_list[1].c};
		float vec2[] = {planevec_list[2].a, planevec_list[2].b, planevec_list[2].c};
		float dir0[] = {vec0[0]-vec1[0], vec0[1]-vec1[1], vec0[2]-vec1[2]};
		float dir1[] = {vec2[0]-vec1[0], vec2[1]-vec1[1], vec2[2]-vec1[2]};
		float normal[] = { (dir0[1]*dir1[2] - dir0[2]*dir1[1]), (dir0[2]*dir1[0] - dir0[0]*dir1[2]), (dir0[0]*dir1[1] - dir0[1]*dir1[0])};
		float plane_parameters[] = {normal[0], normal[1], normal[2], -(normal[0]*vec0[0] + normal[1]*vec0[1] + normal[2]*vec0[2])}; //ax+by+cz+d=0
		cout << "Parameters Plane No.: " << r << ", ";
		for (int t=0; t<4; t++){
			plane_parameters_list.push_back(plane_parameters[t]);
			cout << plane_parameters[t] << ", ";
		}
		cout << " " << endl;
	}

	//Making Orthographic View
    bool visible_ngb_p = true;                                     // __
	//Front:(HORIZ, VERT) X-Y |_, Top: X-(-Z) |, Side: Y,(-Z)
	for (int m = 0; m<3; m++){

		OrthographicView tempOrthographicView;
		//At the level of a node_array that has coordinates and neighbours.
		vector<View_Node2D> node_array_obj;
		for (int i = 0; i< nodelist.size(); i++){
			cout << "Node No.: " << i << " View No.: "<< m << endl;
			View_Node3D current_node = nodelist[i];
			vector3 coord_xyz = current_node.coord3D;
			
			vector<vector3> array_ngb_xyz = current_node.array_neighbour;
			//x-y, y-z, z-x
			vector2 coord_ab;
			
			if (m==0){
				vector2 coord_ab_temp(coord_xyz.get(0),coord_xyz.get(1),current_node.coord3D.name);
				coord_ab = coord_ab_temp;
				vector<vector2> solid_array, dashed_array;

				
				for (int p=0; p<array_ngb_xyz.size(); p++){
					vector3 coord_xyz_ngb(array_ngb_xyz[p].get(0), array_ngb_xyz[p].get(1), array_ngb_xyz[p].get(2), array_ngb_xyz[p].name);
					vector2 coord_ab_ngb(coord_xyz_ngb.get(0),coord_xyz_ngb.get(1),coord_xyz_ngb.name);
					visible_ngb_p = true;
					cout << "Neighbour Number: " << coord_ab_ngb.name << endl;
					for (int d=0; d< (plane_parameters_list.size()); d = d+4){
						cout << "Plane No.: " <<d/4 << "Node No.: " << i << " Front View" << endl;
						float value_point = (coord_xyz.a + coord_xyz_ngb.a)*plane_parameters_list[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*plane_parameters_list[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*plane_parameters_list[d + 2]/2 + plane_parameters_list[d + 3];
						value_point = round( value_point * 1000.0 ) / 1000.0;
						cout << "Value Point: " <<value_point << " Coordinates Point: "<< coord_xyz.a<< ", "<< coord_xyz.b<< ", " << coord_xyz.c<< endl;
						if ((value_point>0 && plane_parameters_list[d + 2] > 0) || (value_point<0 && plane_parameters_list[d + 2] < 0) || value_point==0 || (plane_parameters_list[d + 0]==0 && plane_parameters_list[d + 2] == 0)|| (plane_parameters_list[d + 2]==0 && plane_parameters_list[d + 1] == 0)){
							visible_ngb_p = true;
						}
						else {
							cout<< "Check2" <<endl;
							int num_node = planelist[d/4].circ_neighbour.size();
							float polygon_plane_proj[2*num_node] ;
							for (int c=0; c< 2*num_node; c=c+2){
								polygon_plane_proj[c] = planelist[d/4].circ_neighbour[c/2].a;
								polygon_plane_proj[c+1] = planelist[d/4].circ_neighbour[c/2].b;
								cout << "Polygon: {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;
							}
							float points_proj[2] = {(coord_ab.a + coord_ab_ngb.a)/2, (coord_ab.b + coord_ab_ngb.b)/2};
							if(isInside(polygon_plane_proj, num_node, points_proj)){
								visible_ngb_p = false;
								cout<< "false front" <<endl;
								break;
							}
						}
					}
					if (visible_ngb_p){
						solid_array.push_back(coord_ab_ngb);	
					}
					else{
						dashed_array.push_back(coord_ab_ngb);
					}
					
				}
				View_Node2D tempNode(coord_ab, solid_array, dashed_array);
				node_array_obj.push_back(tempNode);
				tempOrthographicView.node_array = node_array_obj;
				Frontview_outfile = tempOrthographicView;
			}	

			else if (m==1){
				vector2 coord_ab_temp(coord_xyz.get(0),-coord_xyz.get(2),current_node.coord3D.name);
				coord_ab = coord_ab_temp;
				vector<vector2> solid_array, dashed_array;
				
				for (int p=0; p<array_ngb_xyz.size(); p++){
					vector3 coord_xyz_ngb(array_ngb_xyz[p].get(0), array_ngb_xyz[p].get(1), array_ngb_xyz[p].get(2), array_ngb_xyz[p].name);
					vector2 coord_ab_ngb(coord_xyz_ngb.get(0),-coord_xyz_ngb.get(2),coord_xyz_ngb.name);
					visible_ngb_p = true;
					cout << "Neighbour Number: " << coord_ab_ngb.name << endl;
					for (int d=0; d< (plane_parameters_list.size()); d = d+4){
						cout << "Plane No.: " <<d/4 << "Node No.: " << i<< " Top View" << endl;
						float value_point = (coord_xyz.a + coord_xyz_ngb.a)*plane_parameters_list[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*plane_parameters_list[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*plane_parameters_list[d + 2]/2 + plane_parameters_list[d + 3];
						value_point = round( value_point * 1000.0 ) / 1000.0;
						if ((value_point>0 && plane_parameters_list[d + 1] > 0) || (value_point<0 && plane_parameters_list[d + 1] < 0) || value_point==0 || (plane_parameters_list[d + 0]==0 && plane_parameters_list[d + 1] == 0) || (plane_parameters_list[d + 2]==0 && plane_parameters_list[d + 1] == 0)){
							visible_ngb_p = true;
						}
						else {
							cout<< "Check2" <<endl;
							int num_node = planelist[d/4].circ_neighbour.size();
							float polygon_plane_proj[2*num_node];
							for (int c=0; c< 2*num_node; c=c+2){
								polygon_plane_proj[c] = planelist[d/4].circ_neighbour[c/2].a;
								polygon_plane_proj[c+1] = -planelist[d/4].circ_neighbour[c/2].c;
								cout << "Polygon: {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;								
							}
							float points_proj[2] = {(coord_ab.a + coord_ab_ngb.a)/2, (coord_ab.b + coord_ab_ngb.b)/2};
							if(isInside(polygon_plane_proj, num_node, points_proj)){
								visible_ngb_p = false;
								cout<< "false top" <<endl;
								break;
							}
						}
					}
					if (visible_ngb_p){
						solid_array.push_back(coord_ab_ngb);	
					}
					else{
						dashed_array.push_back(coord_ab_ngb);
					}
				}
				View_Node2D tempNode(coord_ab, solid_array, dashed_array);
				node_array_obj.push_back(tempNode);
				tempOrthographicView.node_array = node_array_obj;
				Topview_outfile = tempOrthographicView;
			}

			else if (m==2){
				vector2 coord_ab_temp(-coord_xyz.get(2),coord_xyz.get(1),current_node.coord3D.name);
				coord_ab = coord_ab_temp;
				vector<vector2> solid_array, dashed_array;
				
				for (int p=0; p<array_ngb_xyz.size(); p++){
					vector3 coord_xyz_ngb(array_ngb_xyz[p].get(0), array_ngb_xyz[p].get(1), array_ngb_xyz[p].get(2), array_ngb_xyz[p].name);
					vector2 coord_ab_ngb(-coord_xyz_ngb.get(2),coord_xyz_ngb.get(1),coord_xyz_ngb.name);
					visible_ngb_p = true;
					cout << "Neighbour Number: " << coord_ab_ngb.name << endl;
					for (int d=0; d< (plane_parameters_list.size()); d = d+4){
						cout << "Plane No.: " <<d/4 << "Node No.: " << i<< " Side View" << endl;
						float value_point = (coord_xyz.a + coord_xyz_ngb.a)*plane_parameters_list[d + 0]/2 +(coord_xyz.b + coord_xyz_ngb.b)*plane_parameters_list[d + 1]/2 + (coord_xyz.c + coord_xyz_ngb.c)*plane_parameters_list[d + 2]/2 + plane_parameters_list[d + 3];
						value_point = round( value_point * 1000.0 ) / 1000.0;
						if ((value_point>0 && plane_parameters_list[d + 0] > 0) || (value_point<0 && plane_parameters_list[d + 0] < 0) || value_point==0 || (plane_parameters_list[d + 1]==0 && plane_parameters_list[d + 0] == 0) || (plane_parameters_list[d + 0]==0 && plane_parameters_list[d + 2] == 0)){
							visible_ngb_p = true;
						}
						else {
							cout<< "Check2" <<endl;
							int num_node = planelist[d/4].circ_neighbour.size();
							float polygon_plane_proj[2*num_node];
							for (int c=0; c< 2*num_node; c=c+2){
								polygon_plane_proj[c] = -planelist[d/4].circ_neighbour[c/2].c;
								polygon_plane_proj[c+1] = planelist[d/4].circ_neighbour[c/2].b;
								cout << "Polygon: {"<<polygon_plane_proj[c]<<", "<<polygon_plane_proj[c+1]<<"}"<<endl;
							}
							float points_proj[2] = {(coord_ab.a + coord_ab_ngb.a)/2, (coord_ab.b + coord_ab_ngb.b)/2};
							if(isInside(polygon_plane_proj, num_node, points_proj)){
								visible_ngb_p = false;
								cout<< "false side" <<endl;
								break;
							}
						}
					}
					if (visible_ngb_p){
						solid_array.push_back(coord_ab_ngb);	
					}
					else{
						dashed_array.push_back(coord_ab_ngb);
					}	
				}
				View_Node2D tempNode(coord_ab, solid_array, dashed_array);
				node_array_obj.push_back(tempNode);				
				tempOrthographicView.node_array = node_array_obj;
				Sideview_outfile = tempOrthographicView;
			}
		}
	}
	outFile.Topview = Topview_outfile;
	outFile.Frontview = Frontview_outfile;
	outFile.Sideview = Sideview_outfile;
	return outFile;	
}

/*! \fn void C3DFile()
 * \brief Two Sub Files: Line Drawing , Direct Input
 * \brief Manages the further action depending on mode selected
 */
void C3DFile(  ){


	glui_3dSelection = GLUI_Master.create_glui_subwindow( main_window, 
              			GLUI_SUBWINDOW_RIGHT );

  	/*** Disable/Enable buttons ***/
 	new GLUI_Button( glui_3dSelection, "Line Drawing", Line3D, control_cb_3D );
  	new GLUI_Button( glui_3dSelection, "File Input", FileIn3D, control_cb_3D );
  	new GLUI_Button( glui_3dSelection, "Back", Back6, control_cb_3D );
}



// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000
 
// struct vector<float>
// {
//     int x;
//     int y;
// };
 
// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(float p[], float q[], float r[])
{
    if (q[0] <= max(p[0], r[0]) && q[0] >= min(p[0], r[0]) &&
            q[1] <= max(p[1], r[1]) && q[1] >= min(p[1], r[1]))
        return true;
    return false;
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(float p[], float q[], float r[])
{
    float val = (q[1] - p[1]) * (r[0] - q[0]) -
              (q[0] - p[0]) * (r[1] - q[1]);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(float p1[], float q1[], float p2[], float q2[])
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}
 
// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(float polygon[], int n, float p[])
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;
 
    // Create a point for line segment from p to infinite
    float extreme[] = {INF, p[1]};
    
 
    // Count intersections of the above line with sides of polygon
    float count = 0;
    int iter = 0;
    do
    {
        int next = (iter+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[iter]' to 'polygon[next]'
        float iter_node[] = {polygon[iter*2], polygon[iter*2 + 1]};
        float next_node[] = {polygon[next*2], polygon[next*2 + 1]};
        if (doIntersect(iter_node, next_node, p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(iter_node, p, next_node) == 0)
               return onSegment(iter_node, p, next_node);
 
           if (polygon[iter*2 + 1] == p[1]){
                if (iter==0){
                    if ((polygon[2*n - 1] < polygon[iter*2 + 1] &&  polygon[2*next + 1] < polygon[iter*2 + 1])  || (polygon[2*n -1] > polygon[iter*2 + 1] &&  polygon[2*next + 1] > polygon[iter*2 + 1])){
                        count = count + 1;
                        // cout << "A" << endl;
                    }

                    else{
                        count = count + 0.5;
                        // cout << "B" << endl;
                    }
                }
                else{
                    if ((polygon[iter*2 - 1] < polygon[iter*2 + 1] &&  polygon[2*next + 1] < polygon[iter*2 + 1])  || (polygon[iter*2 - 1] > polygon[iter*2 + 1] &&  polygon[2*next + 1] > polygon[iter*2 + 1])){
                        count = count + 1;
                        // cout << "C" << endl;
                    }
                    else{
                        count = count + 0.5;
                        // cout << "D" << endl;
                    }

                }
                
            }
            else if (polygon[2*next + 1] == p[1]){
                if ((polygon[iter*2 + 1] < polygon[2*next + 1] &&  polygon[2*((next+1)%n) + 1] < polygon[2*next + 1])  || (polygon[iter*2 + 1] > polygon[2*next + 1] &&  polygon[2*((next+1)%n) + 1] > polygon[2*next + 1])){
                        count = count + 1;
                        // cout << "E" << endl;
                    }
                    else{
                        count = count + 0.5;
                        // cout << "F" << endl;
                    }
            }
            else 
                count++;
        }
        iter = next;
    } while (iter != 0);
 
    // Return true if count is odd, false otherwise
    return (((int)count)%2 == 1);  // Same as (count%2 == 1)
}
 


 /*! @} */
