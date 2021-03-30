#include "Sound.h"

Sound::Sound() :fileName(nullptr), sound(nullptr)
{

}
Sound::Sound(const char* fileName) : fileName(fileName), sound(nullptr)
{

}
Sound::~Sound()
{
	Destroy();
}
void Sound::Load()
{
	sound = Mix_LoadWAV(fileName);
}
void Sound::Play()
{
	Mix_PlayChannel(-1, sound, 0);
}
void Sound::Destroy()
{
	Mix_FreeChunk(sound);
}