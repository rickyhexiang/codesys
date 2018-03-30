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
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/CmpModbusLib



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
PROJECT_TARGETS = CmpModbusLib/$(MODE_DIR)/CmpModbusLib.out


#Rules

# CmpModbusLib
ifeq ($(DEBUG_MODE),1)
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-builtin
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-builtin
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-builtin
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpModbusLib/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-builtin
endif
CmpModbusLib/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(WIND_BASE)/target/h/wrn/coreip 
CmpModbusLib/$(MODE_DIR)/% : IDE_LIBRARIES = 
CmpModbusLib/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DMIXED_LINK -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
CmpModbusLib/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CmpModbusLib/$(MODE_DIR)/% : DEFINES = 
CmpModbusLib/$(MODE_DIR)/% : EXPAND_DBG = 0
CmpModbusLib/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
CmpModbusLib/$(MODE_DIR)/% : CPU = ARMARCH7
CmpModbusLib/$(MODE_DIR)/% : TOOL_FAMILY = gnu
CmpModbusLib/$(MODE_DIR)/% : TOOL = gnu
CmpModbusLib/$(MODE_DIR)/% : TOOL_PATH = 
CmpModbusLib/$(MODE_DIR)/% : CC_ARCH_SPEC = -t7 -mfpu=vfp -mfloat-abi=softfp
CmpModbusLib/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
CmpModbusLib/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
CmpModbusLib/$(MODE_DIR)/% : LIBPATH = 
CmpModbusLib/$(MODE_DIR)/% : LIBS = 
CmpModbusLib/$(MODE_DIR)/% : OBJ_DIR := CmpModbusLib/$(MODE_DIR)

CmpModbusLib/$(MODE_DIR)/Objects/CmpModbusLib.o : $(PRJ_ROOT_DIR)/CmpModbusLib/CmpModbusLib.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP -std=c99  -mlong-calls $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_CmpModbusLib = CmpModbusLib/$(MODE_DIR)/Objects/CmpModbusLib.o

CmpModbusLib/$(MODE_DIR)/CmpModbusLib.out : $(OBJECTS_CmpModbusLib)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmarm $(OBJECTS_CmpModbusLib) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_CmpModbusLib) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CmpModbusLib/$(MODE_DIR)/CmpModbusLib_compile_file : $(FILE) ;

_clean :: CmpModbusLib/$(MODE_DIR)/CmpModbusLib_clean

CmpModbusLib/$(MODE_DIR)/CmpModbusLib_clean : 
	$(TRACE_FLAG)if [ -d "CmpModbusLib" ]; then cd "CmpModbusLib"; rm -rf $(MODE_DIR); fi

DEP_FILES := CmpModbusLib/$(MODE_DIR)/Objects/CmpModbusLib.d
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
