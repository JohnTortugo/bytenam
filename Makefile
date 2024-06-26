all:
	g++ -O0 -g src/*.cpp src/parsing/* src/stats/* -o build/bytenam -lzip

clean:
	rm -f build/bytenam