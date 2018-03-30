# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = ARMARCH7gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/IoDrvSpiIO



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = arm
CPU = ARMARCH7
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -t7 -mfpu=vfp -mfloat-abi=softfp
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DMIXED_LINK -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -O2  -fno-builtin
DEBUGFLAGS_C++-Compiler =  -O2  -fno-builtin
DEBUGFLAGS_Linker =  -O2  -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -O2  -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = IoDrvSpiIO/$(MODE_DIR)/IoDrvSpiIO.out


#Rules

# IoDrvSpiIO
ifeq ($(DEBUG_MODE),1)
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-builtin
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-builtin
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-builtin
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
IoDrvSpiIO/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-builtin
endif
IoDrvSpiIO/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(WIND_BASE)/target/h/wrn/coreip 
IoDrvSpiIO/$(MODE_DIR)/% : IDE_LIBRARIES = 
IoDrvSpiIO/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DMIXED_LINK -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
IoDrvSpiIO/$(MODE_DIR)/% : PROJECT_TYPE = DKM
IoDrvSpiIO/$(MODE_DIR)/% : DEFINES = 
IoDrvSpiIO/$(MODE_DIR)/% : EXPAND_DBG = 0
IoDrvSpiIO/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
IoDrvSpiIO/$(MODE_DIR)/% : CPU = ARMARCH7
IoDrvSpiIO/$(MODE_DIR)/% : TOOL_FAMILY = gnu
IoDrvSpiIO/$(MODE_DIR)/% : TOOL = gnu
IoDrvSpiIO/$(MODE_DIR)/% : TOOL_PATH = 
IoDrvSpiIO/$(MODE_DIR)/% : CC_ARCH_SPEC = -t7 -mfpu=vfp -mfloat-abi=softfp
IoDrvSpiIO/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
IoDrvSpiIO/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
IoDrvSpiIO/$(MODE_DIR)/% : LIBPATH = 
IoDrvSpiIO/$(MODE_DIR)/% : LIBS = 
IoDrvSpiIO/$(MODE_DIR)/% : OBJ_DIR := IoDrvSpiIO/$(MODE_DIR)

IoDrvSpiIO/$(MODE_DIR)/Objects/IoDrvSpiIO.o : $(PRJ_ROOT_DIR)/IoDrvSpiIO/IoDrvSpiIO.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP -std=c99  -mlong-calls $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_IoDrvSpiIO = IoDrvSpiIO/$(MODE_DIR)/Objects/IoDrvSpiIO.o

IoDrvSpiIO/$(MODE_DIR)/IoDrvSpiIO.out : $(OBJECTS_IoDrvSpiIO)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmarm $(OBJECTS_IoDrvSpiIO) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_IoDrvSpiIO) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

IoDrvSpiIO/$(MODE_DIR)/IoDrvSpiIO_compile_file : $(FILE) ;

_clean :: IoDrvSpiIO/$(MODE_DIR)/IoDrvSpiIO_clean

IoDrvSpiIO/$(MODE_DIR)/IoDrvSpiIO_clean : 
	$(TRACE_FLAG)if [ -d "IoDrvSpiIO" ]; then cd "IoDrvSpiIO"; rm -rf $(MODE_DIR); fi

DEP_FILES := IoDrvSpiIO/$(MODE_DIR)/Objects/IoDrvSpiIO.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

JOBS?=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS);\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
