#ifndef ID_PONG_SOUND_H
#define ID_PONG_SOUND_H
#include <SDL_mixer.h>
class Sound
{
public:
	Sound(const char* fileName);
	Sound();
	~Sound();
	void Load();
	void Play();
	void Destroy();
private:
	const char* fileName;
	Mix_Chunk* sound;
};
#endif // !ID_PONG_SOUND_H
