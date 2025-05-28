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

void print_ballz(gun *cannon, game *ballz, int mv, resource adds, int selec)
{

    int k;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    for (int i=1; i < LINHAS-1; i++)
        for (int j=1; j < COLUNAS-1; j++)
            if (ballz->board[i][j] > 0)
            {
                k = ballz->board[i][j];
                al_draw_filled_rectangle(j*50, i*50+mv, (j+1)*50, (i+1)*50+mv, al_map_rgb(255-10*(k-1),255-20*(k-1),5*(k-1)));

                if (ballz->board[i][j] <= (ballz->max[i][j])/5)
                    al_draw_bitmap(adds.img.borda_e, j*50, i*50+mv,0);
                else if (ballz->board[i][j] <= (ballz->max[i][j])/2)
                    al_draw_bitmap(adds.img.borda_m, j*50, i*50+mv,0);
                else al_draw_bitmap(adds.img.borda_f, j*50, i*50+mv,0);
                al_draw_textf(adds.txt.arialp, al_map_rgb(0,0,0), (j*50)+25, (i*50)+20+mv, ALLEGRO_ALIGN_CENTER, "%d", ballz->board[i][j]);
            } 

            else if (ballz->board[i][j] == -1)
            {
                if (ballz->frames % 40 < 20)
                    al_draw_ellipse(j*50+25, i*50+mv+25, (ballz->frames % 20)+1, 20, al_map_rgb(0,200,0), 4);
                else al_draw_ellipse(j*50+25, i*50+mv+25, 20-(ballz->frames % 20), 20, al_map_rgb(0,200,0), 4);
                al_draw_filled_circle(j*50+25, i*50+mv+25, 10, al_map_rgb(0,200,0));
            } 

            else if (ballz->board[i][j] == -2)
            {
                if (ballz->frames % 40 < 20)
                    al_draw_ellipse(j*50+25, i*50+mv+25, (ballz->frames % 20)+1, 20, al_map_rgb(255,123,0), 3);
                else al_draw_ellipse(j*50+25, i*50+mv+25, 20 - (ballz->frames % 20), 20, al_map_rgb(255,123,0), 3);
            }

    if ((selec == 2) && (ballz->frames >= 360))
    {
        if (ballz->acel == 1)
            al_draw_filled_circle(375,75,20,al_map_rgb(25,25,25));
        else if (ballz-> acel == 2)
            al_draw_filled_circle(375,75,20,al_map_rgb(123,0,0));
        else al_draw_filled_circle(375,75,20,al_map_rgb(255,0,0));

        al_draw_bitmap(adds.img.fast, 355,55,0);
    }

    for (int i=0; i < cannon->atual; i++)
        al_draw_filled_circle(cannon->bolas[i].center.x, cannon->bolas[i].center.y, RAIO, al_map_rgb(cannon->red, cannon->green, cannon->blue));

    if (selec == 0)
    {
        al_draw_circle(cannon->ball.x, cannon->ball.y, RAIO, al_map_rgb(0,255,0), 2);

        for (int i=0; i < cannon->atual; i++)
            if (cannon->bolas[i].center.x != cannon->ball.x && cannon->bolas[i].center.y == cannon->ball.y)
                cannon->bolas[i].center.x = cannon->ball.x + ((cannon->bolas[i].center.x - cannon->ball.x)/2);
    }

    al_draw_bitmap(adds.img.borda, 0, 0, 0);
    if (selec == 0 || selec == 1)
        al_draw_textf(adds.txt.arialp, al_map_rgb(255,255,255), cannon->ball.x+(3*RAIO), cannon->ball.y-(3*RAIO), ALLEGRO_ALIGN_CENTER, "x%d", cannon->atual);

    al_draw_bitmap(adds.img.pause,5,5,0);

    al_draw_circle(325, 25, 20, al_map_rgb(255,123,0), 2);
    al_draw_text(adds.txt.pixelp, al_map_rgb(250,123,0), 350, 5, 0, "moedas");
    al_draw_textf(adds.txt.pixelm, al_map_rgb(255,255,255), 350, 20, 0, "%d", cannon->moeda);

    al_draw_textf(adds.txt.pixelg, al_map_rgb(0,0,0), 225, 5, ALLEGRO_ALIGN_CENTER, "%d", ballz->round);
    al_draw_text(adds.txt.pixelp, al_map_rgb(250,250,0), 110, 5, ALLEGRO_ALIGN_CENTER, "recorde");
    al_draw_textf(adds.txt.pixelm, al_map_rgb(0,0,0), 110, 20, ALLEGRO_ALIGN_CENTER, "%d", cannon->recorde);

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 555, ALLEGRO_ALIGN_CENTER, "Trabalho feito para a disciplina de prog2 ministrada por");
    if (!ballz->cheat)
        al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 575, ALLEGRO_ALIGN_CENTER, "David Menotti");
    else al_draw_text(adds.txt.arialp, al_map_rgb(240,0,0), 225, 575, ALLEGRO_ALIGN_CENTER, "David Menotti");
}

void print_loja(tipo_loja *loja, resource adds, int option)
{
    al_draw_filled_rectangle(75,25,375,515,al_map_rgba_f(0,0,0,0.75));

    al_draw_text(adds.txt.pixelgg,al_map_rgb(255,255,255), 225, 25, ALLEGRO_ALIGN_CENTER, "LOJINHA");

    al_draw_filled_circle(100, 50, 24, al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.rtrn, 85, 35, 0);

    if (option == 8)
    {
        al_draw_circle(100, 50, 24, al_map_rgb(255,255,255), 3);
        al_draw_text(adds.txt.pixelp,al_map_rgb(255,255,255), 124, 30, 0, "Voltar");
    }


    for (int i=0; i < 8; i++)
    {
        if (i == option)
        al_draw_filled_circle(150+fmod(floor(i/2),4)*100, 150+(i % 2)*150, 40, al_map_rgb(200,200,200));
        else al_draw_filled_circle(150+fmod(floor(i/2),4)*100, 150+(i % 2)*150, 40, al_map_rgb(0,0,0));

        al_draw_filled_circle(130+fmod(floor(i/2),4)*100, 150+(i % 2)*150, RAIO, al_map_rgb(loja->cores[i].red, loja->cores[i].green, loja->cores[i].blue));

        if (loja->cores[i].buy == 0)
        {
            al_draw_text(adds.txt.pixelp,al_map_rgb(loja->cores[i].red,loja->cores[i].green,loja->cores[i].blue), 150+fmod(floor(i/2),4)*100, 150+(i % 2)*150, ALLEGRO_ALIGN_CENTER, "Comprar");
            al_draw_textf(adds.txt.pixelp,al_map_rgb(loja->cores[i].red,loja->cores[i].green,loja->cores[i].blue), 175+fmod(floor(i/2),4)*100, 150+(i % 2)*150, ALLEGRO_ALIGN_CENTER, "%d", loja->cores[i].valor);
        } else
        {
            al_draw_text(adds.txt.pixelm,al_map_rgb(loja->cores[i].red,loja->cores[i].green,loja->cores[i].blue), 150+fmod(floor(i/2),4)*100, 150+(i % 2)*150, ALLEGRO_ALIGN_CENTER, "Obtido");
        }

        if (i == loja->use)
        {
            al_draw_circle(150+fmod(floor(i/2),4)*100, 150+(i % 2)*150, 40, al_map_rgb(0,123,0),6);
            al_draw_text(adds.txt.pixelp,al_map_rgb(0,123,0), 150+fmod(floor(i/2),4)*100, 90+(i % 2)*150, ALLEGRO_ALIGN_CENTER, "Em Uso");
        }

    }
}



void print_menu(resource adds, game *ballz, int option, gun *cannon)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(adds.txt.pixelgg,al_map_rgb(255,0,0), 225, 175, ALLEGRO_ALIGN_CENTER, "Ballz");

    if (ballz->i % 60 >= 30)
        al_draw_text(adds.txt.pixelp,al_map_rgb(255,255,255), 225-(ballz->i % 30)/3, 450-(ballz->i % 30)/3,ALLEGRO_ALIGN_CENTER, "Press any key to start");
    else al_draw_text(adds.txt.pixelp,al_map_rgb(255,255,255), 215+(ballz->i % 30)/3, 440+(ballz->i % 30)/3,ALLEGRO_ALIGN_CENTER, "Press any key to start");

    ballz->i++;

    al_draw_filled_circle(125,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.help, 105, 305, 0);

    if (cannon->volume == 0)
    al_draw_filled_circle(225,325,25,al_map_rgb(75,75,75));
    else al_draw_filled_circle(225,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.nota, 205, 305, 0);

    al_draw_filled_circle(325,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.loja, 305, 305, 0);

    if (option != 0)
        al_draw_circle((option*100)+25,325,25,al_map_rgb(255,255,255),2);

    switch (option)
    {
        case 1:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 125, 355, ALLEGRO_ALIGN_CENTER, "Ajuda");
            break;

        case 2:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 225, 355, ALLEGRO_ALIGN_CENTER, "Som");
            break;

        case 3:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 325, 355, ALLEGRO_ALIGN_CENTER, "Loja");
    }

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 555, ALLEGRO_ALIGN_CENTER, "Trabalho feito para a disciplina de prog2 ministrada por");
    if (!ballz->cheat)
        al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 575, ALLEGRO_ALIGN_CENTER, "David Menotti");
    else al_draw_text(adds.txt.arialp, al_map_rgb(240,0,0), 225, 575, ALLEGRO_ALIGN_CENTER, "David Menotti");

}

void print_pause(resource adds, int option)
{
    al_draw_filled_rectangle(0,0,450,550,al_map_rgba_f(0,0,0,0.75));
    al_draw_text(adds.txt.pixelg, al_map_rgb(250,250,0), 225, 225, ALLEGRO_ALIGN_CENTER, "PAUSE");

    al_draw_filled_circle(125,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.rtrn, 105, 305, 0);
    

    al_draw_filled_circle(225,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.replay, 205, 305, 0);


    al_draw_filled_circle(325,325,25,al_map_rgb(255,0,0));
    al_draw_bitmap(adds.img.menu, 305, 305, 0);

    if (option != 0)
        al_draw_circle((option*100)+25,325,25,al_map_rgb(255,255,255),2);

    switch (option)
    {
        case 1:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 125, 355, ALLEGRO_ALIGN_CENTER, "Continue");
            break;

        case 2:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 225, 355, ALLEGRO_ALIGN_CENTER, "Replay");
            break;

        case 3:
            al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 325, 355, ALLEGRO_ALIGN_CENTER, "Menu");
    }    

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 550, ALLEGRO_ALIGN_CENTER, "Trabalho feito para a disciplina de prog2 ministrada por");
}

void print_help(resource adds, game *ballz)
{
    al_draw_filled_rectangle(50,50,400,550,al_map_rgba_f(0,0,0,0.75));
    al_draw_rectangle(50,50,400,550,al_map_rgb(255,255,255),3);

    al_draw_text(adds.txt.pixelm, al_map_rgb(255,255,255), 225, 55, ALLEGRO_ALIGN_CENTER, "Como Jogar");

    al_draw_text(adds.txt.arialg, al_map_rgb(255,0,0), 225, 90, ALLEGRO_ALIGN_CENTER, "O Jogo");

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 140, ALLEGRO_ALIGN_CENTER, "Seu Objetivo é não deixar os");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 160, ALLEGRO_ALIGN_CENTER,"blocos chegarem na base;");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 180, ALLEGRO_ALIGN_CENTER, "Quanto mais rodadas você durar");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 200, ALLEGRO_ALIGN_CENTER, "Mais Pontos você faz!!");


    al_draw_text(adds.txt.arialg, al_map_rgb(255,0,0), 225, 220, ALLEGRO_ALIGN_CENTER, "Lançamento");

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 280, ALLEGRO_ALIGN_CENTER, "Clique em algum lugar da tela;");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 300, ALLEGRO_ALIGN_CENTER,"Mova o mouse para baixo;");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 320, ALLEGRO_ALIGN_CENTER, "Ao soltar o botão, a bola será arremessada;");

    al_draw_text(adds.txt.arialg, al_map_rgb(255,0,0), 225, 340, ALLEGRO_ALIGN_CENTER, "Colete Moedas!!");

    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 390, ALLEGRO_ALIGN_CENTER, "Você pode usa-las para trocar");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 410, ALLEGRO_ALIGN_CENTER, "a cor da sua bolinha");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 430, ALLEGRO_ALIGN_CENTER, "Isso não te deixará mais poderoso,");
    al_draw_text(adds.txt.arialp, al_map_rgb(255,255,255), 225, 450, ALLEGRO_ALIGN_CENTER, "mas adiciona pontos de estilo!");

    if (ballz->frames % 30 > 10)
        al_draw_text(adds.txt.pixelp, al_map_rgb(255,255,255), 225, 500, ALLEGRO_ALIGN_CENTER, "Press any key to return");

}