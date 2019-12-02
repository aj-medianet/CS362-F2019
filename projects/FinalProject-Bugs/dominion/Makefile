CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest5: unittest5.c dominion.o rngs.o
	gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)

unittest6: unittest6.c dominion.o rngs.o
	gcc -o unittest6 -g  unittest6.c dominion.o rngs.o $(CFLAGS)

unittest7: unittest7.c dominion.o rngs.o
	gcc -o unittest7 -g  unittest7.c dominion.o rngs.o $(CFLAGS)

unittest8: unittest8.c dominion.o rngs.o
	gcc -o unittest8 -g  unittest8.c dominion.o rngs.o $(CFLAGS)

unittest9: unittest9.c dominion.o rngs.o
	gcc -o unittest9 -g  unittest9.c dominion.o rngs.o $(CFLAGS)

unittest10: unittest10.c dominion.o rngs.o
	gcc -o unittest10 -g  unittest10.c dominion.o rngs.o $(CFLAGS)

unittestresults: unittest5 unittest6 unittest7 unittest8 unittest9 unittest10
	echo "Unit Test Results:" > unittestresults.out

	./unittest5 &> unittestresults.out
	./unittest6 >> unittestresults.out
	./unittest7 >> unittestresults.out

	
	./unittest8 >> unittestresults.out
	./unittest9 >> unittestresults.out
	./unittest10 >> unittestresults.out

	echo "*** gcov results ***" >> unittestresults.out
	echo >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe
