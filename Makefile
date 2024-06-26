PROJECTNAME = particleSimulator
OUTPUT_DIR = build

INCLUDE_DIRS = -Iinclude/glad -Iinclude/GLFW -Iinclude/imgui -Iinclude/KHR -Iinclude -Iinclude/particle
LIB_DIRS = -Llib

LIBS = -lmingw32 -lglfw3dll -lopengl32

SRC = $(wildcard src/*.cpp) $(wildcard libsrc/glad/*.c) $(wildcard libsrc/imgui/*.cpp)

default:
	g++ $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)