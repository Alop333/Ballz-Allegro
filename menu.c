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

void save_game(gun cannon)
{
    FILE *arq;

    arq = fopen(SAVE, "w");

    fprintf (arq, "%d\n%d\n%d\n%d\n%d\n%f\n", cannon.moeda, cannon.recorde, cannon.red, cannon.green, cannon.blue, cannon.volume);

    fclose(arq);

    return;
}



void open_loja(tipo_loja *loja)
{
    FILE *arq;
    char line[26];
    char* tok;

    arq = fopen (SAVE, "r");
    fgets(line, 25, arq);

    for (int i=0; i < 8; i++)
    {
        tok = strtok(line," ");
            loja->cores[i].red = atoi(tok);
        tok = strtok(NULL," ");
            loja->cores[i].green = atoi(tok);
        tok = strtok(NULL," ");
            loja->cores[i].blue = atoi(tok);
        tok = strtok(NULL," ");
            loja->cores[i].buy = atoi(tok);
        tok = strtok(NULL," ");
            loja->cores[i].valor = atoi(tok);

        fgets(line, 25, arq);
    }

    loja->use = atoi(line);

    fclose(arq);

    return;
}



void save_loja(tipo_loja loja)
{
    FILE *arq;

    arq = fopen(LOJA_TXT, "w");

    for (int i=0; i < 8; i++)
        fprintf (arq, "%d %d %d %d %d\n", loja.cores[i].red, loja.cores[i].green, loja.cores[i].blue, loja.cores[i].buy, loja.cores[i].valor);

    fprintf(arq, "%d", loja.use);

    fclose(arq);

    return;
}



int circle_opt(ALLEGRO_EVENT event)
{
    if ((125-event.mouse.x)*(125-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
        return 1;

    else if ((225-event.mouse.x)*(225-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
        return 2;

    else if ((325-event.mouse.x)*(325-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
        return 3;

    else return 0;
}



int opt_loja(ALLEGRO_EVENT event)
{
    if ((150-event.mouse.x)*(150-event.mouse.x) + (150-event.mouse.y)*(150-event.mouse.y) <= 1600)
        return 0;

    else if ((150-event.mouse.x)*(150-event.mouse.x) + (300-event.mouse.y)*(300-event.mouse.y) <= 1600)
        return 1;

    else if ((250-event.mouse.x)*(250-event.mouse.x) + (150-event.mouse.y)*(150-event.mouse.y) <= 1600)
        return 2;

    else if ((250-event.mouse.x)*(250-event.mouse.x) + (300-event.mouse.y)*(300-event.mouse.y) <= 1600)
        return 3;

    else if ((350-event.mouse.x)*(350-event.mouse.x) + (150-event.mouse.y)*(150-event.mouse.y) <= 1600)
        return 4;

    else if ((350-event.mouse.x)*(350-event.mouse.x) + (300-event.mouse.y)*(300-event.mouse.y) <= 1600)
        return 5;

    else if ((450-event.mouse.x)*(450-event.mouse.x) + (150-event.mouse.y)*(150-event.mouse.y) <= 1600)
        return 6;

    else if ((450-event.mouse.x)*(450-event.mouse.x) + (300-event.mouse.y)*(300-event.mouse.y) <= 1600)
        return 7;
    
    else if ((100-event.mouse.x)*(100-event.mouse.x) + (50-event.mouse.y)*(50-event.mouse.y) <= 576)
        return 8;

    else return 9;

}



int selec_opt(ALLEGRO_EVENT event, int last_selec, int selec, gun *cannon, resource adds, game *ballz)
{
    if (selec == 5)
    {
        if ((125-event.mouse.x)*(125-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
            return last_selec;

        else if ((225-event.mouse.x)*(225-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
            return 3;

        else if ((325-event.mouse.x)*(325-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
            return 6;
    }

    if (selec == 6)
    {
        if ((125-event.mouse.x)*(125-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
            return 7;

        else if ((225-event.mouse.x)*(225-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
        {
            if (cannon->volume == 0.5)
            {
                al_stop_samples();
                cannon->volume = 0;
            }
            else 
            {
                cannon->volume = 0.5;
                if (ballz->cheat)
                al_play_sample(adds.msc.cheat, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
                else al_play_sample(adds.msc.background, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
            }  
            return 6;
        }

        else if ((325-event.mouse.x)*(325-event.mouse.x) + (325-event.mouse.y)*(325-event.mouse.y) <= 625)
            return 8;
    }

    return selec;
}



int buy_loja (ALLEGRO_EVENT event, tipo_loja *loja, gun *cannon)
{
    for (int i=0; i < 8; i++)
        if ((150+fmod(floor(i/2),4)*100-event.mouse.x)*(150+fmod(floor(i/2),4)*100-event.mouse.x) + (150+(i % 2)*150-event.mouse.y)*(150+(i % 2)*150-event.mouse.y) <= 1600)
        {
            if(loja->cores[i].buy == 0)
                if (cannon->moeda >= loja->cores[i].valor)
                {
                    cannon->moeda -= loja->cores[i].valor;
                    loja->cores[i].buy = 1;
                }

            if(loja->cores[i].buy == 1)
            {
                cannon->red = loja->cores[i].red;
                cannon->green = loja->cores[i].green;
                cannon->blue = loja->cores[i].blue;
                loja->use = i;
                return 8;
            }
        }

    else if ((100-event.mouse.x)*(100-event.mouse.x) + (50-event.mouse.y)*(50-event.mouse.y) <= 576)
        return 5;

    return 8;
}