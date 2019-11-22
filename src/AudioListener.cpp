#include "HumbugEngine/AudioListener.h"




AudioListener::AudioListener(Vector3 pos, Vector3 speed, std::vector<ALfloat> orientation = { 0.f, 0.f, 1.f, 0.f, 1.f, 0.f })
{
	if (orientation.size() == 6 ) {
		m_orientation = orientation;
		m_pos = pos;
		m_speed = speed;
		// D�finition de la position de l'�couteur (ici l'origine)
		alListener3f(AL_POSITION, m_pos.x, m_pos.y, m_pos.z);
		// D�finition de la vitesse de l'�couteur (ici nulle)
		alListener3f(AL_VELOCITY, m_speed.x, m_speed.y, m_speed.z);
		// D�finition de l'orientation de l'�couteur (ici il regarde vers l'axe des Z)
		alListenerfv(AL_ORIENTATION, &m_orientation[0]);

		std::cout << "Object AudioListener initialise"<<std::endl;
	}
	else {
		std::cout << "Object AudioListener NON initialise" << std::endl;
	}

}

void AudioListener::updateListener(Vector3 pos, Vector3 speed, std::vector<ALfloat> orientation)
{
	if (orientation.size() == 6 ) {
		m_orientation = orientation;
		m_pos = pos;
		m_speed = speed;
		// D�finition de la position de l'�couteur (ici l'origine)
		alListener3f(AL_POSITION, m_pos.x, m_pos.y, m_pos.z);
		// D�finition de la vitesse de l'�couteur (ici nulle)
		alListener3f(AL_VELOCITY, m_speed.x, m_speed.y, m_speed.z);
		// D�finition de l'orientation de l'�couteur (ici il regarde vers l'axe des Z)
		alListenerfv(AL_ORIENTATION, &m_orientation[0]);

	}
	else {
		std::cout << "Object AudioListener error in update" << std::endl;
	}
}
