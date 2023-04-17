#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include <algoviz/SVG.hpp>

class Wallnut: public Plants{
    private:
        //private Attribute
        int xPos;
        int yPos;
        int healthPoints;
        Image *picture;
        bool standing;
        int velocity;
    public:
        //Konstruktor des Objektes
        Wallnut(int xPos, int yPos, int healthPoints, int velocity,SVG &game, bool standing): Plants(xPos, yPos, healthPoints,velocity,game,standing){
            //Bild = new Circle(xPos, yPos, 10, &spiel);
            picture = new Image("../Projekt/Pics/wallnut.png", xPos, yPos, 30, 30, &game);
            this->healthPoints = 10;
            this->xPos = xPos;
            this->yPos = yPos;
            this->velocity = 0;
            this->standing = true;
        }
};
#endif