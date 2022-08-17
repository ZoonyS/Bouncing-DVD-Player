all: compile run

compile:
	mkdir -p bin
	gcc -g -o bin/opengl-c -Iinclude `find src -name "*.c"` -lGL -lGLU -lglfw -ldl -lm -lX11 

run:
	./bin/opengl-c

clean:
	rm -rf bin
