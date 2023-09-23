#pragma once
class Jeu
{
private:
    void G�rerEntr�es() {
        // G�rer les entr�es utilisateur
    }

    void Mettre�Jour() {
        // Mettre � jour la simulation (physique, int�gration, etc.)
    }

    void Rendu() {
        // Rendu graphique (OpenGL, ImGui, etc.)
    }

    bool fenetreEstOuverte = true;
    bool fenetreDoitFermer = false;

public:
    Jeu() {
        // Initialisation de votre jeu
    }

    void BoucleDeJeu() {
        while (fenetreEstOuverte) {
            // G�rer les entr�es utilisateur
            G�rerEntr�es();

            // Mettre � jour la simulation (int�gration, physique, etc.)
            Mettre�Jour();

            // Rendu graphique (OpenGL, ImGui, etc.)
            Rendu();

            // V�rifier si la fen�tre doit �tre ferm�e
            if (fenetreDoitFermer) {
                fenetreEstOuverte = false;
            }
        }
    }
};

