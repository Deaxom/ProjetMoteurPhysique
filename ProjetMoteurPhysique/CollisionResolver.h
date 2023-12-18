#pragma once
class CorpsRigide;
class CollisionData;
class Contact;

class CollisionResolver {
private:
    unsigned iterations;
    unsigned iterationsDone;
public:
    CollisionResolver();
    CollisionResolver(unsigned iterations);
    ~CollisionResolver();
    void setIterationsNb(unsigned iterations);
    void resolveCollision(Contact* contactArray, unsigned nbContact, float duration);
};