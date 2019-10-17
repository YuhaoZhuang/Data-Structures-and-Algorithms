all: test_treemap eff_donations

test_treemap: test_treemap.o
	g++ -Wall -Werror -std=c++11 test_treemap.o -o test_treemap -pthread -lgtest

test_treemap.o: test_treemap.cc 
	g++ -Wall -Werror -std=c++11 -c -o test_treemap.o test_treemap.cc -pthread -lgtest

eff_donations: eff_donations.o
	g++ -Wall -Werror -std=c++11 eff_donations.o -o eff_donations

eff_donations.o: eff_donations.cc 
	g++ -Wall -Werror -std=c++11 -c -o eff_donations.o eff_donations.cc

clean:
	rm -f *o test_treemap eff_donations