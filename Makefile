
all: run runcolor

run:	dice_roll_advanced.o
	gcc -g -Wall -o run dice_roll_advanced.o

run.o: dice_roll_advanced.c
	gcc -g -c -Wall dice_roll_advanced.c

runcolor:	dice_roll_advanced_color.o
	gcc -g -Wall -o runcolor dice_roll_advanced_color.o

runcolor.o: dice_roll_advanced_color.c
	gcc -g -c -Wall dice_roll_advanced_color.c	

clean:
	rm -f *.o run runcolor
