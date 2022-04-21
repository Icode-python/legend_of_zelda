compile:
	gcc main.c map.c entities.c sprite_atlas.c logic.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play