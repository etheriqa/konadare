TARGET   = solver
SRC      = solution.cc
CXXFLAGS = -std=c++11 -g -O2 -include {{CLANG_HEADER_PATH}}

.PHONY: test copy clean

test: $(TARGET)
	./checker.sh ./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(TARGET) $(SRC)

copy:
	cat $(SRC) | pbcopy

clean:
	rm -f $(TARGET)
