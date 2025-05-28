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

bool check_perfect(game *ballz)
{
    for (int i=1; i < LINHAS-1; i++)
        for (int j=1; j < COLUNAS-1; j++)
            if (ballz->board[i][j] > 0)
                return false;

    return true;
}


int set_ballz(gun *cannon, game *ballz, resource adds)
{
    int range;
    int pos;
    int num = aleat(3,5);
    bool moeda = false;

    if(ballz->i == 0)
    {
        ballz->round++;
        ballz->acel = 1;

        if(ballz->round != 1)
            ballz->perfect = check_perfect(ballz);

        cannon->atual += cannon->novas;

        if (cannon->atual > cannon->total)
        {
            cannon->bolas = realloc(cannon->bolas, sizeof(ball)*2*cannon->total);
            cannon->total += 2*cannon->total;
        }

        while (cannon->novas != 0)
        {
            cannon->bolas[cannon->atual-cannon->novas].center.x = cannon->ball.x; 
            cannon->novas--;
        }

        while (num != 0)
        {
            pos = aleat(1,7);

            if (ballz->board[1][pos] == 0)
            {
                range = aleat(1,4);

                if (range > 1)
                {
                    range = aleat(1,5);

                    if (range != 1)
                    {
                    ballz->board[1][pos] = ballz->round;
                    ballz->max[1][pos] = ballz->round;
                    }

                    else 
                    {
                    ballz->board[1][pos] = ballz->round*2;
                    ballz->max[1][pos] = ballz->round*2;
                    }
                    num--;
                }

                else if ((range == 1) && (ballz->round != 1))
                {
                    if (!moeda)
                    {
                        num--;
                        ballz->board[1][pos] = -2;
                        moeda = true;
                    }
                }
            }
        }

        num = 1;
        while (num != 0)
        {
            pos = aleat(1,7);
            if (ballz->board[1][pos] == 0)
            {
                if (ballz->round != 1)
                    ballz->board[1][pos] = -1;
                else 
                {
                    ballz->board[1][pos] = ballz->round;
                    ballz->max[1][pos] = ballz->round;
                }
                num--;
            }
        }

        if (ballz->perfect)
            al_play_sample(adds.msc.perfect, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
    }

    if (ballz->i < 50)
    {
        print_ballz(cannon, ballz, ballz->i, adds, 0);
        if (ballz->perfect)
            al_draw_scaled_bitmap(adds.img.perfect, 0, 0, 400, 400, 125-ballz->i, 175-ballz->i, 225+2*ballz->i, 275+2*ballz->i, 0);
        al_flip_display();

        ballz->i++;
        return 0;
    }

    else
    {
        ballz->perfect = false;
        ballz->i = 0;

        for (int i=LINHAS-2; i > 1; i--)
            for (int j=1; j < COLUNAS-1; j++)
            {
                if (ballz->board[i][j] == 0)
                    ballz->max[i][j] = 0;

                ballz->board[i][j] = ballz->board[i-1][j];
                ballz->max[i][j] = ballz->max[i-1][j];
            }

        for (int j=1; j < COLUNAS-1; j++)
            ballz->board[1][j] = 0;

        for (int i=1; i < COLUNAS-1; i++)
            if (ballz->board[9][i] > 0)
            {
                if (cannon->recorde < ballz->round)
                al_play_sample(adds.msc.record, cannon->volume*2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                else al_play_sample(adds.msc.end, cannon->volume*2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

                return 4;
            }

        return 1;
    }
}




int launch_ballz(gun *cannon, game *ballz, int i, resource adds, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event)
{
    vetor ini;
    vetor delta;
    vetor mov;

        ini.x = event.mouse.x;
        ini.y = event.mouse.y;

        while (event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            al_wait_for_event(queue,&event);
            if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                print_ballz(cannon, ballz, 0, adds, 1);

                if (event.mouse.y > ini.y)
                {
                delta.x = (ini.x-event.mouse.x)/8;
                delta.y = (ini.y-event.mouse.y)/8;

                for (int i=1; i <= 8; i++)
                    al_draw_filled_circle(cannon->ball.x+(delta.x*i), cannon->ball.y+(delta.y*i), 4 - i/2, al_map_rgb(255, 255, 255));

                al_wait_for_event(queue,&event); 
                }
                
                al_flip_display();
            }
        }

    if (ini.y < event.mouse.y)
    {
        delta.x = (ini.x-event.mouse.x);
        delta.y = (ini.y-event.mouse.y);

        float hipt = sqrt((delta.x*delta.x) + (delta.y*delta.y));

        mov.x = 5*(delta.x)/hipt;
        mov.y = 5*(delta.y)/hipt;

        for (int i = 0; i < cannon->atual; i++)
        {
            cannon->bolas[i].center.x = cannon->ball.x;
            cannon->bolas[i].center.y = cannon->ball.y;
            cannon->bolas[i].dslc.x = mov.x;
            cannon->bolas[i].dslc.y = mov.y;
        }

        cannon->ball.x = 0;
        ballz->acel = 1;
        ballz->frames = 0;

        return 2;
    } else return 1;

}



int move_ballz(gun *cannon, game *ballz, resource adds)
{
    int i;

    int pos_x;
    int pos_y;

    int x;
    int y;

    for (int j=0; j <= ballz->acel; j++)
    {

    i = 0;

        while ((i*5 <= ballz->frames) && (i < cannon->atual))
        {
            if (cannon->bolas[i].center.x + cannon->bolas[i].dslc.x < 50+RAIO)
                cannon->bolas[i].dslc.x = -1*(cannon->bolas[i].dslc.x);

            if (cannon->bolas[i].center.x + cannon->bolas[i].dslc.x > 400-RAIO)
                cannon->bolas[i].dslc.x = -1*(cannon->bolas[i].dslc.x);

            if (cannon->bolas[i].center.y + cannon->bolas[i].dslc.y < 50+RAIO)
                cannon->bolas[i].dslc.y = -1*(cannon->bolas[i].dslc.y);

            if (cannon->bolas[i].center.y + cannon->bolas[i].dslc.y > 500-RAIO)
            {
                cannon->bolas[i].center.y = 500-RAIO;

                cannon->bolas[i].dslc.y = 0;
                cannon->bolas[i].dslc.x = 0;

                if (cannon->ball.x == 0)
                    cannon->ball.x = cannon->bolas[i].center.x;
            }   

            if (cannon->bolas[i].dslc.x >= 0)
                x = 1;
            else x = -1;

            if (cannon->bolas[i].dslc.y >= 0)
                y = 1;
            else y = -1;   

            pos_x = (cannon->bolas[i].center.x + RAIO*x)/50;
            pos_y = (cannon->bolas[i].center.y + RAIO*y)/50;



            if ((ballz->board[pos_y][pos_x] > 0))   
            {
                cannon->bolas[i].dslc.x = -1*(cannon->bolas[i].dslc.x);
                cannon->bolas[i].dslc.y = -1*(cannon->bolas[i].dslc.y);
                    
                if (ballz->cheat)
                    ballz->board[pos_y][pos_x] = 0;
                else ballz->board[pos_y][pos_x]--;
            }  



            if (ballz->board[pos_y][pos_x+x] > 0)
                if (floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x + RAIO*x)/50) == pos_x+x)
                {
                    cannon->bolas[i].dslc.x = -1*(cannon->bolas[i].dslc.x);
                    if (ballz->cheat)
                        ballz->board[pos_y][pos_x+x] = 0;
                    else ballz->board[pos_y][pos_x+x]--;
                }
            
            if  (ballz->board[pos_y][pos_x+x] == -1)
                if (floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x + RAIO*x)/50) == pos_x+x)
                {
                    cannon->novas++;
                    ballz->board[pos_y][pos_x+x] = 0;
                    al_play_sample(adds.msc.extra, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }

            if  (ballz->board[pos_y][pos_x+x] == -2)
                if (floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x + RAIO*x)/50) == pos_x+x)
                {
                    cannon->moeda++;
                    ballz->board[pos_y][pos_x+x] = 0;
                    al_play_sample(adds.msc.coin, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }



            if (ballz->board[pos_y+y][pos_x] > 0)
                if (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y + RAIO*y)/50) == pos_y+y)
                {
                    cannon->bolas[i].dslc.y = -1*(cannon->bolas[i].dslc.y);
                    if (ballz->cheat)
                        ballz->board[pos_y+y][pos_x] = 0;
                    else ballz->board[pos_y+y][pos_x]--;
                }

            if (ballz->board[pos_y+y][pos_x] == -1)
                if (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y + RAIO*y)/50) == pos_y+y)
                {
                    cannon->novas++;
                    ballz->board[pos_y+y][pos_x] = 0;
                    al_play_sample(adds.msc.extra, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }

            if (ballz->board[pos_y+y][pos_x] == -2)
                if (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y + RAIO*y)/50) == pos_y+y)
                {
                    cannon->moeda++;
                    ballz->board[pos_y+y][pos_x] = 0;
                    al_play_sample(adds.msc.coin, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }



            if ((ballz->board[pos_y+y][pos_x+x] > 0))
                if ((floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x - sqrt(RAIO)*x)/50) == pos_x+x) && (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y - sqrt(RAIO)*y)/50) == pos_y+y))
                {
                    float hipot = sqrt((cannon->bolas[i].center.x - (pos_x*50))*(cannon->bolas[i].center.x - (pos_x*50)) + (cannon->bolas[i].center.y - (pos_y*50))*(cannon->bolas[i].center.y - (pos_y*50)));
                    cannon->bolas[i].dslc.x = 5*(cannon->bolas[i].center.x - (pos_x*50))/hipot;
                    cannon->bolas[i].dslc.y = 5*(cannon->bolas[i].center.y - (pos_y*50))/hipot;
                    
                    if (ballz->cheat)
                        ballz->board[pos_y+y][pos_x+x] = 0;
                    else ballz->board[pos_y+y][pos_x+x]--;
                }

            if ((ballz->board[pos_y+y][pos_x+x] ==  -1))
                if ((floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x + RAIO*x)/50) == pos_x+x) && (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y + RAIO*y)/50) == pos_y+y))
                {
                cannon->novas++; 
                ballz->board[pos_y+y][pos_x+x] = 0;
                al_play_sample(adds.msc.extra, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }

            if ((ballz->board[pos_y+y][pos_x+x] ==  -2))
                if ((floor((cannon->bolas[i].center.x + cannon->bolas[i].dslc.x + RAIO*x)/50) == pos_x+x) && (floor((cannon->bolas[i].center.y + cannon->bolas[i].dslc.y + RAIO*y)/50) == pos_y+y))
                {
                cannon->moeda++; 
                ballz->board[pos_y+y][pos_x+x] = 0;
                al_play_sample(adds.msc.coin, cannon->volume, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                }



            cannon->bolas[i].center.x += cannon->bolas[i].dslc.x;
            cannon->bolas[i].center.y += cannon->bolas[i].dslc.y;

            i++;
        }
    }

    for (int j=0; j < cannon->atual; j++)
        if (cannon->bolas[j].dslc.y != 0)
            return 2;

    return 0;
}


void end_play (gun *cannon, game *ballz, int mv, resource adds, int selec)
{
    print_ballz(cannon, ballz, 0, adds, selec);

    al_draw_filled_rectangle(0,0,450,650,al_map_rgba_f(0,0,0,0.75));

    al_draw_text(adds.txt.pixelg,al_map_rgb(255,0,0),225,105,ALLEGRO_ALIGN_CENTER,"Fim de Jogo");
    al_draw_textf(adds.txt.pixelg,al_map_rgb(255,255,255),225, 205, ALLEGRO_ALIGN_CENTER, "%d", ballz->round); 
    al_draw_text(adds.txt.pixelm,al_map_rgb(255,0,0),225,270,ALLEGRO_ALIGN_CENTER,"Pontos");
    al_draw_text(adds.txt.pixelp,al_map_rgb(255,255,255), 225, 450, ALLEGRO_ALIGN_CENTER, "Pressione qualquer tecla para jogar novamente");

    if (ballz->round > cannon->recorde)
    {
        al_draw_text(adds.txt.arialm,al_map_rgb(220,220,0),225,310,ALLEGRO_ALIGN_CENTER,"NOVO RECORDE!!");
        cannon->recorde = ballz->round;
    }

    return;
}