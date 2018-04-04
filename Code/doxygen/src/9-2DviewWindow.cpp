#include <iostream>
#include <vector>
// #include "File3D.h"
#include "File2D_3D.h"
using namespace std;

File3D viewFile;
File2D inputFile;


void translate2Dview (float x_move, float y_move, float z_move){
	///pan around by entering percentage movement for translation along each direction
}

void zoom2Dview(int zoom_amount){
	///zoom in/out by entering percentage
}

void LabelShow2Dview(int show){
	//View or Hide Labels
}

void Edit3D_2Dview (File3D inputFile){
	///Edit 3D Model
	File3D input = Line3DInput(inputFile);
}


void BackToModeSelectionUI_2Dview(){
	///BackToModeSelectionUI after having seen the 3D object	
}

void Save3D_2Dview(){
	///Makes a text File that contains the 3D array
}

void Save2D_2Dview(){
	///Makes a text File that contains the 3D array
}

void View2DWindow(File2D outFile, File3D inputFile){
	///Manages all actions depending on mouse and keyboard input
}
