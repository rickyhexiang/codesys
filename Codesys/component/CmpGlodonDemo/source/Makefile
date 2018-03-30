PLATFORM ?= vxworks
OUTDIR = build/$(PLATFORM)
GLODON_SDK_PATH = ../../..
TARGET = $(OUTDIR)/app.out

CFLAGS ?=
include $(GLODON_SDK_PATH)/configs/$(PLATFORM).mk
CFLAGS += $(PLATFORM_CFLAG)

LDFLAGS = -lglodoniot -lplatform -lglodoniot -L$(GLODON_SDK_PATH)/lib/$(PLATFORM) 
LDFLAGS += -r -nostdlib -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT
CFLAGS += -Imodel -I$(GLODON_SDK_PATH)/include -I$(GLODON_SDK_PATH)/include/platform

ifneq ($(GLODON_IOT_MQTT_USERNAME), )
CFLAGS += -DGLODON_IOT_MQTT_USERNAME=\"$(GLODON_IOT_MQTT_USERNAME)\"
endif
ifneq ($(GLODON_IOT_MQTT_PASSWORD), )
CFLAGS += -DGLODON_IOT_MQTT_PASSWORD=\"$(GLODON_IOT_MQTT_PASSWORD)\"
endif

CFLAGS += -DENABLE_IOT_DEBUG
CFLAGS += -DENABLE_IOT_INFO
CFLAGS += -DENABLE_IOT_WARN
CFLAGS += -DENABLE_IOT_ERROR

#function session
ifeq ($(ASSIGN_FUCTION_SESSION), )
CFLAGS += -DFUNCTION_SESSION_SET=
else
CFLAGS += -DFUNCTION_SESSION_SET=$(ASSIGN_FUCTION_SESSION)
endif

APP_OBJS = main.o app_data.o

DEV_MODEL_OBJS = cJSON.o glodon_iot_data.o glodon_iot_data_internal.o
DEV_MODEL_OBJS := $(addprefix model/, $(DEV_MODEL_OBJS))

OBJS = $(DEV_MODEL_OBJS) $(APP_OBJS)
OBJS := $(addprefix $(OUTDIR)/, $(OBJS))

.PHONY: all clean

all: $(TARGET) 
	
clean:
	$(RM) $(TARGET)
	$(RM) $(OUTDIR)

$(TARGET): $(OBJS) Makefile
	@if [ ! -d "`dirname $(GLODON_SDK_PATH)/lib/$(PLATFORM)`" ]; then $(MKDIR) "`dirname $(GLODON_SDK_PATH)/lib/$(PLATFORM)`"; fi
#$(CC) -o $@ $(OBJS) $(LDFLAGS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)
	@$(SIZE) -t $@ | sed '/TOTALS/d'

$(OUTDIR)/%.o:%.c Makefile
	@if [ ! -d "`dirname $@`" ]; then $(MKDIR) "`dirname $@`"; fi
	$(CC) -o $@ -c $< $(CFLAGS)

