#include <SFML/Graphics.hpp>
#include <fstream>
#include <time.h>
#include <vector>
using namespace sf;

int tasAlani[50][50][50] = {0};
int& tasSec(int x, int y, int z) { return tasAlani[y+2][x+2][z]; [cite_start]} [cite: 1115-1116]
int& tasSecV(Vector3i v) { return tasSec(v.x, v.y, v.z); }

bool tasBostaMi(int x, int y, int z) {
    for(int i=-1; i<=1; i++)
        for(int j=-1; j<=1; j++)
            if (tasSec(x+2, y+i, z) > 0 && tasSec(x-2, y+j, z) > 0) return 0;
    for(int i=-1; i<=1; i++)
        for(int j=-1; j<=1; j++)
            if (tasSec(x+i, y+j, z+1) > 0) return 0;
    return 1;
[cite_start]} [cite: 1118-1127]

int main() {
    srand(time(0));
    RenderWindow uygulama(VideoMode(740, 570), "Mahjong Solitaire!");
    Texture tTuğla, tArka;
    tTuğla.loadFromFile("files/tiles.png");
    tArka.loadFromFile("files/background.png");
    Sprite sTuğla(tTuğla), sArka(tArka);
    int parcaW = 48, parcaH = 66;
    int adimX = parcaW/2-2, adimY = parcaH/2-2;
    float kayX = 4.6, kayY = 7.1;
    Vector3i nokta1, nokta2;
    std::vector<Vector3i> gecmisHamleler;

    std::fstream haritaDosyasi("files/map.txt");
    for(int y=0; y<18; y++)
        for(int x=0; x<30; x++) {
            char karakter; haritaDosyasi >> karakter;
            int katman = karakter - '0';
            for(int z=0; z<katman; z++)
                if (tasSec(x-1, y-1, z)) tasSec(x-1, y, z) = tasSec(x, y-1, z) = 0;
                else tasSec(x, y, z) = 1;
        [cite_start]} [cite: 1142-1151]

    for(int k=1; ; k++) {
        std::vector<Vector3i> aciklar;
        for(int z=0; z<10; z++)
            for(int y=0; y<18; y++)
                for(int x=0; x<30; x++)
                    if (tasSec(x,y,z) > 0 && tasBostaMi(x,y,z)) aciklar.push_back(Vector3i(x,y,z));
        int n = aciklar.size();
        if (n < 2) break;
        int a=0, b=0;
        while(a == b) { a = rand()%n; b = rand()%n; }
        tasSecV(aciklar[a]) = -k; if (k > 34) k++;
        tasSecV(aciklar[b]) = -k;
        k %= 42;
    [cite_start]} [cite: 1153-1167]

    for(int z=0; z<10; z++)
        for(int y=0; y<18; y++)
            for(int x=0; x<30; x++) tasSec(x,y,z) *= -1;

    while (uygulama.isOpen()) {
        Event olay;
        while (uygulama.pollEvent(olay)) {
            if (olay.type == Event::Closed) uygulama.close();
            if (olay.type == Event::MouseButtonReleased)
                if (olay.key.code == Mouse::Right) {
                    int n = gecmisHamleler.size();
                    if (n == 0) continue;
                    tasSecV(gecmisHamleler[n-1]) *= -1; gecmisHamleler.pop_back();
                    tasSecV(gecmisHamleler[n-2]) *= -1; gecmisHamleler.pop_back();
                [cite_start]} [cite: 1179-1186]
            if (olay.type == Event::MouseButtonPressed)
                if (olay.key.code == Mouse::Left)
                    for(int z=0; z<10; z++) {
                        Vector2i pos = Mouse::getPosition(uygulama) - Vector2i(30,0);
                        int x = (pos.x - z * kayX) / adimX;
                        int y = (pos.y + z * kayY) / adimY;
                        for(int i=0; i<2; i++)
                            for(int j=0; j<2; j++)
                                if (tasSec(x-i, y-j, z) > 0 && tasBostaMi(x-i, y-j, z)) nokta1 = Vector3i(x-i, y-j, z);
                        if (nokta1 == nokta2) continue;
                        int val1 = tasSecV(nokta1), val2 = tasSecV(nokta2);
                        if (val1 == val2 || (val1 > 34 && val1 < 39 && val2 > 34 && val2 < 39) || (val1 >= 39 && val2 >= 39)) {
                            tasSecV(nokta1) *= -1; gecmisHamleler.push_back(nokta1);
                            tasSecV(nokta2) *= -1; gecmisHamleler.push_back(nokta2);
                        }
                        nokta2 = nokta1;
                    }
        [cite_start]} [cite: 1187-1207]

        uygulama.clear(); uygulama.draw(sArka);
        for(int z=0; z<10; z++)
            for(int x=30; x>=0; x--)
                for(int y=0; y<18; y++) {
                    int no = tasSec(x,y,z) - 1;
                    if (no < 0) continue;
                    sTuğla.setTextureRect(IntRect(no * parcaW, 0, parcaW, parcaH));
                    if (tasBostaMi(x,y,z)) sTuğla.setTextureRect(IntRect(no * parcaW, parcaH, parcaW, parcaH));
                    sTuğla.setPosition(x * adimX + z * kayX, y * adimY - z * kayY);
                    sTuğla.move(30,0); uygulama.draw(sTuğla);
                }
        uygulama.display();
    }
    return 0;
}