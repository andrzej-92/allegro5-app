#include "AllegroGraphicDriver.cpp"

/**
 * Rysuje Kota i pozwala na jego transforacje
 *
 * W lewo: Q
 * W prawo E
 *
 * Zoom -: A
 * Zoom +: B
 *
 * Obrót w lewo: Z
 * Obrót w prawo: C
 *
 * Reset: X
 *
 * Wyjście: ESC
 */
class Lab5 : public AllegroGraphicDriver {

public:

    void run() {
        bool spoken = false;
        setInitialState();

        while (true) {
            spoken = !spoken;
            clearScreen();

            drawAwesomeCat(centerX(), centerY(), spoken);
            render();
            waitForKeypress();

            if (isKeyPreset(ALLEGRO_KEY_Q)) {
                offset -= 10;
            }

            if (isKeyPreset(ALLEGRO_KEY_E)) {
                offset += 10;
            }

            if (isKeyPreset(ALLEGRO_KEY_A)) {
                scale -= .1;
            }

            if (isKeyPreset(ALLEGRO_KEY_D)) {
                scale += .1;
            }

            if (isKeyPreset(ALLEGRO_KEY_Z)) {
                decreaseRotate();
            }

            if (isKeyPreset(ALLEGRO_KEY_C)) {
                increaseRotate();
            }

            if (isKeyPreset(ALLEGRO_KEY_X)) {
                setInitialState();
            }

            if (isKeyPreset(ALLEGRO_KEY_ESCAPE)) {
                break;
            }
        }
    }

private:

    float offset;
    float scale;
    float rotate;

    float sinA;
    float cosA;

    void drawAwesomeCat(float x, float y, bool speaking);

    void setInitialState() {
        offset = 0;
        scale = 1;
        rotate = 0;
        calcRotate();
    }

    void calcRotate() {
        sinA = sin(rotate);
        cosA = cos(rotate);
    }

    void increaseRotate() {
        rotate += M_1_PIl;
        calcRotate();
    }

    void decreaseRotate() {
        rotate -= M_1_PIl;
        calcRotate();
    }

    float calcRotateX(float xo, float yo, float x, float y) {
        return xo + (x - xo) * cosA - (y - yo) * sinA;
    }

    float calcRotateY(float xo, float yo, float x, float y) {

        return yo + (x - xo) * sinA + (y - yo) * cosA;
    }

};

void Lab5::drawAwesomeCat(float x, float y, bool speaking) {

    x = x + offset;

    float eyeXDistance = 80 * scale;
    float eyeYDistance = 100 * scale;
    float eyeSize = 25 * scale;


    // LEFT EYE
    drawRectangle(
            calcRotateX(x, y, x - eyeXDistance - eyeSize, y - eyeYDistance - eyeSize),
            calcRotateY(x, y, x - eyeXDistance - eyeSize, y - eyeYDistance - eyeSize),
            calcRotateX(x, y, x - eyeXDistance + eyeSize, y - eyeYDistance + eyeSize),
            calcRotateY(x, y, x - eyeXDistance + eyeSize, y - eyeYDistance + eyeSize),
            whiteColor()
    );

    drawRectangle(
            calcRotateX(x, y, x - eyeXDistance - eyeSize * .5, y - eyeYDistance - eyeSize * .5),
            calcRotateY(x, y, x - eyeXDistance - eyeSize * .5, y - eyeYDistance - eyeSize * .5),
            calcRotateX(x, y, x - eyeXDistance + eyeSize * .5, y - eyeYDistance + eyeSize * .5),
            calcRotateY(x, y, x - eyeXDistance + eyeSize * .5, y - eyeYDistance + eyeSize * .5),
            whiteColor()
    );

    // RIGHT EYE
    drawRectangle(
            calcRotateX(x, y, x + eyeXDistance - eyeSize, y - eyeYDistance - eyeSize),
            calcRotateY(x, y, x + eyeXDistance - eyeSize, y - eyeYDistance - eyeSize),
            calcRotateX(x, y, x + eyeXDistance + eyeSize, y - eyeYDistance + eyeSize),
            calcRotateY(x, y, x + eyeXDistance + eyeSize, y - eyeYDistance + eyeSize),
            whiteColor()
    );

    drawRectangle(
            calcRotateX(x, y, x + eyeXDistance - eyeSize * .5, y - eyeYDistance - eyeSize * .5),
            calcRotateY(x, y, x + eyeXDistance - eyeSize * .5, y - eyeYDistance - eyeSize * .5),
            calcRotateX(x, y, x + eyeXDistance + eyeSize * .5, y - eyeYDistance + eyeSize * .5),
            calcRotateY(x, y, x + eyeXDistance + eyeSize * .5, y - eyeYDistance + eyeSize * .5),
            whiteColor()
    );

    float noseSize = 15 * scale;

    // NOSE
    drawRectangle(
            calcRotateX(x, y, x - noseSize, y - noseSize),
            calcRotateY(x, y, x - noseSize, y - noseSize),
            calcRotateX(x, y, x + noseSize, y + noseSize),
            calcRotateY(x, y, x + noseSize, y + noseSize),
            whiteColor()
    );

    // MOUSTACHE
    float moustacheSize = 230 * scale;
    float moustacheDistance = 70 * scale;

    float mLeft = x - moustacheSize;
    float mRight = x + moustacheSize;
    float mTop = y - moustacheDistance;
    float mMiddle = y - 10;
    float mBottom = y + moustacheDistance;

    float centerRotateX = calcRotateX(x, y, x, y);
    float centerRotateY = calcRotateY(x, y, x, y);

    drawLine(
            calcRotateX(x, y, mLeft, mTop),
            calcRotateY(x, y, mLeft, mTop),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, mLeft, mMiddle),
            calcRotateY(x, y, mLeft, mMiddle),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, mLeft, mBottom),
            calcRotateY(x, y, mLeft, mBottom),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, mRight, mTop),
            calcRotateY(x, y, mRight, mTop),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, mRight, mMiddle),
            calcRotateY(x, y, mRight, mMiddle),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, mRight, mBottom),
            calcRotateY(x, y, mRight, mBottom),
            centerRotateX,
            centerRotateY,
            whiteColor()
    );

    // HEAD
    float headSize = 270 * scale;

    float hTop = y - headSize;
    float hBottom = y + headSize;
    float hLeft = x - headSize;
    float hRight = x + headSize;

    drawLine(
            calcRotateX(x, y, x, hTop),
            calcRotateY(x, y, x, hTop),
            calcRotateX(x, y, hRight, y),
            calcRotateY(x, y, hRight, y),
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, x, hBottom),
            calcRotateY(x, y, x, hBottom),
            calcRotateX(x, y, hRight, y),
            calcRotateY(x, y, hRight, y),
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, x, hBottom),
            calcRotateY(x, y, x, hBottom),
            calcRotateX(x, y, hLeft, y),
            calcRotateY(x, y, hLeft, y),
            whiteColor()
    );

    drawLine(
            calcRotateX(x, y, x, hTop),
            calcRotateY(x, y, x, hTop),
            calcRotateX(x, y, hLeft, y),
            calcRotateY(x, y, hLeft, y),
            whiteColor()
    );

    // MOUTH
    float mouthSize = 120 * scale;
    float mouthDistance = 60 * scale;

    drawLine(
            calcRotateX(x, y, x - (mouthSize * .5), y + moustacheDistance),
            calcRotateY(x, y, x - (mouthSize * .5), y + moustacheDistance),
            calcRotateX(x, y, x + (mouthSize * .5), y + moustacheDistance),
            calcRotateY(x, y, x + (mouthSize * .5), y + moustacheDistance),
            whiteColor()
    );

    if (speaking) {

        drawLine(
                calcRotateX(x, y, x - (mouthSize * .5), y + moustacheDistance),
                calcRotateY(x, y, x - (mouthSize * .5), y + moustacheDistance),
                calcRotateX(x, y, x, y + moustacheSize * .6),
                calcRotateY(x, y, x, y + moustacheSize * .6),
                whiteColor()
        );

        drawLine(
                calcRotateX(x, y, x + (mouthSize * .5),  y + moustacheDistance),
                calcRotateY(x, y, x + (mouthSize * .5),  y + moustacheDistance),
                calcRotateX(x, y, x,  y + moustacheSize * .6),
                calcRotateY(x, y, x,  y + moustacheSize * .6),
                whiteColor()
        );
    }
}