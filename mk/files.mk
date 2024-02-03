include ./mk/project.mk

# Compiler

# GCC Default

ifeq ($(EXT_FILE_PROJECT), c)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -pedantic -D__BYTEBREACHER_VERSION__=\"$(VERSION)\"
STATIC_CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -pedantic -D__BYTEBREACHER_VERSION__=\"$(VERSION)\"
LDFLAGS =
COMPILER_VERSION = $(shell $(CC) --version | head -n1)
endif

# Assembly Compiler using GAS as Default

ifeq ($(EXT_FILE_PROJECT), s)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -pedantic -D__BYTEBREACHER_VERSION__=\"$(VERSION)\"
STATIC_CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR) -pedantic -D__BYTEBREACHER_VERSION__=\"$(VERSION)\"
LDFLAGS =
COMPILER_VERSION = $(shell $(CC) --version | head -n1)
endif

ifeq ($(FORTIFY),1)
	CFLAGS += -D_FORTIFY_SOURCE=$(FORTIFY) -O$(FORTIFY)
	STATIC_CFLAGS += -D_FORTIFY_SOURCE=$(FORTIFY) -O$(FORTIFY)
endif

ifeq ($(FORTIFY),2)
	CFLAGS += -D_FORTIFY_SOURCE=$(FORTIFY) -O$(FORTIFY)
	STATIC_CFLAGS += -D_FORTIFY_SOURCE=$(FORTIFY) -O$(FORTIFY)
endif

ifeq ($(EXECSTACK),1)
	CFLAGS += -z execstack -fno-stack-protector
	STATIC_CFLAGS += -z execstack -fno-stack-protector
endif

ifeq ($(IS_LIBRARY),true)
	CFLAGS += -fPIC
else
ifeq ($(NO_PIE),false)
	CFLAGS += -fPIE
else
	CFLAGS += -no-pie
endif
endif

ifeq ($(STDLIB),false)
	CFLAGS += -nodefaultlibs -nostdlib
	STATIC_CFLAGS += -nodefaultlibs -nostdlib
endif

ifeq ($(CANARY),true)
	CFLAGS += -fstack-protector-all
	STATIC_CFLAGS += -fstack-protector-all
endif

ifeq ($(NO_PIE),false)
	STATIC_CFLAGS += -static-pie
else
	STATIC_CFLAGS += -static
endif

ifdef DEBUG
	CFLAGS += -g3
	STATIC_CFLAGS += -g3
endif

ifdef CLANG
	CC = clang
endif

ifdef FAST
	CFLAGS += -Ofast
	STATIC_CFLAGS += -Ofast
endif

ifdef O2
	CFLAGS += -O2
	STATIC_CFLAGS += -O2
endif

ifdef O3
	CFLAGS += -O3
	STATIC_CFLAGS += -O3
endif

ifdef OSIZE
	CFLAGS += -Osize
	STATIC_CFLAGS += -Osize
endif

ifdef DEBUG
	CFLAGS += -DDEBUG=1
	STATIC_CFLAGS += -DDEBUG=1
endif

ifdef STRIP
	CFLAGS += -s
	STATIC_CFLAGS += -s
endif

# Object Directory
OBJDIR = obj

# Source Files

SRCS = $(shell ls $(SRCS_DIR)/*.$(EXT_FILE_PROJECT))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.$(EXT_FILE_PROJECT)=.o))

# Test Files

TEST_SRCS = $(shell ls $(TEST_SRCS_DIR)/*.$(EXT_FILE_PROJECT) 2> /dev/null)
TEST_SRCS_CNT = $(shell ls $(TEST_SRCS_DIR) | grep -F .c | wc -l)
TEST_OBJS = $(TEST_SRCS:.$(EXT_FILE_PROJECT)=.test)

# VPath

ifeq ($(EXT_FILE_PROJECT), c)
vpath %.c $(SRCS_DIR)
vpath %.h $(INCS_DIR)
endif

ifeq ($(EXT_FILE_PROJECT), s)

ifdef NASM
	CC = nasm
	CFLAGS = -felf64
endif

vpath %.s $(SRCS_DIR)
vpath %.h $(INCS_DIR)
endif
