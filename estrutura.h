#ifndef __ESTRUTURA__
#define __ESTRUTURA__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



typedef struct{
    float x;
    float y;
} vetor;

typedef struct {
    vetor center;
    vetor dslc;
} ball;

typedef struct {
    vetor ball;
    int total;
    int novas;
    int atual;

    int moeda;
    int recorde;
    int red;
    int green;
    int blue;
    double volume;

    ball *bolas;
} gun;

typedef struct {
    int board[LINHAS][COLUNAS];
    int max[LINHAS][COLUNAS];
    int round;
    int frames;
    int acel;
    int i;
    bool cheat;
    bool perfect;
} game;

typedef struct {
    ALLEGRO_SAMPLE *background;
    ALLEGRO_SAMPLE *end;
    ALLEGRO_SAMPLE *extra;
    ALLEGRO_SAMPLE *coin;
    ALLEGRO_SAMPLE *cheat;
    ALLEGRO_SAMPLE *perfect;
    ALLEGRO_SAMPLE *record;
} songs;

typedef struct {
    ALLEGRO_BITMAP *borda;
    ALLEGRO_BITMAP *fast;
    ALLEGRO_BITMAP *replay;
    ALLEGRO_BITMAP *rtrn;
    ALLEGRO_BITMAP *menu;
    ALLEGRO_BITMAP *borda_f;
    ALLEGRO_BITMAP *borda_m;
    ALLEGRO_BITMAP *borda_e;
    ALLEGRO_BITMAP *pause;
    ALLEGRO_BITMAP *nota;
    ALLEGRO_BITMAP *perfect;
    ALLEGRO_BITMAP *loja;
    ALLEGRO_BITMAP *help;
} png;

typedef struct {
    ALLEGRO_FONT *arialp;
    ALLEGRO_FONT *arialm;
    ALLEGRO_FONT *arialg;
    ALLEGRO_FONT *pixelp;
    ALLEGRO_FONT *pixelm;
    ALLEGRO_FONT *pixelg;
    ALLEGRO_FONT *pixelgg;
} fonts;

typedef struct {
    png img;
    fonts txt;
    songs msc;
} resource;

typedef struct {
    int red;
    int green;
    int blue;

    int valor;
    int buy;
} item;

typedef struct {
    item cores[8];
    int use;
} tipo_loja;

int aleat(int n,int m);

gun fill_cannon();

resource fill_adds();

game fill_ballz();

void destroy_adds(resource adds);

#endif