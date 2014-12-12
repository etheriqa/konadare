CXX      = clang++
CXXFLAGS = -std=c++11 -g -O2 -include {{CLANG_HEADER_PATH}}
TARGET   = solver

.PHONY: all clean test copy

all: $(TARGET) test

clean:
	rm -f $(TARGET)

test: all
	./checker.sh ./$(TARGET)

copy:
	cat $(TARGET).cc | pbcopy
