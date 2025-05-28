#ifndef __PRINT__
#define __PRINT__

#include "estrutura.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void print_loja(tipo_loja *loja, resource adds, int option);

void print_menu(resource adds, game *ballz, int option, gun *cannon);

void print_pause(resource adds, int option);

void print_help(resource adds, game *ballz);

void print_ballz(gun *cannon, game *ballz, int mv, resource adds, int selec);

#endif