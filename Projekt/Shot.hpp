//Diese Klasse erstellt das Objekt Schuss und erbt von der Klasse Kreaturen
#ifndef SHOT_HPP
#define SHOT_HPP
#include "Kreaturen.hpp"

class Shot: public Kreaturen{
    private:
        //private Attribute
        Circle* picture;
        int xPos;
        int yPos;
        int healthPoints;
        int velocity;
        bool standing;
    public:
        //Konstrukter
        Shot(int xPos, int yPos,  int healthPoints, int velocity,SVG &game, bool standing):Kreaturen(healthPoints, xPos, yPos, velocity, standing){
            picture = new Circle(xPos, yPos, 5, &game);
            this->xPos = xPos;
            this->yPos = yPos;
            this->healthPoints = 10;
            this->velocity = 5;
            this->standing = false;
        }
        //Der Schuss wird bewegt
        void schritt(SVG &game){
            delete picture;
            picture = new Circle(this->xPos, this->yPos, 5, &game);
            this->xPos += this->velocity;
        }
        
        //Das Bild des Schusses wird geloescht
        void deletePic(){
            delete this->picture;
        }
};
#endif