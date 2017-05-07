
#include <allegro5/system.h>
#include <allegro5/haptic.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

/**
 * Grafika Komputerowa - LAB 1 - Andrzej Tracz
 */
class Lab01 {

public:

    Lab01() {
        srand(time(NULL));

        this->initAllegro();
    }

    ~Lab01() {
        al_destroy_display(this->window);
    }

    void run() {

        this->createDisplay();

        al_set_window_title(this->window, "Grafika Komputerowa - Lab 1 - Andrzej Tracz");

        this->drawCenteredRectangle(100, 200, al_color_html("FAFAFA"));
        this->drawCenteredCircle(200, al_color_html("FF00FF"));
        this->drawCenteredTriangle(240, al_color_html("FF44FF"));

        this->drawRandomPrimitives();

        this->drawCenteredRectangleFromLines(600, 600, al_color_html("FAFAFA"));

        this->drawLinesForAllScreen();

        al_flip_display();

        while (!al_key_down(&this->keyboard, ALLEGRO_KEY_ESCAPE)) {
            al_get_keyboard_state(&this->keyboard);
        }
    }

private:

    ALLEGRO_DISPLAY *window = NULL;
    ALLEGRO_KEYBOARD_STATE keyboard;

    int width;
    int height;

    void createDisplay() {
        this->width = 1000;
        this->height = 800;

        this->window = al_create_display(this->width, this->height);
    }

    int centerX() {
        return this->width / 2;
    }

    int centerY() {
        return this->height / 2;
    }

    void initAllegro() {
        al_init();
        al_init_primitives_addon();
        al_install_keyboard();
    }

    void drawRectangle(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, int think = 1) {

        al_draw_rectangle(x1, y1, x2, y2, color, think);
    }

    void drawCenteredRectangle(int x, int y, ALLEGRO_COLOR color, int thickness = 1) {

        int startX = this->centerX() - (x / 2);
        int startY = this->centerY() - (y / 2);

        int endX = this->centerX() + (x / 2);
        int endY = this->centerY() + (y / 2);

        this->drawRectangle(startX, startY, endX, endY, color, thickness);
    }

    void drawCenteredRectangleFromLines(int x, int y, ALLEGRO_COLOR color, int thickness = 1) {

        int startX = this->centerX() - (x / 2);
        int startY = this->centerY() - (y / 2);
        int endX = this->centerX() + (x / 2);
        int endY = this->centerY() + (y / 2);

        al_draw_line(startX, startY, endX, startY, color, thickness); // gora
        al_draw_line(startX, startY, startX, endY, color, thickness); // lewo
        al_draw_line(endX, startY, endX, endY, color, thickness); // prawo
        al_draw_line(startX, endY, endX, endY, color, thickness); // doł
    }

    void drawCircle(float cx, float cy, float r, ALLEGRO_COLOR color, int thickness = 1) {

        al_draw_circle(cx, cy, r, color, thickness);
    }

    void drawCenteredCircle(float r, ALLEGRO_COLOR color) {

        int x = this->centerX();
        int y = this->centerY();

        this->drawCircle(x, y, r, color);
    }

    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR color, float thickness = 1) {

        al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);
    }

    void drawCenteredTriangle(float a, ALLEGRO_COLOR color, int thickness = 1) {

        int x1 = this->centerX();
        int y1 = this->centerY() - a;

        int x2 = this->centerX() - a;
        int y2 = this->centerY() + a;

        int x3 = this->centerX() + a;
        int y3 = this->centerY() + a;

        this->drawTriangle(x1, y1, x2, y2, x3, y3, color, thickness);
    }

    void drawRandomCircle() {

        int cx = this->randomRange(0, this->width);
        int cy = this->randomRange(0, this->height);
        int r = this->randomRange(100, this->height / 2);


        this->drawCircle(cx, cy, r, this->getRandColor());
    }

    ALLEGRO_COLOR getRandColor() {
        return al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
    }

    void drawRandomRectangle() {

        this->drawRectangle(
                this->randomRange(10, 400),
                this->randomRange(10, 400),
                this->randomRange(400, 800),
                this->randomRange(400, 800),
                this->getRandColor()
        );
    }

    void drawRandomPrimitives() {

        while (!al_key_down(&this->keyboard, ALLEGRO_KEY_ESCAPE)) {
            this->drawRandomCircle();
            this->drawRandomRectangle();

            al_flip_display();
            al_rest(0.2);
            al_get_keyboard_state(&this->keyboard);
        }
    }

    int randomRange(int min, int max) {

        int random = rand() % max + min;

        return random;
    }

    void drawLinesForAllScreen() {

        for (int i = 0; i < this->width; i += 50) {
            rysujOdcinek(i, 0, i, this->height, al_color_html("FFFFFF"));
        }

        for (int j = 0; j < this->height; j += 50) {
            rysujOdcinek(0, j, this->width, j, al_color_html("FFFFFF"));
        }
    }

    void rysujOdcinek(int x0, int y0, int x1, int y1, ALLEGRO_COLOR color) {

        float dx = x1 - x0;
        float dy = y1 - y0;
        float m = dy / dx;
        float y = y0;

        for (int x = x0; x <= x1; x++) {

            al_put_pixel(x, int(y + 0.5), color);
            y += m;
        };
    }
};