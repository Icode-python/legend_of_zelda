compile:
	gcc main.c sprites.c entities.c sprite_atlas.c math.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play