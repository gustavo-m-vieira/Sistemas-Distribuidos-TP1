# Copiado do arquivo pingExample com pequenas alterações

# the compiler
CC = gcc

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

TARGET1 = receiveSignals
TARGET2 = sendSignals

receive: $(TARGET1)

$(TARGET1): $(TARGET1).c
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c

send: $(TARGET2)

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).c
