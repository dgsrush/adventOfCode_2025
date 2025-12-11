INCS=\
	ReadFile.h\
	Utils.h

OBJS=\
	main.o\
	Utils.o\
	ReadFile.o

CFLGS=-c -mconsole -O3

day09.exe : $(OBJS) $(INCS)
	g++ -o day09.exe -mconsole -O3 $(OBJS)

main.o : main.cpp $(INCS)
	g++ $(CFLGS) main.cpp

ReadFile.o : ReadFile.cpp $(INCS)
	g++ $(CFLGS) ReadFile.cpp

Utils.o : Utils.cpp $(INCS)
	g++ $(CFLGS) Utils.cpp

clean :
	rm *.o
