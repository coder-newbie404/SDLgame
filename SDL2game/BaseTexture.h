#ifndef BASE_TEXTURE_H_
#define BASE_TEXTURE_H_

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>

class BaseTexture
{
public:

	//inititalize variables
	BaseTexture();

	//dellocate texture
	~BaseTexture();
	void free();

	//set rect
	void SetRect(const int x, const int y);

	//get rect
	SDL_Rect GetRect();

	//get texture
	SDL_Texture* GetTexture();

	//load image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer* screen);

	//render texture
	void Render(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* Center = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

protected:

	SDL_Texture* my_texture;
	SDL_Rect my_rect;
};

#endif