

#include "../Headers/Audio.hpp"


#include "../Headers/Global.hpp"


namespace Audio
{
	using namespace Global::Audio;

	void Notifier::PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
	{}


	void Notifier::OnError([[maybe_unused]] DFPlayer& mp3, uint16_t errorCode)
	{}


	void Notifier::OnPlayFinished([[maybe_unused]] DFPlayer& mp3, [[maybe_unused]] DfMp3_PlaySources source,
		uint16_t track
	)
	{}


	void Notifier::OnPlaySourceOnline([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source)
	{}


	void Notifier::OnPlaySourceInserted([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source)
	{}


	void Notifier::OnPlaySourceRemoved([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source)
	{}
}
