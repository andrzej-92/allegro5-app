#include "AllegroGraphicDriver.cpp"

class Lab4 :public AllegroGraphicDriver
{

public:

    void run() {

        drawCircle(44);

        // renderujemy obraz
        render();

        // czekamy na ESC
        waitForEscKey();
    }

private:

};
