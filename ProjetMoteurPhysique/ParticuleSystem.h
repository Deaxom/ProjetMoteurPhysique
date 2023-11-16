#pragma once
#include <vector>
#include "ParticuleForceRegistre.h"
#include "ParticuleContactResolver.h"
#include "ParticuleContactGenerator.h"
#include "Integrateur.h"

class Particule;
class ParticuleContact;
class ParticuleContactResolver;
class ParticuleContactGenerator;
class ParticuleForceRegistre;
class Integrateur;

class ParticuleSystem
{
public:
	typedef std::vector<Particule*> Particules;
	typedef std::vector<ParticuleContactGenerator*> ContactGenerator;

protected:
	Particules particules;

public:
	ParticuleSystem(int nbmaxContacts, unsigned iterations = 0);

	void NewFrame();

	ParticuleForceRegistre registre;

	ParticuleContactResolver resolver;

	ContactGenerator contactGenerators;

	ParticuleContact* contacts;

	Integrateur integrateur;

	unsigned int maxContacts;

	unsigned GenerateContact();

	void Integrate(float duration);

	void LaunchFrame(float duration);

};