SOURCES=*.cpp
OUT=funorona.out
CXX=g++
RM=rm -f

all: $(SOURCES)
	@ $(CXX) $(SOURCES) -o $(OUT)

clean:
	@ $(RM) $(OUT)

test: test1

test1: $(OUT) ./tests/test1_input.txt ./tests/test1_correct.txt
	@./$(OUT) < ./tests/test1_input.txt > ./tests/test1_output.txt
	diff ./tests/test1_correct.txt ./tests/test1_output.txt
#	@$(RM) ./tests/outputXY.txt

