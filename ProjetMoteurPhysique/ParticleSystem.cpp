#include "ParticleSystem.h"
#include "ParticleContact.h"
#include "Particule.h"

unsigned ParticleSystem::GenerateContact()
{
	unsigned int max = maxContacts;
	ParticleContact* nextContact = contacts;

	for (ContactGenerator::iterator i = contactGenerators.begin(); i != contactGenerators.end(); ++i)
	{
		unsigned used = (*i)->addContact(nextContact, max);
		max -= used;
		nextContact += used;

		if (max <= 0) break;
	}

	// nb of used contacts
	return maxContacts - max;
}

void ParticleSystem::Intergrate(float duration)
{
	for (Particules::iterator i = particules.begin(); i != particules.end(); ++i)
	{
		double* d = new double(duration);
		integrateur.MiseAJourPositionParticule(*i, d);
		integrateur.MiseAJourVelociteParticule(*i, d);
	}
}

void ParticleSystem::LaunchFrame(float duration)
{
	registre.MiseAJourForce((double)duration);

	Intergrate(duration);

	unsigned usedContacts = GenerateContact();

	if (usedContacts)
	{
		if (calcul)
		{

		}
	}
}