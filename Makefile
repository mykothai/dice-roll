
all: run runcolor

run:	dice_roll.o
	gcc -g -Wall -o run dice_roll.o

run.o: dice_roll.c
	gcc -g -c -Wall dice_roll.c

runcolor:	dice_roll_color.o
	gcc -g -Wall -o runcolor dice_roll_color.o

runcolor.o: dice_roll_color.c
	gcc -g -c -Wall dice_roll_color.c	

clean:
	rm -f *.o run runcolor
