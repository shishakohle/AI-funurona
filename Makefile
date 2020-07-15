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
	@ $(RM) gmon.out

test: $(OUT)
	@ $(RUNPREFIX)$(OUT)

profile: clean $(SOURCES)
	@ $(RM) profile.txt
	@ $(CXX) $(SOURCES) -o $(OUT) -std=$(CXXSTANDARD) -pg
	@ $(RUNPREFIX)$(OUT)
	@ gprof $(RUNPREFIX)$(OUT) gmon.out > profile.txt
	@ $(RM) gmon.out
	@ echo
	@ echo " +++ [MAKE PROFILE] Profiling completed. Here's a small sample for you: '+++"
	@ grep -A 5 'Each sample counts as 0.01 seconds.' profile.txt
	@ echo " +++ [MAKE PROFILE] Checkout the profile.txt file for more... +++"

