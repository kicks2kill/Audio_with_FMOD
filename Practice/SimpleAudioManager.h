#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <fmod.hpp>

/*
	sounds are stored inside an associative container, which allows us to search based on path.
	We will rely on the STL for mapping value and key. This allows us to quickly iterate over them and release from the destructor.
*/
typedef std::map<std::string, FMOD::Sound*> SoundMap;

class SimpleAudioManager {
	public:
		SimpleAudioManager();
		~SimpleAudioManager();
		void Update(float elapsed);
		void Load(const std::string& path);
		void Stream(const std::string& path);
		void Play(const std::string& path);
	private:
		void LoadOrStream(const std::string& path, bool stream);
		FMOD::System* system;
		SoundMap sounds;
};

int main()
{

	return 0;
}