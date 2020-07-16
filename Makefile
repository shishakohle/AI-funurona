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
	@ echo " +++ [MAKE PROFILE] Execution profiling completed. +++"
	@ echo " +++ [MAKE PROFILE] Here's the log for the AI calculating their moves: +++"
	@ grep -A 2 'Each sample counts as 0.01 seconds.' profile.txt
	@ grep -m 1 'getAIUseraction' profile.txt
	@ echo " +++ [MAKE PROFILE] Checkout the profile.txt file for more... +++"

memcheck: clean $(SOURCES)
	@ $(RM) memcheck.txt
	@ $(CXX) $(SOURCES) -o $(OUT) -std=$(CXXSTANDARD) -g
	@ valgrind --log-file=memcheck.txt --tool=memcheck --leak-check=yes $(RUNPREFIX)$(OUT)
	@ echo
	@ echo " +++ [MAKE MEMCHECK] Execution memory check completed. Here's a summary for you: +++"
	@ grep -A 2 'HEAP SUMMARY' memcheck.txt
	@ grep -A 5 'LEAK SUMMARY' memcheck.txt || true
	@ grep -A 0 'All heap blocks were freed' memcheck.txt || true
	@ grep -A 0 'ERROR SUMMARY' memcheck.txt
	@ echo " +++ [MAKE MEMCHECK] Checkout the memcheck.txt file for more... +++"

