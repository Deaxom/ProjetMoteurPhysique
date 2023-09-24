#pragma once
class Jeu
{
private:
    bool etat;

public:
    Jeu();
    bool getEtat();
    void setEtat(bool newEtat);
    void start();
    void update();
};

