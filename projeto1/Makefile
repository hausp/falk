###############################################################################
######################## Copyright 2016 Marleson Graf #########################
############################ <aszdrick@gmail.com> #############################
###############################################################################

################################## VARIABLES ##################################
# Directories
SRCDIR    :=src
HDRDIR    :=include
BUILDIR   :=build
BINDIR    :=.
TESTDIR   :=tests
DEPDIR    :=.deps
MAKEDIR   :=$(BINDIR) $(SRCDIR) $(HDRDIR)
# Compiler & linker flags
CXX       :=clang++
LDLIBS    :=-lgtest -pthread
LDFLAGS   :=
CXXFLAGS  :=-std=c++14 -fcxx-exceptions -Wno-deprecated-register -Wall\
            -Wno-unused-function -Wno-unneeded-internal-declaration
INCLUDE   :=-I$(HDRDIR)
# MaKefile eXtension variables
MKXFILES  :=$(wildcard *.mkx)
MKXCLEAN  :=$(patsubst %.mkx,clean_%,$(MKXFILES))
# Files
SRC       :=$(shell find $(SRCDIR) -name '*.cpp')
DEP       :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(SRC))
OBJ       :=$(patsubst %.cpp,$(BUILDIR)/%.o,$(SRC))
MAIN      :=main
EXEC      :=$(BINDIR)/lukacompiler
PUREOBJ   :=$(filter-out $(BUILDIR)/$(SRCDIR)/$(MAIN).o,$(OBJ))
TSTFILE   :=$(shell find $(TESTDIR) -name '*.cpp' 2> /dev/null)
TSTDEP    :=$(patsubst %.cpp,$(DEPDIR)/%.d,$(TSTFILE))
TSTOBJ    :=$(patsubst %.cpp,$(BUILDIR)/%.o,$(TSTFILE))
TSTEXEC   :=$(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%,$(TSTFILE))

.PHONY: all makedir clean clean_deps clean_all tests

################################# MAIN RULES ##################################
all: makedir $(EXEC)

-include $(MKXFILES)

$(EXEC): $(OBJ)
	@echo "[linking] $@"
	@$(CXX) $^ -o $@ $(LDLIBS) $(LDFLAGS)

$(BUILDIR)/%.o: %.cpp
	@echo "[$(CXX)] $< -> .o"
	@mkdir -p $(BUILDIR)/$(*D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# For each .cpp file, creates a .d file with all dependencies of .cpp,
# including .d as target (to ensure up-to-date dependencies, in case of
# new includes being added)
$(DEPDIR)/%.d: %.cpp
	@echo "[makedep] $< -> .d"
	@mkdir -p $(DEPDIR)/$(*D)
	@$(CXX) $< $(INCLUDE) $(CXXFLAGS)\
	 -MM -MG -MP -MT "$(BUILDIR)/$*.o $@" -MF "$@"

makedir: | $(MAKEDIR)

$(MAKEDIR):
	@echo "[ mkdir ] Creating directory '$@'"
	@mkdir -p $@

################################ TESTS RULES ##################################
tests: makedir $(TSTEXEC)

$(TSTEXEC): $(PUREOBJ) $(TSTOBJ)
	@echo "[linking] $@"
	@$(CXX) $(PUREOBJ) $(BUILDIR)/$(TESTDIR)/$(@F).o -o $@ $(LDLIBS) $(LDFLAGS)

################################ CLEAN RULES ##################################
# Only remove object files
clean: $(MKXCLEAN)
	@$(RM) -r $(BUILDIR)

# Only remove dependency files
clean_deps: $(MKXCLEAN_DEPS)
	@$(RM) -r $(DEPDIR)

# Remove object, binary and dependency files
clean_all: clean clean_deps
	@$(RM) $(EXEC) $(TSTEXEC)

################################ PREREQUISITES ################################
# Do not include list of dependencies when they are going to be deleted, i.e.,
# when the target is clean_all or clean_deps
ifneq ($(MAKECMDGOALS), clean_all)
  ifneq ($(MAKECMDGOALS), clean_deps)
    -include $(DEP)
    ifeq ($(MAKECMDGOALS), tests)
      -include $(TSTDEP)
    endif
  endif
endif
