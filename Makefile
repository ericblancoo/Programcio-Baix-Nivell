# Variable para guardar el nombre del ejecutable
EXEC := exec

# Obtiene todos los archivos .c dentro de la carpeta
SOURCES := $(wildcard *.c)

archivos := $(shell find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.py" -o -name "*.rst.txt" -o -name "Makefile" \))

# Compilación del programa
$(EXEC): $(SOURCES)
	avr-gcc -std=c99 -Os -mmcu=atmega328p -fshort-enums -DF_CPU=16000000UL $^ -o $@

# Generación del archivo .hex
$(EXEC).hex: $(EXEC)
	avr-objcopy -Oihex $< $@

# Limpieza de archivos generados
clean:
	rm -f $(EXEC) $(EXEC).hex

# Ejecución de la programación del microcontrolador
program: $(EXEC).hex
	sudo avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -U $<


tgz:
	tar -czvf EricIzan_prac6.tgz --transform 's/^\.\///' $(archivos) #Crea el archivo .tgz

# Comando por defecto
.DEFAULT_GOAL := $(EXEC).hex

# Evita que make busque archivos con nombres como los targets
.PHONY: clean program
