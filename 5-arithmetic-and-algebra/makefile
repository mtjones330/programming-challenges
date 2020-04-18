build: big-num-tests.o big-num.o
	g++ big-num-tests.o big-num.o

big-num-tests.o: big-num-tests.cpp big-num.o
	g++ -c big-num-tests.cpp

big-num.o: big-num.cpp big-num.h
	g++ -c big-num.cpp

clean:
	rm *.o a.out