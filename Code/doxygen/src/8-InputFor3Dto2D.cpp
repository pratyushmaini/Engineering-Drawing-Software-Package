#include <iostream>
#include <vector>
// #include "File3D.h"
#include "File2D_3D.h"
using namespace std;

///Labeled File
///Unlabeled File 
///Get users to label it.
int chooseMode3D(){
	/// 0 for labeled and 1 for unlabeled
}

File3D Takeinput3D(){
	///Browse from directory
	
}

void File3D::getLabels3D(){
	///Convert into labeled file by taking input
}

File3D File3DInput(){
	///Manages the further action depending on mode selected	
	int mode = chooseMode3D();
	File3D input;
	if(mode == 0){
		input = Takeinput3D();
	}
	else {
		input = Takeinput3D();
		input.getLabels3D();			
	}

	return input;
}