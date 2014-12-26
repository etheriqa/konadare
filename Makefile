SRC_DIR = src
DEPEND = Makefile.depends

SRCS = $(shell find $(SRC_DIR) -name '*_test.cc')
OBJS = $(SRCS:.cc=.o)

GTEST_DIR = vendor/gtest-1.7.0/fused-src
GTEST_SRCS = $(GTEST_DIR)/gtest/gtest-all.cc \
	     $(GTEST_DIR)/gtest/gtest_main.cc
GTEST_OBJS = $(GTEST_SRCS:.cc=.o)

CPPFLAGS += -I$(GTEST_DIR) -I$(SRC_DIR)
CXXFLAGS += -std=c++11 -g -pthread -O2

.PHONY: all test depend clean

all: dist/universal dist/vimcoder

dist/universal: templates/header.cc templates/clang++.h $(shell find templates/universal/**)
	rm -fr $@
	mkdir -p $@
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/universal/clang++.h@ templates/universal/Makefile > $@/Makefile
	cat templates/header.cc templates/universal/solution.cc > $@/solution.cc
	cp templates/universal/checker.sh $@
	cp templates/clang++.h $@

dist/vimcoder: templates/header.cc templates/clang++.h $(shell find templates/vimcoder/**)
	rm -fr $@
	mkdir -p $@
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/vimcoder/clang++.h@ templates/vimcoder/Makefile > $@/C++Makefile
	cat templates/header.cc templates/vimcoder/solution.cc > $@/C++Template
	cp templates/clang++.h $@

dist/%: dist/universal
	rm -fr $@
	cp -r dist/universal $@

depend:
	cat /dev/null > $(DEPEND)
	$(foreach src,$(SRCS),$(CXX) $(CPPFLAGS) -MM -MT $(src:.cc=.o) $(src) >> $(DEPEND);)

build/test: $(OBJS) $(GTEST_OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

build/%_test: $(SRC_DIR)/%_test.o $(GTEST_OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

test:
	make build/$@
	./build/$@

%_test:
	[ -f $(SRC_DIR)/$@.cc ]
	make build/$@
	./build/$@

clean:
	rm -f $(OBJS)
	rm -f $(GTEST_OBJS)
	rm -fr build/*
	rm -fr dist/*

-include $(DEPEND)
