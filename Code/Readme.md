This a documentation for Engineering Drawing Software Package 
  
  Work by Pratyush Maini and Pranav Baurasia
  
  The Code has been Modularised into 9 C++ files and two header files.

  1-main.cpp:: The first file that is compiled and is basically used for mode selection and calling sub-functions. This enables users selection of a 2D window or 3D window.

  This also the point where we make use of th rendering libraries in OpenGL and GLUT to draw objects and provide graphic user interface for the user. The same have been included in the libraries.

  File2D.h:: Contains all the classes that we require for the two dimensional interface, and also the window that is seen upon 2D transformation into a 3D object. The functions associated with each class are also flagged herein.

  2-twoDmain.cpp:: Functions in this file are called when the user decides to draw 2D orthographic projections of an object or import a file from his local database. The basic purpose of the functions in this file is to make a user select between drawing/importing a file.

  3-LineDrawing.cpp:: Contains all the functions that enable a user to create new nodes, join two nodes, delete nodes etc. while making a 2D diagram. 
	
  4-InputFor2D.cpp:: The user is given two choices of either loading a labeled file, or an unlabeled one, in whic case he is supposed to Add Labels through getLabels().

  5-3DviewWindow.cpp:: The basic UI for viewing the 3D object in different ways as per the user's convenience.

  File3D.h:: Contains all the classes that we require for the three dimensional interface, and also the window that is seen upon 3D transformation into a 2D object. The functions associated with each class are also flagged herein.

  6-threeDmain.cpp:: Functions in this file are called when the user decides to draw 3D view of an object or import a file from his local database. The basic purpose of the functions in this file is to make a user select between drawing/importing a file.

  7-LineDrawingFor3Dto2D.cpp:: Contains all the functions that enable a user to create new nodes, join two nodes, delete nodes etc. while making a 3D diagram.

  8-InputFor3Dto2D.cpp:: The user is given two choices of either loading a labeled file, or an unlabeled one, in whic case he is supposed to Add Labels through getLabels(), and mark all the Solid Planes.

  9-2DviewWindow.cpp:: The basic UI for viewing the orthographic projections of the object in different ways as per the user's convenience.


