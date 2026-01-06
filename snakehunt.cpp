#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int sutunAdedi = 30, satirAdedi = 20;
int kareBoyutu = 16;
int ekranGenislik = kareBoyutu * sutunAdedi;
int ekranYukseklik = kareBoyutu * satirAdedi;

int hareketYonu, yilanUzunlugu = 4;

struct YilanParcasi { int x_koordinat, y_koordinat; } govde[100];
struct Yem { int x_koordinat, y_koordinat; } elma;

void oyunGuncelle() {
    for (int i = yilanUzunlugu; i > 0; --i) { 
        govde[i].x_koordinat = govde[i-1].x_koordinat; 
        govde[i].y_koordinat = govde[i-1].y_koordinat; 
    } [cite: 258, 259]

    if (hareketYonu == 0) govde[0].y_koordinat += 1; [cite: 260]
    if (hareketYonu == 1) govde[0].x_koordinat -= 1; [cite: 261]
    if (hareketYonu == 2) govde[0].x_koordinat += 1; [cite: 262]
    if (hareketYonu == 3) govde[0].y_koordinat -= 1; [cite: 263]

    if ((govde[0].x_koordinat == elma.x_koordinat) && (govde[0].y_koordinat == elma.y_koordinat)) {
        yilanUzunlugu++; 
        elma.x_koordinat = rand() % sutunAdedi; 
        elma.y_koordinat = rand() % satirAdedi;
    } [cite: 264, 265]

    if (govde[0].x_koordinat >= sutunAdedi) govde[0].x_koordinat = 0; 
    if (govde[0].x_koordinat < 0) govde[0].x_koordinat = sutunAdedi - 1; [cite: 266]
    if (govde[0].y_koordinat >= satirAdedi) govde[0].y_koordinat = 0; 
    if (govde[0].y_koordinat < 0) govde[0].y_koordinat = satirAdedi - 1; [cite: 267]

    for (int i = 1; i < yilanUzunlugu; i++)
        if (govde[0].x_koordinat == govde[i].x_koordinat && govde[0].y_koordinat == govde[i].y_koordinat) 
            yilanUzunlugu = i; [cite: 268, 269]
}

int main() {
    srand(time(0)); [cite: 273]
    RenderWindow pencere(VideoMode(ekranGenislik, ekranYukseklik), "Yilan Oyunu"); [cite: 274]

    Texture tBeyaz, tKirmizi;
    tBeyaz.loadFromFile("images/white.png"); [cite: 276]
    tKirmizi.loadFromFile("images/red.png"); [cite: 277]

    Sprite zeminSprite(tBeyaz), objeSprite(tKirmizi); [cite: 278, 279]
    Clock kronometre;
    float zamanlayici = 0, gecikmeSuresi = 0.1; [cite: 280, 281]

    elma.x_koordinat = 10; elma.y_koordinat = 10; [cite: 282, 283]

    while (pencere.isOpen()) {
        float gecenSaniye = kronometre.getElapsedTime().asSeconds();
        kronometre.restart();
        zamanlayici += gecenSaniye; [cite: 286, 287, 288]

        Event olay;
        while (pencere.pollEvent(olay)) {
            if (olay.type == Event::Closed) pencere.close(); [cite: 290, 292, 293]
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) hareketYonu = 1; [cite: 295]
        if (Keyboard::isKeyPressed(Keyboard::Right)) hareketYonu = 2; [cite: 296]
        if (Keyboard::isKeyPressed(Keyboard::Up)) hareketYonu = 3; [cite: 297]
        if (Keyboard::isKeyPressed(Keyboard::Down)) hareketYonu = 0; [cite: 298]

        if (zamanlayici > gecikmeSuresi) { zamanlayici = 0; oyunGuncelle(); } [cite: 299]

        pencere.clear(); [cite: 301]
        for (int i = 0; i < sutunAdedi; i++)
            for (int j = 0; j < satirAdedi; j++) {
                zeminSprite.setPosition(i * kareBoyutu, j * kareBoyutu);
                pencere.draw(zeminSprite);
            } [cite: 302, 303, 304]

        for (int i = 0; i < yilanUzunlugu; i++) {
            objeSprite.setPosition(govde[i].x_koordinat * kareBoyutu, govde[i].y_koordinat * kareBoyutu);
            pencere.draw(objeSprite);
        } [cite: 305, 306]

        objeSprite.setPosition(elma.x_koordinat * kareBoyutu, elma.y_koordinat * kareBoyutu);
        pencere.draw(objeSprite); [cite: 307]
        pencere.display(); [cite: 308]
    }
    return 0; [cite: 310]
}