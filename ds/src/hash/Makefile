
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../../..

#PROJ_SRCS = $(shell xmlstarlet select -t -v //Unit/@filename xx.cbp | grep -e '\.c')
PROJ_SRCS = hash.c hash_test_yara.c

# list of directories containing header files
PROJ_INC_DIR = ../dll

# the executable file
PROJ_OUT = hash.out

# list of compiler flags (prepended with "-" sign)
PROJ_CFLAGS = -Wunused-but-set-variable

#PROJ_MACROS = _BSD_SOURCE

# additional object files (created by other projects)
PROJ_ADD_OBJS = dll.o

# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
# PROJ_DEPENDS  = ../dll/Makefile

include $(ROOT_DIR)/Make/Project.mak
