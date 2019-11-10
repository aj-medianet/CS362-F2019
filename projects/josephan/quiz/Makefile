CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme -g  testme.c $(CFLAGS)

runtests: testme 
	echo "Unit Test Results:" > unittestresults.out

	./testme &> unittestresults.out
		
runcoverage:
	echo "Coverage Results:" > coverageresults.out
	gcov -b -f testme.c >> coverageresults.out
	cat testme.c.gcov >> coverageresults.out

clean:
	rm -f *.o testme

cleanall:
	rm -f rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out
