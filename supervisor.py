
#developer: Eric Blanco
#revised: hizan hernandez

import serial
import time

# Defineix els comandaments i els corresponents missatges a enviar a l'Arduino
commands = {
    "force a": "FA",
    "force b": "FB",
    "state a": "?A",
    "state b": "?B",
    "run": "R",
    "halt": "H"
}

def command_to_hex(command):
    # Converteix la cadena a bytes i afegeix un byte nul
    return bytes(command, 'utf-8') + b'\0'

def print_menu():
    # Mostra el menú de comandaments
    print("ESCULL UNA DE LES SEGÜENTS OPCIONS:\n\r")
    print("----------------------------------------------------")
    print("force a --> Força el semàfor del carrer A a verd (FA)")
    print("force b --> Força el semàfor del carrer B a verd (FB)")
    print("state a --> Consulta l'estat del semàfor del carrer A (?A)")
    print("state b --> Consulta l'estat del semàfor del carrer B (?B)")
    print("run --> Engega el sistema (R)")
    print("halt --> Atura el sistema (H)")
    print("exit --> Surt")
    print("----------------------------------------------------")

def main():
    # Configura el port sèrie
    port = "/dev/ttyACM0"  
    baudrate = 9600
    arduino = serial.Serial(port, baudrate, timeout=1)

    print("Supervisor iniciat. Escriu 'menu' per veure les diferents opcions o 'exit' per sortir.")

    try:
        while True:
            user_input = input(">> ").strip().lower()
            if user_input == "exit":
                break
            elif user_input == "menu":
                print_menu()
            elif user_input in commands:
                command = command_to_hex(commands[user_input])
                arduino.write(command)
                
                # Espera un moment per a rebre la resposta de l'Arduino
                time.sleep(1)
                
                response = ""
                while arduino.in_waiting > 0:
                    response += arduino.read(arduino.in_waiting).decode('utf-8')
                
                if response:
                    print(f"Missatge rebut de l'Arduino: {response}")
                else:
                    print("No hi ha resposta de l'Arduino.")
            else:
                print("Comanda no reconeguda.")
    except KeyboardInterrupt:
        print("Sortint del programa.")
    finally:
        arduino.close()

if __name__ == '__main__':
    main()

