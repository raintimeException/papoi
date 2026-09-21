#TODO: https://github.com/raysan5/raylib/wiki/Working-for-Android-(on-Linux)

RAYLIB=../third/raylib-6.0_linux_amd64/lib/libraylib.a

MATH=-lm
X11=-lX11

IN=main.c
OUT=papoi

CC=clang

CFLAGS=-g
CFLAGS+=-Wall
CFLAGS+=-Wextra

all:
	$(CC) $(CFLAGS) $(IN) $(RAYLIB) $(MATH) $(X11) -o $(OUT)
	./$(OUT)

format:
	clang-format -i $(IN)

clean:
	rm -rf ./$(OUT)
