TARGET = chat
PREFIX = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
	rm -rf *.a *.o

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)

$(TARGET): main.cpp lib
	g++ -o $(TARGET) main.cpp -L. -lMyLib

lib: Shell.cpp Shell.h LinkStorage.cpp LinkStorage.h ChatBox.cpp ChatBox.h UserStorage.cpp UserStorage.h User.h SHA1.h SHA1.cpp
	g++ -o Shell.o Shell.cpp -c
	g++ -o ChatBox.o ChatBox.cpp -c
	g++ -o UserStorage.o UserStorage.cpp -c
	g++ -o User.o User.h -c
	g++ -o LinkStorage.o LinkStorage.cpp -c
	g++ -o SHA1.o SHA1.cpp -c
	ar rc libMyLib.a Shell.o LinkStorage.o ChatBox.o UserStorage.o User.o SHA1.o
