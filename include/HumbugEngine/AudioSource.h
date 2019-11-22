#pragma once



#include <al.h>
#include <alc.h>
#include <iomanip>
#include <iostream>
#include <string>

#include <sndfile.h>
#include "HumbugEngine/Object.h"



class AudioSource
{
private:
	ALuint m_sourceID;
	ALint m_status;
	ALuint m_buffer;
	ALfloat m_currentTime;
	Vector3 m_pos;

public:

	AudioSource(Vector3 pos);

	ALuint getSourceID() {return m_sourceID;}

	ALfloat getCurrentTime();
	
	ALint getState();

	void setDistance(float distance);

	void setBuffer(ALuint buffer);

	void loadSong(const std::string& Filename);

	ALuint loadBuffer(const std::string& fileName);

	bool isPlaying();

	void play();

	void pause();

	void stop();

	void rewind();

	void setPosition(Vector3 pos);

	Vector3 getPosition();

	void setPitch(float pitch);

	void setVolume(float volume);

	void setLooping(bool loop);

	void close();
};
