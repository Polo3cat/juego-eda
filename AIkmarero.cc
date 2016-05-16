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
   stack<Dir> recorrido; //El camino que habrá que seguir
   Pos destino;

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
        if(yo.alive) {
            Pos posActual = yo.pos;
            if (buscar) {
                while (not recorrido.empty()) {
                    recorrido.pop();                   
                }
                destino = busqueda(posActual, Point, recorrido);
                buscar = false;
            }
            if(points_value(destino) <= 0) {
                buscar = true;
            } 
            if(not recorrido.empty()) {
                Dir d;
                d = recorrido.top();
                recorrido.pop();
                Move(d);                
            }
        }
    }

    Pos busqueda(Pos posActual, CType& tipo, stack<Dir>& recorridoFinal){
        vector<vector<bool> > mVisitado(r, vector<bool>(c, false));
        vector<vector<int> > mDistancia(r, vector<int>(c, -1));
        vector<vector<Pos> > mPadre(r, vector<Dir>(c));

        //iniciamos la busqueda en la posActual
        mVisitado[posActual.i][posActual.j] = true;
        mDistancia[posActual.i][posActual.j] = 0;
        mPadre[posActual.i][posActual.j] = NULL;
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
            if (not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
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
            if (not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
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
            if (not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
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
            if (not mVisitado[posAux.i][posAux.j] and (cell_type(posAux) != Wall or (cell_type(posAux) == Wall and ghost_wall(posAux) > mDistancia[posActual.i][posActual.j] ) ) ) {
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
        ret = posEncontrado;
        while(posEncontrado != posInicial) {
            recorridoFinal.push(mPadre[posEncontrado.i][posEncontrado.j]);
            posEncontrado = posEncontrado + mPadre[posEncontrado.i][posEncontrado.j];
        }
        return ret;

    }
                
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

