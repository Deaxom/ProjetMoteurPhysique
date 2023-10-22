#pragma once
#include <vector>
#include "ParticuleForceRegistre.h"
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"
#include "Integrateur.h"

class Particule;
class ParticleContact;
class ParticleContactResolver;
class ParticleContactGenerator;
class ParticuleForceRegistre;
class Integrateur;

class ParticleSytem
{
public:
	typedef std::vector<Particule*> Particules;
	typedef std::vector<ParticleContactGenerator*> ContactGenerator;

protected:
	Particules particules;

public:
	ParticleSytem(int nbmaxContacts, unsigned iterations = 0);

	void NewFrame();

	ParticuleForceRegistre registre;

	ParticleContactResolver resolver;

	ContactGenerator contactGenerators;

	ParticleContact* contacts;

	Integrateur integrateur;

	unsigned int maxContacts;

	unsigned GenerateContact();

	void Intergrate(float duration);

	void LaunchFrame(float duration);

};