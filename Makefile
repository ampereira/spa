################################################################################
# Makefile for Simple Performance Analyser
#
# by André Pereira (LIP-Minho)
################################################################################

SHELL = /bin/sh

DEFINES = -Dextname

LIB_NAME = libspa

CXX        = g++
LD         = g++

CXXFLAGS   = -Wall -Wextra --std=c++11

ifeq ($(DEBUG),yes)
	CXXFLAGS += -ggdb3
else
	CXXFLAGS += -O3
endif

INCLUDES = -I/

################################################################################
# Control awesome stuff
################################################################################

SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
DEPS = $(patsubst build/%.o,build/%.d,$(OBJ))
LIB = $(addsufix .a, $(LIB_NAME))

vpath %.cpp $(SRC_DIR)

################################################################################
# Rules
################################################################################

.DEFAULT_GOAL = all

$(BUILD_DIR)/%.d: %.cpp
	$(CXX) -M $(CXXFLAGS) $(INCLUDES) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

$(LIB_DIR)/$(LIB_NAME).a: $(DEPS) $(OBJ)
	ar -r $@ $(OBJ)

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(LIB_DIR)

all: checkdirs $(LIB_DIR)/$(LIB_NAME).a

clean:
	rm -f $(BUILD_DIR)/* $(LIB_DIR)/* 