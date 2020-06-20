<div align="center">
	<img src="https://raw.githubusercontent.com/blooser/gemini/3fc4b6911cc3e403a2063cb23aeb864a65401c0b/gemini/resources/svg/gemini-with-text.svg" width="350" height="350">
</div>

Gemini is an audio player with wallpaper changer

<i> Gemini is currently in the early development stage, it might have unfinished features or bugs</i>

## Dependency

This software is based on 
 - [Qt](https://www.qt.io/)
 - [TagLib](https://taglib.org/)
 - [LibVlc](https://wiki.videolan.org/LibVLC)

## Build and run

To build this software, follow the instructions

### Repository

Clone the repository

```bash
git clone https://github.com/blooser/gemini && cd gemini
```

### Build

Prepare the build

```bash
mkdir build && cd build
cmake ..
make
```

### Unit tests
Run the unit tests

```bash
make test
```

### Install

Install the gemini

```bash
make install
```

## License

Gemini is a free software released under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html) 

