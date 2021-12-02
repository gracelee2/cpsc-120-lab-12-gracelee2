#
# Copyright 2021 Michael Shafae
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

TARGET = rt
# C++ Files
CXXFILES = ray.cc rng.cc rt.cc vec3.cc utilities.cc
HEADERS = ray.h rng.h vec3.h utilities.h

CXX = clang++
CFLAGS += -g -O3 -Werror -pipe -std=c++17 
LDFLAGS += -g -O3 -Werror -pipe -std=c++17 -lGraphicsMagick++

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CFLAGS += -D LINUX -I/usr/include/GraphicsMagick
	SED = sed
	GTESTINCLUDE = ""
	GTESTLIBS = -lgtest -lgtest_main -lpthread
endif
ifeq ($(UNAME_S),Darwin)
	ifeq (,$(wildcard "/opt/local/bin/port"))
		GTESTINCLUDE = -I/opt/local/include -I/opt/local/src/googletest
		GTESTLIBS = -lgtest -lgtest_main
		CFLAGS += -D OSX -nostdinc++ -I/opt/local/include/libcxx/v1 -I /opt/local/include/GraphicsMagick $(GTESTINCLUDE)
		LDFLAGS += -mmacosx-version-min=11.0 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -L/opt/local/lib/libcxx -L/opt/local/lib
		SED = gsed
	else
		CFLAGS += -D OSX
	endif
endif
UNAME_M = $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
	CFLAGS += -D AMD64
endif
ifneq ($(filter %86,$(UNAME_M)),)
	CFLAGS += -D IA32
endif
ifneq ($(filter arm%,$(UNAME_M)),)
	CFLAGS += -D ARM
endif

DOXYGEN = doxygen
DOCDIR = doc

OBJECTS = $(CXXFILES:.cc=.o)

DEP = $(CXXFILES:.cc=.d)

.SILENT: lint format header

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

-include $(DEP)

%.d: %.cc
	set -e; $(CXX) -MM $(CFLAGS) $< \
	| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
	[ -s $@ ] || rm -f $@

%.o: %.cc
	$(CXX) $(CFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core

spotless: clean cleanunittest
	-rm -f $(TARGET) $(DEP) a.out
	-rm -rf $(DOCDIR)
	-rm -rf $(TARGET).dSYM
	-rm -f compile_commands.json

doc: $(CXXFILES) $(HEADERS)
	 (cat Doxyfile; echo "PROJECT_NAME = ${TARGET}") | $(DOXYGEN) -

compilecmd:
	@echo "$(CXX) $(CFLAGS)"

format:
	python3 ../.action/format_check.py $(CXXFILES) $(HEADERS)

lint:
	python3 ../.action/lint_check.py $(CXXFILES) $(HEADERS)

header:
	python3 ../.action/header_check.py $(CXXFILES) $(HEADERS)

test:
	python3 ../.action/solution_check_p2.py . $(TARGET)

#%.h: %.cc
#ifndef MAKEHEADERS
#	$(warning "makeheaders not available.")
#else
#	$(eval GUARD := $(shell basename $< .cc | tr [:lower:] [:upper:]))
#	makeheaders -h $< | $(SED) -e '$$a#endif\n' -e '/^extern using/d' -e '/^#/d' -e '1i\/* Automatically generated using makeheaders. Do not edit. */\n#ifndef __$(GUARD)__ \n#define __$(GUARD)__\n\/\/\/ \\file\n' > $@
#endif

unittest: cleanunittest utest

utest: vec3.o vec3_unittest.o ray.o ray_unittest.o
	$(CXX) $(GTESTINCLUDE) $(LDFLAGS) -o unittest $^ $(GTESTLIBS)
	./unittest

cleanunittest:
	-@rm -rf unittest.dSYM
	-@rm unittest
	-@rm *_unittest.o
