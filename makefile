compile:
	gcc main.c map.c entities.c logic.c arrays/world_map_blocking.c arrays/sprite_atlas.c arrays/entire_world_map.c arrays/tiles_sprites.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play


