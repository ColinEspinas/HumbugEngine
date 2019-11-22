#include "HumbugEngine/AudioMaster.h"

AudioMaster* AudioMaster::singleton = nullptr;

AudioMaster::AudioMaster()
{
	// Recuperation des devices
	m_devices = GetDevices();

	// On affiche la liste a l'utilisateur
	//std::cout << "Veuillez choisir un device :" << std::endl << std::endl;
	//for (std::size_t i = 0; i < m_devices.size(); ++i)
		//std::cout << "[" << i << "] " << m_devices[i] << std::endl;

	int Choice = 0;
	//std::cin >> Choice;

	// Initialisation d'OpenAL
	InitOpenAL(m_devices[Choice].c_str());

}

std::vector<std::string> AudioMaster::GetDevices()
{
	m_devices.clear();

	// Recupuration des devices disponibles
	const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

	if (DeviceList)
	{
		// Extraction des devices contenus dans la chaine renvoyee
		while (strlen(DeviceList) > 0)
		{
			m_devices.push_back(DeviceList);
			DeviceList += strlen(DeviceList) + 1;
		}
	}
	else
	{
		std::cerr << "Impossible de recuperer la liste des devices" << std::endl;
	}
	return m_devices;
}

bool AudioMaster::InitOpenAL(const char* DeviceName)
{
	// Ouverture du device(peripherique de sorties audio)
	ALCdevice* Device = alcOpenDevice(DeviceName);
	if (!Device)
	{
		std::cerr << "Impossible d'ouvrir le device par defaut" << std::endl;
		return false;
	}

	// Creation du contexte
	ALCcontext* Context = alcCreateContext(Device, NULL);
	if (!Context)
	{
		std::cerr << "Impossible de creer un contexte audio" << std::endl;
		return false;
	}

	// Activation du contexte
	if (!alcMakeContextCurrent(Context))
	{
		std::cerr << "Impossible d'activer le contexte audio" << std::endl;
		return false;
	}

	return true;
}

void AudioMaster::setListener(Vector3 pos, Vector3 speed, std::vector<float> orientation)
{
	m_listener = AudioListener(pos, speed, orientation);
}

void AudioMaster::updateListener(Vector3 pos, Vector3 speed, std::vector<float> orientation)
{
	m_listener.updateListener(pos, speed, orientation);

	for (int i = 0; i < m_sources.size();++i) {
		Vector3 sourcePos = m_sources[i]->getPosition();
		float distance = pow((sourcePos - pos).Mag(),3.0f);
		std::cout << "posSOURCE:" << sourcePos << std::endl;
		std::cout << "pos:" << pos << std::endl;
		std::cout <<"distance:"<< distance<<std::endl;
		m_sources[i]->setDistance(distance);
	}
}
void AudioMaster::showSources() {
	for (int i = 0; i < m_sources.size(); ++i) {
		std::cout<<"position of sources"<<m_sources[i]->getPosition();
	}
}

void AudioMaster::addSource(std::shared_ptr<AudioSource> source)
{
	m_sources.push_back(source);
}

// Ferme proprement OpenAL
void AudioMaster::ShutdownOpenAL()
{
	for (size_t i = 0; i < m_sources.size(); i++)
	{
		m_sources[i]->close();
		std::cout << "fermeture de la source" << std::endl;
	}

	// Recuperation du contexte et du device
	ALCcontext* Context = alcGetCurrentContext();
	ALCdevice* Device = alcGetContextsDevice(Context);

	// Desactivation du contexte
	alcMakeContextCurrent(NULL);

	// Destruction du contexte
	alcDestroyContext(Context);

	// Fermeture du device
	alcCloseDevice(Device);
}