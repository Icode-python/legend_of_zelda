build:
	gcc main.c map.c entities.c logic.c enemies.c weapon.c arrays/*.c -o play -I include -lGL -lglut -lm  -lGLU -lGLEW
	./play



