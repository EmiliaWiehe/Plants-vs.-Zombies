//Diese Klasse erstellt das Objekt Pflanze und erbt von der Klasse Kreaturen
#ifndef PLANTS_HPP
#define PLANTS_HPP
#include <algoviz/SVG.hpp>


class Plants: public Kreaturen{

    private:
        //private Attribute
        int xPos;
        int yPos;
        int healthPoints = 100;
        bool standing;
        int velocity;
        Image *picture;
    public:
        //Konstruktor des Objektes
        Plants(int xPos, int yPos,  int healthPoints, int velocity,SVG &game, bool standing): Kreaturen(healthPoints, xPos, yPos, velocity, standing){            
            this->healthPoints = 10;
            this->xPos = xPos;
            this->yPos = yPos;
            this->velocity = 0;
            this->standing = false;
            this->picture;
        }
        void deletePic(){
            delete this->picture;
        }
        
};
#endif