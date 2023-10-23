# Kompiler Informationen
CC = g++
STD_CFLAGS = -g -Wall 		# Standardflags
OPT_CFLAGS = 			# Optimierungsflags

# Projektabhängige Flags
PRJ_CFLAGS = -I..

# Quellcode Pfade
SRC_PATH = PotentialGird/src
OBJ_PATH = PotentialGird/obj
BIN_PATH = PotentialGird/bin

# Temporärer Outputpath
TMP_PATH = PotentialGird/tmp/

# Quellcode Dateien
SRC_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC_FILES))

# Zielpfad und Projektname
TARGET = $(BIN_PATH)/main
SUBMITNAME = MoonFlight.zip

# Remove Befehl
RM = rm

# Standard Befehl
all: $(TARGET)

# Erstelle aus den Quellcode Dateien die Objekt Dateien
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) $(STD_CFLAGS) $(OPT_CFLAGS) $(PRJ_CFLAGS) -c $< -o $@

# Erstelle aus den Objekt Dateien das ausführbare Programm
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) $(STD_CFLAGS) $(OPT_CFLAGS) $(PRJ_CFLAGS) $(OBJ_FILES) -o $@

# --- Optionen ---

# Lösche alle Objekt Dateien und das ausführbare Programm
clean:
	$(RM) -r PotentialGird/bin/* PotentialGird/obj/*

# Lösche bisheriges Zip Archiv und erstelle ein neues mit der Binärdatei
submit:
	$(RM) $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN_PATH)

# Führe das Programm aus und erstelle ggf. den Output Ordner
run: $(TARGET)
	mkdir -p $(TMP_PATH)
	./$(TARGET)
