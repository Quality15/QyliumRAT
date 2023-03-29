# compiler
CC = g++

# flags
CFLAGS = -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -fpermissive

# target name
# TARGET = client

# source
SOURCE_DIR = src

# output
OUTPUT_DIR = build

all: client	server

client: client
	$(CC) -O2 $(SOURCE_DIR)/client.cpp -o $(OUTPUT_DIR)/client.exe $(CFLAGS)
server: server
	$(CC) -O2 $(SOURCE_DIR)/server.cpp -o $(OUTPUT_DIR)/server.exe $(CFLAGS)

clean:
	rm $(OUTPUT_DIR)/client.exe $(OUTPUT_DIR)/server.exe