# compiler & flags
CXX = g++
CXXFLAGS = -O2 -std=c++11

# makefile targets
all : WordSort.exe

WordSort.exe : main.cpp sortingcompetition.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean :
	\rm -f *.o *.txt *.png

realclean : clean
	\rm -f *.exe *~


####### End of Makefile #######
