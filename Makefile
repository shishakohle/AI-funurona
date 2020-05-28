SOURCES=*.cpp
CXX=g++
CXXSTANDARD=c++11

ifeq ($(OS),Windows_NT)
	OUT=funorona.exe
	RM=if exist $(OUT) del /F /Q
#	RUNPREFIX=
else
	OUT=funorona.out
	RM=rm -rf
	RUNPREFIX=./
endif

all: clean $(SOURCES)
	@ $(CXX) $(SOURCES) -o $(OUT) -std=$(CXXSTANDARD)

all+run: all
	@ $(RUNPREFIX)$(OUT)

clean:
	@ $(RM) $(OUT)

test: test1

test1: $(OUT) ./tests/test1_input.txt ./tests/test1_correct.txt
	@./$(OUT) < ./tests/test1_input.txt > ./tests/test1_output.txt
	diff ./tests/test1_correct.txt ./tests/test1_output.txt
#	@$(RM) ./tests/outputXY.txt
