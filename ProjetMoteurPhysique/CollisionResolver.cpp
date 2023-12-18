#include "CollisionResolver.h"
#include "CorpsRigide.h"
#include "CollisionData.h"
#include "Contact.h"

CollisionResolver::CollisionResolver(){
    this->iterations = 1;
    this->iterationsDone = 0;
}

CollisionResolver::CollisionResolver(unsigned iterations) {
    this->iterations = iterations;
    this->iterationsDone = 0;
}

CollisionResolver::~CollisionResolver() {

}

void CollisionResolver::setIterationsNb(unsigned iterations) {
    this->iterations = iterations;
}

void CollisionResolver::resolveCollision(Contact* contactArray, unsigned nbContact, float duration) {
	 unsigned i;

	 iterationsDone = 0;

	 while (iterationsDone < iterations)
	 {
		 float max = 1000.f;

		 unsigned maxIndex = nbContact;

		 for (i = 0; i < nbContact; ++i)
		 {
			 float sepVel = contactArray[i].CalculateSeparatingVelocity();
			 if (sepVel < max && (sepVel < 0 || contactArray[i].penetration > 0))
			 {
				 max = sepVel;
				 maxIndex = i;
			 }
		 }

		 if (maxIndex == nbContact) break;

		 //std::cout << "Contact!" << std::endl;
		 contactArray[maxIndex].Resolve(duration);
		 ++iterationsDone;
	 }
}