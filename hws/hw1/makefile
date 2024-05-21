all:clear compile run clean

clear: 
	@clear
compile:
	@g++ -std=c++11 main.cpp piece.cpp board.cpp -o main.out
d:
	@clear
	@g++ -g -o deb main.cpp piece.cpp board.cpp
	@gdb deb
run:
	@./main.out 
clean:
	@rm main.out