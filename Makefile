CC = clang++
CXXLFAGS = -std=c++20
INCLUDES = -lcurl -lcurlpp -lpthread

build: src/i3nstatus.cpp
	$(CC) $(CXXLFAGS) src/i3nstatus.cpp -Isrc/ -I. $(INCLUDES) -o i3nstatus

install: build
	-rm /usr/bin/i3status
	cp i3nstatus /usr/bin/i3status
