INCS=\
	ReadFile.h\
	Utils.h

OBJS=\
	main.o\
	Utils.o\
	ReadFile.o

CFLGS=-c -mconsole -O2

day07.exe : $(OBJS) $(INCS)
	g++ -o day07.exe -mconsole -O2 $(OBJS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

Utils.o : Utils.cpp $(INCS)
	g++ $(CFLGS) Utils.cpp

clean :
	rm *.o
