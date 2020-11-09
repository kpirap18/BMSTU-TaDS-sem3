CFILES := $(wildcard *.c)
OBJECTS := $(CFILES:%.c=%.o)
FLAGS := -pedantic -Wall -Werror -Wextra -Wvla -Wfloat-equal -Wfloat-conversion -std=c99

app.exe: $(OBJECTS) *.h
	gcc $(FLAGS) $(OBJECTS) -o app.exe

%.o: %.c *.h
	gcc $(FLAGS) -c $<

run: app.exe
	./app.exe
	
# .PHONY - чтобы не было конфликтов с файлами
.PHONY : clean 
clean:
	$(RM) *.o *.exe
