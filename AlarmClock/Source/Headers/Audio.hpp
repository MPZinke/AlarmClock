

#pragma once


#include <Arduino.h>
#include <DFMiniMp3.h>


// Forward declaration for `typedef DFMiniMp3<HardwareSerial, ::Audio::Notifier> Global::Audio::DFPlayer;`
namespace Audio
{
	class Notifier;
}


namespace Global
{
	namespace Audio
	{
		typedef DFMiniMp3<HardwareSerial, ::Audio::Notifier> DFPlayer;
	}
}


namespace Audio
{
	namespace Tracks
	{
		enum
		{
			START_UP = 1,
			CLICK,
			DROP,
			ALARM,
		};
	}


	using namespace Global::Audio;

	class Notifier
	{
		public:
			static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action);
			static void OnError([[maybe_unused]] DFPlayer& mp3, uint16_t errorCode);
			static void OnPlayFinished([[maybe_unused]] DFPlayer& mp3, [[maybe_unused]] DfMp3_PlaySources source,
				uint16_t track
			);
			static void OnPlaySourceOnline([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source);
			static void OnPlaySourceInserted([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source);
			static void OnPlaySourceRemoved([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source);
	};
}
