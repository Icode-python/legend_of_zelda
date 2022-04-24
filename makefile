compile:
	gcc main.c map.c entities.c sprite_atlas.c logic.c world_map.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play


