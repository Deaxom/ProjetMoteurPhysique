#pragma once
#include <vector>

class ParticuleContact;
class Particule;

class ParticuleContactGenerator
{
public:
	// recuperer un array de contact et le nombre de contact restant à generer
	virtual unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;
};

class ParticuleLink : public ParticuleContactGenerator
{
public:
	ParticuleLink();
	~ParticuleLink();

	Particule* particules[2];
	
	// link list length
	float currentLength() const;

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const = 0;
};

class ParticuleCable : public ParticuleLink
{
public:
	// longeur max du cable entre deux particules
	float maxLength;

	// value 0-1 elasticit� pour la "rebondassibilit�"
	// 1 = collision parfaitement �lastique, 0 perte d'�nergie
	// 0 < e < 1 = collision partiellement elastique, perte partielle d'�nergie
	//0 = coolision non elastique, energie cin�tique perdue
	float restitution;

	ParticuleCable(ParticuleContact* contact, float maxLength, float restitution);
	~ParticuleCable();

	// pour eviter de trop etendre le cable
	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

class ParticuleRod : public ParticuleLink
{
public:
	float length;

	ParticuleRod(ParticuleContact* contact, float Length);
	~ParticuleRod();

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

class NaiveParticuleContactGenerator : public ParticuleContactGenerator
{
public:
	float radius;

	std::vector<Particule*> particules;

	NaiveParticuleContactGenerator(float _radius, std::vector<Particule*> _particules);
	~NaiveParticuleContactGenerator();

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};

class WallContactGenerator : public ParticuleContactGenerator
{
public:
	float groundHeight;
	float wallMinX;
	float wallMinY;

	std::vector<Particule*> particules;

	WallContactGenerator(float _groundHeight, float wallMinX, float wallMinZ, std::vector<Particule*> _particules);
	~WallContactGenerator();

	unsigned int addContact(ParticuleContact* contact, unsigned int limit) const;
};