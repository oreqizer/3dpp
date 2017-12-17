CFLAGS = -std=c++11 -lstdc++ -lGL -lGLEW -lSDL2

pogchamp: display.o shader.o
	gcc -o main main.cpp display.o shader.o $(CFLAGS)

clean:
	-rm main display.o shader.o

shader.o: src/shader.cpp
	gcc -c src/shader.cpp $(CFLAGS)

display.o: src/display.cpp
	gcc -c src/display.cpp $(CFLAGS)
