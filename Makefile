HEAP_SIZE      = 8388208
STACK_SIZE     = 61800

PRODUCT = SafetyDiver.pdx

# Locate the SDK
SDK = ${PLAYDATE_SDK_PATH}
ifeq ($(SDK),)
SDK = $(shell egrep '^\s*SDKRoot' ~/.Playdate/config | head -n 1 | cut -c9-)
endif

ifeq ($(SDK),)
$(error SDK path not found; set ENV value PLAYDATE_SDK_PATH)
endif

# List C source files here
SRC = $(shell find src/ -name '*.c')

# List all user directories here
UINCDIR =

# List user asm files
UASRC =

# List all user C define here, like -D_DEBUG=1
USER_DEFS =

# Define ASM defines here
UADEFS =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

UDEFS = $(USER_DEFS) -fsingle-precision-constant
override GCCFLAGS := $(USER_DEFS) -g

include $(SDK)/C_API/buildsupport/common.mk

run: all
	$(info Running built PDX in Simulator)
	$(SDK)/bin/PlaydateSimulator $(PRODUCT)