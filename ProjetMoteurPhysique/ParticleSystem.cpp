#include "ParticleSystem.h"
#include "ParticleContact.h"
#include "Particule.h"

unsigned ParticleSytem::GenerateContact()
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

void ParticleSytem::Intergrate(float duration)
{
	for (Particules::iterator i = particules.begin(); i != particules.end(); ++i)
	{
		double* d = new double(duration);
		integrateur.MiseAJourPositionParticule(*i, d);
		integrateur.MiseAJourVelociteParticule(*i, d);
		delete d;
	}
}

void ParticleSytem::LaunchFrame(float duration)
{
	registre.MiseAJourForce((double)duration);

	Intergrate(duration);

	unsigned usedContacts = GenerateContact();

	if (usedContacts)
	{
		if (true) // si nb iteration non defini
		{
			resolver.setIterationsNb(usedContacts * 2);
		}
		resolver.resolveContacts(contacts, usedContacts, duration);
	}
}