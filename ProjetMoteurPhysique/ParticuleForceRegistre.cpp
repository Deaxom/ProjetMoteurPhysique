#include "ParticuleForceRegistre.h"

ParticuleForceRegistre::Registre ParticuleForceRegistre::getRegistre()
{
	return m_registre;
}

void ParticuleForceRegistre::setRegiste(Registre nouveauRegistre)
{
	m_registre = nouveauRegistre;
}

void ParticuleForceRegistre::addParticuleForceRegistre(Particule* particule, ParticuleGenerateurForce* generateurForce) {
	ParticuleForceParametre parametre;
	parametre.particule = particule;
	parametre.generateurForce = generateurForce;
	m_registre.push_back(parametre);
}

void ParticuleForceRegistre::removeParticuleForceRegistre(Particule* particule, ParticuleGenerateurForce* generateurForce)
{
	for (auto it = m_registre.begin(); it != m_registre.end(); ++it) {
		if (it->particule == particule && it->generateurForce == generateurForce) {
			m_registre.erase(it);
			break;
		}
	}
}

void ParticuleForceRegistre::clear()
{
	for (int i = 0; i < m_registre.size(); i++) {
		removeParticuleForceRegistre(m_registre[i].particule, m_registre[i].generateurForce);
	}
}

void ParticuleForceRegistre::MiseAJourForce(double deltaTime) {
	for (int i = 0; i < m_registre.size(); i++) {
		m_registre[i].generateurForce->MiseAJourForce(m_registre[i].particule, deltaTime);
	}
}