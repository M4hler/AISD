FLAGS= -Wall --pedantic -std=c++11
all:	main1 main2 main3 main4
main1:	./zad1/z1.cpp; \
	g++ $< -o ./zad1/main $(FLAGS)

main2:	./zad2/z2.cpp; \
	g++ $< -o ./zad2/main $(FLAGS)

main3:	./zad3/z3.cpp; \
	g++ $< -o ./zad3/main $(FLAGS)

main4:	./zad4/z4.cpp; \
	g++ $< -o ./zad4/main $(FLAGS)

.clean:	rm -rf .out .o

