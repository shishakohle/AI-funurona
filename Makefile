SOURCES=main.cpp
OUT=funorona.out
CXX=g++
RM=rm -f

all: $(SOURCES)
	$(CXX) $(SOURCES) -o $(OUT)

clean:
	$(RM) $(OUT)

