FLAGS= -Wall --pedantic
main:	z1.cpp
	g++ $< -o $@ $(FLAGS)
main2: z1.commented.cpp
	g++ $< -o $@ $(FLAGS)

.clean:	rm -rf .out .o

