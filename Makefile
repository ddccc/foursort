all: usefoursort useparfoursort

usefoursort: UseFourSort.c FourSort.o
	gcc -Wall -Werror -lm -o $@ $^

useparfoursort: UseParFourSort.c ParFourSort.o
	gcc -Wall -Werror -lm -lpthread -o $@ $^

clean:
	$(RM) usefoursort useparfoursort *.o
