TARGET   = driver
SRC      = $CLASSNAME$.cc
CXXFLAGS = -std=c++11 -g -O2 -include {{CLANG_HEADER_PATH}}

.PHONY: test copy clean

$(TARGET): $(SRC)

test: $(TARGET)
	./$(TARGET)

copy:
	cat $(SRC) | pbcopy

clean:
	rm -f $(TARGET)
