//Diese Klasse erstellt das Objekt Zombie und erbt von der Klasse Kreaturen
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <vector>
#include <algoviz/SVG.hpp>
#include "Kreaturen.hpp"


class Zombie: public Kreaturen{

    private:
        //private Attribute
        int xPos;
        int yPos;
        int healthPoints;
        bool stehen;
        Image *picture;
        bool wechsel;
        bool standing;
        int velocity;
    public:
        
        Zombie(int xPos, int yPos, int healthPoints, int velocity, SVG &game,bool standing):Kreaturen(healthPoints, xPos, yPos, velocity, standing){
            picture = new Image("../Projekt/Pics/Walk.png", xPos, yPos, 40, 40, &game);
            this->xPos = 400;
            this->yPos = yPos;
            this->healthPoints = 10;
            this->wechsel = true;
            this->velocity = -2;
            this->standing = false;
        }
        
        //Zombie wird bewegt mit abwechselnden Bildern
        void schritt(SVG &game){
            delete picture;
            if(wechsel){
                picture = new Image("../Projekt/Pics/Walk5.png", this->xPos, this->yPos, 40, 40, &game);
                wechsel = false;
            }else{
                picture = new Image("../Projekt/Pics/Walk.png", this->xPos, this->yPos, 40, 40, &game);
                wechsel = true;
            }
            this->xPos += this->velocity;
        }
    
        void deletePic(){
            delete this->picture;
        }
       
   
}; //End of class zombie
#endif