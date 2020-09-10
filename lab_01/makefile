CC = gcc

CFLAGS = -std=c99 -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wenum-compare -Wfloat-equal -Wredundant-decls

app.exe : print.o normalization.o trans.c correct.o divistion.o main.o
	$(CC) -o app.exe print.o normalization.o trans.c correct.o divistion.o main.o


main.o : main.o print.h normalization.h trans.c correct.h divistion.h main.h
	$(CC) $(CFLAGS) -c main.c

normalization.o  : normalization.o 
	$(CC) $(CFLAGS) -c normalization.c

print.o  : print.o print.h normalization.h trans.c correct.h divistion.h main.h
	$(CC) $(CFLAGS) -c print.c
	
trans.o  : trans.o print.h normalization.h trans.c correct.h divistion.h main.h
	$(CC) $(CFLAGS) -c trans.c
	
correct.o  : correct.o print.h normalization.h trans.c correct.h divistion.h main.h
	$(CC) $(CFLAGS) -c correct.c
	
divistion.o  : divistion.o print.h normalization.h trans.c correct.h divistion.h main.h
	$(CC) $(CFLAGS) -c divistion.c
	
clean:././
	rm *.o *.exe