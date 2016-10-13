# Target appearing at the very top ensures this is the default target
default: run

### C/C++

CXX := g++
LINK := $(CXX)
AUTODEPS := $(CXX)

HEADERS := $(HEADERS) -I/usr/local/include

### Libraries ###

LDSDL := `sdl2-config --libs`
LDMATH := -lm

### Flags ###

# CXXFLAGS is lazy expanded to allow for modification of HEADERS
CXXFLAGS = -Wall -pedantic -g -std=c++11 $(HEADERS)
LDFLAGS := $(LDFLAGS) $(LDSDL) -L/usr/local/lib $(LDMATH)
AUTODEPSFLAGS = -MM $(CXXFLAGS)

### Files and Paths ###

EXE := navalngage
TARGETS += $(EXE)

SRCDIRS :=common core render components go systems game

# For convenience, allow all of our source directories to be valid include paths
define ADD_INCLUDE
HEADERS += -I$(1)
endef
$(foreach dir,$(SRCDIRS),$(eval $(call ADD_INCLUDE,$(dir))))

### Environment Variables ###

# ENV := LD_LIBRARY_PATH=/usr/local/lib

### Profiler/Debugger ###

ifeq ($(CXX), g++)
	DEBUG := gdb
else ifeq ($(CXX), clang++)
	DEBUG := lldb
endif

### Templates ###

define COMPILE_TEMPLATE
# $(1) => SRCDIR
# $(2) => OBJDIR
# $(3) => DEPSDIR

SRC_$(1) := $$(wildcard $(1)/*.cpp)
OBJ_$(1) := $$(patsubst $(1)/%.cpp,$(2)/%.o,$$(SRC_$(1)))
DEPS_$(1) := $$(patsubst $(1)/%.cpp,$(3)/%.d,$$(SRC_$(1)))

TARGETS +=$$(OBJ_$(1)) $$(DEPS_$(1))
TARGETS_OBJ +=$$(OBJ_$(1))
CLEAN_DIRS +=$(2) $(3)

# Pull in deps info for existing .o files
-include $$(DEPS_$(1))

$(2)/%.o: $(1)/%.cpp
	@mkdir -p $(2) $(3)
	@echo Compiling $$<...
	$(CXX) $$< $(CXXFLAGS) -c -o $$@
	@echo Generating dependencies for $$<...
	$(AUTODEPS) $$< $(AUTODEPSFLAGS) -o $(3)/$$*.d
	@# Based on http://scottmcpeak.com/autodepend/autodepend.html
	@mv -f $(3)/$$*.d $(3)/$$*.d.tmp
	@sed -e 's|.*:|$(2)/$$*.o:|' < $(3)/$$*.d.tmp > $(3)/$$*.d
	@sed -e 's/.*://' -e 's/\\$$$$//' < $(3)/$$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$$$/:/' >> $(3)/$$*.d
	@rm -f $(3)/$$*.d.tmp
endef

### Templatize the non-recursive make code when needed
# # Non-recursive make technique courtesy of https://evbergen.home.xs4all.nl/nonrecursive-make.html

# ### Push ###
# sp := $(sp).x
# dirstack_$(sp) := $(d)
# d := $(dir)

# ### BEGIN ###

# ### END ###

# ### Pop ###
# d := $(dirstack_$(sp))
# sp := $(basename $(sp))

### Run root directory rules ###

SRCDIR := .
OBJDIR := debug
DEPSDIR := $(OBJDIR)
$(eval $(call COMPILE_TEMPLATE,$(SRCDIR),$(OBJDIR),$(DEPSDIR)))

### Run subdirectory rules ###

$(foreach dir,$(SRCDIRS),$(eval $(call COMPILE_TEMPLATE,$(dir)/$(SRCDIR),$(dir)/$(OBJDIR),$(dir)/$(DEPSDIR))))

# define INCLUDE_MAKEFILES
# include $(1)/Makefile
# endef
# $(foreach dir,$(SRCDIRS),$(eval $(call INCLUDE_MAKEFILES,$(dir))))

### Main rules ###

.PHONY: default build run debug clean

debug:
	$(DEBUG) -f $(EXE) -s lldb

run: build
	@echo Running $(EXE)...
	./$(EXE)

build: $(EXE)

$(EXE): $(TARGETS_OBJ)
	@echo Linking $^...
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	@echo Removing targets...
	rm -f $(TARGETS)
	@echo Removing directories...
	rm -rf $(CLEAN_DIRS)