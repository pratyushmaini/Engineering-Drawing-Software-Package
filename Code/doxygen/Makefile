CXX = g++
CXXFLAGS += -std=c++14
INCPATH = `pkg-config --cflags --libs gtk+-2.0`
LIBS =   -framework OpenGl -framework GLUT -framework GLUI 
TARGET = autocad

all: 1-main.o 2-twoDmain.o 3-LineDrawing.o 4-InputFor2D.o 5-3DviewWindow.o 6-threeDmain.o 7-LineDrawingFor3Dto2D.o 8-InputFor3Dto2D.o 9-2DviewWindow.o 10-display_main.o
	$(CXX) -o $(TARGET) $(CXXFLAGS) 1-main.o 2-twoDmain.o 3-LineDrawing.o 4-InputFor2D.o 5-3DviewWindow.o 6-threeDmain.o 7-LineDrawingFor3Dto2D.o 8-InputFor3Dto2D.o 9-2DviewWindow.o 10-display_main.o  $(LIBS) $(INCPATH)

1-main.o: 1-main.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 1-main.cpp $(LIBS) $(INCPATH)
2-twoDmain.o: 2-twoDmain.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 2-twoDmain.cpp $(LIBS) $(INCPATH)
3-LineDrawing.o: 3-LineDrawing.cpp  File2D_3D.h
	$(CXX) -c $(CX`XFLAGS) 3-LineDrawing.cpp $(LIBS) $(INCPATH)
4-InputFor2D.o: 4-InputFor2D.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 4-InputFor2D.cpp $(LIBS) $(INCPATH)
5-3DviewWindow.o: 5-3DviewWindow.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 5-3DviewWindow.cpp $(LIBS) $(INCPATH)
6-threeDmain.o: 6-threeDmain.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 6-threeDmain.cpp $(LIBS) $(INCPATH)
7-LineDrawingFor3Dto2D.o: 7-LineDrawingFor3Dto2D.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 7-LineDrawingFor3Dto2D.cpp $(LIBS) $(INCPATH)
8-InputFor3Dto2D.o: 8-InputFor3Dto2D.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 8-InputFor3Dto2D.cpp $(LIBS) $(INCPATH)
9-2DviewWindow.o: 9-2DviewWindow.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 9-2DviewWindow.cpp $(LIBS) $(INCPATH)
10-display_main.o: 10-display_main.cpp  File2D_3D.h
	$(CXX) -c $(CXXFLAGS) 10-display_main.cpp $(LIBS) $(INCPATH)

.PHONY: clean

clean: 
	rm -f *.o $(TARGET)