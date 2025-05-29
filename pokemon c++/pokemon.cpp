#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Ataque {
public:
    string nombre;
    int dano;

    Ataque(string nombre, int dano) : nombre(nombre), dano(dano) {}
};

class Pokemon {
public:
    string nombre;
    int vida;
    Ataque ataque1;
    Ataque ataque2;

    Pokemon(string nombre, int vida, Ataque atk1, Ataque atk2)
        : nombre(nombre), vida(vida), ataque1(atk1), ataque2(atk2) {}

    void atacar(Pokemon &enemigo, int numAtaque) {
        Ataque atk = (numAtaque == 1) ? ataque1 : ataque2;
        cout << nombre << " usa " << atk.nombre << "!\n";
        enemigo.vida -= atk.dano;
        if (enemigo.vida < 0) enemigo.vida = 0;
        cout << enemigo.nombre << " tiene " << enemigo.vida << " puntos de vida restantes.\n\n";
    }

    bool estaDerrotado() {
        return vida <= 0;
    }
};

int elegirAtaque(Pokemon &poke) {
    int opcion;
    cout << "Elige un ataque para " << poke.nombre << ":\n";
    cout << "1. " << poke.ataque1.nombre << " (" << poke.ataque1.dano << " de daño)\n";
    cout << "2. " << poke.ataque2.nombre << " (" << poke.ataque2.dano << " de daño)\n";
    cout << "Opción: ";
    cin >> opcion;
    while (opcion != 1 && opcion != 2) {
        cout << "Opción inválida. Intenta nuevamente: ";
        cin >> opcion;
    }
    return opcion;
}

int elegirEquipo(int jugadorNum) {
    int opcion;
    cout << "Jugador " << jugadorNum << ", elige tu equipo:\n";
    cout << "1. Equipo 1 (Pikachu, Charizard, Mew)\n";
    cout << "2. Equipo 2 (Eevee, Venusaur, Ho-oh)\n";
    cout << "Opción: ";
    cin >> opcion;
    while (opcion != 1 && opcion != 2) {
        cout << "Opción inválida. Intenta nuevamente: ";
        cin >> opcion;
    }
    return opcion;
}

int main() {
    cout << "---------- BATALLA POKEMON ----------\n\n";

    vector<Pokemon> equipo1 = {
        Pokemon("Pikachu", 250, Ataque("Cola de Hierro", 35), Ataque("Impactrueno", 50)),
        Pokemon("Charizard", 400, Ataque("Zarpazo", 30), Ataque("Lanzallamas", 75)),
        Pokemon("Mew", 325, Ataque("Alarido", 25), Ataque("Psiquico", 150))
    };

    vector<Pokemon> equipo2 = {
        Pokemon("Eevee", 250, Ataque("Ataque Rápido", 30), Ataque("Última Baza", 55)),
        Pokemon("Venusaur", 350, Ataque("Látigo Cepa", 45), Ataque("Planta Feroz", 60)),
        Pokemon("Ho-oh", 500, Ataque("Calcinación", 35), Ataque("Pájaro Osado", 120))
    };

    int opcionJugador1 = elegirEquipo(1);
    int opcionJugador2 = elegirEquipo(2);

    vector<Pokemon> jugador1 = (opcionJugador1 == 1) ? equipo1 : equipo2;
    vector<Pokemon> jugador2 = (opcionJugador2 == 1) ? equipo1 : equipo2;

    int index1 = 0;
    int index2 = 0;
    bool turno = true;

    while (index1 < jugador1.size() && index2 < jugador2.size()) {
        Pokemon &pokemon1 = jugador1[index1];
        Pokemon &pokemon2 = jugador2[index2];

        cout << "------------------------------------------\n";
        cout << "¡" << pokemon1.nombre << " vs. " << pokemon2.nombre << "!\n";

        while (!pokemon1.estaDerrotado() && !pokemon2.estaDerrotado()) {
            if (turno) {
                cout << "--- Turno de " << pokemon1.nombre << " ---\n";
                int opcion = elegirAtaque(pokemon1);
                pokemon1.atacar(pokemon2, opcion);
            } else {
                cout << "--- Turno de " << pokemon2.nombre << " ---\n";
                int opcion = elegirAtaque(pokemon2);
                pokemon2.atacar(pokemon1, opcion);
            }
            turno = !turno;
        }

        if (pokemon1.estaDerrotado()) {
            cout << pokemon1.nombre << " ha sido derrotado.\n";
            index1++;
        }
        if (pokemon2.estaDerrotado()) {
            cout << pokemon2.nombre << " ha sido derrotado.\n";
            index2++;
        }
    }

    if (index1 == jugador1.size()) {
        cout << "¡Jugador 2 gana la batalla!\n";
    } else {
        cout << "¡Jugador 1 gana la batalla!\n";
    }

    return 0;
}