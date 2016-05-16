#include "Player.hh"

using namespace std;


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME kmarero





struct PLAYER_NAME : public Player {


    /**
     * Factory: returns a new instance of this class.
     * Do not modify this function.
     */
    static Player* factory () {
        return new PLAYER_NAME;
    }
    

    /**
     * Attributes for your player can be defined here.
     */     
   int r = rows();
   int c = cols();
   bool buscar = true;
   vector<Dir> recorrido; //El camino que habrá que seguir
   Pos destino;
   vector<Dir>::iterator trace; //nos indica donde buscar en el vector que contiene las direcciones

   ////////////////////////////////
   //////////FUNCIONES/////////////
   ////////////////////////////////

   Pos busqueda(Pos posActual, CType tipo, vector<Dir>& recorridoFinal){
        vector<vector<bool> > mVisitado(r, vector<bool>(c, false));
        vector<vector<int> > mDistancia(r, vector<int>(c, -1));
        vector<vector<Dir> > mPadre(r, vector<Dir>(c, None));

        //iniciamos la busqueda en la posActual
        mVisitado[posActual.i][posActual.j] = true;
        mDistancia[posActual.i][posActual.j] = 0;
        mPadre[posActual.i][posActual.j] = None;
        queue<Pos> colaBFS;
        colaBFS.push(posActual);
        bool found = false;

        //iniciamos el BFS
        Pos posInicial = posActual;
        Pos posEncontrado;
        Pos posAux;
        while(not found and not colaBFS.empty()) {
            posActual = colaBFS.front();
            colaBFS.pop();
            posAux = posActual + Left;
            if (pos_ok(posAux) and not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
                mVisitado[posAux.i][posAux.j] = true;
                mDistancia[posAux.i][posAux.j] = mDistancia[posActual.i][posActual.j] + 1;
                mPadre[posAux.i][posAux.j] = Right;
                colaBFS.push(posAux);
                if (cell_type(posAux) == tipo) {
                    found = true;
                    posEncontrado = posAux;
                }

            }

            posAux = posActual + Top;
            if (pos_ok(posAux) and not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
                mVisitado[posAux.i][posAux.j] = true;
                mDistancia[posAux.i][posAux.j] = mDistancia[posActual.i][posActual.j] + 1;
                mPadre[posAux.i][posAux.j] = Bottom;
                colaBFS.push(posAux);
                if (cell_type(posAux) == tipo) {
                    found = true;
                    posEncontrado = posAux;
                }

            }

            posAux = posActual + Right;
            if (pos_ok(posAux) and not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
                mVisitado[posAux.i][posAux.j] = true;
                mDistancia[posAux.i][posAux.j] = mDistancia[posActual.i][posActual.j] + 1;
                mPadre[posAux.i][posAux.j] = Left;
                colaBFS.push(posAux);
                if (cell_type(posAux) == tipo) {
                    found = true;
                    posEncontrado = posAux;
                }

            }

            posAux = posActual + Bottom;
            if (pos_ok(posAux) and not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
                mVisitado[posAux.i][posAux.j] = true;
                mDistancia[posAux.i][posAux.j] = mDistancia[posActual.i][posActual.j] + 1;
                mPadre[posAux.i][posAux.j] = Top;
                colaBFS.push(posAux);
                if (cell_type(posAux) == tipo) {
                    found = true;
                    posEncontrado = posAux;
                }                
            }
        }
        //guardamos el recorrido en una pila
        Pos ret = posEncontrado;
        while(posEncontrado != posInicial) {
            if (trace != recorridoFinal.end()) {
                *trace = mPadre[posEncontrado.i][posEncontrado.j];
                ++trace;
            }
            else {
                recorridoFinal.push_back(mPadre[posEncontrado.i][posEncontrado.j]);
                trace = recorridoFinal.end() - 1;
            }
            posEncontrado = posEncontrado + mPadre[posEncontrado.i][posEncontrado.j];
        }
        return ret;

    }
    /**
     * Play method.
     * 
     * This method will be invoked once per each round.
     * You have to read the board here to place your actions
     * for this round.
     *
     */          

    virtual void play () {
        const Poquemon& yo = poquemon(me());
        Action accion;
        if(yo.alive) {
            Pos posActual = yo.pos;
            if (buscar) {
                trace = recorrido.begin();
                destino = busqueda(posActual, Point, recorrido);
                buscar = false;
            }
            if(points_value(destino) <= 0) {
                buscar = true;
            } 
            if(trace != recorrido.begin()) {
                Dir d;
                d = *trace;
                --trace;
                if(trace == recorrido.begin()) 
                    buscar = true;
                accion.move(d);                
            }
        }
    }

    
                
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

