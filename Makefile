.PHONY: clean doc
CXX = g++-5
CXXFLAGS = -g -std=c++11

PROJECT = tron

# Directories
OBJDIR = obj
SRCDIR = src
AVI = src/main.cpp src/imageloader.cpp src/Co-ordinates.h
NAN = obj/main.o obj/imageloader.o obj/Co-ordinates.o


# Libraries
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-network -lGL -lGLU -lglut

# Files and folders
SRCS    = $(shell find $(SRCDIR) -name '*.cpp' ||' *.h')
OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Targets
$(PROJECT): buildrepo $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@
	
clean: clean_doc
	rm $(PROJECT) $(OBJDIR) -Rf

clean_doc:
	cd doc && make clean

execute:
	make
	./tron

debug: CXX += $(CXXFLAGS) -DDEBUG
debug: buildrepo $(PROJECT)
	./tron

doc:
	cd doc && make fill

buildrepo:
	@$(call make-repo)

# Create obj directory structure
define make-repo
	mkdir -p $(OBJDIR)
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef
