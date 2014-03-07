#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!
#
##############################################################################################
#
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#

##############################################################################################
# Start of default section
#

PROJECT_DIR = ../firmware

# Output directory and files
ifeq ($(BUILDDIR),)
  BUILDDIR = build
endif
ifeq ($(BUILDDIR),.)
  BUILDDIR = build
endif



#TRGT = mingw32-
CC   = $(TRGT)gcc
AS   = $(TRGT)gcc -x assembler-with-cpp

# List all default C defines here, like -D_DEBUG=1
DDEFS = -DSIMULATOR -DSHELL_USE_IPRINTF=FALSE

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =

# List all default directories to look for include files here
DINCDIR =

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = -lws2_32

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

# Define project name here
PROJECT = rusefi_simulator

# Define linker script file here
LDSCRIPT =

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# Imported source files
CHIBIOS = ../firmware/chibios
include $(CHIBIOS)/boards/simulator/board.mk
include ${CHIBIOS}/os/hal/hal.mk
include ${CHIBIOS}/os/hal/platforms/Win32/platform.mk
include ${CHIBIOS}/os/ports/GCC/SIMIA32/port.mk
include ${CHIBIOS}/os/kernel/kernel.mk

include $(PROJECT_DIR)/util/util.mk
include $(PROJECT_DIR)/config/engines/engines.mk
include $(PROJECT_DIR)/controllers/algo/algo.mk
include $(PROJECT_DIR)/controllers/math/math.mk
include $(PROJECT_DIR)/controllers/sensors/sensors.mk
include $(PROJECT_DIR)/controllers/trigger/trigger.mk
include $(PROJECT_DIR)/controllers/system/system.mk
include $(PROJECT_DIR)/console/console.mk
include $(PROJECT_DIR)/console_util/console_util.mk

# List C source files here
SRC  = ${PORTSRC} \
       ${KERNSRC} \
       ${TESTSRC} \
       ${HALSRC} \
       ${PLATFORMSRC} \
	$(TRIGGERSRC) \
	$(SYSTEMSRC) \
	$(CONSOLESRC) \
	$(CONSOLEUTILSRC) \
	$(CONTROLLERS_ALGO_SRC) \
	$(CONTROLLERS_MATH_SRC) \
	$(CONTROLLERS_SENSORS_SRC) \
	$(ENGINES_SRC) \
       $(BOARDSRC) \
       ${CHIBIOS}/os/various/chprintf.c \
       ${CHIBIOS}/os/various/memstreams.c \
	$(UTILSRC) \
       rusEfiFunctionalTest.c \
       boards.c \
       main.c

#	$(ENGINES_SRC) \
#	$(CONTROLLERS_ALGO_SRC) \
#	$(CONTROLLERS_MATH_SRC) \


# List ASM source files here
ASRC =

# List all user directories here
UINCDIR = $(PORTINC) $(KERNINC) $(TESTINC) \
          $(HALINC) $(PLATFORMINC) $(BOARDINC) \
	$(PROJECT_DIR)/util \
	$(PROJECT_DIR)/console \
	$(PROJECT_DIR)/console_util \
	$(PROJECT_DIR)/config/engines \
	$(PROJECT_DIR)/ext_algo \
	$(PROJECT_DIR)/controllers/sensors \
	$(PROJECT_DIR)/controllers/system \
	$(PROJECT_DIR)/controllers/algo \
	$(PROJECT_DIR)/controllers/math \
	$(PROJECT_DIR)/controllers/trigger \
        ${CHIBIOS}/os/various \
	simulator

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

# more debugging
#OPT = -ggdb -g3 -O0 -fomit-frame-pointer -fgnu89-inline -std=gnu99 -Werror-implicit-function-declaration

# smaller file size
OPT = -O0 -fomit-frame-pointer -fgnu89-inline -std=gnu99 -Werror-implicit-function-declaration

#
# End of user defines
##############################################################################################


# Various directories
OBJDIR    = $(BUILDDIR)/obj
LSTDIR    = $(BUILDDIR)/lst


INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))
DEFS    = $(DDEFS) $(UDEFS)
ADEFS   = $(DADEFS) $(UADEFS)
#OBJS    = $(ASRC:.s=.o) $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)

#ACOBJS    = $(addprefix $(OBJDIR)/, $(notdir $(ACSRC:.c=.o)))
#ACPPOBJS  = $(addprefix $(OBJDIR)/, $(notdir $(ACPPSRC:.cpp=.o)))
#TCOBJS    = $(addprefix $(OBJDIR)/, $(notdir $(TCSRC:.c=.o)))
#TCPPOBJS  = $(addprefix $(OBJDIR)/, $(notdir $(TCPPSRC:.cpp=.o)))
#ASMOBJS   = $(addprefix $(OBJDIR)/, $(notdir $(ASMSRC:.s=.o)))
#ASMXOBJS  = $(addprefix $(OBJDIR)/, $(notdir $(ASMXSRC:.S=.o)))
#OBJS	  = $(ASMXOBJS) $(ASMOBJS) $(ACOBJS) $(TCOBJS) $(ACPPOBJS) $(TCPPOBJS)



LDFLAGS = -Wl,-Map=$(PROJECT).map,--cref,--no-warn-mismatch $(LIBDIR)
ASFLAGS = -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = $(OPT) -Wall -Wextra -Wstrict-prototypes -fverbose-asm -Wa,-alms=$(<:.c=.lst) $(DEFS)

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(PROJECT).exe

%.o : %.c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%.o : %.s
	$(AS) -c $(ASFLAGS) $< -o $@

%exe: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

gcov:
	-mkdir gcov
	$(COV) -u $(subst /,\,$(SRC))
	-mv *.gcov ./gcov

clean:
	-rm -f $(OBJS)
	-rm -f $(PROJECT).exe
	-rm -f $(PROJECT).map
	-rm -f $(SRC:.c=.c.bak)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.s.bak)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep

#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
