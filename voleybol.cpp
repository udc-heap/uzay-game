#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
using namespace sf;

const float OLC = 30.f;
const float RAD_TO_DEG = 57.29577f;
b2Vec2 Yercekimi(0.f, 9.8f);
[cite_start]b2World fizikDunyasi(Yercekimi); [cite: 1457-1460]

void duvarKur(int x, int y, int w, int h) {
    b2PolygonShape kutu; kutu.SetAsBox(w/OLC, h/OLC);
    b2BodyDef tanim; tanim.position.Set(x/OLC, y/OLC);
    b2Body *zemin = fizikDunyasi.CreateBody(&tanim);
    zemin->CreateFixture(&kutu, 1);
[cite_start]} [cite: 1461-1469]

int main() {
    RenderWindow pencere(VideoMode(800, 600), "Volleyball Game!");
    pencere.setFramerateLimit(60); pencere.setSize(Vector2u(800 * 0.8, 600 * 0.8));
    Texture tArka, tTop, tBlob;
    tArka.loadFromFile("images/background.png"); tTop.loadFromFile("images/ball.png"); tBlob.loadFromFile("images/blobby.png");
    Sprite sArka(tArka), sTop(tTop), sOyuncu(tBlob);
    sOyuncu.setOrigin(75/2, 90/2); sTop.setOrigin(32, 32);

    duvarKur(400, 520, 2000, 10); duvarKur(400, 450, 10, 170); duvarKur(0, 0, 10, 2000); duvarKur(800, 0, 10, 2000);
    b2BodyDef bDef; bDef.type = b2_dynamicBody;
    b2Body *oyuncuGovdesi[2];
    for(int i=0; i<2; i++) {
        bDef.position.Set(20 * i, 2);
        b2CircleShape c1; c1.m_radius = 32/OLC; c1.m_p.Set(0, 13/OLC);
        oyuncuGovdesi[i] = fizikDunyasi.CreateBody(&bDef); oyuncuGovdesi[i]->CreateFixture(&c1, 5);
        b2CircleShape c2; c2.m_radius = 25/OLC; c2.m_p.Set(0, -20/OLC);
        oyuncuGovdesi[i]->CreateFixture(&c2, 5); oyuncuGovdesi[i]->SetFixedRotation(true);
    [cite_start]} [cite: 1494-1507]
    oyuncuGovdesi[0]->SetUserData("player1"); oyuncuGovdesi[1]->SetUserData("player2");

    bDef.position.Set(5, 1);
    b2CircleShape topSekli; topSekli.m_radius = 32/OLC;
    b2Body *topBody = fizikDunyasi.CreateBody(&bDef);
    b2FixtureDef fDef; fDef.shape = &topSekli; fDef.restitution = 0.95; fDef.density = 0.2;
    [cite_start]topBody->CreateFixture(&fDef); topBody->SetUserData("ball"); [cite: 1510-1521]

    while (pencere.isOpen()) {
        Event olay;
        while (pencere.pollEvent(olay)) { if (olay.type == Event::Closed) pencere.close(); }
        [cite_start]for(int n=0; n<2; n++) fizikDunyasi.Step(1/60.f, 8, 3); [cite: 1531-1532]

        b2Vec2 p1Pos = oyuncuGovdesi[0]->GetPosition(), p1Vel = oyuncuGovdesi[0]->GetLinearVelocity();
        if (Keyboard::isKeyPressed(Keyboard::Right)) p1Vel.x = 5;
        if (Keyboard::isKeyPressed(Keyboard::Left)) p1Vel.x = -5;
        if (Keyboard::isKeyPressed(Keyboard::Up) && p1Pos.y * OLC >= 463) p1Vel.y = -13;
        if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)) p1Vel.x = 0;
        [cite_start]oyuncuGovdesi[0]->SetLinearVelocity(p1Vel); [cite: 1534-1542]

        b2Vec2 p2Pos = oyuncuGovdesi[1]->GetPosition(), p2Vel = oyuncuGovdesi[1]->GetLinearVelocity();
        if (Keyboard::isKeyPressed(Keyboard::D)) p2Vel.x = 5;
        if (Keyboard::isKeyPressed(Keyboard::A)) p2Vel.x = -5;
        if (Keyboard::isKeyPressed(Keyboard::W) && p2Pos.y * OLC >= 463) p2Vel.y = -13;
        if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A)) p2Vel.x = 0;
        [cite_start]oyuncuGovdesi[1]->SetLinearVelocity(p2Vel); [cite: 1544-1552]

        b2Vec2 ballVel = topBody->GetLinearVelocity();
        if (ballVel.Length() > 15) topBody->SetLinearVelocity(15 / ballVel.Length() * ballVel);

        pencere.draw(sArka);
        for (b2Body* b = fizikDunyasi.GetBodyList(); b != 0; b = b->GetNext()) {
            b2Vec2 pos = b->GetPosition(); float ang = b->GetAngle();
            if (b->GetUserData() == "player1") { 
                sOyuncu.setPosition(pos.x*OLC, pos.y*OLC); sOyuncu.setRotation(ang*RAD_TO_DEG); sOyuncu.setColor(Color::Red); pencere.draw(sOyuncu); 
            }
            if (b->GetUserData() == "player2") { 
                sOyuncu.setPosition(pos.x*OLC, pos.y*OLC); sOyuncu.setRotation(ang*RAD_TO_DEG); sOyuncu.setColor(Color::Green); pencere.draw(sOyuncu); 
            }
            if (b->GetUserData() == "ball") { 
                sTop.setPosition(pos.x*OLC, pos.y*OLC); sTop.setRotation(ang*RAD_TO_DEG); pencere.draw(sTop); 
            }
        }
        pencere.display();
    }
    return 0;
}