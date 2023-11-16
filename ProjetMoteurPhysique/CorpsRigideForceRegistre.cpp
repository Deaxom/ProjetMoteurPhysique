#include "CorpsRigideForceRegistre.h"

CorpsRigideForceRegistre::Registre CorpsRigideForceRegistre::getRegistre()
{
	return m_registre;
}

void CorpsRigideForceRegistre::setRegiste(Registre nouveauRegistre)
{
	m_registre = nouveauRegistre;
}

void CorpsRigideForceRegistre::addCorpsRigideForceRegistre(CorpsRigide* corpsRigide, CorpsRigideGenerateurForce* generateurForce) {
	CorpsRigideForceParametre parametre;
	parametre.corpsRigide = corpsRigide;
	parametre.generateurForce = generateurForce;
	m_registre.push_back(parametre);
}

void CorpsRigideForceRegistre::removeCorpsRigideForceRegistre(CorpsRigide* corpsRigide, CorpsRigideGenerateurForce* generateurForce)
{
	for (auto it = m_registre.begin(); it != m_registre.end(); ++it) {
		if (it->corpsRigide == corpsRigide && it->generateurForce == generateurForce) {
			m_registre.erase(it);
			break;
		}
	}
}

void CorpsRigideForceRegistre::clear()
{
	for (int i = 0; i < m_registre.size(); i++) {
		removeCorpsRigideForceRegistre(m_registre[i].corpsRigide, m_registre[i].generateurForce);
	}
}

void CorpsRigideForceRegistre::MiseAJourForce(double deltaTime) {
	for (int i = 0; i < m_registre.size(); i++) {
		m_registre[i].generateurForce->MiseAJourForce(m_registre[i].corpsRigide, deltaTime);
	}
}