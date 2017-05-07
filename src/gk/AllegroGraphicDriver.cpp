#include <allegro5/system.h>
#include <allegro5/haptic.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro_image.h"
#include <cmath>
#include <stdio.h>
#include <iostream>

#ifndef ALLEGRO_GRAPHIC_DRIVER

#define ALLEGRO_GRAPHIC_DRIVER

using namespace std;

class AllegroGraphicDriver {

public:

    AllegroGraphicDriver() {
        //srand(time(NULL));
        initAllegro();

        createDisplay();
    }

    ~AllegroGraphicDriver() {
        al_destroy_display(window);
    }

protected:

    ALLEGRO_DISPLAY *window = NULL;
    ALLEGRO_BITMAP *bitmap = NULL;

    ALLEGRO_KEYBOARD_STATE keyboard;

    int width;

    int height;

    void createDisplay() {
        width = 1000;
        height = 700;

        window = al_create_display(width, height);
    }

    void setWindowTitle(const char *title) {
        al_set_window_title(window, title);
    }

    void render() {
        al_flip_display();
    }

    void clearScreen() {
        al_clear_to_color(blackColor());
    }

    void wait(float s) {
        al_rest(s);
    }

    void waitForEscKey() {
        while (!al_key_down(&keyboard, ALLEGRO_KEY_ESCAPE)) {
            al_get_keyboard_state(&keyboard);
        }
    }

    bool isKeyPreset(int keyCode) {
        return al_key_down(&keyboard, keyCode);
    }

    void waitForKeypress()
    {
        ALLEGRO_EVENT_QUEUE *event_queue;
        ALLEGRO_EVENT event;

        event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        do
            al_wait_for_event(event_queue, &event);
        while (event.type != ALLEGRO_EVENT_KEY_DOWN);
        getKeyboardState();

        al_destroy_event_queue(event_queue);
    }

    ALLEGRO_KEYBOARD_STATE getKeyboardState() {
        al_get_keyboard_state(&keyboard);

        return keyboard;
    }

    int centerX() {
        return width / 2;
    }

    int centerY() {
        return height / 2;
    }

    void initAllegro() {
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();
    }

    void drawRectangle(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, int think = 1) {

        al_draw_rectangle(x1, y1, x2, y2, color, think);
    }

    void drawCenteredRectangleFromLines(int x, int y, ALLEGRO_COLOR color, int thickness = 1) {

        int startX = centerX() - (x / 2);
        int startY = centerY() - (y / 2);
        int endX = centerX() + (x / 2);
        int endY = centerY() + (y / 2);

        al_draw_line(startX, startY, endX, startY, color, thickness); // gora
        al_draw_line(startX, startY, startX, endY, color, thickness); // lewo
        al_draw_line(endX, startY, endX, endY, color, thickness); // prawo
        al_draw_line(startX, endY, endX, endY, color, thickness); // doł
    }

    void drawLine(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness = 1) {
        al_draw_line(x1, y1, x2, y2, color, thickness);
    }

    void loadImage(const char *path) {
        ALLEGRO_BITMAP *image = NULL;

        image = al_load_bitmap(path);

        al_draw_bitmap(image, 200, 200, 0);

        al_flip_display();
        al_rest(2);
    }

    ALLEGRO_COLOR getRandColor() {
        return al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
    }

    ALLEGRO_COLOR whiteColor() {
        return al_map_rgb(255, 255, 255);
    }

    ALLEGRO_COLOR greenColor() {
        return al_map_rgb(0, 255, 0);
    }

    ALLEGRO_COLOR blueColor() {
        return al_map_rgb(0, 0, 255);
    }

    ALLEGRO_COLOR redColor() {
        return al_map_rgb(255, 0, 0);
    }

    ALLEGRO_COLOR blackColor() {
        return al_map_rgb(0, 0, 0);
    }

    int randomRange(int min, int max) {
        int random = rand() % max + min;

        return random;
    }

    void putPixel(float x, float y, ALLEGRO_COLOR color) {
        al_put_pixel(x, y, color);
    }

    ALLEGRO_COLOR getPointColor(float x, float y) {
        bitmap = al_get_target_bitmap();

        return al_get_pixel(bitmap, x, y);
    }

    void drawCircle(int r) {

        cout.precision(5);
        cout.setf(ios::fixed);

        int x = centerX();
        int y = centerY();

        float xi[1000];
        float yi[1000];

        float i = 0;
        int j = 0;

        for (;;) {

            if (i > (M_PI_2)) {
                break;
            }

            i = i + (float) 1 / r;

            xi[j] = r * (cos(i));
            yi[j] = r * (sin(i));

            j++;
        }

        for (int k = 0; k <= j; k++) {
            putPixel(x + xi[k], y + yi[k], whiteColor());
        }

        for (int k = 0; k <= j; k++) {
            putPixel(x + xi[k], y - yi[k], whiteColor());
        }

        for (int k = 0; k <= j; k++) {
            putPixel(x - xi[k], y - yi[k], whiteColor());
        }

        for (int k = 0; k <= j; k++) {
            putPixel(x - xi[k], y + yi[k], whiteColor());
        }

        fillAround(x + 2, y - 1, whiteColor());
    }

    bool isSameColors(ALLEGRO_COLOR c1, ALLEGRO_COLOR c2) {
        return c1.r == c2.r
               && c1.g == c2.g
               && c1.b == c2.b
               && c1.a == c2.a;
    }

    void fillAround(int x, int y, ALLEGRO_COLOR color) {

        int top = y - 1;
        int right = x + 1;
        int bottom = y + 1;
        int left = x - 1;


        if (!isSameColors(getPointColor(x, y), color)) {

            putPixel(x, y, color);
            fillAround(right, y, color);
            fillAround(x, top, color);
            fillAround(x, bottom, color);
            fillAround(left, y, color);
        }

    }
};

#endif //ALLEGRO_GRAPHIC_DRIVER