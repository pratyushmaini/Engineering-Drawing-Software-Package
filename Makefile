CXX=g++
LFLAGS        = -m64
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtGui
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB
OBJECTS       = main.o
TARGET        = draw

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS) $(INCPATH)

$(TARGET):  $(OBJECTS)  
	$(CXX) $(LFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean: 
	rm -f *.o $(TARGET)