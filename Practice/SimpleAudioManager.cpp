#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <fmod.hpp>
#include "SimpleAudioManager.h"


SimpleAudioManager::SimpleAudioManager() {
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);
}

void SimpleAudioManager::Update(float elapsed) {
	system->update();
}

SimpleAudioManager::~SimpleAudioManager() {
	//Release every sound object and clear map
	SoundMap::iterator iter;
	for (iter = sounds.begin(); iter != sounds.end(); ++iter)
		iter->second->release();
	sounds.clear();

	//Release system object
	system->release();
	system = 0;
}

/*
	Take in path of audio file as parameter and check if it's been loaded. If it has been loaded, don't do it again. Otherwise, it is loaded (or streamed, depending on value of second parameter)
	and stored in the sound map under appropriate key
*/

void SimpleAudioManager::LoadOrStream(const std::string& path, bool stream)
{
	//ignore call if sound is already loaded
	if (sounds.find(path) != sounds.end()) return;


	//load(or stream) file into a sound object
	FMOD::Sound* sound;
	if (stream)
		system->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
	else
		system->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);

	//store sound object in the map using path as key
	sounds.insert(std::make_pair(path, sound));
}

//pretty trivial implementation
void SimpleAudioManager::Load(const std::string& path) {
	LoadOrStream(path, false);
}

void SimpleAudioManager::Stream(const std::string& path) {
	LoadOrStream(path, true);
}

void SimpleAudioManager::Play(const std::string& path) {
	//search for a matching sound in map
	SoundMap::iterator sound = sounds.find(path);

	//ignore call if none
	if (sound == sounds.end()) return;

	//play sound otherwise
	system->playSound(sound->second, 0, false, 0);
}