#!/usr/bin/python
import sys

if __name__ == "__main__":
    with open("/tmp/debugplayer.log", "w") as f:
        f.write(repr(sys.argv) + "\n")
        f.flush()
        try:
            while True:
                line = raw_input() + "\n"
                f.write(line)
                f.flush()
        except:
            f.write("closed")
