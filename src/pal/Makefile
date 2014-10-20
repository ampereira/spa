#!/bin/sh

CXX = g++
CXX_FLAGS = -O3 -Wall -Wextra -std=c++11
PAPI_DIR = /home/ampereira/tools/papi-gcc4.9.0
LIB_FLAGS = -I$(PAPI_DIR)/include -L$(PAPI_DIR)/lib
PAPI_FLAGS = -lpapi

BUILD_DIR = build
SRC_DIR = src
LIB_DIR = lib
TEST_DIR = examples

default: pal

event.o: $(SRC_DIR)/event.cpp $(SRC_DIR)/event.h
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/event.o $(SRC_DIR)/event.cpp

eventset.o: $(SRC_DIR)/eventset.cpp $(SRC_DIR)/eventset.h $(SRC_DIR)/event.h $(SRC_DIR)/errors.h
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/eventset.o $(SRC_DIR)/eventset.cpp $(PAPI_FLAGS)

measure.o: $(SRC_DIR)/pal_measure.cpp $(SRC_DIR)/pal_measure.h $(SRC_DIR)/eventset.h
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/measure.o $(SRC_DIR)/pal_measure.cpp $(PAPI_FLAGS)

pal.o: $(SRC_DIR)/pal.cpp $(SRC_DIR)/pal.h $(SRC_DIR)/pal_measure.h
	$(CXX) $(CXX_FLAGS) $(LIB_FLAGS) -c -o $(BUILD_DIR)/pal.o $(SRC_DIR)/pal.cpp $(PAPI_FLAGS)

pal: event.o eventset.o measure.o pal.o
	ar -r libpal.a $(BUILD_DIR)/pal.o $(BUILD_DIR)/event.o $(BUILD_DIR)/eventset.o $(BUILD_DIR)/measure.o $(PAPI_FLAGS)
	@mv libpal.a $(LIB_DIR)/libpal.a

test: pal $(TEST_DIR)/test.cpp
	$(CXX) -O3 -Wall -Wextra -o examples/test.out $(LIB_FLAGS) -L/home/ampereira/spa/src/pal/lib examples/test.cpp -lpapi -lpal

#test2: pal.o event.o errors.o eventset.o measure.o $(TEST_DIR)/test.cpp
#	$(CXX) -g -Wall -Wextra -o examples/test.out build/pal.o build/event.o build/eventset.o build/errors.o build/measure.o examples/test.cpp -lpapi

clean:
	rm -f $(BUILD_DIR)/*.o $(LIB_DIR)/*