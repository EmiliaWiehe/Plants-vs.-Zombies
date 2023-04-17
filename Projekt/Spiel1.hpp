#ifndef SPIEL1_HPP
#define SPIEL1_HPP
#include <algoviz/SVG.hpp>
#include <math.h>
#include <iostream>
#include "Zombie.hpp"
#include "Plants.hpp"
#include "Shot.hpp"
#include "Wallnut.hpp"
#include "Sonne.hpp"
#include "PeaShooter.hpp"

using namespace std;

class Spiel1{
    private:
        //Position Zombie
        int xPosZombie = 400;
        int counter;
        int zombieZaehler;
        int Y[5] = {95, 135, 175, 215, 255};
        bool endWhile = false;
        MouseState mouse;
        string key = "";
        
        //Listen der Kreaturen
        list<Zombie> listeZombie;
        Zombie *newZombie = nullptr;
        list<Plants> listePlant;
        Plants *newPlant = nullptr;
        list<Shot> listeShot;
        Shot *newShot = nullptr;
        list<Sonne> listeSonne;
        Sonne *newSonne = nullptr;
        
        int punkte = 75;
        
        //Groesse des Spielfeldes
        int width;
        int height;
        int x;
        int y;
        int j;
        int i;
        
        bool setzenPflanze = false;
        bool setWallnut = false;
    
    public:
        //Konstruktor
        Spiel1(int i, int j, int width, int height, int x, int y){
            this->i = i;
            this->j = j;
            this->width = width;
            this->height = height;
            this->x = x;
            this->y = y; 
        }
    
        bool collision(int x1, int x2){
            int distance = sqrt(pow(x1 - x2, 2));
            if(distance <= 5){
                return true;
            }
            return false;
        }
    
        
        int mappingColumn(int xPos){
            return (xPos - this->x)/this->width;
        }
    
        int mappingRow(int yPos){
            return (yPos - this->y)/this->height;
        }
        
        //Mittelpunkt einer Spielfeldzelle ermitteln
        int centerX(int a){
            return a * this->width + this->x + width/2;
        }
    
        int centerY(int a){
            return a * this->height + this->y + height/2;
        }
    
       
        void startGame(int numberOfZombies, int frequenz, SVG &game){
            while((key != "x") &&  !endWhile){
                
                key = game.lastKey();
                mouse = game.lastClick();
                
                Text points = Text (to_string(this->punkte), 365,30, &game);
                
                //Sonne wird erstellt und in die Sonnenliste eingefuegt
                if(this->counter % 100 == 0){
                    newSonne = new Sonne(rand() % 400, 0, 100, 4, game, false);
                    listeSonne.push_back(*newSonne);
                }
                
                
                //Zombies nach einer Zeit zufaellig setzen
                if(this->counter % frequenz == 0 && this->zombieZaehler < numberOfZombies){
                    newZombie = new Zombie(this->xPosZombie, this->Y[rand() % 5], 100, -2, game, false);
                    listeZombie.push_back(*newZombie);
                    this->zombieZaehler++;
                }
                
                if(this->punkte >= 100){
                    //Peashooter auswaehlen
                    if(mouse.isLegal() && mouse.x()> 10  && mouse.x() < 50 && mouse.y() > 75 && mouse.y() < 115 ){
                        game.setStatusMsg("Eine Pflanze wurde ausgewaehlt");
                        this->setzenPflanze = true;
                    }
                    
                    //Peashooter setzen und in die Liste einfuegen
                    if(mouse.isLegal() && mouse.x()> this->x && mouse.x() < 400 && mouse.y() > this->y && mouse.y() < 275 && this->setzenPflanze){
                        newPlant = new PeaShooter(centerX(mappingColumn(mouse.x())) , centerY(mappingRow(mouse.y())), 100, 0, game, false);
                        listePlant.push_back(*newPlant);
                        this->punkte -= 100;
                        this->setzenPflanze = false;
                    }
                }
                
                //Wallnuss-Pflanze setzen
                if(this->punkte >= 50){
                    //Wallnut auswaehlen
                    if(mouse.isLegal() && mouse.x()> 10 && mouse.x() < 50 && mouse.y() > 115 && mouse.y() < 145 ){
                        game.setStatusMsg("Eine Wallnuss wurde ausgewaehlt");
                        this->setWallnut = true;                        
                    }
                    
                    //Wallnut erstellen
                    if(mouse.isLegal() && mouse.x()> this->x && mouse.x() < 400 && mouse.y() > this->y && mouse.y() < 275&& this->setWallnut){
                        newPlant = new Wallnut(centerX(mappingColumn(mouse.x())) , centerY(mappingRow(mouse.y())), 200, 0, game, true);
                        listePlant.push_back(*newPlant);
                        this->punkte -= 50;
                        this->setWallnut = false;
                     }
                }
                
                //Interaktion Zombie - Pflanzen
                for(auto it = this->listeZombie.begin(); it != this->listeZombie.end(); it++){
                    for(auto it2 = this->listePlant.begin(); it2 != this->listePlant.end(); it2++){
                       //Schuss wird erstellt, wenn in der gleichen Reihe
                        if((it2->getY() == it->getY())){
                            if(this->counter % 15 == 0 && it2->getStanding() == false){
                                newShot = new Shot( it2->getX(), it2->getY(), 1, 5, game, false);
                                listeShot.push_back(*newShot);
                            }
                            
                            //Kollision zwischen Pflanze und Zombie
                            if(this->collision(it2->getX(), it->getX())){
                                //Pflanze verliert Leben und das Zombie bleibt stehen
                                it2->setHealthPoints(it2->getHealthPoints() - 10);
                                it->setStanding(true);
                                 
                                //Pflanze wird aus der Liste entfernt
                                if(it2->getHealthPoints() == 0){
                                   it2->deletePic();
                                   it2 = this->listePlant.erase(it2);
                                   it->setStanding(false);
                                }
                            }
                        }  
                    }
                }
                
                //Interaktion Zombie - Shot
                 for(auto it = this->listeZombie.begin(); it != this->listeZombie.end(); it++){
                    for(auto it2 = this->listeShot.begin(); it2 != this->listeShot.end(); it2++){
                        
                        //Kollision Schuss-Zombie
                        if(this->collision(it2->getX(), it->getX())){
                            
                            //Zombie verliert Lebenspunkte
                            it->setHealthPoints(it->getHealthPoints() - 10);
                            
                            //Zombie loeschen, wenn er stirbt
                            if(it->getHealthPoints() == 0){
                                it->deletePic();
                                it = this->listeZombie.erase(it);
                            }
                            
                            //Schuss wird getoetet
                            it2->deletePic();
                            it2 = this->listeShot.erase(it2);
                        }
                    }
                }
                
                //Sonnen werden bewegt
                for(auto it = listeSonne.begin(); it != listeSonne.end(); it++){
                    if(it->getY() <= 298){
                        it->setY(it->getY()+it->getVelocity());
                        it->Schritt(game);
                    }
                    
                    //Wenn die Sonne angeklickt wird, dann gibt es Punkte
                    if(mouse.isLegal() && mouse.x() > it->getX() - 20 && mouse.x() < (it->getX() + 20) && mouse.y() > it->getY() - 20 && mouse.y() < (it->getY() + 20)){
                        it->Delete();
                        it = this->listeSonne.erase(it);
                        this->punkte += 25;
                        
                    }
                }
                //Zombie laeuft
                for(auto it = this->listeZombie.begin(); it != this->listeZombie.end(); it++){
                    if(it->getStanding() == false){
                        it->setX(it->getX()+it->getVelocity());
                        it->schritt(game);
                    }
                }
                
                //Schuss bewegt sich
                for(auto it = this->listeShot.begin(); it != this->listeShot.end(); it++){
                    it->setX(it->getX()+it->getVelocity());
                    it->schritt(game); 
                }
                
                //Spiel beenden, wenn ein Zombie das Ziel erreicht
                for(auto it = this->listeZombie.begin(); it != this->listeZombie.end(); it++){
                    if(it->getX() <= this->x){
                        this->endWhile = true;
                    }
                }
                AlgoViz::sleep(100);
                this->counter++;
            }
            
            if(endWhile == true){
                cout << "Game over!";
            }else if(key == "x"){
                cout <<"Das Spiel wurde beendet";
            }else{
                cout << "Sie haben gewonnen";
            }
        }
};//end of class
#endif