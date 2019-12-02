# brainf-ck
[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter in C.

It's honestly not that great but I needed something to do on my spare time. Should work with most Brainfuck files. I do some parsing and check if `[` `]` are well-balanced but nothing else beyond that.

I haven't tested this extensively but I have used a few of the files [here](http://www.hevanet.com/cristofd/brainfuck/). With files that require input, you might need to use `CTRL+C` to exit. Also of note, some of the Brainfuck programs on the previous link do not terminate so read the notes carefully.

## Building
Requirements:
- make
- gcc
- gdb (for debugging)

Run `make` or `make build`.

## Debugging
Run `make debug` to get the binary with debug symbols. Run `gdb .\bf --f FILENAME` to debug.

## Usage
Run `.\bf --f FILENAME` to run a Brainfuck file, where `FILENAME` is the path of the file. Use `--h` to get help and dispaly information about the interpreter.

## License
Licensed under MIT.