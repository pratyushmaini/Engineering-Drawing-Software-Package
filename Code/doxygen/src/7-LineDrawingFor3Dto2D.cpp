#include <iostream>
#include <vector>
// #include "File3D.h"
#include "File2D_3D.h"
using namespace std;


int selectView3D(){
	///View Selection (XY, YZ, ZX) --0,1,2
	int n;
	//insert Code
	return n;
}

void selectPlane(){
	///Plane Selection (XY, Yz, Zx)
	/// --0,1,2
}


void translate3D (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom3D (int zoom_amount){
	///zoom in/out by entering percentage
}

void undo3D (){
	///Undo previous Move
}

void File3D::extrude(float height, File3D inputFile){
	//Creates solid of desired height on the last plane created 
}

void File3D::Makenode3D(View_Node3D node){
	//Make a new Node in a 3D File

} 
void File3D::MakeEdge3D(View_Node3D node1, View_Node3D node2){
	//Make solid line between two nodes
}

void File3D::deleteNode3D(View_Node3D node){
	// Remove a particular node and the dependent lines from the file
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

File3D Line3DInput(File3D inputFile){
	int view = 3;

	File3D fileoutput;
	fileoutput = inputFile;
	view = selectView3D();
	fileoutput =  editView(fileoutput);
	return fileoutput;
	
}
