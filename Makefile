.PHONY: all universal vimcoder clean

all: universal vimcoder

universal:
	mkdir -p dist/universal
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/universal/clang++.h@ universal/Makefile > dist/universal/Makefile
	cat header.cc universal/solver.cc > dist/universal/solver.cc
	cp universal/checker.sh dist/universal/
	cp clang++.h dist/universal/

vimcoder:
	mkdir -p dist/vimcoder
	sed s@{{CLANG_HEADER_PATH}}@$(PWD)/dist/vimcoder/clang++.h@ vimcoder/Makefile > dist/vimcoder/C++Makefile
	cat header.cc vimcoder/solver.cc > dist/vimcoder/C++Template
	cp clang++.h dist/vimcoder/

clean:
	rm -rf dist
