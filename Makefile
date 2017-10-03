EXE="a.out"
CXX=g++
CFLAGS=-Wall -Wextra -std=c99
CXXFLAGS=-Wall -Wextra
LFLAGS=-lfftw3
OBJ=main.o Bitmap.o DiffractiveStructure.o Lens.o Zernike.o ./bmp/EasyBMP.o

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

${EXE}: $(OBJ)
	$(CXX) -o $@ $^ $(LFLAGS)

.PHONY: clean distclean

clean:
	rm -f *.o ./bmp/*.o

distclean: clean
	rm -f ${EXE}
