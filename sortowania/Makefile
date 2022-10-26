# Makefile
# spis polecen
# Make: all clean quicksort heapsort
#
# zmienne nazwowe
NAME1 = quicksort
NAME2 = heapsort
# Kompilator g++.
CC = g++
# Mozliwe dodatkowe zmienne
# LIBS = -ll -lm
LIBS =
CFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstaja z plikow *.cpp.
OBJECTS1 = $(NAME1).o
OBJECTS2 = $(NAME2).o
# Pliki naglowkowe - sa wlaczane do plikow *.cpp.
HFILES = 
# Koncowy plik wykonywalny.
EXEC1 = $(NAME1).out
EXEC2 = $(NAME2).out

# Definicja domyslnej reguly wzorcowej.
# $< oznacza nazwe pliku pierwszej zaleznosci reguly.
# $@ oznacza nazwe pliku celu w regule.
# Wszystkie pliki obiektowe zaleza od wszystkich plikow naglowkowych.
%.o : %.cpp $(HFILES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC1) : $(OBJECTS1)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS1) -o $@

$(EXEC2) : $(OBJECTS2)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS2) -o $@

.PHONY : run1, run2, all

all : $(EXEC1) $(EXEC2)

run1 : $(EXEC1)
	./$(EXEC1)

run2: $(EXEC2)
	./$(EXEC2)

# Sprzatanie
.PHONY : clean

clean :
	$(RM) *.x *.o *.out core