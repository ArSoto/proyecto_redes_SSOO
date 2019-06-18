prefix=/usr/local
CC = g++

CFLAGS = -g -Wall 
LDFLAGS = $(kdlib) -lm
SRC = Controller.cpp servidor/Server.cpp client/Client.cpp
OBJ = Controller.o server/Server.o client/Client.o
APP = Controller

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(APP) $(OBJ) $(LIBS) $(LDFLAGS)

/%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJ) $(APP)

install: $(APP)
	install -m 0755 $(APP) $(prefix)/bin

uninstall: $(APP)
	$(RM) $(prefix)/bin/$(APP)
