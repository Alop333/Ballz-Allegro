#include "def.h"
#include "estrutura.h"
#include "jogo.h"
#include "menu.h"
#include "print.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int aleat(int n,int m)
{
    return n + rand() % (m-n+1);
}

gun fill_cannon()
{
    gun cannon;

    FILE *arq;
    char line[26];

    arq = fopen (SAVE, "r");

    fgets(line, 25, arq);
        cannon.moeda = atoi(line);
    fgets(line, 25, arq);
        cannon.recorde = atoi(line);

    fgets(line,25,arq);
        cannon.red = atoi(line);
    fgets(line,25,arq);
        cannon.green = atoi(line);
    fgets(line,25,arq);
        cannon.blue = atoi(line);
    fgets(line,25,arq);
        cannon.volume = atof(line);

    fclose(arq);

    cannon.ball.x = 225;
    cannon.ball.y = 500-RAIO;
    cannon.total = SIZE;
    cannon.atual = 1;
    cannon.novas = 0;

    cannon.bolas = malloc (sizeof(ball)*SIZE);

    for (int cont=0; cont < cannon.total; cont++)
    {
        cannon.bolas[cont].center.x = cannon.ball.x;
        cannon.bolas[cont].center.y = cannon.ball.y;
        cannon.bolas[cont].dslc.x = 0;
        cannon.bolas[cont].dslc.y = 0;
    }

    return cannon;
}

resource fill_adds()
{
    resource adds;

    adds.img.borda = al_load_bitmap(BORDA);
    adds.img.fast = al_load_bitmap(ACEL);
    adds.img.rtrn = al_load_bitmap(RETURN);
    adds.img.replay = al_load_bitmap(REPLAY);
    adds.img.menu = al_load_bitmap(MENU);
    adds.img.borda_f = al_load_bitmap(MARGEM_1);
    adds.img.borda_m = al_load_bitmap(MARGEM_2);
    adds.img.borda_e = al_load_bitmap(MARGEM_3);
    adds.img.pause = al_load_bitmap(PAUSE);
    adds.img.perfect = al_load_bitmap(PERFECT_IMG);
    adds.img.nota = al_load_bitmap(NOTA);
    adds.img.loja = al_load_bitmap(LOJA);
    adds.img.help = al_load_bitmap(AJUDA);

    adds.txt.arialp = al_load_font(ARIAL,15,0);
    adds.txt.arialm = al_load_font(ARIAL,30,0);
    adds.txt.arialg = al_load_font(ARIAL,45,0);
    adds.txt.pixelp = al_load_font(PIXEL,10,0);
    adds.txt.pixelm = al_load_font(PIXEL,25,0);
    adds.txt.pixelg = al_load_font(PIXEL,40,0);
    adds.txt.pixelgg = al_load_font(PIXEL,75,0);

    adds.msc.background = al_load_sample(BACKGROUND);
    adds.msc.end = al_load_sample(END);
    adds.msc.extra = al_load_sample(EXTRA);
    adds.msc.coin = al_load_sample(COIN);
    adds.msc.cheat = al_load_sample(CHEAT);
    adds.msc.perfect = al_load_sample(PERFECT);
    adds.msc.record = al_load_sample(RECORDE);

    al_reserve_samples(7);

    return adds;
}

game fill_ballz()
{
    game ballz;

    for (int i=0; i < LINHAS; i++)
        for (int j=0; j < COLUNAS; j++)
        {
            ballz.board[i][j] = 0;
            ballz.max[i][j] = 0;
        }

    ballz.round = 0;
    ballz.acel = 1;
    ballz.frames = 0;
    ballz.i = 0;
    ballz.cheat = false;
    ballz.perfect = false;

    return ballz;
}

void destroy_adds(resource adds)
{
    al_destroy_font(adds.txt.arialp);
    al_destroy_font(adds.txt.arialm);
    al_destroy_font(adds.txt.arialg);
    al_destroy_font(adds.txt.pixelp);
    al_destroy_font(adds.txt.pixelm);
    al_destroy_font(adds.txt.pixelg);
    al_destroy_font(adds.txt.pixelgg);

    al_destroy_bitmap(adds.img.borda);
    al_destroy_bitmap(adds.img.fast);
    al_destroy_bitmap(adds.img.menu);
    al_destroy_bitmap(adds.img.replay);
    al_destroy_bitmap(adds.img.rtrn);
    al_destroy_bitmap(adds.img.borda_f);
    al_destroy_bitmap(adds.img.borda_m);
    al_destroy_bitmap(adds.img.borda_e);
    al_destroy_bitmap(adds.img.pause);
    al_destroy_bitmap(adds.img.perfect);
    al_destroy_bitmap(adds.img.nota);
    al_destroy_bitmap(adds.img.loja);
    al_destroy_bitmap(adds.img.help);

    al_destroy_sample(adds.msc.background);
    al_destroy_sample(adds.msc.end);
    al_destroy_sample(adds.msc.extra);
    al_destroy_sample(adds.msc.coin);
    al_destroy_sample(adds.msc.cheat);
    al_destroy_sample(adds.msc.perfect);
    al_destroy_sample(adds.msc.record);

    return;
}