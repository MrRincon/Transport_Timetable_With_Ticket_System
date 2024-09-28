CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic

main: readwrite.o Bus.o Ticket.o User.o Route.o Stop.o Menu.o IDObject.o

readwrite.o: ReadWrite.hpp
	$(CXX) -c ReadWrite.cpp

Bus.o: Bus.hpp
	$(CXX) -c Bus.cpp

Ticket.o: Ticket.hpp
	$(CXX) -c Ticket.cpp

User.o: User.hpp
	$(CXX) -c User.cpp

Stop.o: Stop.hpp
	$(CXX) -c Stop.cpp

Route.o: Route.hpp
	$(CXX) -c Route.cpp

Menu.o: Menu.hpp
	$(CXX) -c Menu.cpp

IDObject.o: IDObject.hpp
	$(CXX) -c IDObject.cpp
