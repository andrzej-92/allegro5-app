#include "Cohen.cpp"
#include "iostream"

using namespace std;

/**
 * Grafika Komputerowa - LAB 3 - Andrzej Tracz
 */
class Lab03 : public Cohen {

public:

    void run() {

        setWindowTitle("Grafika Komputerowa - Lab 3 - Andrzej Tracz");

        // rysujemy prostokat ktory bedzie wyznaczał granice widocznosci
        drawCenteredRectangle(400, 300, whiteColor());

        // dwie losowe linie, rusujemy i obcinamy
        drawRandomLineAndCrop(greenColor());
        drawRandomLineAndCrop(greenColor());

        // rysujemy losowy prostokat i obcinamy
        drawRandomRectangleFromLinesAndCrop(rand() % 400, rand() % 400, greenColor());

        drawRandomTriangleAndCrop(greenColor());

        // renderujemy obraz
        render();

        // czekamy na ESC
        waitForEscKey();
    }

};
