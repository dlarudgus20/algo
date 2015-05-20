## @file makefile
## @author dlarudgus20

##################
# parameter      #
##################
# PROJECT_NAME   #
# LIBS           #
##################

# config
ifeq ($(CONFIG), Release)
	# ok
else ifeq ($(CONFIG), Debug)
	# ok
else ifeq ($(CONFIG), )
	# default to Debug
	CONFIG := Debug
else
	$(error [CONFIG] '$(CONFIG)': unknown configuration.)
endif

# directories
DIR_BIN := bin/$(CONFIG)
DIR_DEP := dep/$(CONFIG)
DIR_OBJ := obj/$(CONFIG)
DIR_SRC := src

DIR_DEPENS := $(DIR_BIN) $(DIR_DEP) $(DIR_OBJ)

# tools
GDB := gdb

# flags
CXXFLAGS := -std=c++11 -I$(DIR_SRC) -static \
	-Wall -Wextra -Wno-unused-parameter

ifeq ($(CONFIG), Release)
CXXFLAGS := $(CXXFLAGS) -DNDEBUG -Ofast -flto
else
CXXFLAGS := $(CXXFLAGS) -DDEBUG -O0 -ggdb
endif

# files
OUTPUT_FILE := $(DIR_BIN)/$(PROJECT_NAME)

CXX_SOURCES := $(wildcard $(DIR_SRC)/*.cpp)
CXX_OBJECTS := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.cpp.o, $(CXX_SOURCES))

DEPENDENCIES := $(patsubst $(DIR_SRC)/%.cpp, $(DIR_DEP)/%.cpp.d, $(CXX_SOURCES))

# phony targets
.PHONY: all rebuild run rerun run-dbg distclean clean mostlyclean dep-clean
NODEPEN_TARGETS := rebuild rerun distclean clean mostlyclean dep-clean

all: $(OUTPUT_FILE)

rebuild:
	make clean
	make

run:
	make all
	$(OUTPUT_FILE)

rerun:
	make clean
	make run

run-dbg:
	make all
	$(GDB) $(OUTPUT_FILE)

distclean: clean
	-rmdir $(DIR_OBJ)
	-rmdir obj
	-rmdir $(DIR_DEP)
	-rmdir dep
	-rmdir $(DIR_BIN)
	-rmdir bin

clean: mostlyclean dep-clean
	-$(RM) $(DIR_BIN)/*
	-$(RM) $(OUTPUT_FILE)

mostlyclean:
	-$(RM) $(DIR_OBJ)/*

dep-clean:
	-$(RM) $(DIR_DEP)/*

# rules
$(OUTPUT_FILE): $(CXX_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(DIR_OBJ)/%.cpp.o: $(DIR_SRC)/%.cpp makefile | $(DIR_DEPENS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(DIR_DEP)/%.cpp.d: $(DIR_SRC)/%.cpp makefile | $(DIR_DEPENS)
	$(CXX) $(CXXFLAGS) $< -MM -MT $(DIR_OBJ)/$*.cpp.o \
		| sed 's@\($(DIR_OBJ)/$*.cpp.o\)[ :]*@\1 $@ : @g' > $@

$(DIR_DEPENS):
	mkdir -p bin
	mkdir -p $(DIR_BIN)
	mkdir -p dep
	mkdir -p $(DIR_DEP)
	mkdir -p obj
	mkdir -p $(DIR_OBJ)

# include dependencies
ifeq ($(filter $(NODEPEN_TARGETS), $(MAKECMDGOALS)), )
include $(DEPENDENCIES)
endif
