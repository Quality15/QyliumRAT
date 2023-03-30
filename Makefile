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

all: window client

client: client
	$(CC) -O2 $(SOURCE_DIR)/client.cpp -o $(OUTPUT_DIR)/client.exe $(CFLAGS)
window: window
	$(CC) -O2 $(SOURCE_DIR)/window.cpp $(SOURCE_DIR)/server.cpp -o $(OUTPUT_DIR)/Qylium.exe $(CFLAGS)

clean:
	rm $(OUTPUT_DIR)/client.exe $(OUTPUT_DIR)/server.exe