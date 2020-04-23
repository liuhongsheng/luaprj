TARGET = array.so 

# 定义编译参数
CC = gcc
CXX = g++
CFLAGS = -g -O2 -Wall
SHARED := -fPIC -shared
LDFLAGS = -Wl,-R /usr/local/lib


#定义命令参数
RM := rm -fr
CP := cp -fr

# 定义目录
DESTDIR := ../bin/

# 定义子目录
SUB_DIR := 

#定义bin目录
BIN := ../bin

#获取当前目录
PWD := $(shell pwd)

#获取源文件
SOURCES = $(wildcard $(PWD)/*.c)

#获取obj文件【变量替换】
OBJECTS = $(SOURCES:.c=.o)

#定义源文件搜索路径
vpath %.c = $(PWD)/

#定义头文件搜索路径
vpath %.h = $(PWD)/

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


#静态模式
$(OBJECTS):%.o:%.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) $(LIBDIRS) $(LIBS) $(SHARED) $(INCLUDES) $< -o $@


clean:
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)
	$(RM) $(DESTDIR)$(TARGET)


install:
	$(CP) $(TARGET) $(DESTDIR)$(TARGET)
	$(RM) $(TARGET)
	$(RM) $(OBJECTS)