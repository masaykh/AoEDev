# Build and run the standalone CvTaggedStream test.
#
# CvTaggedStream.cpp starts with CvGameCoreDLL.h, because the DLL build compiles every
# .cpp in that directory with /Yu"CvGameCoreDLL.h" and one that omits it dies with C1010.
# That header cannot be compiled outside the game, so the encoder is staged into a
# scratch directory beside a stub of it: a quoted include is resolved against the
# including file's own directory first, so the staged copy picks up the stub and the real
# umbrella header is never opened.
#
#   python tests/run_taggedstream_test.py
#
# Uses clang++ or g++, whichever is on PATH; set CXX to pick one.
import os
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(ROOT, "NoCrash DLL SourceCode")
TESTS = os.path.join(ROOT, "tests")

STUB = """// Stands in for the DLL's umbrella header while CvTaggedStream.cpp is built without the
// game. Written by tests/run_taggedstream_test.py; not part of the DLL build.
#pragma once
#include "test_prelude.h"
"""


def compiler():
    for cxx in (os.environ.get("CXX"), "clang++", "g++"):
        if cxx and shutil.which(cxx):
            return cxx
    sys.exit("no C++ compiler found: install clang++ or g++, or set CXX")


def main():
    cxx = compiler()
    stage = tempfile.mkdtemp(prefix="taggedstream-")
    try:
        with open(os.path.join(stage, "CvGameCoreDLL.h"), "w") as f:
            f.write(STUB)
        shutil.copy(os.path.join(SRC, "CvTaggedStream.cpp"), stage)

        exe = os.path.join(stage, "test_taggedstream.exe")
        cmd = [cxx, "-Wall", "-I", stage, "-I", TESTS, "-I", SRC,
               os.path.join(stage, "CvTaggedStream.cpp"),
               os.path.join(TESTS, "test_taggedstream.cpp"),
               "-o", exe]
        print(" ".join(cmd))
        if subprocess.call(cmd) != 0:
            return 1
        return subprocess.call([exe])
    finally:
        shutil.rmtree(stage, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
