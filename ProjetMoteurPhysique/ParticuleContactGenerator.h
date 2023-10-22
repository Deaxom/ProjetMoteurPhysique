#pragma once

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

	// pour eviter de trop etendre le cable
	virtual unsigned addContact(ParticuleContact* contact, unsigned int limit) const;
};

class ParticuleRod : public ParticuleLink
{
public:
	float length;

	virtual unsigned addContact(ParticuleContact* contact, unsigned int limit) const;
};