# 1、准备工作，编译方式、目标文件名、依赖库路径的定义。
CROSS=

CC=${CROSS}gcc
CFLAGS  := -Wall -g -O3 -std=gnu99

OBJS = io_posix.o io.o sha3.o util.o internal.o ethtool.o #.o文件与.cpp文件同名
TARGET=ethtool


# 依赖的lib名称
LD_FLAGS := -lm

all : $(TARGET)

# 2. 生成.o文件 
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# 3. 生成动态库文件
$(TARGET) : $(OBJS)
	rm -f $@
	$(CC) -o $@ $(OBJS) $(LD_FLAGS)
	rm -f $(OBJS)


# 4. 删除中间过程生成的文件 
clean:
	rm -f $(OBJS) $(TARGET) 

install:
	cp -f $(LIB) $(INSTALL_DIR)
