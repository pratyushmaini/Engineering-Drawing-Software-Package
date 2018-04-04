#include <iostream>
#include <vector>
// #include "File2D.h"
#include "File2D_3D.h"
using namespace std;


int selectView(){
	///View Selection (Front, Top, Side) --0,1,2
	int n;
	//insert Code
	return n;
}
void translate2D (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom2D (int zoom_amount){
	///zoom in/out by entering percentage
}

void undo2D (){
	///Undo previous Move
}

void File2D::Makenode2D(View_Node2D node){
	//Make a new Node in a 2D File
	vector2 coordinates;// = new vector2(0,0);

	///The first linked adjacency list is of those neighbours connected via a solid line
	vector<vector2> solid_array;
	///The second linked adjacency list is of those neighbours connected via a dashed line
	vector<vector2> dashed_array;
	View_Node2D newNode(coordinates, solid_array, dashed_array){
		coord.set (coordinates.get(0), coordinates.get(1), coordinates.name);
		solid_array_neighbour = n1;
		dashed_array_neighbour = n2;
	}
	OrthographicView currentOrthView;
	currentOrthView.n
} 
void File2D::SolidLine2D(View_Node2D node1, View_Node2D node2){
	//make solid line
}

void File2D::DashedLine2D(View_Node2D node1, View_Node2D node2){
	//make dashhed line
}

void File2D::deleteNode(View_Node2D node){
	// Remove a particular node and the dependent lines from the file
}

void SetView2D(){
	///Set view as done
}

void NextStep2D(){
	///Choose between going to Next View or Completing the drawing
}



OrthographicView editView(OrthographicView initialView){
	OrthographicView view;
	///Functional Specification: 
	///Make node
	///pan around
	///make solid line
	///make dashhed line
	///undo or go back
	///zoom in/out
	///Set view
	///Next View or Complete
	return view;
}

File2D Line2DInput(File2D inputFile){
	int view = 3;
	File2D fileoutput = inputFile;
	view = selectView();
	if (view == 0){
		fileoutput.setView(0, editView(fileoutput.getView(0)));
	}
	else if (view == 1){
		fileoutput.setView(1, editView(fileoutput.getView(1)));
	}
	else if (view == 2){
		fileoutput.setView(2, editView(fileoutput.getView(2)));
	}	
	return fileoutput;
}
