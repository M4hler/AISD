FLAGS= -Wall --pedantic
main:	z3.cpp
	g++ $< -o $@ $(FLAGS)
main2: z3.commented.cpp
	g++ $< -o $@ $(FLAGS)

.clean:	rm -rf .out .o

