SMS-Tilificator-Tools
=====================

[Tilificator](https://sourceforge.net/projects/tilificator/) by Bananmos is a capable tool for converting retro style graphics for developer use on 8-bit consoles. It slices meta sprite frames into the smaller sprite tiles (usually 8 x 8 pixels or 8 x 16 pixels in size) the machines' video hardware expects and outputs the raw tile data as well as a project file with additional data in it. It can convert whole sprite sheets with multiple frames, which makes for highly efficient output, especially if tiles can be re-used in more than one frame.

However, since Tilificator is tailored for NES development, using it for Master System development can be a bit awkward.

- Even though Tilificator seems to have an option to output the tile data in SMS format, it outputs the bitplanes in the wrong order.
- Tilificator auto-crops each frame to the size of just the lump of opaque pixels, ignoring its position within a given frame.
- Tilificator assumes that sprites can be flipped, which is possible on the NES, but not on the SMS. This can (very rarely) create false positives for re-used sprite tiles.

I haven't developed a solution for the flipped sprites, as in my experience the occurence is so rare that it's easier to replace them manually. For the other issues, these three small tools provide a way of mitigating them.


mixbpls
-------

mixbpls shuffles the bitplanes in the raw tile data output from Tilificator, so they actually match the format expected by the SMS. As a bonus, you can exclude empty bitplanes if your graphics data only use 1, 2 or 3.

Usage: mixbpls inputfile.bin outputfile.bin [1|2|3|4]


OffsetFinder
------------

OffsetFinder is a little Python script that takes a sprite sheet, divides it into predefined frames, and outputs the XY-positions of the first opaque pixels within each frame. Empty frames are skipped.

Make sure you adjust the definitions of *FrameXSize,* and *FrameYSize* as well as *clear_color* to match your project. (Mine had a frame size of 48 x 48 pixels and pure blue as the transparent color.)

If you want to use the output for the next tool, paste it into a plain txt file.


mmframes
--------

mmframes takes a project file created by Tilificator and a txt file with a list of offsets created by OffsetFinder. It outputs two text files which contain a LUT for each meta sprite frame, with sprite position data and tile numbers respectively. The first entry in each LUT is the number of sprites in the current frame.

If you don't want the upper left corner of the frame as your reference point, simply change the definitions of *zeroX* and *zeroY* to values that suit your needs better.

Usage: mmframes inputfile.tpr inputfile.txt
