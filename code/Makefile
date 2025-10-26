# --------------------------------------------
# Project State Init (UNITY BUILD)
# --------------------------------------------
CXX = clang++
CC  = clang

SILENT_OUTPUT ?= 
DEBUG_BUILD   ?=

# --------------------------------------------
# Project OS settings
# --------------------------------------------
ifeq ($(OS),Windows_NT)
    OS_DEFINE = -DOS_WINDOWS=1
    PLATFORM_LIBS = -lopengl32 -luser32 -lgdi32 -lwinmm -lshell32 -lole32 -luuid -lversion -ladvapi32 -lsetupapi -lcfgmgr32 -loleaut32 -limm32
    LDFLAGS = -Wl,/IGNORE:4099 -Wl,/STACK:314572800 
    EXE_EXT = .exe
    DLL_EXT = .dll
    LIB_EXT = .lib
    OBJ_EXT = .obj
    DEV_NULL = NUL
    PIC_FLAG =
    PDB_SUFFIX := $(shell powershell -Command "[guid]::NewGuid().ToString('N').Substring(0,8)")
	PDB_LDFLAG = -Wl,/PDB:../build/game_$(BUILD_TYPE)_$(PDB_SUFFIX).pdb

	DEL_PDB = powershell -NoProfile -Command "Get-ChildItem ..\\build\\game_$(BUILD_TYPE)*.pdb -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue"
	DEL_RDI = powershell -NoProfile -Command "Get-ChildItem ..\\build\\game_$(BUILD_TYPE)*.rdi -ErrorAction SilentlyContinue | Remove-Item -Force -ErrorAction SilentlyContinue"
else
    UNAME_S := $(shell uname -s)
    DLL_EXT = .so
    LIB_EXT = .a
    OBJ_EXT = .o
    PIC_FLAG = -fPIC
	PDB_SUFFIX := $(shell head -c4 /dev/urandom | od -An -tx1 | tr -d ' \n')
	PDB_LDFLAG =

	DEL_PDB = rm -f ../build/game_$(BUILD_TYPE)*.pdb || true
	DEL_RDI = rm -f ../build/game_$(BUILD_TYPE)*.rdi || true

    ifeq ($(UNAME_S),Linux)
        OS_DEFINE = -DOS_LINUX=1
        PLATFORM_LIBS = -lX11 -lGL -lm
        DEV_NULL = /dev/null
    else ifeq ($(UNAME_S),Darwin)
        OS_DEFINE = -DOS_MAC=1
        PLATFORM_LIBS = -framework Cocoa -framework OpenGL -lm
        DEV_NULL = /dev/null
    endif
endif

# --------------------------------------------
# Build Flags
# --------------------------------------------
PROJECT_COMMON_COMPILER_FLAGS = -Wall -Wextra

BUILD_TYPE ?= debug
ifeq ($(DEBUG_BUILD),1)
    BUILD_COMPILER_FLAGS = -g -O0 -fno-inline-functions $(PROJECT_COMMON_COMPILER_FLAGS)
else
    BUILD_COMPILER_FLAGS = -O3 $(PROJECT_COMMON_COMPILER_FLAGS)
endif

# --------------------------------------------
# Set The Inputs
# --------------------------------------------
COMMON_INCLUDES = -I../code/ -I../run_tree/deps/raylib/include/

GAME_SRC                = ../code/main.cpp
GAME_INCLUDES           = $(COMMON_INCLUDES) 
GAME_EXTERNAL_LIBRARIES = $(PLATFORM_LIBS) -L../run_tree/deps/raylib/windows/lib/ -lraylib

# --------------------------------------------
# Set the Outputs
# --------------------------------------------
GAME_OUT = ../build/game_$(BUILD_TYPE)$(EXE_EXT)

# --------------------------------------------
# Create The Build Instructions
# --------------------------------------------
all: game_out

../build:
	-mkdir -p ../build

game_out: $(GAME_SRC) | ../build
	@echo Building the game...
	$(SILENT_OUTPUT) $(CXX) $(BUILD_COMPILER_FLAGS) $(OS_DEFINE) -I$(GAME_INCLUDES) $(GAME_SRC) -o $(GAME_OUT) $(GAME_EXTERNAL_LIBRARIES) -MMD -MF ../misc/game_build_info.d

.PHONY: all

# --------------------------------------------
# Include Built '.d' files
# --------------------------------------------
