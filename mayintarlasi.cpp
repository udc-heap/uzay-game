#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int main() {
    srand(time(0));
    RenderWindow uygulama(VideoMode(400, 400), "Mayin Tarlasi Analizi");

    int kareGenislik = 32;
    int gercekDegerler[12][12];
    int maskelenmisDegerler[12][12];

    Texture dokuSeti;
    dokuSeti.loadFromFile("images/tiles.jpg");
    Sprite kareSprite(dokuSeti);

    // Harita oluşturma
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            maskelenmisDegerler[i][j] = 10; // Kapalı kutu
            if (rand() % 5 == 0) gercekDegerler[i][j] = 9; // Mayın
            else gercekDegerler[i][j] = 0;
        }

    // Sayıları hesaplama
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++) {
            if (gercekDegerler[i][j] == 9) continue;
            int komsuMayin = 0;
            if (gercekDegerler[i + 1][j] == 9) komsuMayin++;
            if (gercekDegerler[i][j + 1] == 9) komsuMayin++;
            if (gercekDegerler[i - 1][j] == 9) komsuMayin++;
            if (gercekDegerler[i][j - 1] == 9) komsuMayin++;
            if (gercekDegerler[i + 1][j + 1] == 9) komsuMayin++;
            if (gercekDegerler[i - 1][j - 1] == 9) komsuMayin++;
            if (gercekDegerler[i - 1][j + 1] == 9) komsuMayin++;
            if (gercekDegerler[i + 1][j - 1] == 9) komsuMayin++;
            gercekDegerler[i][j] = komsuMayin;
        }

    while (uygulama.isOpen()) {
        Vector2i fareKonum = Mouse::getPosition(uygulama);
        int satir = fareKonum.x / kareGenislik;
        int sutun = fareKonum.y / kareGenislik;

        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close();
            if (olay.type == Event::MouseButtonPressed) {
                if (olay.key.code == Mouse::Left) maskelenmisDegerler[satir][sutun] = gercekDegerler[satir][sutun];
                else if (olay.key.code == Mouse::Right) maskelenmisDegerler[satir][sutun] = 11; // Bayrak
            }
        }

        uygulama.clear(Color::White);
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++) {
                // Kaybetme durumu: Mayına tıklandıysa her şeyi göster
                if (maskelenmisDegerler[satir][sutun] == 9) maskelenmisDegerler[i][j] = gercekDegerler[i][j];
                
                kareSprite.setTextureRect(IntRect(maskelenmisDegerler[i][j] * kareGenislik, 0, kareGenislik, kareGenislik));
                kareSprite.setPosition(i * kareGenislik, j * kareGenislik);
                uygulama.draw(kareSprite);
            }
        uygulama.display();
    }
    return 0;
}