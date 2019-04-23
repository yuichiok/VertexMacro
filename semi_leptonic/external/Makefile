CXXFLAGS = $(shell root-config --cflags) -fPIC 
ROOTLIBS = $(shell root-config --libs)

FileSelector.so : FileSelector.o FileSelector.o
	g++ $(ROOTLIBS) -shared -o libFileSelector.so FileSelector.o FileSelectorDict.o 
FileSelector.o : src/FileSelector.cc FileSelectorDict.cc
	g++ $(CXXFLAGS) -c src/FileSelector.cc FileSelectorDict.cc 
FileSelectorDict.cc : include/FileSelector.hh include/LinkDef.h
	rootcint -f FileSelectorDict.cc -c include/FileSelector.hh include/LinkDef.h

clean :
	rm *.o *.so *.pcm FileSelectorDict.cc
