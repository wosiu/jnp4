all : run-test

test : test.cpp holding.hh
	g++ -std=c++11 test.cpp -otest

main : main.cpp holding.hh
	g++ -std=c++11 main.cpp -omain

run-test : test main
	./test
	./main
