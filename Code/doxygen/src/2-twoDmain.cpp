#include <iostream>
#include <vector>
// #include "File2D.h"
#include "File2D_3D.h"

using namespace std;

/*! \addtogroup Module Module for 2D window
   *  All the functions related to 2D file are available here.
   *  @{
   */

 /*! \fn void Start3DTrans(input)
 * \param input
 * \brief Gives the option for Line Drawing and File Input.
 */

File3D Start3DTrans(File2D input){
	///Starts the 3D Transformation of the given 2D projections
	///Algorithm for 2D to 3D is inserted here
	File3D outFile;
	vector<PlaneNode3D> Plane_array;
	vector<View_Node3D> Node_array;
	
	OrthographicView currentView = input.Frontview;

	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		
		vector3 coordi(nod.coord.a,nod.coord.b,0,nod.coord.name);
		vector<vector3> arr;

		for(int j=0; j<nod.solid_array_neighbour.size(); j++){
			vector2 point = nod.solid_array_neighbour[j];
			vector3 coordi1(point.a,point.b,0,point.name);
			arr.push_back(coordi1);	
		}
		for(int j=0; j<nod.dashed_array_neighbour.size(); j++){
			vector2 point = nod.dashed_array_neighbour[j];
			vector3 coordi1(point.a,point.b,0,point.name);		
			arr.push_back(coordi1);	
		}
		View_Node3D v(coordi,arr);
		Node_array.push_back(v);
	}

	currentView = input.Sideview;

	for(int i=0; i<currentView.node_array.size(); i++){
		View_Node2D nod = currentView.node_array[i];
		
		int l=0;
		for(int j=0; ;j++){
			if(nod.coord.name==Node_array[j].coord3D.name){
				l=j;
				break;
			}
		}

		Node_array[l].coord3D.c = (-nod.coord.b);

		for(int j=0; j<nod.solid_array_neighbour.size(); j++){
			vector2 point = nod.solid_array_neighbour[j];
			
			vector<vector3> array = Node_array[l].array_neighbour;
			
			int m=0;
				for(int j=0; ;j++){
					if(point.name==array[j].name){
						m=j;
						break;
					}
				}
				array[m].c=(-point.b);	
		}
		for(int j=0; j<nod.dashed_array_neighbour.size(); j++){
			vector2 point = nod.dashed_array_neighbour[j];
			
			vector<vector3> array = Node_array[l].array_neighbour;
			
			int m=0;
				for(int j=0; ;j++){
					if(point.name==array[j].name){
						m=j;
						break;
					}
				}
				array[m].c=(-point.b);	
		}
	}



	return outFile;
}

/*! \fn void C2DFile()
 * \brief This is the mode selection function for the 2D interface, gives a choice between line drawing and file input.
 * \brief Gives the option for Line Drawing and File Input.
 */

void C2DFile(){
	int mode2D = 2;
	/// int mode2D represents the mode for 2D to 3D resconstruction
	/// 0 for Line Drawing
	/// 1 for File Input

	///Two Sub Files: Line Drawing , Direct Input
	File2D input;
	if (mode2D == 0) {
		File2D nulls;
		input = Line2DInput(nulls);
		mode2D = 2;
	}
	else if (mode2D == 1) {
		input = File2DInput();
		mode2D = 2;
	}
	File3D outFile = Start3DTrans(input);
	View3DWindow(outFile, input);

}

  /*! @} */


