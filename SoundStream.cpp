#include "pch.h"
#include <iostream>
#include "SoundStream.h"

bool SoundStream::isMusicOn{ true };

SoundStream::SoundStream( const std::string& path )
	:m_pMixMusic{ Mix_LoadMUS( path.c_str( )) }
{
	if ( m_pMixMusic == nullptr )
	{
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError( );
		std::cerr << errorMsg;
	}
}

SoundStream::~SoundStream( )
{
	Mix_FreeMusic( m_pMixMusic );
	m_pMixMusic = nullptr;
}

bool SoundStream::IsLoaded( ) const
{
	return m_pMixMusic != nullptr;
}

bool SoundStream::Play(bool repeat ) const
{
	if (isMusicOn)
	{
		if (m_pMixMusic != nullptr)
		{
			int result{ Mix_PlayMusic(m_pMixMusic, repeat ? -1 : 1) };
			return result == 0 ? true : false;
		}
	}
	return false;
}

void SoundStream::Stop( )
{
	Mix_HaltMusic( );
}
void SoundStream::Pause( )
{
	Mix_PauseMusic( );
}

void SoundStream::Resume( )
{
	Mix_ResumeMusic( );
}

void SoundStream::FadeOut(int ms)
{

	// **** bron: https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_68.html ****//

	while (!Mix_FadeOutMusic(ms) && Mix_PlayingMusic()) {
		// wait for any fades to complete
		SDL_Delay(100);
	}
}

int SoundStream::GetVolume( )
{
	return Mix_VolumeMusic( -1 );
}

bool SoundStream::IsPlaying( )
{
	return Mix_PlayingMusic( ) == 0 ? false : true;
}

void SoundStream::SetVolume( int value )
{
	Mix_VolumeMusic( value );
}

void SoundStream::ToggleAudio(bool isOn)
{
	isMusicOn = isOn;
}
