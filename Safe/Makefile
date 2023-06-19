# Makefile
#
# zmienne nazwowe
NAME1 = sejfy
NAME2 = Graph_listImplementation
# Kompilator g++.
CC = g++
# Mozliwe dodatkowe zmienne
# LIBS = -ll -lm
LIBS =
CFLAGS = -Wall -std=c++11
# Pliki obiektowe - powstaja z plikow *.cpp.
OBJECT1 = $(NAME1).o
OBJECT2 = $(NAME2).o
OBJECTS = $(OBJECT1) $(OBJECT2)
# Pliki naglowkowe - sa wlaczane do plikow *.cpp.
HFILES = $(NAME2).h
# Koncowy plik wykonywalny.
TARGET = $(NAME1).out

# Definicja domyslnej reguly wzorcowej.
# $< oznacza nazwe pliku pierwszej zaleznosci reguly.
# $@ oznacza nazwe pliku celu w regule.
# Wszystkie pliki obiektowe zaleza od wszystkich plikow naglowkowych.
%.o : %.cpp $(HFILES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $@

.PHONY : all

all : $(TARGET)

# Sprzatanie
.PHONY : clean

clean :
	$(RM) *.x *.o *.out core