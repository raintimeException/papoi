#TODO: https://github.com/raysan5/raylib/wiki/Working-for-Android-(on-Linux)

RAYLIB_LINUX=../third/raylib-6.0_linux_amd64/lib/libraylib.a
RAYLIB_MAC=../third/raylib-6.0_macos/lib/libraylib.a

MATH=-lm

LDLIBS_LINUX=-lX11 $(MATH)
LDLIBS_MAC=-framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo $(MATH)

IN=main.c
OUT=papoi

CC=clang

CFLAGS=-g
CFLAGS+=-Wall
CFLAGS+=-Wextra

OS=$(shell uname)

ifeq ($(OS),Darwin)
	RAYLIB=$(RAYLIB_MAC) $(LDLIBS_MAC)
else
	RAYLIB=$(RAYLIB_LINUX) $(LDLIBS_LINUX)
endif

all:
	$(CC) $(CFLAGS) $(IN) $(RAYLIB) -o $(OUT)
	./$(OUT)

format:
	clang-format -i $(IN)

clean:
	rm -rf ./$(OUT)
