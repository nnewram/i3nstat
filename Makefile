CC = clang++
CXXLFAGS = -std=c++20 -O2
INCLUDES = -lcurl -lcurlpp

build: src/i3nstatus.cpp
	$(CC) $(CXXLFAGS) src/i3nstatus.cpp -Isrc/ -I. $(INCLUDES) -o i3status

install: build
	-rm /usr/bin/i3status
	cp i3nstatus /usr/bin/i3status
