
#ifndef ALLEGRO_HELLO_WORLD_APPLICATION_H
#define ALLEGRO_HELLO_WORLD_APPLICATION_H

#include <allegro5/system.h>
#include <allegro5/haptic.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

class Application {

public:

    Application() {
        this->initAllegro();
    }

    ~Application() {
        al_destroy_display(this->window);
    }

    void run() {
        this->window = al_create_display(1000, 800);
        al_set_window_title(this->window, "Allegro5 - Application");


        while(!al_key_down(&this->keyboard, ALLEGRO_KEY_ESCAPE))
        {
            al_get_keyboard_state(&this->keyboard);

            al_draw_filled_circle(500, 400, this->radius, al_color_html("F45533"));
            al_flip_display();

            al_clear_to_color(al_color_html("000000"));

            if (this->shouldBeBigger) {
                this->radius++;

                if (this->radius > 50) {
                    this->shouldBeBigger = false;
                }

            } else {
                this->radius--;

                if (this->radius < 0) {
                    this->shouldBeBigger = true;
                }
            }
        }

    }

    ALLEGRO_DISPLAY * getWindow() {

        return this->window;
    }

private:

    int radius = 0;
    bool shouldBeBigger = true;

    ALLEGRO_DISPLAY * window = NULL;
    ALLEGRO_KEYBOARD_STATE keyboard;

    void initAllegro() {
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();
    }
};

#endif
