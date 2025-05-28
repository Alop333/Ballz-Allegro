#include "def.h"
#include "estrutura.h"
#include "print.h"
#include "jogo.h"
#include "menu.h"

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

int main ()
{
    srand(time(NULL));
    gun cannon;
    game ballz;
    resource adds;
    tipo_loja loja;
    int option = 0;
    int last_selec = 0;
    int selec = 6;
    bool redraw = true;

    cannon = fill_cannon();
    ballz = fill_ballz();

    al_init();

    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_mouse();
    al_init_primitives_addon();

    adds = fill_adds();

    al_play_sample(adds.msc.background, cannon.volume, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(450, 600);
    ALLEGRO_EVENT event;

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    print_ballz(&cannon, &ballz, 0, adds, selec);
    al_flip_display();

    al_start_timer(timer);


    while (1)
    {

        al_wait_for_event(queue,&event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            ballz.frames++;
        }

        if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
            if ((event.mouse.x >= 180) && (event.mouse.x <= 290) && (event.mouse.y >= 575))
            {
                ballz.cheat = true;
                al_stop_samples();
                al_play_sample(adds.msc.cheat, cannon.volume, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);
            }

        switch (selec)
        {
            case 0:

                if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
                    if ((25-event.mouse.x)*(25-event.mouse.x) + (25-event.mouse.y)*(25-event.mouse.y) <= 400)
                    {
                        last_selec = selec;
                        selec = 5;
                    } 

                if (redraw)
                {
                    selec = set_ballz(&cannon, &ballz, adds);
                }
                break;

            case 1:
                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    selec = launch_ballz(&cannon, &ballz, 0, adds, queue, event);

                if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
                    if ((25-event.mouse.x)*(25-event.mouse.x) + (25-event.mouse.y)*(25-event.mouse.y) <= 400)
                    {
                        last_selec = selec;
                        selec = 5;
                    } 

                if (redraw)
                {
                    print_ballz(&cannon, &ballz, 0, adds, selec);
                    al_flip_display();
                }
                break;

            case 2:
                if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) && (ballz.frames >= 360))
                {
                    if ((375-event.mouse.x)*(375-event.mouse.x) + (75-event.mouse.y)*(75-event.mouse.y) <= 400)
                    {
                        if (ballz.acel == 1)
                            ballz.acel = 2;
                        if ((ballz.acel == 2) && (ballz.frames >= 720))
                            ballz.acel = 5;
                    }
                }

                if ((event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN))
                    if ((25-event.mouse.x)*(25-event.mouse.x) + (25-event.mouse.y)*(25-event.mouse.y) <= 400)
                    {
                        last_selec = selec;
                        selec = 5;
                    } 

                if (redraw)
                {
                    print_ballz(&cannon, &ballz, 0, adds, selec);
                    al_flip_display();
                    selec = move_ballz(&cannon, &ballz, adds);
                }
                break;

            case 3:
                free(cannon.bolas);

                ballz = fill_ballz();
                cannon = fill_cannon();
                
                selec = 0;
                break;

            case 4:
                if (event.type == ALLEGRO_EVENT_KEY_DOWN)
                    selec = 3;

                if (redraw)
                {
                    end_play(&cannon, &ballz, 0, adds, selec);
                    al_flip_display();
                    save_game(cannon);
                }
                break;
            
            case 5:
                if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
                    option = circle_opt(event);

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    selec = selec_opt(event, last_selec, selec, &cannon, adds, &ballz);

                if (redraw)
                {
                    print_ballz(&cannon, &ballz, ballz.i, adds, selec);
                    print_pause(adds, option);
                    al_flip_display();
                }
                break;
            
            case 6:

                if (event.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    selec = last_selec;
                    ballz.i = 0;
                }

                if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
                    option = circle_opt(event);

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    selec = selec_opt(event, last_selec, selec, &cannon, adds, &ballz);

                if (redraw)
                {
                    print_menu(adds, &ballz, option, &cannon);
                    al_flip_display();
                }

                save_game(cannon);

                if (selec == 8)
                    open_loja(&loja);

                break;

            case 7:
                if (event.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    selec = 6;
                    ballz.i = 0;
                }

                if (redraw)
                {
                    print_menu(adds, &ballz, option, &cannon);
                    print_help(adds, &ballz);
                    al_flip_display();
                }

                break;

            case 8:
                if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
                    option = opt_loja(event);

                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                    selec = buy_loja(event, &loja, &cannon);

                if (redraw)
                {
                    print_menu(adds, &ballz, option, &cannon);
                    print_loja(&loja, adds, option);
                    al_flip_display();
                }

                if (selec != 8)
                    save_loja(loja);

                break;

            default:
                break;
        }
        redraw = false;
    }

    free(cannon.bolas);
    destroy_adds(adds);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}