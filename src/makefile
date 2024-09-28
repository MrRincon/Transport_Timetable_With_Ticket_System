CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic
SUBDIR = ./classes/

main: main.o
	$(MAKE) -C classes
	$(CXX) -o main main.o $(SUBDIR)ReadWrite.o $(SUBDIR)Bus.o $(SUBDIR)Ticket.o $(SUBDIR)User.o $(SUBDIR)Route.o $(SUBDIR)Stop.o $(SUBDIR)Menu.o $(SUBDIR)IDObject.o

testcase: testcase.o
	$(MAKE) -C classes
	$(CXX) -o testcase testcase.o $(SUBDIR)ReadWrite.o $(SUBDIR)Bus.o $(SUBDIR)Ticket.o $(SUBDIR)User.o $(SUBDIR)Route.o $(SUBDIR)Stop.o $(SUBDIR)Menu.o $(SUBDIR)IDObject.o


classes:
	make $(SUBDIR)

main.o: main.cpp
	$(CXX) -c main.cpp

testcase.o: test.cpp
	$(CXX) -c test.cpp -o testcase.o

.PHONY: clean all

clean:
	-rm -f *.o && cd $(SUBDIR) && rm -f *.o
	-rm -f main
	-rm -f testcase
