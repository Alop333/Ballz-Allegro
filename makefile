CFLAGS = -Wall -g -lm
ALLEGRO =  -lallegro -lallegro_font -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_audio -lallegro_acodec -lallegro_image

all: ballz


ballz: ballz.o def.o estrutura.o jogo.o menu.o print.o
	gcc *.o $(CFLAGS) $(ALLEGRO) -o ballz

ballz.o: ballz.c
	gcc -c ballz.c $(CFLAGS) $(ALLEGRO)

def.o: def.c def.h
	gcc -c def.c $(CFLAGS) $(ALLEGRO)

estrutura.o: estrutura.c estrutura.h
	gcc -c estrutura.c $(CFLAGS) $(ALLEGRO)

jogo.o: jogo.c jogo.h
	gcc -c jogo.c $(CFLAGS) $(ALLEGRO)

menu.o: menu.c menu.h
	gcc -c menu.c $(CFLAGS) $(ALLEGRO)

print.o: print.c print.h
	gcc -c print.c $(CFLAGS) $(ALLEGRO)



clean:
	-rm -f *.o

purge: clean
	-rm -f ./ballz