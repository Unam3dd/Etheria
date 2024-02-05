# Project Info

PROJECT_NAME=bytebreacher

IS_LIBRARY=false
NO_PIE=false
CANARY=true
STDLIB=true
FORTIFY=2
EXECSTACK=0

AUTHOR=Unam3dd
GITHUB=https://github.com/Unam3dd
VERSION=0.0.1


# Shell Information

SHELL := /bin/zsh

# System information

DISTRO = $(shell cat /etc/os-release | grep "^ID" | head -n1 | cut -d '=' -f2 | tr -d '\"')
WHOAMI = $(shell whoami)
INTERFACE = $(shell ls /sys/class/net | grep "wl")
LOCAL_IP = $(shell ifconfig $(shell ls /sys/class/net/ | grep "wl")  | grep "inet" | head -n1 | sed "s/^[[:space:]]*//" | cut -d ' ' -f2)

# Project files configuration

INCS_DIR = inc
SRCS_DIR = src
EXT_FILE_PROJECT = $(shell ls src | head -n1 | sed 's/^.*\.//')

# Test Project files configuration

TEST_INCS_DIR = test
TEST_SRCS_DIR = test

# Progress Bar

NF=$(shell ls -lR $(SRCS_DIR) | grep -F .$(EXT_FILE_PROJECT) | wc -l)
HNF=$(shell ls -lR $(INCS_DIR) | grep -F .h | wc -l)
P=0
COUNTER=1
MOD=1
LOADING_ITER=0
FILE_SIZE=0
BIN_FILE_SIZE=0
NF_O=0
HASH=0

DIST_ROOT = dist
DIST_BASE=$(DIST_ROOT)/$(DISTRO)
DIST:=$(DIST_BASE)/release/
ifeq ($(IS_LIBRARY),true)
NAME:=$(DIST)$(PROJECT_NAME).so
STATIC_NAME:=$(DIST)$(PROJECT_NAME).a
else
NAME:=$(DIST)$(PROJECT_NAME).out
STATIC_NAME:=$(DIST)$(PROJECT_NAME).static
endif

ifdef DEBUG
DIST := $(DIST_BASE)/debug/
ifeq ($(IS_LIBRARY),true)
NAME := $(DIST)$(PROJECT_NAME).so
STATIC_NAME := $(DIST)$(PROJECT_NAME).a
else
NAME := $(DIST)$(PROJECT_NAME).out
STATIC_NAME := $(DIST)$(PROJECT_NAME).static
endif
endif
