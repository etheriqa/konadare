TARGET   = solver
SRC      = solution.cc
CXXFLAGS = -std=c++11 -g -O2 -include g++.h -include clang++.h

.PHONY: test copy copy-g++ copy-clang++ clean

test: $(TARGET)
	./checker.sh ./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $(TARGET) $(SRC)

copy: copy-g++

copy-g++:
	cat g++.h solution.cc | pbcopy

copy-clang++:
	cat clang++.h solution.cc | pbcopy

clean:
	rm -f $(TARGET)
