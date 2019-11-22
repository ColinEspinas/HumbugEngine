#include "HumbugEngine/AudioSource.h"
#include "HumbugEngine/AudioMaster.h"


AudioSource::AudioSource(Vector3 pos)
{
	alGenSources(1, &m_sourceID);
	m_status = AL_PAUSED;
	m_buffer = NULL;
	m_currentTime = 0;
	m_pos = pos;
	AudioMaster::get()->addSource(std::make_shared<AudioSource>(*this));
}

ALfloat AudioSource::getCurrentTime()
{
	alGetSourcef(getSourceID(), AL_SEC_OFFSET, &m_currentTime);
	return m_currentTime;
}

ALint AudioSource::getState()
{
	alGetSourcei(getSourceID(), AL_SOURCE_STATE, &m_status);
	return m_status;
}

void AudioSource::setDistance(float distance)
{
	std::cout << "distanc in gain:" << distance<<std::endl;

	std::cout << "I1:" << (distance - AL_REFERENCE_DISTANCE) << std::endl;
	std::cout << "I2" << (AL_REFERENCE_DISTANCE + AL_ROLLOFF_FACTOR) << std::endl;
	float max = 180;
	float gain = (max - distance)/ max;
	gain = GH_CLAMP(gain, 0.0f, 1.0f);
	std::cout << "gain:" << gain;
	setVolume(gain);
}

void AudioSource::setBuffer(ALuint buffer)
{
		// on attache le buffer a la source
		alSourcei(m_sourceID, AL_BUFFER, buffer);
		alSourcei(m_sourceID, AL_ROLLOFF_FACTOR, 100.0f);

		alSourcei(m_sourceID, AL_MAX_DISTANCE, 300.0f);
		setVolume(0.9f);
}

void AudioSource::loadSong(const std::string& fileName)
{
	ALuint Buffer = loadBuffer(fileName);
	if (Buffer == 0) {
		std::cout << "error while loading";
		//return EXIT_FAILURE;
	}
	setBuffer(Buffer);
}

ALuint AudioSource::loadBuffer(const std::string& fileName)
{
	// Ouverture du fichier audio avec libsndfile
	SF_INFO FileInfos;
	SNDFILE* File = sf_open(fileName.c_str(), SFM_READ, &FileInfos);

	if (!File)
	{
		std::cerr << "Impossible d'ouvrir le fichier audio" << std::endl;
		return 0;
	}

	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
	ALsizei NbSamples = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
	ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

	// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
	std::vector<ALshort> Samples(NbSamples);

	if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
	{
		std::cerr << "Impossible de lire les échantillons stockés dans le fichier audio" << std::endl;
		return 0;
	}

	// Fermeture du fichier
	sf_close(File);

	// Détermination du format en fonction du nombre de canaux
	ALenum Format;
	switch (FileInfos.channels)
	{
		
	case 1: Format = AL_FORMAT_MONO16;   break;
	case 2: Format = AL_FORMAT_STEREO16; break;

	default:
		std::cerr << "Format audio non supporté (plus de 2 canaux)" << std::endl;
		return 0;
	}

	// Création du tampon OpenAL
	ALuint Buffer;
	alGenBuffers(1, &Buffer);

	// Remplissage avec les échantillons lus
	alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

	// Vérification des erreurs
	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "Impossible de remplir le tampon OpenAL avec les échantillons du fichier audio" << std::endl;
		return 0;
	}

	return Buffer;
}

bool AudioSource::isPlaying()
{
	alGetSourcei(m_sourceID, AL_SOURCE_STATE, &m_status);
	return m_status ==AL_PLAYING;
}

void AudioSource::pause()
{
	alSourcePause(m_sourceID);
}

void AudioSource::play()
{
	// On play le son dans le soft
	alSourcePlay(m_sourceID);
}

void AudioSource::stop()
{
	alSourceStop(m_sourceID);
}

void AudioSource::rewind()
{
	alSourceRewind(m_sourceID);
}

void AudioSource::setPosition(Vector3 pos)
{
	m_pos = pos;
	std::cout << "depuis le main  : " << m_pos << std::endl;
	alSource3f(m_sourceID, AL_POSITION, m_pos.x, m_pos.y, m_pos.z);
}

Vector3 AudioSource::getPosition()
{
	std::cout <<"de l'autre coté pos : "<< m_pos << std::endl;
	return m_pos;
}

void AudioSource::setPitch(float pitch)
{
	alSourcef(m_sourceID, AL_PITCH, pitch);
}

void AudioSource::setVolume(float volume)
{
	alSourcef(m_sourceID, AL_GAIN, volume);
}

void AudioSource::setLooping(bool loop)
{
	alSourcei(m_sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void AudioSource::close()
{
	// Destruction du tampon
	alDeleteBuffers(1, &m_buffer);
	// Destruction de la source
	alSourcei(m_sourceID, AL_BUFFER, 0);
	alDeleteSources(1, &m_sourceID);
}
