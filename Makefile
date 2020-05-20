SOURCES=*.cpp
CXX=g++
CXXSTANDARD=c++11

ifeq ($(OS),Windows_NT)
	OUT=funorona.exe
	RM=DEL /F /Q
#	RUNPREFIX=
else
	OUT=funorona.out
	RM=rm -f
	RUNPREFIX=./
endif

all: clean $(SOURCES)
	@ $(CXX) $(SOURCES) -o $(OUT) -std=$(CXXSTANDARD)

all+run: all
	@ $(RUNPREFIX)$(OUT)

clean:
	ifeq ($(OS),Windows_NT)
		@ IF EXIST $(OUT) $(RM) $(OUT)
	else
		@ $(RM) $(OUT)
	endif

test: test1

test1: $(OUT) ./tests/test1_input.txt ./tests/test1_correct.txt
	@./$(OUT) < ./tests/test1_input.txt > ./tests/test1_output.txt
	diff ./tests/test1_correct.txt ./tests/test1_output.txt
#	@$(RM) ./tests/outputXY.txt
