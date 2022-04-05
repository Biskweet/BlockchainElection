CC=gcc
CFLAGS=-Wall -lm
PROGRAMS=main6

exercice1:
	$(CC) $(CFLAGS) -c exercice1.c

main1: exercice1
	$(CC) $(CFLAGS) exercice1.o main1.c -o main1

exercice2:
	$(CC) $(CFLAGS) -c exercice2.c

main2: exercice1 exercice2
	$(CC) $(CFLAGS) exercice2.o exercice1.o main2.c -o main2

exercice3:
	$(CC) $(CFLAGS) -c exercice3.c

main3: exercice1 exercice2 exercice3
	$(CC) $(CFLAGS) exercice3.o exercice2.o exercice1.o main3.c -o main3

exercice4:
	$(CC) $(CFLAGS) -c exercice4.c

main4: exercice1 exercice2 exercice3 exercice4
	$(CC) $(CFLAGS) exercice4.o exercice3.o exercice2.o exercice1.o main4.c -o main4

exercice5:
	$(CC) $(CFLAGS) -c exercice5.c

main5: exercice1 exercice2 exercice3 exercice4 exercice5 exercice6
	$(CC) $(CFLAGS) exercice6.o exercice5.o exercice4.o exercice3.o exercice2.o exercice1.o main5.c -o main5

exercice6:
	$(CC) $(CFLAGS) -c exercice6.c

main6: exercice1 exercice2 exercice3 exercice4 exercice5 exercice6
	$(CC) $(FLAGS) exercice6.o exercice5.o exercice4.o exercice3.o exercice2.o exercice1.o main6.c -o main6

all: $(PROGRAMS)

clean:
	rm -f *.o main1 main2 main3 main4 main5 main6 vgcore.*
