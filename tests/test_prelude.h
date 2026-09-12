// What CvGameCoreDLL.h provides that FDataStreamBase.h assumes, and nothing else. The
// standalone test includes this directly; the staged copy of CvTaggedStream.cpp gets
// it through the stub CvGameCoreDLL.h that run_taggedstream_test.py writes.
#pragma once
#include <string>
#include <vector>
typedef unsigned char byte;
typedef wchar_t wchar;
