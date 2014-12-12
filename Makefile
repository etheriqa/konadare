.PHONY: all universal vimcoder clean

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

clean:
	rm -rf dist

.DEFAULT:
	rm -rf dist/$@
	cp -r dist/universal dist/$@
