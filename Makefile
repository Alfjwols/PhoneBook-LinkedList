CC = g++
TARGET = phoneBook
CFLAGS = -Wall -Wextra -c

all: $(TARGET)

$(TARGET): PhoneBook.o main.o
	$(CC) PhoneBook.o main.o -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

PhoneBook.o: PhoneBook.cpp PhoneBook.h
	$(CC) $(CFLAGS) PhoneBook.cpp -o PhoneBook.o

clean:
	rm -f PhoneBook.o main.o $(TARGET)
