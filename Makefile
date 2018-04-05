CXX := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/autocad


SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CXXFLAGS += -std=c++11
CFLAGS := -g # -Wall
LIB := -lGL -lglui -lglut -lGLU
INC := -I include
INCPATH = `pkg-config --cflags --libs gtk+-2.0`

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CXX) $^ -o $(TARGET) $(LIB) $(INCPATH)"; $(CXX) $^ -o $(TARGET) $(LIB) $(INCPATH)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CXX) -c $(CXXFLAGS) $(CFLAGS) $(INC) -o $@ $< $(INCPATH)"; $(CXX) -c $(CXXFLAGS) $(CFLAGS) $(INC) -o $@ $< $(INCPATH)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CXX) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CXX) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean