all: zap unzap

zap: zap.cc
	g++ -Wall -Werror -std=c++11 zap.cc -o zap

unzap: unzap.cc
	g++ -Wall -Werror -std=c++11 unzap.cc -o unzap

clean:
	rm -f *.zap *.unzap zap unzap