#include <iostream>
#include <vector>
// #include "File2D.h"
#include "File2D_3D.h"
using namespace std;



void translate3Dview (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom3Dview(int zoom_amount){
	///zoom in/out by entering percentage
}

void LabelShow3Dview(int show){
	///View or Hide Labels
}

void Rotate3Dview (float x_rotate, float y_rotate, float z_rotate){
	///Rotate XYZ by entering degree rotation along each axis
}

void Edit3Dview (File2D inputFile){
	///Edit 2D Model
	File2D input = Line2DInput(inputFile);
}

void BackToModeSelectionUI3Dview(){
	///BackToModeSelectionUI after having seen the 3D object	
}

void Save3D_3Dview(){
	///Makes a text File that contains the 3D array
}

void Save2D_3Dview(){
	///Makes a text File that contains the 3D array
}

void View3DWindow(File3D outFile, File2D inputFile){
	///Manages all actions depending on mouse and keyboard input
}


