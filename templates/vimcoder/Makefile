CXX      = clang++
CXXFLAGS = -std=c++11 -g -O2 -include {{CLANG_HEADER_PATH}}
TARGET   = driver

.PHONY: all clean test copy

all: $(TARGET) test

clean:
	rm -f $(TARGET)

test: all
	./$(TARGET)

copy:
	cat $CLASSNAME$.cc | pbcopy

$(TARGET): $CLASSNAME$.cc
