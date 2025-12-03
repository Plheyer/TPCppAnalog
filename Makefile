# Makefile du projet TP2_CatalogueTrajets
# Objectifs:
# - Compilation avec g++ et les options minimales demandées: -ansi -pedantic -Wall -std=c++11
# - Génération automatique des dépendances (-MMD)
# - Possibilité d'activer le traçage des constructeurs/destructeurs via la constante MAP
#   -> utiliser: make MAP=1 (ou make run-map / make trace)
# - Cibles pratiques: run, run-map, valgrind (si dispo), clean

# Compilateur et commandes
CXX      = g++
RM       = rm
RMFLAGS  = -f

# Options de compilation
CXXFLAGS = -ansi -pedantic -Wall -std=c++11 -MMD
# Active le traçage si MAP est défini (ex: make MAP=1)
ifdef MAP
CXXFLAGS += -DMAP=$(MAP)
endif

# Fichiers sources (ajoutez ici tout nouveau .cpp du projet)
SOURCES  = main.cpp \
           Graph.cpp \
           ApacheLogStream.cpp \


OBJECTS  = $(SOURCES:.cpp=.o)
DEPS     = $(OBJECTS:.o=.d)

# Nom de l'exécutable
EXE      = TP4_Analog

# Cibles phony
.PHONY: all clean run run-map trace valgrind

# Cible par défaut
all: $(EXE)

# Edition de liens
$(EXE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

# Compilation avec génération de dépendances
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Inclusion des fichiers de dépendances (.d) générés par -MMD
-include $(DEPS)

# Exécuter le programme
run: $(EXE)
	./$(EXE)

# Compiler et exécuter avec MAP activé (MAP=1)
run-map: clean
	$(MAKE) MAP=1 all
	$(MAKE) run

# Test mémoire avec Valgrind (si installé sur la machine)
valgrind: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE)

# Nettoyage
clean:
	$(RM) $(RMFLAGS) $(OBJECTS) $(DEPS) core

