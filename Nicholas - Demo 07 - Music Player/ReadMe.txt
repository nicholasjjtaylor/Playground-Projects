Reduce ROM to single bin file

1. Open cue file into Daemon tools
2. Open ImgBurn
3. Create Image file from Disc
4. Choose virtual drive
5. Choose where to save .bin file
6. Add wav music files to directory
6. Edit Cue file using the following template:

REM MyGame created by Author
REM Copyright (C) 2021 All Rights Reserved
CATALOG 0000000000000
TITLE "MyGame"
PERFORMER "Author"
FILE "MyGame Track 01.bin" BINARY
  TRACK 01 MODE1/2352
    INDEX 01 00:00:00
FILE "MyGame Track 02.wav" WAVE
	TRACK 02 AUDIO
		TITLE "Track 02"
		PERFORMER "Author"
		INDEX 01 00:00:00
FILE "MyGame Track 03.wav" WAVE
	TRACK 03 AUDIO
		TITLE "Track 03"
		PERFORMER "Author"
		INDEX 01 00:00:00