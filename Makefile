all: usefoursort useparfoursort

usefoursort: UseFourSort.c FourSort.o
# usefoursort: UseFourSort.c  FourSort.c 
# usefoursort: UseFourSort.c  FourSort.o 
# usefoursort: FourSort.o UseFourSort.c  
# usefoursort: FourSort.c UseFourSort.c  
# usefoursort: UseFourSort.c  
#	gcc -O2 -Wall -Werror -o $@ $^ -lm -I.
	gcc -O2 -Wall -Werror -o $@ $^ -lm 

useparfoursort: UseParFourSort.c ParFourSort.o
	gcc -O2 -Wall -Werror -o $@ $^ -lm -lpthread

clean:
	$(RM) usefoursort useparfoursort *.o
