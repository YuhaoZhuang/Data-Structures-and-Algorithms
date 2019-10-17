all: test_deque plane_boarding

test_deque: test_deque.o
	g++ -Wall -Werror -std=c++11 test_deque.o -o test_deque -pthread -lgtest

test_deque.o: test_deque.cc 
	g++ -Wall -Werror -std=c++11 -c -o test_deque.o test_deque.cc -pthread -lgtest

plane_boarding: plane_boarding.o
	g++ -Wall -Werror -std=c++11 plane_boarding.o -o plane_boarding

plane_boarding.o: plane_boarding.cc 
	g++ -Wall -Werror -std=c++11 -c -o plane_boarding.o plane_boarding.cc

clean:
	rm -f *o test_deque plane_boarding