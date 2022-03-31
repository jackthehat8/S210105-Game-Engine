#include "SDL.h"
#include <string>
#include <map>
#include <SDL_audio.h>
#include <SDL_ttf.h>

using namespace std;
class ResourceManager {
private:
	static ResourceManager* instance;

	map<string, SDL_Surface*>  imageFiles;
	map<string, SDL_AudioSpec*>  audioFiles; //used for SDL_Audio https://docs.huihoo.com/sdl/sdl-1.0-intro-en/usingsound.html
	map<string, TTF_Font*>  fontFiles;

public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();

	SDL_Surface* LoadImage(string fileDirectory);
	TTF_Font* LoadFont(string fileDirectory, int fontSize = 15);
	SDL_AudioSpec* LoadAudio(string fileDirectory);

	void UnloadImage(string fileDirectory);
	void UnloadFont(string fileDirectory);
	void UnloadAudio(string fileDirectory);
};
