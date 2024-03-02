CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -fprofile-arcs -ftest-coverage
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TESTFLAGS += -g -lgtest -lstdc++
SRC = ./model/calc_model.cc
OBJ = calc_model.o
TEST = ./model/calc_test.cc
LIB = ./model/calc_model.a
REPORT = GcovReport
VIEW = makefile.qt
PROFILE =./view/SmartCalc_v2.pro
ARCHIVE = Archive_SmartCalc_v2
OS= $(shell uname -s)

ifeq ($(OS), Linux)
  CC+= -D OS_LINUX
  TESTFLAGS+= -lgmock -pthread -lm
  OS_COMMAND = @valgrind --leak-check=yes -s ./
  EXEC=SmartCalc_v2
endif
ifeq ($(OS), Darwin)
  CC+= -D OS_MAC
  OS_COMMAND = leaks --atExit -- ./
  EXEC=SmartCalc_v2.app
endif

all: style test install

calc_model.a:
	$(CC) $(CFLAGS) $(SRC) -c
	ar rcs $(LIB) $(OBJ)

test: calc_model.a
	$(CC) $(CFLAGS) $(TEST) $(LIB) $(TESTFLAGS) -o test.out
	@./test.out

install: clean
	mkdir build
	qmake -o $(VIEW) $(PROFILE) && make -f $(VIEW) && make clean -f $(VIEW) && rm $(VIEW) && mv $(EXEC) build
	open ./build/$(EXEC)

uninstall:
	rm -rf build*

dist:
	@rm -rf $(ARCHIVE)/
	@mkdir $(ARCHIVE)/
	@mkdir $(ARCHIVE)//src
	@mv ./build/$(EXEC) ./$(ARCHIVE)/src/
	tar cvzf $(ARCHIVE).tgz $(ARCHIVE)/src 
	@rm -rf $(ARCHIVE)

dvi:
	open dvi.pdf

gcov_report:
	$(CC) $(GCOVFLAGS) $(TEST) $(SRC) $(TESTFLAGS) -o $(REPORT)
	@chmod +x *
	@./$(REPORT)
	lcov --capture --directory . --output-file GcovReport.info
	lcov --remove GcovReport.info "*/usr/*" --output-file GcovReportFiltered.info
	genhtml -o report GcovReportFiltered.info
	@rm -rf ./*.gcno ./*.gcda ./$(REPORT).*
	@open ./report/index.html
	@rm -rf GcovReport.info GcovReportFiltered.info
	@rm -rf report

rebuild: clean all

style:
	@cp ../materials/linters/.clang-format ./
	clang-format -n ./model/*.h --verbose
	clang-format -n ./model/*.cc --verbose
	clang-format -n ./view/*.h --verbose
	clang-format -n ./view/*.cpp --verbose
	clang-format -n ./controller/*.h --verbose
	clang-format -n ./controller/*.cpp --verbose
	@rm .clang-format

.PHONY: git
git: clean cs
	@if [ -z "$(filter-out git,$(MAKECMDGOALS))" ]; then \
		echo "Usage: make git <comment>"; \
		exit 1; \
	fi
	@git add ..
	@git commit -m "$(filter-out $@,$(MAKECMDGOALS))"
	@git push origin develop

cs:
	@cp ../materials/linters/.clang-format ./
	clang-format -i ./model/*.h --verbose
	clang-format -i ./model/*.cc --verbose
	clang-format -i ./view/*.h --verbose
	clang-format -i ./view/*.cpp --verbose
	clang-format -i ./controller/*.h --verbose
	clang-format -i ./controller/*.cpp --verbose
	@rm .clang-format

clean:
	@rm -rf *.out
	@rm -rf ./model/*.a
	@rm -rf *.o
	@rm -rf *.info
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf GcovReport
	@rm -rf report
	@rm -rf build*
	@ rm -rf ui_creditcalc.h ui_mainwindow.h test.out.dSYM makefile.qt
	
leaks: test
	$(OS_COMMAND)test.out
