
VERSION  =1.00
CC   =gcc
CPP =g++
LD = g++
DEBUG   =-DUSE_DEBUG
CFLAGS  =-Wall
SRC_C   = $(wildcard ../resources/*.c) $(wildcard ./*.c)
SRC_CPP= $(wildcard ./*.cpp)
INCLUDES   =-I. -I../resources -I./include
TEST_SET?=$(wildcard ./test*.txt)
# LIB_NAMES  =-lfun_a -lfun_so
# LIB_PATH  =-L./lib
OBJ   =$(patsubst %.c, %.o, $(SRC_C)) $(patsubst %.cpp, %.o, $(SRC_CPP))
TARGET  =app_$(VERSION)
#links
$(TARGET):$(OBJ)
	@mkdir -p output
	$(LD) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o output/$(TARGET)
	@rm -rf $(OBJ)

#compile
%.o: %.c
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@


run:$(TARGET)
	./output/$(TARGET)

test:$(TARGET)
	cat ${TEST_SET} | ./output/$(TARGET)


.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output
