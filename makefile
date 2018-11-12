# -Wall == all warnings enabled
# -Werror == treat warnings as ERRORS!
CPPFLAGS = --std=c++11 -Wall -DBOOST_TEST_DYN_LINK
LINKFLAGS = --std=c++11 -lboost_unit_test_framework

test_SOURCES = \
	test.cpp \

test_OBJECTS=$(test_SOURCES:.cpp=.o)

test_EXECUTABLE = test_bin

all: test

%.o : %.c
	$(CXX) -c $(CPPFLAGS) $< -o $@

$(test_EXECUTABLE): $(test_OBJECTS) $(lib_OBJECTS)
	$(CXX) -o $@ $(test_OBJECTS) $(lib_OBJECTS) $(LINKFLAGS)

test: $(test_EXECUTABLE)
	./$(test_EXECUTABLE)


.PHONY: clean test

clean:
	- rm *.o
	- rm test_bin
