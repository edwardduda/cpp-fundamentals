NETID=edwardd
#Used for naming your tar file
ASN=HW3
#Used for naming the executable
SOURCES=HW3.cpp
#List any files you need to make for source files
HEADERS=
#List any Header files
OBJECTS=HW3.o
#List any Object files you need to create for your assignment
TARNAME=$(NETID)_$(ASN).tar

RM=rm
#Change to del if on a windows machine
#Used to create a standard tar file naming convention

#Required Content Do not Modify below this line
CXXFLAGS=-Wall -Werror -Wfatal-errors -O2

%.o: %.cpp
		g++ -c -g $(CXXFLAGS) $<

$(ASN): $(OBJECTS)
		g++ $(CXXFLAGS) -o $(ASN) $(OBJECTS)

tar:
		tar -cf $(TARNAME) $(SOURCES) $(HEADERS) Makefile

clean:
		$(RM) -f $(TARNAME) $(ASN) $(OBJECTS) *.gch *.gcov a.out
