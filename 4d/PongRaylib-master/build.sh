set -e
cc -g -std=c99 -c main.c -o .obj/main.o
cc -o main .obj/main.o -s -Wall -std=c99 -lraylib -lm -lpthread -ldl -lrt -lX11
./main 2
