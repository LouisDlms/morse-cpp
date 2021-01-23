CXX=g++
CXXFLAGS=-Wall -ggdb -I include
AR=/usr/bin/ar -r 

src := $(wildcard src/*.cpp) # Génère la liste des fichier .cpp contenu dans le dossier src
obj := $(subst src, build, $(src:.cpp=.o)) #Génère la liste des fichiers .o (n'existe pas encore mais prend juste les titres des cpp)

.PHONY: directories

all: directories libmorse.a morse 
	@echo $(obj)

morse: main.cpp libmorse.a
	$(CXX) $(CXXFLAGS) $^ -o $@ 

libmorse.a: ${obj}
	${AR} $@ $^

build/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

directories: build

build:
	mkdir -p $@

clean: 
	rm morse
	rm libmorse.a
	rm -r build
