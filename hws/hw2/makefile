all:clear compile run clean

clear: 
	@clear
compile:
	@g++ -std=c++11 main.cpp shell.cpp file.cpp -o main.out
d:
	@clear
	@g++ -g -o deb main.cpp shell.cpp file.cpp
	@gdb deb
run:
	@./main.out 
clean:
	@rm main.out