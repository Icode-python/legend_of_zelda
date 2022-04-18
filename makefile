compile:
	gcc main.c sprites.c entities.c player.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play