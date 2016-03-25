#Oniel Toledo     Assignment 14 makefile    cs202
# make file for the main and ladder executable files
# also creates an object file for the wordLadder 
# implementation file

#current compiler
cc = g++

#objects to be created
#client programs
OBJS1 = testQueue.o
OBJS2 = ladder.o
#implementation object files
OBJS3 = wordLadder.cpp

#dependency list
DEPS1 = wordLadder.h
DEPS2 = linkedStack.h
DEPS3 = linkedQueue.h

all: testQueue ladder

#create implementation object file
wordLadder: $(OBJS3)
	$(cc) -o wordLadder $(OBJS3)

wordLadder.o: wordLadder.cpp $(DEPS1) $(DEPS2) $(DEPS3)
	$(cc) -c -g wordLadder.cpp


#create the main executable
testQueue: $(OBJS1)
	$(cc) -o testQueue $(OBJS1)

testQueue.o: testQueue.cpp $(DEPS2) $(DEPS3)
	$(cc) -c -g testQueue.cpp

#create the ladder executable file
ladder: $(OBJS2) $(OBJS3)
	$(cc) -o ladder $(OBJS2) $(OBJS3)

ladder.o: ladder.cpp $(DEPS1) $(DEPS2) $(DEPS3)
	$(cc) -c -g ladder.cpp

#remove objects
clean:
	rm $(OBJS1)
	rm $(OBJS2)
	rm $(OBJS3)