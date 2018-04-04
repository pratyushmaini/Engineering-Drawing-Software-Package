#include <iostream>
#include <list>
// #include "File2D.h"
#include "File2D_3D.h"
using namespace std;

///Labeled File
///Unlabeled File 
///Get users to label it.

int chooseMode(){
	/// 0 for labeled and 1 for unlabeled
	int n;
	//insert code
	return n;
}

File2D Takeinput(){
	///Browse from directory
	File2D file;
	//insert code
	return file;
}

void File2D::getLabels(){
	///Convert into labeled file by taking input
}

File2D File2DInput(){
	///Manages the further action depending on mode selected
	int mode = chooseMode();
	File2D input;

	if(mode == 0){
		input = Takeinput();
	}
	else {
		input = Takeinput();
		input.getLabels();		
	}
	return input;
}