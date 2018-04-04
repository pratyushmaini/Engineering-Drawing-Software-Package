#include <iostream>
#include <vector>
// #include "File3D.h"
#include "File2D_3D.h"


using namespace std;

/*! \addtogroup Module1 Module for 3D window
   *  All the functions related to 3D file are available here.
   *  @{
   */

 /*! \fn void Start2DTrans(input)
 * \param input
 * \brief Gives the option for Line Drawing and File Input.
 */


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

	vector<View_Node3D> nodelist = input.Node_array;
	//Making Orthographic View

	//Front: y-z, Top: x-y, Side: z-x
	for (int m = 0; m<3; m++){
		OrthographicView tempOrthographicView;
		//At the level of a node_array that has coordinates and neighbours.
		vector<View_Node2D> node_array_obj;
		for (int i = 0; i< nodelist.size(); i++){
			View_Node3D current_node = nodelist[i];
			vector3 coord_xyz = current_node.coord3D;
			vector<vector3> array_ngb_xyz = current_node.array_neighbour;
			//x-y, y-z, z-x
			vector2 coord_ab(coord_xyz.get(m),coord_xyz.get(m%2),current_node.coord3D.name);
			vector<vector2> solid_array, dashed_array;

			for (int p=0; p<array_ngb_xyz.size(); p++){
				vector3 coord_xyz_ngb(array_ngb_xyz[p].get(0), array_ngb_xyz[p].get(1), array_ngb_xyz[p].get(2), current_node.coord3D.name);
				
				vector2 coord_ab_ngb(coord_xyz_ngb.get(m),coord_xyz_ngb.get(m%2), current_node.coord3D.name);
				solid_array.push_back(coord_ab_ngb);
				View_Node2D output_node(coord_ab, solid_array, dashed_array);
			}
			View_Node2D tempNode(coord_ab, solid_array, dashed_array);
			node_array_obj.push_back(tempNode);
		}
		tempOrthographicView.node_array = node_array_obj;
		if (m==0) {
			Topview_outfile = tempOrthographicView;
		}
		else if (m==1){
			Frontview_outfile = tempOrthographicView;
		}
		else{
			Sideview_outfile = tempOrthographicView;
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
void C3DFile(){
	int mode3D = 2; 
	/// This represents the mode for 2D to 3D resconstruction
	/// 0 for Line Drawing
	/// 1 for File Input
	File3D input;
	if (mode3D == 0) {
		File3D null_array;
		input = Line3DInput(null_array);
		mode3D = 2;
	}
	else if (mode3D == 1) {
		input = File3DInput();
		mode3D = 2;
	}
	File2D outFile = Start2DTrans(input);
	//View2DWindow(outFile, input);

}

 /*! @} */
