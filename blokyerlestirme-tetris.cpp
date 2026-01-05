#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int SATIR_SAYISI = 20;
const int SUTUN_SAYISI = 10;
int oyunAlani[SATIR_SAYISI][SUTUN_SAYISI] = {0};

struct Koordinat { int yatay, dikey; } parcaAnlik[4], parcaYedek[4];

int blokKutuphanesi[7][4] = {
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool hareketGecerliMi() {
    for (int i=0; i<4; i++)
        if (parcaAnlik[i].yatay < 0 || parcaAnlik[i].yatay >= SUTUN_SAYISI || parcaAnlik[i].dikey >= SATIR_SAYISI) return false;
        else if (oyunAlani[parcaAnlik[i].dikey][parcaAnlik[i].yatay]) return false;
    return true;
};

int main() {
    srand(time(0));
    RenderWindow pencere(VideoMode(320, 480), "Blok Yerlestirme Oyunu");

    Texture dokuKutu, dokuArkaplan, dokuCerceve;
    dokuKutu.loadFromFile("images/tiles.png");
    dokuArkaplan.loadFromFile("images/background.png");
    dokuCerceve.loadFromFile("images/frame.png");

    Sprite spriteKutu(dokuKutu), spriteArka(dokuArkaplan), spriteCerceve(dokuCerceve);

    int yanaHareket = 0; 
    bool dondurmeIptal = false; 
    int aktifRenk = 1;
    float zamanSayaci = 0, dususHizi = 0.3;
    Clock saat;

    while (pencere.isOpen()) {
        float gecenZaman = saat.getElapsedTime().asSeconds();
        saat.restart();
        zamanSayaci += gecenZaman;

        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed) pencere.close();
            if (olay.type == Event::KeyPressed) {
                if (olay.key.code == Keyboard::Up) dondurmeIptal = true;
                else if (olay.key.code == Keyboard::Left) yanaHareket = -1;
                else if (olay.key.code == Keyboard::Right) yanaHareket = 1;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) dususHizi = 0.05;

        // --- Yatay Hareket ---
        for (int i=0; i<4; i++) { parcaYedek[i] = parcaAnlik[i]; parcaAnlik[i].yatay += yanaHareket; }
        if (!hareketGecerliMi()) for (int i=0; i<4; i++) parcaAnlik[i] = parcaYedek[i];

        // --- Döndürme İşlemi ---
        if (dondurmeIptal) {
            Koordinat merkez = parcaAnlik[1]; 
            for (int i=0; i<4; i++) {
                int y = parcaAnlik[i].dikey - merkez.dikey;
                int x = parcaAnlik[i].yatay - merkez.yatay;
                parcaAnlik[i].yatay = merkez.yatay - y;
                parcaAnlik[i].dikey = merkez.dikey + x;
            }
            if (!hareketGecerliMi()) for (int i=0; i<4; i++) parcaAnlik[i] = parcaYedek[i];
        }

        // --- Zamanla Aşağı Düşme ---
        if (zamanSayaci > dususHizi) {
            for (int i=0; i<4; i++) { parcaYedek[i] = parcaAnlik[i]; parcaAnlik[i].dikey += 1; }
            if (!hareketGecerliMi()) {
                for (int i=0; i<4; i++) oyunAlani[parcaYedek[i].dikey][parcaYedek[i].yatay] = aktifRenk;
                aktifRenk = 1 + rand() % 7;
                int yeniTip = rand() % 7;
                for (int i=0; i<4; i++) {
                    parcaAnlik[i].yatay = blokKutuphanesi[yeniTip][i] % 2;
                    parcaAnlik[i].dikey = blokKutuphanesi[yeniTip][i] / 2;
                }
            }
            zamanSayaci = 0;
        }

        // --- Satır Temizleme Kontrolü ---
        int dolulukSiniri = SATIR_SAYISI - 1;
        for (int i = SATIR_SAYISI - 1; i > 0; i--) {
            int hucreSay = 0;
            for (int j = 0; j < SUTUN_SAYISI; j++) {
                if (oyunAlani[i][j]) hucreSay++;
                oyunAlani[dolulukSiniri][j] = oyunAlani[i][j];
            }
            if (hucreSay < SUTUN_SAYISI) dolulukSiniri--;
        }

        yanaHareket = 0; dondurmeIptal = false; dususHizi = 0.3;

        // --- Çizim Alanı ---
        pencere.clear(Color::White);
        pencere.draw(spriteArka);

        for (int i=0; i<SATIR_SAYISI; i++)
            for (int j=0; j<SUTUN_SAYISI; j++) {
                if (oyunAlani[i][j] == 0) continue;
                spriteKutu.setTextureRect(IntRect(oyunAlani[i][j]*18, 0, 18, 18));
                spriteKutu.setPosition(j*18, i*18);
                spriteKutu.move(28, 31);
                pencere.draw(spriteKutu);
            }

        for (int i=0; i<4; i++) {
            spriteKutu.setTextureRect(IntRect(aktifRenk*18, 0, 18, 18));
            spriteKutu.setPosition(parcaAnlik[i].yatay*18, parcaAnlik[i].dikey*18);
            spriteKutu.move(28, 31);
            pencere.draw(spriteKutu);
        }

        pencere.draw(spriteCerceve);
        pencere.display();
    }
    return 0;
}