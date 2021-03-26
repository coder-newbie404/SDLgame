#include "BaseTexture.h"

BaseTexture::BaseTexture()
{
	my_texture = NULL;
	my_rect.x = 0;
	my_rect.y = 0;
	my_rect.w = 0;
	my_rect.h = 0;
}

BaseTexture::~BaseTexture()
{
	free();
}

void BaseTexture::free()
{
	//free texture if it exist
	if (my_texture != NULL)
	{
		SDL_DestroyTexture(my_texture);
		my_texture = NULL;
		my_rect.x = -640;
		my_rect.y = -640;
		my_rect.w = 0;
		my_rect.h = 0;
	}
}

void BaseTexture::SetRect(const int x, const int y)
{
	my_rect.x = x;
	my_rect.y = y;
}

SDL_Rect BaseTexture::GetRect()
{
	return my_rect;
}

SDL_Texture* BaseTexture::GetTexture()
{
	return my_texture;
}

bool BaseTexture::LoadFromFile(std::string path, SDL_Renderer* screen)
{
	//get rid of preexisting texture
	free();

	//final texture
	SDL_Texture* FinalTexture = NULL;

	//load image from path
	SDL_Surface* LoadedSurface = IMG_Load(path.c_str());

	if (LoadedSurface == NULL)
	{
		std::cout << "failed to load image from path \n IMG Error:" << IMG_GetError();
	}
	else
	{

		//color key
		SDL_SetColorKey(LoadedSurface, SDL_TRUE, SDL_MapRGB(LoadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

		//create texture from surface
		FinalTexture = SDL_CreateTextureFromSurface(screen, LoadedSurface);
		if (FinalTexture == NULL)
		{
			std::cout << "failed to create texture from surface \n SDL Error:" << SDL_GetError();
		}
		else
		{
			my_rect.w = 
		}

		//get rid from Loaded Texture
		SDL_FreeSurface(LoadedSurface);
	}

	my_texture = FinalTexture;
	return my_texture != NULL;
}

void BaseTexture::Render(SDL_Renderer* screen, int x, int y, SDL_Rect* Clip, double angle, SDL_Point* Center, SDL_RendererFlip flip)
{
	// setting render space and update to the screen
	SDL_Rect renderQuad{ x, y, my_rect.w, my_rect.h };
	if (Clip != NULL)
	{
		renderQuad.w = Clip->w;
		renderQuad.h = Clip->h;
	}
	SDL_RenderCopyEx(screen, my_texture, Clip, &renderQuad, angle, Center, flip);
}