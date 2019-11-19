out := mazegen

default:

	g++ -std=c++17 -O2 src/*.cpp src/generators/*.cpp -o $(out) `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`

debug:

	g++ -std=c++17 -g src/*.cpp src/generators/*.cpp -o $(out) `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`

lcount:
	wc -l src/*.cpp src/*/*.cpp src/include/*.h src/include/*/*.h

clean:
	rm -rf *.o $(out)
