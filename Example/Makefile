all: example

example: example.o
	g++  -m32 -framework libxml -framework Iscore -framework QtCore -framework QtGui -o "example"  ./example.o -L. 

example.o: example.cpp
	g++ -m32 -O3 -c -fmessage-length=0 -o"example.o" "example.cpp"

clean:
	rm -rf example.o example
