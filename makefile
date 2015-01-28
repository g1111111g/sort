main: print.c tool.o tool.h
	gcc print.c -o print tool.o
tool.o: tool.h tool.c
	gcc -c tool.c
clean:
	rm -rf tool.o print
