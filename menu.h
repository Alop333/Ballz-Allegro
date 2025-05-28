#ifndef __MENU__
#define __MENU__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void save_game(gun cannon);

void open_loja(tipo_loja *loja);

void save_loja(tipo_loja loja);

int circle_opt(ALLEGRO_EVENT event);

int opt_loja(ALLEGRO_EVENT event);

int selec_opt(ALLEGRO_EVENT event, int last_selec, int selec, gun *cannon, resource adds, game *ballz);

int buy_loja (ALLEGRO_EVENT event, tipo_loja *loja, gun *cannon);

#endif