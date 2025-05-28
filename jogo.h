#ifndef __JOGO__
#define __JOGO__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

bool check_perfect(game *ballz);

int set_ballz(gun *cannon, game *ballz, resource adds);

int launch_ballz(gun *cannon, game *ballz, int i, resource adds, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event);

int move_ballz(gun *cannon, game *ballz, resource adds);

void end_play (gun *cannon, game *ballz, int mv, resource adds, int selec);

#endif