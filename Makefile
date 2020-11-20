all: usefoursort useparfoursort

usefoursort: UseFourSort.c FourSort.o
	gcc -O2 -Wall -Werror -o $@ $^ -lm

useparfoursort: UseParFourSort.c ParFourSort.o
	gcc -O2 -Wall -Werror -o $@ $^ -lm -lpthread

clean:
	$(RM) usefoursort useparfoursort *.o
