#pragma once

class ParticleContact;

class ParticleContactResolver
{
public:
	// nb d'iteration accord� pour l'operation
	unsigned iterations;
	unsigned iterationDone;

	ParticleContactResolver(unsigned iterations);

	void setIterationsNb(unsigned iterations);

	void resolveContacts(ParticleContact* contactArray, unsigned nbComtact, float duration);

};