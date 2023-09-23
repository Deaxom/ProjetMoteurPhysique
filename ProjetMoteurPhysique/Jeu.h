#pragma once
class Jeu
{
private:
    void GérerEntrées() {
        // Gérer les entrées utilisateur
    }

    void MettreÀJour() {
        // Mettre à jour la simulation (physique, intégration, etc.)
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
            // Gérer les entrées utilisateur
            GérerEntrées();

            // Mettre à jour la simulation (intégration, physique, etc.)
            MettreÀJour();

            // Rendu graphique (OpenGL, ImGui, etc.)
            Rendu();

            // Vérifier si la fenêtre doit être fermée
            if (fenetreDoitFermer) {
                fenetreEstOuverte = false;
            }
        }
    }
};

