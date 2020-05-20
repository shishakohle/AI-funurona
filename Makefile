SOURCES=*.cpp
OUT=funorona.out
CXX=g++
CXXSTANDARD=c++11
RM=rm -f

all: clean $(SOURCES)
	@ $(CXX) $(SOURCES) -o $(OUT) -std=$(CXXSTANDARD)

all+run: all
	@./$(OUT)

clean:
	@ $(RM) $(OUT)

test: test1

test1: $(OUT) ./tests/test1_input.txt ./tests/test1_correct.txt
	@./$(OUT) < ./tests/test1_input.txt > ./tests/test1_output.txt
	diff ./tests/test1_correct.txt ./tests/test1_output.txt
#	@$(RM) ./tests/outputXY.txt

