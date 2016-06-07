clean:
	@echo
	cd collatz; make clean

config:
	git config -l

init:
	touch README
	git init
	git add README

pull:
	make clean
	@echo
	git pull
	git status

push:
	make clean
	@echo
	git add .travis.yml
	git add collatz
	git add makefile
	git commit -m "another commit"
	git push
	git status

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

sync:
	@rsync -r -t -u -v --delete             \
    --include "Collatz.c++"                 \
    --include "Collatz.h"                   \
    --include "RunCollatz.c++"              \
    --include "RunCollatz.in"               \
    --include "RunCollatz.out"              \
    --include "TestCollatz.c++"             \
    --include "TestCollatz.out"             \
    --exclude "*"                           \
    ../../projects/c++/collatz/ collatz

test:
	make clean
	@echo
	cd collatz; make test
