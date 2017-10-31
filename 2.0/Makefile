# Target appearing at the very top ensures this is the default target
default: run

### C/C++

CXX := g++
LINK := $(CXX)
AUTODEPS := $(CXX)

HEADERS := $(HEADERS) -I/usr/local/include

### Libraries ###

LDSDL := $(shell sdl2-config --libs)
LDMATH := -lm

### Flags ###

# CXXFLAGS is lazy expanded to allow for modification of HEADERS
# Note: -Wmissing-braces may be safely disabled as per http://stackoverflow.com/questions/13905200/is-it-wise-to-ignore-gcc-clangs-wmissing-braces-warning
CXXFLAGS = -Wall -Wextra -Wno-missing-braces -pedantic -g -std=c++11 $(shell sdl2-config --cflags) $(HEADERS) -pthread
LDFLAGS := $(LDFLAGS) $(LDSDL) -L/usr/local/lib $(LDMATH)
AUTODEPSFLAGS = -MM $(CXXFLAGS)

### Files and Paths ###

EXE := navalngage
TARGETS += $(EXE)

SRCDIRS :=common 3rdparty core render components go systems game math

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

MEMCHECK := valgrind
MEMCHECKFLAGS := --leak-check=full --track-origins=yes

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
	@echo "\033[36mCompiling $$<...\033[0m"
	$(CXX) $$< $(CXXFLAGS) -c -o $$@
	@echo "\033[36mGenerating dependencies for $$<...\033[0m"
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

.PHONY: default vg run build clean

debug:
	$(DEBUG) -f $(EXE) -s lldb

vg: build
	@echo "\033[90mRunning memcheck on $(EXE)...\033[0m"
	$(MEMCHECK) $(MEMCHECKFLAGS) ./$(EXE)

run: build
	@echo "\033[90mRunning $(EXE)...\033[0m"
	./$(EXE)

build: $(EXE)

$(EXE): $(TARGETS_OBJ)
	@echo "\033[34mLinking object files to create target $@...\033[0m"
	$(CXX) $^ $(LDFLAGS) -o $@
	@echo "\033[32mSuccessfully built $(EXE)!\033[0m"

clean:
	@echo "\033[33mRemoving targets...\033[0m"
	rm -f $(TARGETS)
	@echo "\033[33mRemoving directories...\033[0m"
	rm -rf $(CLEAN_DIRS)