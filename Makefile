SOURCES=*.cpp
CXX=g++

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
	@ $(CXX) $(SOURCES) -o $(OUT)

all+run: all
	@ $(RUNPREFIX)$(OUT)

clean:
	@ $(RM) $(OUT)

test: test1

test1: $(OUT) ./tests/test1_input.txt ./tests/test1_correct.txt
	@./$(OUT) < ./tests/test1_input.txt > ./tests/test1_output.txt
	diff ./tests/test1_correct.txt ./tests/test1_output.txt
#	@$(RM) ./tests/outputXY.txt
