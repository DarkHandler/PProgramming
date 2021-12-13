TARGET=./tarea02

DEBUG=-DDEBUG
DEBUG=

CXX = g++

#
DIR_OBJ=src/objs
SOURCES=$(filter-out arrayGenerator.cc, $(wildcard src/*.cc))
OBJECTS=$(patsubst %.cc,$(DIR_OBJ)/%.o,$(subst src/,,$(SOURCES)))
INTRINSICS=-msse2 -mavx -mavx2 

INCLUDES =-I./src -I./src/include
CPPFLAGS =-std=c++17  -Wno-deprecated $(INTRINSICS) 
LDFLAGS =-L/usr/local/lib 
LDLIBS = -lm -lpthread

all: $(TARGET)
	@echo Made [ $? ] OK :\)
	
$(TARGET): $(OBJECTS) 
	@echo Linking [$@]
	@eval $(CXX) $(LDFLAGS) $^ $(LDLIBS)  -o $@ 
	
$(DIR_OBJ)/%.o: src/%.cc
	@echo Compiling [$@]
	@mkdir -p $(DIR_OBJ)
	@eval $(CXX) -c $(INCLUDES) $(CPPFLAGS)  $< -o $@
	
clean:
	@$(RM) core *~ \#*\# *.bak *.BAK *\%
	@$(RM) -f .dummy $(OBJECTS)

distclean:
	@$(RM) $(TARGET)
	@$(RM) -rf $(DIR_OBJ)





