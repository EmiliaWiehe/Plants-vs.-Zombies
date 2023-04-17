#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include <algoviz/SVG.hpp>

class PeaShooter: public Plants{
    private:
        //private Attribute
        int xPos;
        int yPos;
        int healthPoints = 400;
        Image *picture;
        bool standing;
        int velocity;
    public:
        //Konstruktor des Objektes
        PeaShooter(int xPos, int yPos, int healthPoints, int velocity,SVG &game, bool standing): Plants(xPos, yPos, healthPoints,velocity,game,standing){
            //Bild = new Circle(xPos, yPos, 10, &spiel);
            picture = new Image("../Projekt/Pics/pea-shooter.png", xPos, yPos, 30, 30, &game);            
            this->healthPoints = 100;
            this->xPos = xPos;
            this->yPos = yPos;
            this->velocity = 0;
            this->standing = false;
        }
};
#endif