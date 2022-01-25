all:
	g++ -std=c++17 -g *.cpp -o proj1
debug:
	g++ -DDEBUG -std=c++17 -g *.cpp -o proj1