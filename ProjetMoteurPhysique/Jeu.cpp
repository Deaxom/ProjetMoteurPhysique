#include "Jeu.h"
#include "OpenglImGui.h"
#include <iostream>

#include "collide_narrow.h"
#include "CollisionData.h"
#include "Contact.h"
#include "ParticuleGravite.h"
#include "ParticuleRessortFixe.h"
#include "ParticuleRessort.h"
#include "ParticuleTrainee.h"
#include "ParticuleFlottabilite.h"
#include "CorpsRigide.h"
#include "CorpsRigideRessortFixe.h"
#include "CorpsRigideFlottabilite.h"
#include "CorpsRigideGravite.h"
#include "CorpsRigideRessort.h"
#include "CorpsRigideTrainee.h"
#include "Octree.h"
#include "Plane.h"
#include "PrimitiveInSet.h"
#include "Sphere.h"
#include "Box.h"


//Constructeurs
Jeu::Jeu() {
    this->setEtat(false);
    this->setWindow(nullptr);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
    this->contact = new ParticuleContact();
    this->collisionData = new CollisionData;
}

Jeu::Jeu(OpenGlImGui* window, Particule* particule) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    this->setParticule(particule);
    this->collisionData = new CollisionData;
}

Jeu::Jeu(OpenGlImGui* window) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
    this->collisionData = new CollisionData;
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

std::vector<CorpsRigide*> Jeu::getListeCorpsRigide()
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

#pragma region Particule

    ////particule0 La particule reference au centre du monde
    //Vecteur3D positionParticuleReference(0, 2, 0);
    //Vecteur3D vitesseParticuleReference(0, 0, 0);
    //Vecteur3D accelerationReference(0, 0, 0);

    //Particule* particuleReference = new Particule(positionParticuleReference, vitesseParticuleReference, accelerationReference, 1000, true);

    ////particule1 Particule soumise la force de gravite
    //Vecteur3D positionParticuleGravite(2, 2, 0);
    //Vecteur3D vitesseParticuleGravite(0, 0, 0);
    //Vecteur3D accelerationGravite(0, 0, 0);

    //Particule* particuleGravite = new Particule(positionParticuleGravite, vitesseParticuleGravite, accelerationGravite, 10, true);

    ////particule2 sur lequel on applique la force de traine
    //Vecteur3D positionParticuleTraine(2, 0, 0);
    //Vecteur3D vitesseParticuleTraine(0, 0, 0);
    //Vecteur3D accelerationTraine(15, 0, 0);

    //Particule* particuleTraine = new Particule(positionParticuleTraine, vitesseParticuleTraine, accelerationTraine, 10, true);

  
    ////particule3 sur lequel on applique la force de ressort fixe
    //Vecteur3D positionParticuleRessortFixe(1, 3, 0);
    //Vecteur3D vitesseParticuleRessortFixe(0, 0, 0);
    //Vecteur3D accelerationRessortFixe(0.2, 0, 0);

    //Particule* particuleRessortFixe = new Particule(positionParticuleRessortFixe, vitesseParticuleRessortFixe, accelerationRessortFixe, 10, true);

    ////particule4 particule sur lequel on applique la force ressort
    //Vecteur3D positionParticuleRessort(-3, -2, 0);
    //Vecteur3D vitesseParticuleRessort(0, 0, 0);
    //Vecteur3D accelerationRessort(0, -1, 0);

    //Particule* particuleRessort = new Particule(positionParticuleRessort, vitesseParticuleRessort, accelerationRessort, 10, true);

    ////particule5 autre particule pour la force ressort
    //Vecteur3D positionAutreParticuleRessort(-3, 0, 0);
    //Vecteur3D vitesseAutreParticuleRessort(0, 0, 0);
    //Vecteur3D accelerationAutreRessort(0, 0, 0);

    //Particule* autreParticuleRessort = new Particule(positionAutreParticuleRessort, vitesseAutreParticuleRessort, accelerationAutreRessort, 10, true);

    ////particule6 sur lequel va s'appliquer la force de flotabilite
    //Vecteur3D positionParticuleFlotabilite(4, -2, 0);
    //Vecteur3D vitesseParticuleFlotabilite(0, 0, 0);
    //Vecteur3D accelerationFlotabilite(0, 0, 0);

    //Particule* ParticuleFlotabilite = new Particule(positionParticuleFlotabilite, vitesseParticuleFlotabilite, accelerationFlotabilite, 10, true);

    ////On cree la force de gravite et on la lie � la particule gravite | -98.1 pour la terre
    //ParticuleGravite *forceGravite = new ParticuleGravite(0.0, -98.1, 0.0);
    //ParticuleGravite *forceGraviteBis = new ParticuleGravite(0.0, 98.1, 0.0);
    //this->forceRegistre.addParticuleForceRegistre(particuleGravite, forceGravite);


    //On cree la force de traine et on la lie � la particule traine
    //ParticuleTrainee* forceTrainee = new ParticuleTrainee(1.5f, 13.6f);
    //this->forceRegistre.addParticuleForceRegistre(particuleTraine, forceTrainee);

    //this->listeParticule = { particuleTraine };

    ////On cree la force de ressort fixe avec une position fixe sur 0,0,0 et on la lie � la particule ressort fixe
    //Vecteur3D positionFixe(0, 2, 0);
    //float k = 1;
    //float restLenght = 3;
    //ParticuleRessortFixe* forceRessortFixe = new ParticuleRessortFixe(positionFixe, k, restLenght);
    //this->forceRegistre.addParticuleForceRegistre(particuleRessortFixe, forceRessortFixe);

    ////On cree la force de ressort et on la lie � la particule de ressort ainsi que l'autre particule
    //ParticuleRessort* forceRessort = new ParticuleRessort(autreParticuleRessort, k, restLenght);
    //this->forceRegistre.addParticuleForceRegistre(particuleRessort, forceRessort);


    ////On cree la force de flotabilite et on la lie � la particule de flotabilite
    //ParticuleFlottabilite* forceFlotabilite = new ParticuleFlottabilite(-2, 1, 1, 1);
    //this->forceRegistre.addParticuleForceRegistre(ParticuleFlotabilite, forceFlotabilite);

    ////On initialise un lien de contact entre deux particules
    //ParticuleContact *_contact = new ParticuleContact;
    //contact = new ParticuleContact;

    //_contact->particules[0] = particuleGravite;
    //_contact->particules[1] = particuleReference;

    ////On ajoute ce lien dans un type de detection de collision
    ////ParticuleRod rod(contact, 2.f);
    //ParticuleCable* cable = new ParticuleCable(_contact, 2.5f, 0.5f);
    //ParticuleRod* rod = new ParticuleRod(_contact, 2.f);

    //contactGenerators.push_back(cable);

        //On ajoute tout les particules dans une liste pour ensuite les afficher graphiquement
    //avec la methode de mise a jour de la class camera (qui est utilise dans le main)
    //this->listeParicule = { particuleReference, particuleGravite, particuleTraine, particuleRessortFixe, particuleRessort, autreParticuleRessort, ParticuleFlotabilite};
    //
    //    NaiveParticuleContactGenerator* naive = new NaiveParticuleContactGenerator(1.f, listeParticule);

    //contactGenerators.push_back(naive);

    //WallContactGenerator* ground = new WallContactGenerator(-3.f, 10.f, 0.f, listeParticule);

    //contactGenerators.push_back(ground);
    
#pragma endregion

#pragma region CorpsRigide
    //CorpsRigide0 CorpsRigide reference au centre du monde
    Vecteur3D positionCorpsRigideReference(0, 0, 0);
    Vecteur3D vitesseCorpsRigideReference(0, 0, 0);
    Vecteur3D accelerationReference(0, 0, 0);
    Quaternion orientationReference(0, 0, 0, 0);
    Vecteur3D velociteAngulaireReference(0, 0, 0);
    Vecteur3D accelerationAngulaireReference(0, 0, 0);
    Matrix3x3 tenseurInertieReference({ 3, 2, 2,
                                        1, 2, 1,
                                        1, 1, 1
                                     });

    CorpsRigide* corpsRigideReference = new CorpsRigide(positionCorpsRigideReference, vitesseCorpsRigideReference, accelerationReference, 10000, orientationReference, velociteAngulaireReference, accelerationAngulaireReference, tenseurInertieReference, "corpsRigideReference");
    // Ajout d'une primitive plane sur le RigideBody Ref car ne bouge pas (PrimitiveSet à l'avenir)
    /*Plane* plane = new Plane(Vecteur3D(0.0, 1.0, 0.0), 0.5f);
    plane->corpsRigide = corpsRigideReference;
    corpsRigideReference->primitive = plane;*/
    Sphere* sphere2 = new Sphere(0.5f);
    sphere2->corpsRigide = corpsRigideReference;
    corpsRigideReference->primitive = sphere2;

    /*CorpsRigideGravite* forceGraviteCorpsRigide1 = new CorpsRigideGravite(0, 1, 0);

    this->corpsRigideForceRegistre.addCorpsRigideForceRegistre(corpsRigideReference, forceGraviteCorpsRigide1);*/
    
    //CorpsRigide1 CorpsRigide test orientation a 180 degree
    Vecteur3D positionCorpsRigideOrientation(0, 2, 0);
    Vecteur3D vitesseCorpsRigideOrientation(0, 0, 0);
    Vecteur3D accelerationOrientation(0, 0, 0);
    Quaternion orientationOrientation(0, 1, 0, 0); // on change l'orientation de 180 degree
    Vecteur3D velociteAngulaireOrientation(0, 0, 0);
    Vecteur3D accelerationAngulaireOrientation(0, 0, 0);
    Matrix3x3 tenseurInertieOrientation({ 3, 0, 0,      0, 2, 0,    0, 0, 1});

    CorpsRigide* corpsRigideOrientation = new CorpsRigide(positionCorpsRigideOrientation, vitesseCorpsRigideOrientation, accelerationOrientation, 10, orientationOrientation, velociteAngulaireOrientation, accelerationAngulaireOrientation, tenseurInertieOrientation, "corpsRigideOrientation");


    Plane* plane1 = new Plane(Vecteur3D(0.0, 1.0, 0.0), 0.5f);
    plane1->corpsRigide = corpsRigideOrientation;
    corpsRigideOrientation->primitive = plane1;

    //CorpsRigide2 CorpsRigide de test rotation
    Vecteur3D positionCorpsRigideRotation(0, 4, 0);
    Vecteur3D vitesseCorpsRigideRotation(0, 0, 0);
    Vecteur3D accelerationRotation(0, 0, 0);
    Quaternion orientationRotation(1, 1, 1, 0);
    Vecteur3D velociteAngulaireRotation(0, 0, 0);
    Vecteur3D accelerationAngulaireRotation(1, 0, 0);
    Matrix3x3 tenseurInertieRotation({ 3, 3, 3,      3, 2, 3,    3, 3, 1 });

    CorpsRigide* corpsRigideRotation = new CorpsRigide(positionCorpsRigideRotation, vitesseCorpsRigideRotation, accelerationRotation, 10, orientationRotation, velociteAngulaireRotation, accelerationAngulaireRotation, tenseurInertieRotation, "corpsRigideRotation");

    Plane* plane2 = new Plane(Vecteur3D(0.0, 1.0, 0.0), 0.5f);
    plane2->corpsRigide = corpsRigideRotation;
    corpsRigideRotation->primitive = plane2;

    //CorpsRigide3 CorpsRigide soumise la force de gravite
    Vecteur3D positionCorpsRigideGravite(0, 4, 0);
    Vecteur3D vitesseCorpsRigideGravite(0, 0, 0);
    Vecteur3D accelerationGravite(0, 0, 0);
    Quaternion orientationGravite(0, 0, 0, 0);
    Vecteur3D velociteAngulaireGravite(0, 0, 0);
    Vecteur3D accelerationAngulaireGravite(0, 0, 0);
    Matrix3x3 tenseurInertieGravite({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideGravite = new CorpsRigide(positionCorpsRigideGravite, vitesseCorpsRigideGravite, accelerationGravite, 10, orientationGravite, velociteAngulaireGravite, accelerationAngulaireGravite, tenseurInertieGravite, "corpsRigideGravite");
    // Ajout d'une primitive sphere sur le RigideBody gravity (PrimitiveSet à l'avenir)
    /*Sphere* sphere = new Sphere(0.5f);
    sphere->corpsRigide = corpsRigideGravite;
    corpsRigideGravite->primitive = sphere;*/
    Box* box = new Box(Vecteur3D(0.5f, 0.5f, 0.5f));
    box->corpsRigide = corpsRigideGravite;
    box->offset = corpsRigideGravite->getTransmationMatrice();
    corpsRigideGravite->primitive = box;
    
    CorpsRigideGravite* forceGraviteCorpsRigide = new CorpsRigideGravite(0, -1, 0);

    this->corpsRigideForceRegistre.addCorpsRigideForceRegistre(corpsRigideGravite, forceGraviteCorpsRigide);

    //CorpsRigide4 CorpsRigide soumise la force ressort fixe
    Vecteur3D positionCorpsRigideRessortFixe(-3, 1, 0);
    Vecteur3D vitesseCorpsRigideRessortFixe(0, 0, 0);
    Vecteur3D accelerationRessortFixe(0.2, 0, 0);
    Quaternion orientationRessortFixe(0, 0, 0, 0);
    Vecteur3D velociteAngulaireRessortFixe(0, 0, 0);
    Vecteur3D accelerationAngulaireRessortFixe(0, 0, 0);
    Matrix3x3 tenseurInertieRessortFixe({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideRessortFixe = new CorpsRigide(positionCorpsRigideRessortFixe, vitesseCorpsRigideRessortFixe, accelerationRessortFixe, 10, orientationRessortFixe, velociteAngulaireRessortFixe, accelerationAngulaireRessortFixe, tenseurInertieRessortFixe, "corpsRigideRessortFixe");
    
    Sphere* sphere3 = new Sphere(0.5f);
    sphere3->corpsRigide = corpsRigideRessortFixe;
    corpsRigideRessortFixe->primitive = sphere3;


    //On cree la force de ressort fixe pour corps rigide avec une position fixe sur 0,0,0
    Vecteur3D positionFixe(-4, 0, 0);
    float k = 1;
    float restLenght = 3;
    CorpsRigideRessortFixe* ressortFixeCorpsRigide = new CorpsRigideRessortFixe(positionFixe, k, restLenght);

    //On applique la force de ressort fixe au corps
    this->corpsRigideForceRegistre.addCorpsRigideForceRegistre(corpsRigideRessortFixe, ressortFixeCorpsRigide);

    //CorpsRigide5 CorpsRigide soumise la force ressort
    Vecteur3D positionCorpsRigideRessort(-3, -2, 0);
    Vecteur3D vitesseCorpsRigideRessort(0, 0, 0);
    Vecteur3D accelerationRessort(0, -1, 0);
    Quaternion orientationRessort(0, 0, 0, 0);
    Vecteur3D velociteAngulaireRessort(0, 0, 0);
    Vecteur3D accelerationAngulaireRessort(0, 0, 0);
    Matrix3x3 tenseurInertieRessort({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideRessort = new CorpsRigide(positionCorpsRigideRessort, vitesseCorpsRigideRessort, accelerationRessort, 10, orientationRessort, velociteAngulaireRessort, accelerationAngulaireRessort, tenseurInertieRessort, "corpsRigideRessort");

    Sphere* sphere4 = new Sphere(0.5f);
    sphere4->corpsRigide = corpsRigideRessort;
    corpsRigideRessort->primitive = sphere4;

    //CorpsRigide6 CorpsRigide autre soumise la force ressort
    Vecteur3D positionCorpsRigideRessortAutre(-3, 0, 0);
    Vecteur3D vitesseCorpsRigideRessortAutre(0, 0, 0);
    Vecteur3D accelerationRessortAutre(0, 0, 0);
    Quaternion orientationRessortAutre(0, 0, 0, 0);
    Vecteur3D velociteAngulaireRessortAutre(0, 0, 0);
    Vecteur3D accelerationAngulaireRessortAutre(0, 0, 0);
    Matrix3x3 tenseurInertieRessortAutre({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideRessortAutre = new CorpsRigide(positionCorpsRigideRessortAutre, vitesseCorpsRigideRessortAutre, accelerationRessortAutre, 10, orientationRessortAutre, velociteAngulaireRessortAutre, accelerationAngulaireRessortAutre, tenseurInertieRessortAutre, "corpsRigideRessortAutre");

    Sphere* sphere5 = new Sphere(0.5f);
    sphere5->corpsRigide = corpsRigideRessortAutre;
    corpsRigideRessortAutre->primitive = sphere5;

    //On cree la force de ressort pour les deux corps
    CorpsRigideRessort* ressortCorpsRigide = new CorpsRigideRessort(corpsRigideRessortAutre, k, restLenght);

    //On applique la force de ressort au deux corps
    this->corpsRigideForceRegistre.addCorpsRigideForceRegistre(corpsRigideRessort, ressortCorpsRigide);

    //CorpsRigide7 CorpsRigide soumise la force de la trainee
    Vecteur3D positionCorpsRigideTrainee(0, -2 , 0);
    Vecteur3D vitesseCorpsRigideTrainee(0, 0, 0);
    Vecteur3D accelerationTrainee(80, 0, 0);
    Quaternion orientationTrainee(0, 0, 0, 0);
    Vecteur3D velociteAngulaireTrainee(0, 0, 0);
    Vecteur3D accelerationAngulaireTrainee(0, 0, 0);
    Matrix3x3 tenseurInertieTrainee({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideTrainee = new CorpsRigide(positionCorpsRigideTrainee, vitesseCorpsRigideTrainee, accelerationTrainee, 10, orientationTrainee, velociteAngulaireTrainee, accelerationAngulaireTrainee, tenseurInertieTrainee, "corpsRigideTrainee");

    Sphere* sphere6 = new Sphere(0.5f);
    sphere6->corpsRigide = corpsRigideTrainee;
    corpsRigideTrainee->primitive = sphere6;

    //On cree la force de trainee
    CorpsRigideTrainee* forceTraineeCorpsRigide = new CorpsRigideTrainee(1.5f, 13.6f);

    //On applique la force de trainee
    this->corpsRigideForceRegistre.addCorpsRigideForceRegistre(corpsRigideTrainee, forceTraineeCorpsRigide);

    //CorpsRigide8 CorpsRigide soumis à l'utilisateur
    Vecteur3D positionCorpsRigideUtilisateur(5, 4, 0);
    Vecteur3D vitesseCorpsRigideUtilisateur(0, 0, 0);
    Vecteur3D accelerationUtilisateur(0, 0, 0);
    Quaternion orientationUtilisateur(0, 0, 0, 0);
    Vecteur3D velociteAngulaireUtilisateur(0, 0, 0);
    Vecteur3D accelerationAngulaireUtilisateur(0, 0, 0);
    Matrix3x3 tenseurInertieUtilisateur({ 3, 0, 0,      0, 2, 0,    0, 0, 1 });

    CorpsRigide* corpsRigideUtilisateur = new CorpsRigide(positionCorpsRigideUtilisateur, vitesseCorpsRigideUtilisateur, accelerationUtilisateur, 10, orientationUtilisateur, velociteAngulaireUtilisateur, accelerationAngulaireUtilisateur, tenseurInertieUtilisateur, "corpsRigideUtilisateur");

    Sphere* sphere7 = new Sphere(0.5f);
    sphere7->corpsRigide = corpsRigideUtilisateur;
    corpsRigideUtilisateur->primitive = sphere7;

    //On ajoute tous les Corps Rigides dans une liste pour ensuite les afficher graphiquement
    //avec la methode de mise a jour de la class camera (qui est utilise dans le main)
    this->listeCorpsRigide = { corpsRigideReference,corpsRigideOrientation, corpsRigideRotation, corpsRigideGravite,  corpsRigideRessortFixe, corpsRigideRessort, corpsRigideRessortAutre, corpsRigideTrainee, corpsRigideUtilisateur }; //si on enleve le dernier, enlever la partie dans main avec [2] pour ne pas crash
#pragma endregion
}

//Fonction qui update le jeu a chaque unit� de temps
void Jeu::update() {
    if (etat) {
        double currentFrame = glfwGetTime();
        //this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setDeltaTime(0.008);
        this->setLastFrameTime(currentFrame);

#pragma region ParticuleMiseAJour

        //Le registre applique les forces sur les particules
        //forceRegistre.MiseAJourForce(deltaTime);

        /*std::cout << contact->particules[0]->getAcceleration().getY() << std::endl;
        std::cout << contact->particules[0]->getVitesse().getY() << std::endl;*/

        // Methode pour Particules
        //for (std::vector<Particule*>::iterator i = listeParticule.begin(); i != listeParticule.end(); ++i)
        //{
        //    integrateur.MiseAJourPositionParticule(*i, &deltaTime);
        //    integrateur.MiseAJourVelociteParticule(*i, &deltaTime);
        //}
#pragma endregion

        corpsRigideForceRegistre.MiseAJourForce(deltaTime);

        // Initialisation octree
        Octree octree;
        Noeud* arbre = octree.construireOctree(Vecteur3D(-1, -1, -1), 10.f, 1);
        
        for (std::vector<CorpsRigide*>::iterator i = listeCorpsRigide.begin(); i != listeCorpsRigide.end(); ++i)
        {
            // 1 Maj Position
            integrateur.MiseAJourPositionCorpsRigide(*i, &deltaTime);
            // Ajout CropsRigide à l'octree
            octree.InsererCorpsRigideOctree(arbre, *i);
        }

        // 2 Collision
        // Broad-Phase by Octree
        octree.DetecterCollisionsPotentielles(arbre, &listPairCollider);
        // Narrow-Phase
        collisionData->contactLeft = listPairCollider.size();
        for (auto pair : listPairCollider)
        {
            collider.CheckRealCollision(*pair.first->primitive, *pair.second->primitive, collisionData);
        }

        mainList = collisionData->contacts;
        
        for (auto data : collisionData->contacts) {
            resolverCorpsRigide.resolveCollision(data, 1, deltaTime);
        }

        for (std::vector<CorpsRigide*>::iterator i = listeCorpsRigide.begin(); i != listeCorpsRigide.end(); ++i)
        {
            // 3 Maj Acceleration
            integrateur.MiseAJourForceCorpsRigide(*i, &deltaTime);
            // 4 Maj Vitesse
            integrateur.MiseAJourVitesseCorpsRigide(*i, &deltaTime);
        }

        // Nettoyage liste de Contacts.*
        if (!collisionData->contacts.empty())
        {
            collisionData->contacts.clear();
            collisionData->contactLeft = 0;
        }

        // Nettoyage liste des pairs de Corps-Rigide.*
        if (!listPairCollider.empty())
        {
            listPairCollider.clear();
        }

        // PrimitiveSet Version Test
        /*PrimitiveInSet sphereInSet01 = {&sphere1, Matrix3x4()};
        PrimitiveInSet sphereInSet02 = {&sphere2, Matrix3x4()};
        
        
        PrimitiveSet set01, set02;
        set01.primitives.push_back(sphereInSet01);
        set01.corpsRigide = set01.primitives.front().primitive->corpsRigide;
        set02.primitives.push_back(sphereInSet02);
        set02.corpsRigide = set02.primitives.front().primitive->corpsRigide;*/
        
        //collider.generateContacts(sphere1, sphere2, collisionData);

        
        //std::cout << "accel angul: " << listeCorpsRigide[2]->getAccelerationAngulaire().getX() << std::endl;
        //std::cout << "vit angul: " << listeCorpsRigide[2]->getVelociteAngulaire().getX() << std::endl;
        //Iteration sur tout les link
        //for (ContactGenerator::iterator i = contactGenerators.begin(); i != contactGenerators.end(); ++i)
        //{
        //    if ((*i)->addContact(contact, 1))
        //    {
        //        resolver.resolveContacts(contact, 1, deltaTime);
        //    }
        //}
    }
}

//Fonction qui arr�te le jeu
void Jeu::stop() {
    //...
    this->setEtat(false);
}

std::vector<Contact*>* Jeu::GetCollisionList()
{
    return &mainList;
}
