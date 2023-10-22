#include "ParticuleContactResolver.h"
#include "ParticuleContact.h"

ParticuleContactResolver::ParticuleContactResolver(unsigned iterations)
{
	this->iterations = iterations;
	this->iterationDone = 0;
}

void ParticuleContactResolver::setIterationsNb(unsigned iterations)
{
	this->iterations = iterations;
}

void ParticuleContactResolver::resolveContacts(ParticuleContact* contactArray, unsigned nbComtact, float duration)
{
	unsigned i;

	iterationDone = 0;

	while (iterationDone < iterations)
	{
		float max = 1000.f;

		unsigned maxIndex = nbComtact;

		for (i = 0; i < nbComtact; ++i)
		{
			float sepVel = contactArray[i].CalculateSeparatingVelocity();
			if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex == nbComtact) break;

		contactArray[maxIndex].Resolve(duration);
		++iterationDone;
	}

}
