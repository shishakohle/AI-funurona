SOURCES=*.cpp
OUT=funorona.out
CXX=g++
RM=rm -f

all: $(SOURCES)
	@ $(CXX) $(SOURCES) -o $(OUT)

clean:
	@ $(RM) $(OUT)

# test: test1 test2 test3

# testXY:
#	@./funorona.out < ./tests/inputXY.txt > ./tests/outputXY.txt
#	diff ./tests/correctXY.txt ./tests/outputXY.txt
#	@$(RM) ./tests/outputXY.txt

