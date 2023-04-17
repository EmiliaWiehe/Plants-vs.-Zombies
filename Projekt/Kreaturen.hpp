//Basisklasse
#ifndef KREATUREN_HPP
#define KREATUREN_HPP

class Kreaturen{
    private:
        int healthPoints;
        int xPos;
        int yPos;
        Image *Picture;
        int velocity;
        bool type;
        bool standing;
    public:
       Kreaturen(int healthPoints, int xPos, int yPos, int velocity, bool standing){
            this->healthPoints = healthPoints;
            this->xPos = xPos;
            this->yPos = yPos;
            this->velocity = velocity;
            this->standing = standing;
       }

        // handle healthPoints 
        int getHealthPoints(){
            return this->healthPoints;
        }
    
        void setHealthPoints( int a){ 
            this->healthPoints = a;
        }
                  
        // handle psosition
        int getX(){ 
            return this->xPos;
        }
        int getY(){ 
            return this->yPos;
        }
        void setX( int a){ 
            this->xPos = a;
        }
        void setY( int a){ 
            this->yPos = a;
        }
        void setPos(int a, int b){ 
            this->xPos = a; 
            this->yPos = b;
        }
                          
        void step(){
            this->xPos = this->xPos + this->velocity;
        }
        int getVelocity(){
            return this->velocity;
        }
        void setStanding(bool a){
            this->standing = a;
        }
    
        bool getStanding(){
            return this->standing;
        }
        
        
};
#endif