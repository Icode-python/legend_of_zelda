build:
	mkdir build
	gcc main.c map.c entities.c logic.c arrays/*.c -o build/play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./build/play



