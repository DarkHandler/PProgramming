TARGET=./tarea03

CXX = g++

DIR_OBJ=src/objs
SOURCES=$(wildcard src/*.cc)
OBJECTS=$(patsubst %.cc,$(DIR_OBJ)/%.o,$(subst src/,,$(SOURCES)))

INCLUDES =-I./src -I./src/include
CPPFLAGS =-std=c++17  -Wno-deprecated 
LDFLAGS =-L/usr/local/lib 
CXXFLAGS=-std=c++17 -fopenmp
LDLIBS = -lm -lpthread -fopenmp

all: $(TARGET)
	@echo Made [ $? ] OK :\)
	
$(TARGET): $(OBJECTS) 
	@echo Linking [$@]
	@eval $(CXX) $(LDFLAGS) $^ $(LDLIBS) $(CXXFLAGS)  -o $@ 
	
$(DIR_OBJ)/%.o: src/%.cc
	@echo Compiling [$@]
	@mkdir -p $(DIR_OBJ)
	@eval $(CXX) -c $(INCLUDES) $(CPPFLAGS) $(CXXFLAGS)  $< -o $@
	
clean:
	@$(RM) core *~ \#*\# *.bak *.BAK *\%
	@$(RM) -f .dummy $(OBJECTS)




