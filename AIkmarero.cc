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
   bool buscar = true;
    //El camino que habrรก que seguir

   ////////////////////////////////
   //////////FUNCIONES/////////////
   ////////////////////////////////

   vector<Pos> busqueda(Pos posActual, CType tipo, bool& found){
        vector< vector<bool> > mVisitado(rows(), vector<bool>(cols(), false));
        vector< vector<int> > mDistancia(rows(), vector<int>(cols(), -1));
        vector< vector<Pos> > mPadre(rows(), vector<Pos>(cols()));
        vector<Pos> recorrido;
        //iniciamos la busqueda en la posActual
        mVisitado[posActual.i][posActual.j] = true;
        mDistancia[posActual.i][posActual.j] = 0;
        vector<Dir> dirs = {Top, Right,Bottom,Left};
        queue<Pos> colaBFS;
        colaBFS.push(posActual);
        found = false;
        //iniciamos el BFS
        Pos posInicial = posActual;
        Pos posEncontrado;
        Pos posAux;
        while(not found and not colaBFS.empty()) {
            posActual = colaBFS.front();
            colaBFS.pop();
            for(int i=0;i<dirs.size();++i){
                posAux = posActual + dirs[i];
                if (pos_ok(posAux) and not mVisitado[posAux.i][posAux.j] and cell_type(posAux) != Wall ) {
                    mVisitado[posAux.i][posAux.j] = true;
                    mDistancia[posAux.i][posAux.j] = mDistancia[posActual.i][posActual.j] + 1;
                    mPadre[posAux.i][posAux.j] = posActual;
                    colaBFS.push(posAux);
                    if (cell_type(posAux) == tipo) {
                        found = true;
                        posEncontrado = posAux;
                    }
                }
            }   

        }
        //guardamos el recorrido en una pila
        if (found) {
            Pos ret = posEncontrado;
                while(ret!=posInicial){
                    recorrido.push_back(ret);
                    ret = mPadre[ret.i][ret.j];
                }
                int i = 0;
                int j = recorrido.size()-1;
                while(i<j){
                    Pos aux = recorrido[i];
                    recorrido[i] = recorrido[j];
                    recorrido[j] = aux;
                    ++i; --j;
                }
        }
        return recorrido;

    }

    Dir pos2dir(Pos p1, Pos p2) {
        if(p2.i>p1.i) return Bottom;
        if(p2.i<p1.i) return Top;
        if(p2.j>p1.j) return Right;
        if(p2.j<p1.j) return Left;
        return None;
    }

        

    virtual void play () {
        const Poquemon& yo = poquemon(me());
        Action accion;
        Pos destino;
        if(yo.alive) {
            Pos posActual = yo.pos;
            bool found;
            vector<Pos> camino = busqueda(posActual, Point, found);
            if(found){
                Dir d = pos2dir(posActual, camino[0]);

                move(d);  
            }     

         /*   Pos posActual = yo.pos;
            if (buscar) {
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
            }*/
        }
    }

    
                
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
