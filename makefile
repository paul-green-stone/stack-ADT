cc = gcc
objs = temp/stack.o guard/temp/guard.o
dirs = temp
CFLAGS = -O1

# Object files
temp/stack.o: stack.h stack.c guard/temp/guard.o
	$(CC) -c -g -o temp/stack.o stack.c

guard/temp/guard.o:
	$(MAKE) -C guard

# If there is a main.c file
test: main.o $(objs)
	$(CC) -o a.out main.o $(objs)

.PHONY: clean

clean:
	rm -rf temp ./*.o a.out
	rm -rf guard/temp

$(shell mkdir -p $(dirs))