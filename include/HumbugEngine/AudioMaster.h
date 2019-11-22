#pragma once

#include <al.h>
#include <alc.h>
#include <sndfile.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "HumbugEngine/Object.h"
#include "HumbugEngine/AudioSource.h"

#include "HumbugEngine/AudioListener.h"



#define MASTER AudioMaster::get()

class AudioMaster
{
private:
	std::vector<std::string> m_devices;

	AudioListener m_listener;
	static AudioMaster* singleton;
	std::vector<std::shared_ptr<AudioSource>> m_sources;
	AudioMaster();
public:
	static AudioMaster* get()
	{
		if (!singleton)
			singleton = new AudioMaster();
		return singleton;
	}

	// Recupere la liste des noms des devices disponibles
	// param Devices : Tableau de chaines a remplir avec les noms des devices
	std::vector<std::string> GetDevices();

	// Initialise OpenAL (ouvre un device et cree un contexte audio)
	// param DeviceName : Nom du device a ouvrir (NULL pour le device par defaut)
	// return True si tout s'est bien passe, false en cas d'erreur
	bool InitOpenAL(const char* DeviceName = NULL);

	void setListener(Vector3 pos, Vector3 speed, std::vector<float> orientation);

	void updateListener(Vector3 pos, Vector3 speed, std::vector<float> orientation);

	void addSource(std::shared_ptr<AudioSource> source);

	void showSources();
	// Fermeture d'OpenAL OBLIGATOIRE
	void ShutdownOpenAL();
};
