#include "Jeu.h"
#include "OpenglImGui.h"
#include <iostream>
#include "ParticuleGravite.h"
#include "ParticuleRessortFixe.h"
#include "ParticuleRessort.h"
#include "ParticuleTrainee.h"
#include "ParticuleFlottabilite.h"
#include "CoprsRigide.h"

//Constructeurs
Jeu::Jeu() {
    this->setEtat(false);
    this->setWindow(nullptr);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
    this->contact = new ParticuleContact();
}

Jeu::Jeu(OpenGlImGui* window, Particule* particule) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    this->setParticule(particule);
}

Jeu::Jeu(OpenGlImGui* window) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
}

//GETTERS
bool Jeu::getEtat() {
    return this->etat;
}

OpenGlImGui* Jeu::getWindow() {
    return this->window;
}

double Jeu::getDeltaTime() {
    return this->deltaTime;
}

double Jeu::getLastFrameTime() {
    return this->lastFrameTime;
}

Particule* Jeu::getParticule() {
    return this->particule;
}

std::vector<Particule*> Jeu::getListeParticule() {
    return this->listeParticule;
}

std::vector<CoprsRigide*> Jeu::getListeCorpsRigide()
{
    return this->listeCorpsRigide;
}

//SETTERS
void Jeu::setEtat(bool newEtat) {
    this->etat = newEtat;
}

void Jeu::setWindow(OpenGlImGui* newWindow) {
    this->window = newWindow;
}

void Jeu::setDeltaTime(double newDeltaTime) {
    this->deltaTime = newDeltaTime;
}

void Jeu::setLastFrameTime(double newLastFrameTime) {
    this->lastFrameTime = newLastFrameTime;
}

void Jeu::setParticule(Particule* newParticule) {
    this->particule = newParticule;
}

//Fonction qui d�marre le jeu
void Jeu::start() {
    /*glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);*/
    this->setEtat(true);
    this->setLastFrameTime(glfwGetTime());

    //particule0 La particule reference au centre du monde
    Vecteur3D positionParticuleReference(0, 2, 0);
    Vecteur3D vitesseParticuleReference(0, 0, 0);
    Vecteur3D accelerationReference(0, 0, 0);
    Quaternion orientationReference(0,0,0,0);

    CoprsRigide* particuleReference = new CoprsRigide(positionParticuleReference, vitesseParticuleReference, accelerationReference, 10000, orientationReference, Vecteur3D(0,0,0));

    //particule1 Particule soumise � la force de gravite
    Vecteur3D positionParticuleGravite(2.3f, 2, 0);
    Vecteur3D vitesseParticuleGravite(0, 0, 0);
    Vecteur3D accelerationGravite(0, 0, 0);
    Quaternion orientationGravite(10.f,20.f,30.f,40.f);

    CoprsRigide* particuleGravite = new CoprsRigide(positionParticuleGravite, vitesseParticuleGravite, accelerationGravite, 10, orientationGravite, Vecteur3D(50,10,10));

#pragma region Particule
    /*//particule2 sur lequel on applique la force de traine
    Vecteur3D positionParticuleTraine(-2, 0, 0);
    Vecteur3D vitesseParticuleTraine(0, 0, 0);
    Vecteur3D accelerationTraine(5, 0, 0);

    Particule* particuleTraine = new Particule(positionParticuleTraine, vitesseParticuleTraine, accelerationTraine, 10, true);

    //particule3 sur lequel on applique la force de ressort fixe
    Vecteur3D positionParticuleRessortFixe(1, 3, 0);
    Vecteur3D vitesseParticuleRessortFixe(0, 0, 0);
    Vecteur3D accelerationRessortFixe(0.2, 0, 0);

    Particule* particuleRessortFixe = new Particule(positionParticuleRessortFixe, vitesseParticuleRessortFixe, accelerationRessortFixe, 10, true);

    //particule4 particule sur lequel on applique la force ressort
    Vecteur3D positionParticuleRessort(-3, -2, 0);
    Vecteur3D vitesseParticuleRessort(0, 0, 0);
    Vecteur3D accelerationRessort(0, -1, 0);

    Particule* particuleRessort = new Particule(positionParticuleRessort, vitesseParticuleRessort, accelerationRessort, 10, true);

    //particule5 autre particule pour la force ressort
    Vecteur3D positionAutreParticuleRessort(-3, 0, 0);
    Vecteur3D vitesseAutreParticuleRessort(0, 0, 0);
    Vecteur3D accelerationAutreRessort(0, 0, 0);

    Particule* autreParticuleRessort = new Particule(positionAutreParticuleRessort, vitesseAutreParticuleRessort, accelerationAutreRessort, 10, true);

    //particule6 sur lequel va s'appliquer la force de flotabilite
    Vecteur3D positionParticuleFlotabilite(4, -2, 0);
    Vecteur3D vitesseParticuleFlotabilite(0, 0, 0);
    Vecteur3D accelerationFlotabilite(0, 0, 0);

    Particule* ParticuleFlotabilite = new Particule(positionParticuleFlotabilite, vitesseParticuleFlotabilite, accelerationFlotabilite, 10, true);

    //On cree la force de gravite et on la lie � la particule gravite | -98.1 pour la terre
    ParticuleGravite *forceGravite = new ParticuleGravite(0.0, -98.1, 0.0);
    ParticuleGravite *forceGraviteBis = new ParticuleGravite(0.0, 98.1, 0.0);
    this->forceRegistre.addParticuleForceRegistre(particuleGravite, forceGravite);


    //On cree la force de traine et on la lie � la particule traine
    ParticuleTrainee* forceTrainee = new ParticuleTrainee(1.5f, 13.6f);
    this->forceRegistre.addParticuleForceRegistre(particuleTraine, forceTrainee);

    //On cree la force de ressort fixe avec une position fixe sur 0,0,0 et on la lie � la particule ressort fixe
    Vecteur3D positionFixe(0, 2, 0);
    float k = 1;
    float restLenght = 3;
    ParticuleRessortFixe* forceRessortFixe = new ParticuleRessortFixe(positionFixe, k, restLenght);
    this->forceRegistre.addParticuleForceRegistre(particuleRessortFixe, forceRessortFixe);

    //On cree la force de ressort et on la lie � la particule de ressort ainsi que l'autre particule
    ParticuleRessort* forceRessort = new ParticuleRessort(autreParticuleRessort, k, restLenght);
    this->forceRegistre.addParticuleForceRegistre(particuleRessort, forceRessort);


    //On cree la force de flotabilite et on la lie � la particule de flotabilite
    ParticuleFlottabilite* forceFlotabilite = new ParticuleFlottabilite(-2, 1, 1, 1);
    this->forceRegistre.addParticuleForceRegistre(ParticuleFlotabilite, forceFlotabilite);

    //On initialise un lien de contact entre deux particules
    ParticuleContact *_contact = new ParticuleContact;
    contact = new ParticuleContact;

    _contact->particules[0] = particuleGravite;
    _contact->particules[1] = particuleReference;

    //On ajoute ce lien dans un type de detection de collision
    //ParticuleRod rod(contact, 2.f);
    ParticuleCable* cable = new ParticuleCable(_contact, 2.5f, 0.5f);
    ParticuleRod* rod = new ParticuleRod(_contact, 2.f);

    contactGenerators.push_back(cable);*/
#pragma endregion

    //On ajoute tout les particules � une liste pour ensuite les afficher graphiquement
    //avec la methode de mise a jour de la class camera (qui est utilise dans le main)
    this->listeCorpsRigide = { particuleReference, particuleGravite/*, particuleTraine, particuleRessortFixe, particuleRessort, autreParticuleRessort, ParticuleFlotabilite*/ };
    
    /*NaiveParticuleContactGenerator* naive = new NaiveParticuleContactGenerator(1.f, listeParticule);

    contactGenerators.push_back(naive);

    WallContactGenerator* ground = new WallContactGenerator(-3.f, 10.f, 0.f, listeParticule);

    contactGenerators.push_back(ground);*/
}

//Fonction qui update le jeu � chaque unit� de temps
void Jeu::update() {
    if (etat) {
        double currentFrame = glfwGetTime();
        //this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setDeltaTime(0.008);
        this->setLastFrameTime(currentFrame);

        //Le registre applique les forces sur les particules
        forceRegistre.MiseAJourForce(deltaTime);

        /*std::cout << contact->particules[0]->getAcceleration().getY() << std::endl;
        std::cout << contact->particules[0]->getVitesse().getY() << std::endl;*/

        // Methode pour Particules
        /*for (std::vector<Particule*>::iterator i = listeParticule.begin(); i != listeParticule.end(); ++i)
        {
            integrateur.MiseAJourPositionParticule(*i, &deltaTime);
            integrateur.MiseAJourVelociteParticule(*i, &deltaTime);
        }*/

        // Methode pour CorpsRigides
        /*for (std::vector<CoprsRigide*>::iterator i = listeCorpsRigide.begin(); i != listeCorpsRigide.end(); ++i)
        {
            (*i)->MiseAJourCorps(deltaTime);
        }*/
        listeCorpsRigide[1]->MiseAJourCorps(deltaTime);

        //Iteration sur tout les link
        for (ContactGenerator::iterator i = contactGenerators.begin(); i != contactGenerators.end(); ++i)
        {
            if ((*i)->addContact(contact, 1))
            {
                resolver.resolveContacts(contact, 1, deltaTime);
            }
        }
    }
}

//Fonction qui arr�te le jeu
void Jeu::stop() {
    //...
    this->setEtat(false);
}