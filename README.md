Pcmprint, as the name suggests, prints PCM data to stdout in what
could be considered human-readable form.

Input data is assumed to be in "CD-Audio" format, i.e signed 16-bit
integer, little-endian, stereo, 44100 samplerate.

You can use it, for example, for live view of music wavform:

* with sndio:
	tee /dev/audio0 < music.pcm | pcmprint
* with aplay:
	mkfifo /tmp/fifo
	(tee /tmp/fifo < music.pcm | pcmrpint)&
	aplay -f cd < /tmp/fifo

Features considered and rejected:
---------------------------------

* more than 2 levels of "intensity"
* using non-ASCII characters for output
* automatic width setting
* configurable input format
