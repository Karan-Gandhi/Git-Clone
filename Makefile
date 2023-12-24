all: build

build:
	g++ ./src/gitc.cpp -o ./bin/gitc

clean:
	rm -r ./bin/*