GTEST_DIR = vendor/gtest-1.7.0
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS = $(GTEST_DIR)/src/*.cc \
             $(GTEST_DIR)/src/*.h \
             $(GTEST_HEADERS)

CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -std=c++11 -pthread -O2

.PHONY: all universal vimcoder test clean distclean

all: universal vimcoder

universal:
	mkdir -p dist/universal
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/universal/clang++.h@ templates/universal/Makefile > dist/universal/Makefile
	cat templates/header.cc templates/universal/solver.cc > dist/universal/solver.cc
	cp templates/universal/checker.sh dist/universal/
	cp templates/clang++.h dist/universal/

vimcoder:
	mkdir -p dist/vimcoder
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/vimcoder/clang++.h@ templates/vimcoder/Makefile > dist/vimcoder/C++Makefile
	cat templates/header.cc templates/vimcoder/solver.cc > dist/vimcoder/C++Template
	cp templates/clang++.h dist/vimcoder/

build/gtest-all.o: $(GTEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

build/gtest_main.o: $(GTEST_SRCS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

build/gtest_main.a: build/gtest-all.o build/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

build/%_test.o: src/%.cc src/%_test.cc $(GTEST_HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(patsubst build/%.o,src/%.cc,$@) -o $@

build/%_test: build/%_test.o build/gtest_main.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

build/test-all: $(patsubst src/%.cc,build/%.o,$(wildcard src/*_test.cc)) build/gtest_main.a
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

%_test: build/%_test
	./build/$@

test: build/test-all
	./build/test-all

clean:
	rm -rf build/*
	rm -rf dist/*
	rm -f *.a
	rm -f *.o
	rm -f **/*.a
	rm -f **/*.o

distclean: clean
	rm -rf vendor/*

.DEFAULT:
	rm -rf dist/$@
	cp -r dist/universal dist/$@
