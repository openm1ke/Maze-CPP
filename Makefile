CXX=g++
CXX_FLAGS=-std=c++17 -Wall -Werror -Wextra -pedantic -g -fsanitize=address
LIBGTEST=-lgtest -lgtest_main $(LIBS)
OS:=$(shell uname -s)
BIN_NAME=Maze
ALL_FILES := main.cc $(wildcard s21_*.cc) $(wildcard */s21_*.cc) $(wildcard s21_*.h) $(wildcard */s21_*.h)
ifeq ($(OS), Darwin)
	FLAGS += -D MACOS
	OPEN:=open
	QMAKE:=qmake
else
	LIBS += -Lsubunit -lrt -lm -lpthread
	OPEN:=xdg-open
	QMAKE:=qmake6
endif

rebuild: clean all

all: clean gcov_report dvi install

clean: uninstall
	@rm -rf *.o *.gcda *.gcno gcov_test ./report ./build ./html ./latex CPPLINT.cfg cpplint.py

build: clean
	@mkdir -p ./build
	$(QMAKE) $(BIN_NAME).pro -o ./build/$(BIN_NAME)_makefile
	cd ./build && make -f $(BIN_NAME)_makefile
	rm -rf ./build/moc_* ./build/*.o ./build/*.h ./build/$(BIN_NAME)_makefile ./build/.qmake.stash

install: build
ifeq ($(OS), Darwin)
	open ./build/$(BIN_NAME).app/
else 
	./build/$(BIN_NAME)
endif

uninstall:
ifeq ($(OS), Darwin)
	@rm -rf ./build/$(BIN_NAME).app ./build/$(BIN_NAME).tar.gz
else
	@rm -rf ./build/$(BIN_NAME) ./build/$(BIN_NAME).tar.gz
endif

dist: build
ifeq ($(OS), Darwin)
	cd ./build && tar -czvf $(BIN_NAME).tar.gz $(BIN_NAME).app
else
	cd ./build && tar -czvf $(BIN_NAME).tar.gz $(BIN_NAME)
endif

tests: clean
	@$(CXX) $(CXX_FLAGS) ./tests/s21_test_model.cc ./model/s21_model.cc $(LIBGTEST) -o test
	@./test
	@rm -rf test

clf:
	clang-format -n --style=Google ${ALL_FILES}

cpk:
	cppcheck --language=c++ ${ALL_FILES}

cpl:
	@cp ../materials/linters/CPPLINT.cfg ../materials/linters/cpplint.py ./
	@python3 cpplint.py --extensions=cc,h ${ALL_FILES}
	@rm -rf CPPLINT.cfg cpplint.py

style: clf cpk cpl

fix_style:
	@clang-format -i --style=Google ${ALL_FILES}


gcov_report: clean
	@$(CXX) $(CXX_FLAGS) ./tests/s21_test_model.cc ./model/s21_model.cc --coverage $(LIBGTEST) -o gcov_test
	@./gcov_test
	@mkdir -p report
	@gcovr . -e "tests/*" --html --html-details report/index.html
	@rm -rf *.gcda *.gcno *.info gcov_test *.dSYM 
	@sh -c "if grep -iq microsoft /proc/version ; then cd ./report; cmd.exe /c start index.html; else $(OPEN) ./report/index.html; fi"

dvi:
	doxygen Doxyfile
	@sh -c "if grep -iq microsoft /proc/version ; then cd ./html; cmd.exe /c start index.html; else $(OPEN) ./html/index.html; fi"
