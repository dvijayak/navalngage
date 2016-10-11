# Non-recursive make technique courtesy of https://evbergen.home.xs4all.nl/nonrecursive-make.html

### Push ###
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

### BEGIN ###

SRCDIR := $(d)
OBJDIR := $(d)/debug
DEPSDIR := $(OBJDIR)

$(eval $(call COMPILE_TEMPLATE,$(SRCDIR),$(OBJDIR),$(DEPSDIR)))

### END ###

### Pop ###
d := $(dirstack_$(sp))
sp := $(basename $(sp))