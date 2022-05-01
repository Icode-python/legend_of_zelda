build:
	gcc main.c map.c entities.c logic.c arrays/*.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play



