FLAGS= -Wall --pedantic -std=c++11
main:	./zad1/z1.cpp; \
	g++ $< -o ./zad1/$@ $(FLAGS)
main2: z1.commented.cpp
	g++ $< -o $@ $(FLAGS)

.clean:	rm -rf .out .o

