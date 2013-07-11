# DBZ Pebble Watch Face
_by Rafa Leano_

Watch face featuring characters from the _Dragon Ball Z_ Anime. The characters change every minute. Currently has images for:
* Goku (SSJ)
* Gohan (SSJ2)
* Vegeta
* Piccolo

## Build Instructions

Clone this repository:

	git clone https://github.com/rleano/pebble-dbz.git

Set up waf:

	python %PEBBLE_HOME%/pebble-dev/PebbleSDK-1.12/Pebble/tools/create_pebble_project.py --symlink-only %PEBBLE_HOME%/pebble-dev/PebbleSDK-1.12/Pebble/sdk/ pebble-dbz
	cd pebble-dbz
	
	Replace %PEBBLE_HOME% with the path to where you have installed your PebbleSDK (e.g. in Mac by default it is in the user home directory "~")

Configure and build:

	./waf configure
	./waf build

Install pebble-dbz.pbw in build directory

## License

Copyright (C) 2013  Rafa Leano

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

## Acknowledgements

* Character images extracted from [spritedatabase.net/](http://spritedatabase.net/game/20) and reduced to 2-bit from sprites by [GRIM](http://spritedatabase.net/contributor.php?contid=1)

## Fonts Used

Big Noodle Titling from Sentinel Type, designed by James Arboghast
* [Free for personal use](http://www.dafont.com/bignoodle-titling.font)

