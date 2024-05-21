all: clean compile run

clean:
	@rm -rf bin

compile:
	@javac -d bin src/hw3/*.java

run:
	@java -cp bin hw3.HwDemo

doc:
	@rm -rf doc
	@javadoc -d doc src/hw3/*.java
