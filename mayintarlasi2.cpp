#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
 
int main() {
    srand(time(0)); [cite: 318]
    RenderWindow uygulama(VideoMode(400, 400), "Mayin Tarlasi!"); [cite: 319]

    int kareBoyutu = 32; [cite: 320]
    int mayinHaritasi[12][12]; [cite: 321]
    int gorunurHarita[12][12]; [cite: 322]

    Texture doku;
    doku.loadFromFile("images/tiles.jpg"); [cite: 324]
    Sprite kutuSprite(doku); [cite: 325]

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            gorunurHarita[i][j] = 10; [cite: 329]
            if (rand() % 5 == 0) mayinHaritasi[i][j] = 9; [cite: 330]
            else mayinHaritasi[i][j] = 0; [cite: 331]
        } [cite: 332]

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            int komsuSayisi = 0; [cite: 336]
            if (mayinHaritasi[i][j] == 9) continue; [cite: 337]
            if (mayinHaritasi[i + 1][j] == 9) komsuSayisi++; [cite: 338]
            if (mayinHaritasi[i][j + 1] == 9) komsuSayisi++; [cite: 339]
            if (mayinHaritasi[i - 1][j] == 9) komsuSayisi++; [cite: 340]
            if (mayinHaritasi[i][j - 1] == 9) komsuSayisi++; [cite: 341]
            if (mayinHaritasi[i + 1][j + 1] == 9) komsuSayisi++; [cite: 342]
            if (mayinHaritasi[i - 1][j - 1] == 9) komsuSayisi++; [cite: 343]
            if (mayinHaritasi[i - 1][j + 1] == 9) komsuSayisi++; [cite: 344]
            if (mayinHaritasi[i + 1][j - 1] == 9) komsuSayisi++; [cite: 345]
            mayinHaritasi[i][j] = komsuSayisi; [cite: 346]
        } [cite: 347]

    while (uygulama.isOpen()) {
        Vector2i imlecKonumu = Mouse::getPosition(uygulama); [cite: 350]
        int satir = imlecKonumu.x / kareBoyutu; [cite: 351]
        int sutun = imlecKonumu.y / kareBoyutu; [cite: 352]

        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close(); [cite: 356, 357]
            if (olay.type == Event::MouseButtonPressed)
                if (olay.key.code == Mouse::Left) gorunurHarita[satir][sutun] = mayinHaritasi[satir][sutun]; [cite: 358, 359]
                else if (olay.key.code == Mouse::Right) gorunurHarita[satir][sutun] = 11; [cite: 360]
        }

        uygulama.clear(Color::White); [cite: 362]
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++) {
                if (gorunurHarita[satir][sutun] == 9) gorunurHarita[i][j] = mayinHaritasi[i][j]; [cite: 366]
                kutuSprite.setTextureRect(IntRect(gorunurHarita[i][j] * kareBoyutu, 0, kareBoyutu, kareBoyutu)); [cite: 367]
                kutuSprite.setPosition(i * kareBoyutu, j * kareBoyutu); [cite: 368]
                uygulama.draw(kutuSprite); [cite: 369]
            } [cite: 370]
        uygulama.display(); [cite: 371]
    }
    return 0; [cite: 373]
}