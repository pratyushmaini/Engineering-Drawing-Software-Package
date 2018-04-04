#ifndef FILE2D_3D_H
#define FILE2D_3D_H
#include <vector>
#include <iostream>
// #include "File3D.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

using namespace  std;
extern int window_num;

// int window_num = 1;

///Local two tuple implementation for storing co-ordinates
class vector2 {
	public:
	///Local Definition of first member of a two tuple for x, y, or z co-ordinates depending on orthographic view chosen
	float a;
	///Local Definition of first member of a two tuple for y, z, or x co-ordinates depending on orthographic view chosen
	float b;
	///Identifier
	string name;

	///Constructor for a vector2 tuple
	
		vector2 (): a(0), b(0), name(""){}
		// 	this -> a = x; 
		// 	this -> b = y;
		// }
		vector2 (float x, float y, string name_in){
			a = x; 
			b = y;
			name = name_in;
		}

		float get(int n){
			if (n== 0) return a; 
			else return b;
		}
		void set(float x, float y, string name_in){
			a = x; 
			b = y;
			name = name_in;
		}
};

///View_Node2D stores the coordinates of itself and its neighbours
class View_Node2D{
	public:
	///coord stores a two-tuple of the coordinates of the node
	vector2 coord;// = new vector2(0,0);

	///The first linked adjacency list is of those neighbours connected via a solid line
	vector<vector2> solid_array_neighbour;
	///The second linked adjacency list is of those neighbours connected via a dashed line
	vector<vector2> dashed_array_neighbour;
	///Constructor function that creates a node having the coordinates and a list of solid and dashed neighbours linked to it.
	View_Node2D(vector2 coordinates, vector<vector2> n1, vector<vector2> n2){
		coord.set (coordinates.get(0), coordinates.get(1), coordinates.name);
		solid_array_neighbour = n1;
		dashed_array_neighbour = n2;
	}
};

///Stores an individual orthographic projection (top/side/front)
class OrthographicView {
	public:
	///This class contains an array of all the nodes of the view.
	vector<View_Node2D> node_array;
	///Constructor for storing OrthographicView
	public:
		OrthographicView(){
			vector<View_Node2D> emptyList;
			node_array = emptyList;
		}
		OrthographicView(vector<View_Node2D> n){
			node_array = n;
		}
};

/// Basic datatype that implements the 2D projections

class File2D{
	public:
	///This contains the Orthographic View of the Frontview of the object.
	OrthographicView Frontview;
	///This contains the Orthographic View of the Sideview of the object
	OrthographicView Sideview;
	///This contains the Orthographic View of the Topview of the object
	OrthographicView Topview;
		/// Default Constructor
	public:
	File2D(){
			vector<View_Node2D> emptyList;
			OrthographicView nullView = emptyList;
			Frontview = nullView;
			Sideview = nullView;
			Topview = nullView;		
	}
	public:
		///Set Orthographic View -- 0,1,2 correspond to Front, Side, Top
		void setView(int n, OrthographicView view){
			if (n== 0) Frontview = view;
			else if (n == 1) Sideview = view; 
			else Topview = view;
		}
		///Get Orthographic View -- 0,1,2 correspond to Front, Side, Top
		OrthographicView getView(int n){
			if (n== 0) return Frontview;
			else if (n == 1) return Sideview; 
			else return Topview;
		}
	///Make a new Node in a 2D File
	bool Makenode2D(vector2 node); 
	///make a solid line between two nodes
	bool SolidLine2D(string node1, string node2);
	///make a dashed line between two nodes
	bool DashedLine2D(string node1, string node2);
	///Get Labels for Unlabled 2D File
	void getLabels();
	///Delete a selected node from the 2D File
	void deleteNode(string node);

};

///Implements the functions that provide UI options to users while viewing 3D model
// class View3DWindow{
	///Used to pan around the screen while viewing the 3D model
	void translate3Dview (float x_move, float y_move, float z_move);
	///Used to zoom in or out of the screen while viewing the 3D model
	void zoom3Dview(int zoom_amount);
	///View or Hide the Node Labels while viewing the 3D model
	void LabelShow3Dview(int show);
	///Used to rotate the angle of view along x, y, or z aaxes while viewing the 3D model	
	void Rotate3Dview (float x_rotate, float y_rotate, float z_rotate);
	///Constructor for 3D Window-- Takes Standard Window Size as 800*600
// 	View3DWindow(){
	void Selection2dDisplay();

// 	}
// };

///////////////////////////////////////////////////////////////////////


///Local three tuple implementation for storing co-ordinates
class vector3 {
	public:
	///Local Definition of first member of a three tuple for x co-ordinate 
	float a;
	///Local Definition of second member of a three tuple for y co-ordinate
	float b;
	///Local Definition of third member of a three tuple for z co-ordinate
	float c;
	///Constructor for a vector3 tuple
	string name;

	vector3 (): a(0), b(0), c(0), name(""){}
		// 	this -> a = x; 	
		// 	this -> b = y;
		// }
	
	vector3 (float x, float y, float z, string name_in){
		a = x; 
		b = y;
		c = z;
		name = name_in;
	}

	float get(int n){
		if (n== 0) return a;
		else if (n == 1) return b; 
		else return c;
	}
	void set(int x, int y, int z, string name_in){
		a = x; 
		b = y;
		c = z;
		name = name_in;
	}
	

};	
///PlaneNode3D stores the planes in a circular linked list 
class PlaneNode3D{
	
	public:
	///Circular linkedlist of all neighbouring nodes in the plane
	vector<vector3> circ_neighbour;
	///Constructor function that creates a circular linked list of nodes in the plane.
	PlaneNode3D( ){
		vector<vector3> ngb;
		circ_neighbour = ngb;
	}

	PlaneNode3D( vector<vector3> ngb){
		circ_neighbour = ngb;
	}
	
};	
///View_Node3D stores the coordinates of itself and its neighbours	
class View_Node3D{
	public:
	///coord3D stores a two-tuple of the coordinates of the node
	vector3 coord3D;
	///The first linked adjacency list is of those neighbours connected to it
	vector<vector3> array_neighbour;
	///Constructor function that creates a node having the coordinates and a list of neighbours linked to it.
	View_Node3D(vector3 coordinates, vector<vector3> n1){
		coord3D = coordinates;
		array_neighbour = n1;

	}
};

/// Basic datatype that implements the 3D model
class File3D{
	public:
	///This contains Nodes, Edges, Planes of the object.
	vector<PlaneNode3D> Plane_array ;
	///This is an adjacency list of all nodes and their neighbours
	vector<View_Node3D> Node_array;
	
	File3D(){
	/// if number entered is zero then an empty File2D is created, else an imported one can be used.
			vector<PlaneNode3D> nullArray;
			Plane_array = nullArray;
			vector<View_Node3D> emptyList;
			Node_array = emptyList;
	}
	///Make a new Node in a 3D File
	bool Makenode3D(float x, float y, float z, string nam);
	///Make solid line between two nodes
	bool MakeEdge3D(string node1, string node2);
	///Get Labels for Unlabled 3D File
	void getLabels3D();
	///Creates solid of desired height on the last plane created 
	void extrude(float height, File3D inputFile);
	///Label Solid Surfaces on the given 3D object
	void getSolidSurfaceLabels();
	/// Remove a particular node and the dependent lines from the file
	void deleteNode3D(string n);
};

///Implements the functions that provide UI options to users while viewing projections
// class View2DWindow{
	///Used to pan around the screen while viewing the orthographic projections
	void translate2Dview (float x_move, float y_move, float z_move);
	///Used to zoom in or out of the screen while viewing the orthographic projections
	void zoom2Dview(int zoom_amount);
	///View or Hide the Node Labels while viewing the orthographic projections
	void LabelShow2Dview(int show);
	///Constructor for 2D Window-- Takes Standard Window Size as 800*600
// 	View2DWindow(){

// 	}

// };

////////////////////////////////////////////////////////////////////////////////////
//class File3D{};
// int window_num;
File3D Start3DTrans(File2D input);
void mainGlutDisplay();
void line_2d_printer();
void line_2d_printer_of_selected(OrthographicView printView, int sel);
void file_2d_printer();
void view_3d_printer();
void C2DFile();
File2D Line2DInput(File2D inputFile);
File2D File2DInput();
void View3DWindow(File3D outFile, File2D inputFile);
//extern class File2D{};


File2D Start2DTrans(File3D input);
void line_3d_printer();
void file_3d_printer();
void C3DFile();
void view_2d_printer();
File3D Line3DInput(File3D inputFile);
File3D File3DInput();
void View2DWindow(File2D outFile, File3D inputFile);


#endif
