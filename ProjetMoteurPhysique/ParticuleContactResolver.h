#pragma once

class ParticuleContact;

class ParticuleContactResolver
{
public:
	// nb d'iteration accord� pour l'operation
	unsigned iterations;
	unsigned iterationDone;

	ParticuleContactResolver();
	ParticuleContactResolver(unsigned iterations);
	~ParticuleContactResolver();

	void setIterationsNb(unsigned iterations);

	void resolveContacts(ParticuleContact* contactArray, unsigned nbComtact, float duration);

};