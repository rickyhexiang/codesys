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

BUILD_SPEC = ARMARCH7diab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/CmpPulseOutput



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = arm
CPU = ARMARCH7
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV7LV:vxworks69
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIXED_LINK -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_Linker =  -XO -Xsize-opt 
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif


#Project Targets
PROJECT_TARGETS = CmpPulseOutput/$(MODE_DIR)/CmpPulseOutput.out


#Rules

# CmpPulseOutput
ifeq ($(DEBUG_MODE),1)
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -XO -Xsize-opt 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpPulseOutput/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif
CmpPulseOutput/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(WIND_BASE)/target/h/wrn/coreip 
CmpPulseOutput/$(MODE_DIR)/% : IDE_LIBRARIES = 
CmpPulseOutput/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIXED_LINK -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
CmpPulseOutput/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CmpPulseOutput/$(MODE_DIR)/% : DEFINES = 
CmpPulseOutput/$(MODE_DIR)/% : EXPAND_DBG = 0
CmpPulseOutput/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
CmpPulseOutput/$(MODE_DIR)/% : CPU = ARMARCH7
CmpPulseOutput/$(MODE_DIR)/% : TOOL_FAMILY = diab
CmpPulseOutput/$(MODE_DIR)/% : TOOL = diab
CmpPulseOutput/$(MODE_DIR)/% : TOOL_PATH = 
CmpPulseOutput/$(MODE_DIR)/% : CC_ARCH_SPEC = -tARMV7LV:vxworks69
CmpPulseOutput/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
CmpPulseOutput/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
CmpPulseOutput/$(MODE_DIR)/% : LIBPATH = 
CmpPulseOutput/$(MODE_DIR)/% : LIBS = 
CmpPulseOutput/$(MODE_DIR)/% : OBJ_DIR := CmpPulseOutput/$(MODE_DIR)

CmpPulseOutput/$(MODE_DIR)/Objects/CmpPulseOutput.o : $(PRJ_ROOT_DIR)/CmpPulseOutput/CmpPulseOutput.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xfp-fast  -Xc-new -Xdialect-c89  -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_CmpPulseOutput = CmpPulseOutput/$(MODE_DIR)/Objects/CmpPulseOutput.o

CmpPulseOutput/$(MODE_DIR)/CmpPulseOutput.out : $(OBJECTS_CmpPulseOutput)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_CmpPulseOutput) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tARMV7LV:vxworks69 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_CmpPulseOutput) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CmpPulseOutput/$(MODE_DIR)/CmpPulseOutput_compile_file : $(FILE) ;

_clean :: CmpPulseOutput/$(MODE_DIR)/CmpPulseOutput_clean

CmpPulseOutput/$(MODE_DIR)/CmpPulseOutput_clean : 
	$(TRACE_FLAG)if [ -d "CmpPulseOutput" ]; then cd "CmpPulseOutput"; rm -rf $(MODE_DIR); fi

DEP_FILES := CmpPulseOutput/$(MODE_DIR)/Objects/CmpPulseOutput.d
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
