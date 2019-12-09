OUT ?= mazegen
CXX ?= g++

default:

	$(CXX) -std=c++17 -O2 -Wall src/*.cpp src/generators/*.cpp -o $(OUT) `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`

debug:

	$(CXX) -std=c++17 -Wall -g src/*.cpp src/generators/*.cpp -o $(OUT) `GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`

lcount:
	wc -l src/*.cpp src/*/*.cpp src/include/*.h src/include/*/*.h

clean:
	rm -rf *.o $(OUT)
