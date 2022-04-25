CC=gcc
CFLAGS=-Wall -lm -lcrypto
FUNCTIONS=exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o exercice9.o
MAINS=main1 main2 main3 main4 main5 main6 main7 main8 main9

# DO NOT add block.txt or testvotes.txt to the FILES variable
FILES=benchmarks.txt benchmarks_proofofwork.txt keys.txt declarations.txt candidates.txt


all: $(MAINS)


clean:
	rm -f $(MAINS) $(FILES) *.o vgcore.* ./blockchain/* 


exercice1.o: exercice1.c
	$(CC) $(CFLAGS) -c $^

exercice2.o: exercice2.c
	$(CC) $(CFLAGS) -c $^

exercice3.o: exercice3.c
	$(CC) $(CFLAGS) -c $^

exercice4.o: exercice4.c
	$(CC) $(CFLAGS) -c $^

exercice5.o: exercice5.c
	$(CC) $(CFLAGS) -c $^

exercice6.o: exercice6.c
	$(CC) $(CFLAGS) -c $^

exercice7.o: exercice7.c
	$(CC) $(CFLAGS) -c $^

exercice8.o: exercice8.c
	$(CC) $(CFLAGS) -c $^

exercice9.o: exercice9.c
	$(CC) $(CFLAGS) -c $^


main1: main1.c exercice1.o
	$(CC) $(CFLAGS) $^ -o $@

main2: main2.c exercice1.o exercice2.o
	$(CC) $(CFLAGS) $^ -o $@

main3: main3.c exercice1.o exercice2.o exercice3.o
	$(CC) $(CFLAGS) $^ -o $@

main4: main4.c exercice1.o exercice2.o exercice3.o exercice4.o
	$(CC) $(CFLAGS) $^ -o $@

main5: main5.c exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o
	$(CC) $(CFLAGS) $^ -o $@

main6: main6.c exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o
	$(CC) $(CFLAGS) $^ -o $@

main7: main7.c exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o
	$(CC) $(CFLAGS) $^ -o $@

main8: main8.c exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o
	$(CC) $(CFLAGS) $^ -o $@

main9: main9.c exercice1.o exercice2.o exercice3.o exercice4.o exercice5.o exercice6.o exercice7.o exercice8.o exercice9.c
	$(CC) $(CFLAGS) $^ -o $@

