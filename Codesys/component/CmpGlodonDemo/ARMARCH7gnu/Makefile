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
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/CmpGlodonDemo



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

IDE_INCLUDES = -I$(WIND_BASE)/target/h/wrn/coreip -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(PRJ_ROOT_DIR)/include 

IDE_LIBRARIES = -L$(PRJ_ROOT_DIR)/lib -lglodoniot -lplatform 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DFUNCTION_SESSION_SET= -DENABLE_IOT_DEBUG -DENABLE_IOT_INFO -DENABLE_IOT_WARN -DENABLE_IOT_ERROR -DMIXED_LINK -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 



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
PROJECT_TARGETS = CmpGlodonDemo/$(MODE_DIR)/CmpGlodonDemo.out


#Rules

# CmpGlodonDemo
ifeq ($(DEBUG_MODE),1)
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-builtin
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-builtin
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-builtin
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CmpGlodonDemo/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-builtin
endif
CmpGlodonDemo/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/wrn/coreip -I$(WIND_BASE)/target/h -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Components -IC:/WindRiver/workspace/Cheery_0x1_ARM_VxWorks_V3.5.11.20/Platforms/VxWorks -I$(PRJ_ROOT_DIR)/include 
CmpGlodonDemo/$(MODE_DIR)/% : IDE_LIBRARIES = -L$(PRJ_ROOT_DIR)/lib -lglodoniot -lplatform 
CmpGlodonDemo/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DFUNCTION_SESSION_SET= -DENABLE_IOT_DEBUG -DENABLE_IOT_INFO -DENABLE_IOT_WARN -DENABLE_IOT_ERROR -DMIXED_LINK -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
CmpGlodonDemo/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CmpGlodonDemo/$(MODE_DIR)/% : DEFINES = 
CmpGlodonDemo/$(MODE_DIR)/% : EXPAND_DBG = 0
CmpGlodonDemo/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
CmpGlodonDemo/$(MODE_DIR)/% : CPU = ARMARCH7
CmpGlodonDemo/$(MODE_DIR)/% : TOOL_FAMILY = gnu
CmpGlodonDemo/$(MODE_DIR)/% : TOOL = gnu
CmpGlodonDemo/$(MODE_DIR)/% : TOOL_PATH = 
CmpGlodonDemo/$(MODE_DIR)/% : CC_ARCH_SPEC = -t7 -mfpu=vfp -mfloat-abi=softfp
CmpGlodonDemo/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
CmpGlodonDemo/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
CmpGlodonDemo/$(MODE_DIR)/% : LIBPATH = 
CmpGlodonDemo/$(MODE_DIR)/% : LIBS = 
CmpGlodonDemo/$(MODE_DIR)/% : OBJ_DIR := CmpGlodonDemo/$(MODE_DIR)

CmpGlodonDemo/$(MODE_DIR)/Objects/source/CmpGlodonDemo.o : $(PRJ_ROOT_DIR)/source/CmpGlodonDemo.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


CmpGlodonDemo/$(MODE_DIR)/Objects/source/app_data.o : $(PRJ_ROOT_DIR)/source/app_data.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


CmpGlodonDemo/$(MODE_DIR)/Objects/source/glodon_iot_main.o : $(PRJ_ROOT_DIR)/source/glodon_iot_main.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/cJSON.o : $(PRJ_ROOT_DIR)/source/model/cJSON.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data.o : $(PRJ_ROOT_DIR)/source/model/glodon_iot_data.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data_internal.o : $(PRJ_ROOT_DIR)/source/model/glodon_iot_data_internal.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP  $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<" -std=c99 -mlong-calls


OBJECTS_CmpGlodonDemo = CmpGlodonDemo/$(MODE_DIR)/Objects/source/CmpGlodonDemo.o \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/app_data.o \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/glodon_iot_main.o \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/cJSON.o \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data.o \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data_internal.o

CmpGlodonDemo/$(MODE_DIR)/CmpGlodonDemo.out : $(OBJECTS_CmpGlodonDemo)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmarm $(OBJECTS_CmpGlodonDemo) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_CmpGlodonDemo) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CmpGlodonDemo/$(MODE_DIR)/CmpGlodonDemo_compile_file : $(FILE) ;

_clean :: CmpGlodonDemo/$(MODE_DIR)/CmpGlodonDemo_clean

CmpGlodonDemo/$(MODE_DIR)/CmpGlodonDemo_clean : 
	$(TRACE_FLAG)if [ -d "CmpGlodonDemo" ]; then cd "CmpGlodonDemo"; rm -rf $(MODE_DIR); fi

DEP_FILES := CmpGlodonDemo/$(MODE_DIR)/Objects/source/CmpGlodonDemo.d CmpGlodonDemo/$(MODE_DIR)/Objects/source/app_data.d CmpGlodonDemo/$(MODE_DIR)/Objects/source/glodon_iot_main.d \
	 CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/cJSON.d CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data.d CmpGlodonDemo/$(MODE_DIR)/Objects/source/model/glodon_iot_data_internal.d
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
