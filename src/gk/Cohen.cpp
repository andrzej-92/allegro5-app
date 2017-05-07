#include "iostream"
#include "AllegroGraphicDriver.cpp"

using namespace std;

/**
 * Implementation of Cohena-Sutherlanda algorithm
 */
class Cohen : public AllegroGraphicDriver {

public:

    unsigned char calc(int x, int y) {
        unsigned char result = 0;

        if (x < left) result |= 0x1;
        if (x > right) result |= 0x2;
        if (y > bottom) result |= 0x4;
        if (y < top) result |= 0x8;

        return result;
    }

    void cropLine(int x1, int y1, int x2, int y2) {

        unsigned char rcode1, rcode2, rcode;
        int x, y;

        rcode1 = calc(x1, y1);
        rcode2 = calc(x2, y2);

        /* 2. Jeżeli iloczyn logiczny (AND) tych kodów <>0,
            to odcinek może być pominięty (w całości poza
            oknem) - zaznacz go na czerwono */

        if (rcode1 & rcode2) {
            cout << "ALL OUT" << endl;
            drawLine(x1, y1, x2, y2, getCroppedColor());

        } else if ((rcode1 | rcode2) == 0) {

            cout << "ALL IN" << endl;
            drawLine(x1, y1, x2, y2, greenColor());

        } else {

            do {

                if (rcode1 != 0) {
                    rcode = rcode1;
                } else {
                    rcode = rcode2;
                }

                if (rcode & 0x1) {

                    x = left;
                    y = y1 + (y2 - y1) * (left - x1) / (x2 - x1);

                } else if (rcode & 0x2) {

                    x = right;
                    y = y1 + (y2 - y1) * (right - x1) / (x2 - x1);

                } else if (rcode & 0x4) {

                    x = x1 + (x2 - x1) * (bottom - y1) / (y2 - y1);
                    y = bottom;

                } else if (rcode & 0x8) {

                    x = x1 + (x2 - x1) * (top - y1) / (y2 - y1);
                    y = top;
                }

                if (rcode == rcode1) {
                    cout << "RED LINE ->" << x1 << " " << y1 << " " << " " << x << " " << y << endl;
                    drawLine(x1, y1, x, y, getCroppedColor());

                    x1 = x;
                    y1 = y;
                    rcode1 = calc(x1, y1);
                } else {
                    drawLine(x2, y2, x, y, getCroppedColor());
                    x2 = x;
                    y2 = y;
                    rcode2 = calc(x2, y2);
                }

                cout << "CALCULATE..." << endl;

            } while ((rcode1 & rcode2) == 0 && (rcode1 | rcode2) != 0);
        }
    }

    /**
     * Metoda rekurencyjna
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     */
    void cropLine1(int x1, int y1, int x2, int y2) {
        unsigned char rcode1, rcode2, rcode;
        int x, y;

        rcode1 = calc(x1, y1);
        rcode2 = calc(x2, y2);

        if (rcode1 & rcode2) {
            cout << "ALL OUT" << endl;
            drawLine(x1, y1, x2, y2, getCroppedColor());

        } else if ((rcode1 | rcode2) == 0) {

            cout << "ALL IN" << endl;
            drawLine(x1, y1, x2, y2, greenColor());

        } else {

            if (rcode1 == 0x0) {
                rcode = rcode1;
                rcode1 = rcode2;
                rcode2 = rcode;

                x = x1;
                y = y1;

                x1 = x2;
                y1 = y2;

                x2 = x;
                y2 = y;
            }

            if (rcode & 0x1) {

                y1 = y1 + (left - x1) * (y2 - y1) / (x2 - x1);
                x1 = left;
                cropLine1(x1, y1, x2, y2);

            } else if (rcode & 0x2) {

                y1 = y1 + (bottom - x1) * (y2 - y1) / (x2 - x1);
                x1 = right;
                cropLine1(x1, y1, x2, y2);

            } else if (rcode & 0x4) {
//              x1= x1+ (ymax– y1) * (x2– x1) / (y2– y1); y1=ymax
                x1 = x1 + (right - y1) * (x2 - x1) / (y2 - y1);
                y1 = bottom;
                cropLine1(x1, y1, x2, y2);

            } else if (rcode & 0x8) {
//              x1= x1+ (ymin– y1) * (x2– x1) / (y2– y1); y1=ymin
                x1 = x1 + (top - y1) * (x2 - x1) / (y2 - y1);
                y1 = top;
                cropLine1(x1, y1, x2, y2);
            }
        }
    }

    void drawCenteredRectangle(int x, int y, ALLEGRO_COLOR color, int thickness = 1) {

        int startX = left = centerX() - (x / 2);
        int startY = top = centerY() - (y / 2);
        int endX = right = centerX() + (x / 2);
        int endY = bottom = centerY() + (y / 2);

        cout << "Limit range: TOP:" << top << " RIGHT:" << right << " BOTTOM:" << bottom << " LEFT:" << left << endl;

        drawRectangle(startX, startY, endX, endY, color, thickness);
    }

    void drawRandomRectangleFromLinesAndCrop(int width, int height, ALLEGRO_COLOR color, int thickness = 1) {

        int x = centerX() - (rand() % (width / 3)) + (rand() % (width / 3));
        int y = centerY() - (rand() % (height / 3)) + (rand() % (height / 3));

        int startX = x - (width / 2);
        int startY = y - (height / 2);
        int endX = x + (width / 2);
        int endY = y + (height / 2);

        //al_draw_line(startX, startY, endX, startY, color, thickness);

        drawLine(startX, startY, endX, startY, color, thickness);
        cropLine(startX, startY, endX, startY);

        drawLine(startX, startY, startX, endY, color, thickness);
        cropLine(startX, startY, startX, endY);

        drawLine(endX, startY, endX, endY, color, thickness);
        cropLine(endX, startY, endX, endY);

        drawLine(startX, endY, endX, endY, color, thickness);
        cropLine(startX, endY, endX, endY);
    }

    void drawRandomLineAndCrop(ALLEGRO_COLOR color, int thickness = 1) {
        int x1 = (width / 2) - rand() % (width / 2);
        int y1 = (height / 2) - rand() % (height / 2);

        int x2 = (width / 2) + rand() % (width / 2);
        int y2 = (height / 2) + rand() % (height / 2);

        drawLine(x1, y1, x2, y2, color, thickness);
        cropLine(x1, y1, x2, y2);
    }

    void drawRandomTriangleAndCrop(ALLEGRO_COLOR color, int thickness = 1) {
        int triangleCenterX = (width / 2) - rand() % (width / 4);
        int triangleCenterY = (height / 2) - rand() % (height / 4);
        int triangleWidth = rand() % 200;

        int x1 = triangleCenterX;
        int y1 = triangleCenterY - triangleWidth;

        int x2 = triangleCenterX - triangleWidth;
        int y2 = triangleCenterY + triangleWidth;

        int x3 = triangleCenterX + triangleWidth;
        int y3 = triangleCenterY + triangleWidth;

        drawLine(x1, y1, x2, y2, color);
        cropLine(x1, y1, x2, y2);

        drawLine(x2, y2, x3, y3, color);
        cropLine(x2, y2, x3, y3);

        drawLine(x3, y3, x1, y1, color);
        cropLine(x3, y3, x1, y1);
    }

    ALLEGRO_COLOR getCroppedColor() {
        return redColor();
    }

protected:

    int top;
    int right;
    int bottom;
    int left;
};