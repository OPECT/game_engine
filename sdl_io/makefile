CXX=g++
CFLAGS = -I../inc -g
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJ = sdl_wrapper.o ui_engine.o

sdl_io.o: $(OBJ) 
	 ld -r $(OBJ) -o $@ 

$(OBJ): %.o: %.cpp
	 $(CXX) -c $(CFLAGS) $< -o $@ $(LIBS)

