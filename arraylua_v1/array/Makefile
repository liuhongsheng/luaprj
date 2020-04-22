TARGET = libarraylua.so

# 定义编译参数
CC = gcc
CXX = g++
CFLAGS = -g -O2 -Wall
SHARED := -fPIC -shared
LDFLAGS = -Wl,-R /usr/local/lib


#定义命令参数
RM := rm -fr
CP := cp -r

# 定义目录
DESTDIR := ../bin/

# 定义子目录
SUB_DIR := 

PWD := $(shell pwd)
BIN := ../bin
SOURCES = $(wildcard $(PWD)/*.c)
OBJECTS = $(SOURCES:.c=.o)

#定义源文件搜索目录
vpath %.c = $(PWD)/

#定义头文件搜索路径
INCLUDES += -I. \
	-I/usr/include/lua5.1

#定义链接库搜索路径
LIBDIRS = 

#定义链接的库
LIBS += -llua5.1



 .PHONY : all clean install

all: $(TARGET)
 
$(TARGET):$(OBJECTS)
	$(CC) $(OBJECTS) $(SHARED) -o $(TARGET)


$(OBJECTS):%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBDIRS) $(LIBS) $(SHARED) $< -o $@


clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)


install:
	$(CP) $(TARGET) $(DESTDIR)$(TARGET)