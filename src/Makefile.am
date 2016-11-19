AM_CXXFLAGS = -std=c++11 -O3 $(LIBSDL_CFLAGS) -I$(top_srcdir)/include -I$(prefix)/include
AM_LDFLAGS = 
bin_PROGRAMS=Breakout
Breakout_SOURCES=main.cpp breakout.cpp intro.cpp game.cpp start.cpp
Breakout_LDADD=$(LIBSDL_LIBS) $(TTF_LIB)
