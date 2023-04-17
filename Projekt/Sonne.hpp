#ifndef SONNE_HPP
#define SONNE_HPP
#include <algoviz/SVG.hpp>


class Sonne: public Kreaturen{

    private:
        //private Attribute
        int xPos;
        int yPos;
        int healthPoints;
        Image *Picture;
        bool standing;
        int velocity;
    public:
        //Konstruktor des Objektes
        Sonne(int xPos, int yPos,  int healthPoints, int velocity,SVG &game, bool standing): Kreaturen(healthPoints, xPos, yPos, velocity, standing){
            //Bild = new Circle(xPos, yPos, 10, &spiel);
            Picture = new Image("../Projekt/Pics/sun.png", xPos, yPos, 30, 30, &game);
            this->xPos = xPos;
            this->yPos = yPos;
            this->velocity = 4;
            this->standing = false;
            this->healthPoints = 1;
        }
        void Delete(){
            delete this->Picture;
        }
        void Schritt(SVG &game){
            delete Picture;
            Picture = new Image("../Projekt/Pics/sun.png", this->xPos, this->yPos, 30, 30, &game);
            this->yPos += this->velocity;
        }
};
#endif