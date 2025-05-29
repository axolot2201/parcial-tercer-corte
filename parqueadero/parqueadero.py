import time
#se utiliza os para limpiar 
import os
#se utiliza datetime para trabajar con la fecha y hora en tiempo real de manera facil
from datetime import datetime

# se determina el tamaño y la cantidad de cobro por minuto
TAMANO = 8
tarifa_por_minuto = 100  

# aqui se definen las opciones del menu para ingresar el vehiculo, retirarlo o salir y tambien se muestra es mapa
def menu():
    parqueadero = Parqueadero(TAMANO, TAMANO)
    while True:
        parqueadero.mostrar_mapa()
        print("1. Ingresa tu vehiculo")
        print("2. Retira tu vehiculo")
        print("3. Salir")
        opcion = input("Seleccione una opcion: ")
        
# se agrega un if para cada opcion, se pide la placa y se crea un else para una opcion no valida
        if opcion == "1":
            placa = input("Ingrese la placa del vehiculo: ").upper()
            parqueadero.registrar_entrada(placa)
            input("Presione enter para continuar...")
        elif opcion == "2":
            placa = input("Ingrese la placa del vehiculo a retirar: ").upper()
            parqueadero.registrar_salida(placa)
            input("Presione enter para continuar...")
        elif opcion == "3":
            break
        else:
            print("Opción no valida.\n")

# se determina la clase y el tiempo de entrada y la placa
class Vehiculo:
    def __init__(self, placa):
        self.placa = placa
        self.hora_entrada = datetime.now()
# se crea una matriz con las celdas del parqueadero siendo l, o, v, e, y s
class Parqueadero:
    def __init__(self, filas, columnas):
        self.filas = filas
        self.columnas = columnas
        self.mapa = [['L' for int in range(columnas)] for int in range(filas)]
        self.vehiculos = {}
        self.definir_vias_entrada_salida()

    def definir_vias_entrada_salida(self):
        for i in range(self.filas):
            self.mapa[i][0] = 'V'
        for j in range(self.columnas):
            self.mapa[0][j] = 'V'
        self.mapa[0][0] = 'E'
        self.mapa[self.filas - 1][self.columnas - 1] = 'S'

# limpia la pantalla y dibuja el mapa del parqueadero con las especificaiones dadas
    def mostrar_mapa(self):
        os.system('cls' if os.name == 'nt' else 'clear')
        print("MAPA DEL PARQUEADERO")
        for fila in self.mapa:
            print(" ".join(fila))
        print()

#se registra la salida y se le hace el cobro conforme el tiempo que ha pasado
    def registrar_salida(self, placa):
        for pos, vehiculo in list(self.vehiculos.items()):
            if vehiculo.placa == placa:
                tiempo = (datetime.now() - vehiculo.hora_entrada).total_seconds() / 60
                costo = int(tiempo * tarifa_por_minuto)
                self.mapa[pos[0]][pos[1]] = 'L'
                del self.vehiculos[pos]
                print(f"Vehiculo {placa} ha salido.")
                print(f"Tiempo: {tiempo:.2f} minutos. Total a pagar: ${costo}\n")
                return
        print("Vehículo no encontrado.\n")

#se encuentra un lugar libre
    def encontrar_lugar_libre(self):
        for i in range(1, self.filas):
            for j in range(1, self.columnas):
                if self.mapa[i][j] == 'L':
                    return (i, j)
        return None
#se registra la entrada con la placa dada
    def registrar_entrada(self, placa):
        posicion = self.encontrar_lugar_libre()
        if not posicion:
            print("Parqueadero ocupado.")
            return
        fila, col = posicion
        self.mapa[fila][col] = 'O'
        self.vehiculos[(fila, col)] = Vehiculo(placa)
        print(f"Vehiculo con placa {placa} registrado en posicion {fila},{col}.\n")

