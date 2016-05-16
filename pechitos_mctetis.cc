
#include "Player.hh"

using namespace std;


/**
 * Write the name of your player and save this file
 * as AI<name>.cc
 */
#define PLAYER_NAME JIJohn





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
    
    typedef vector<Pos> Path;

    /**
     * It calculates the shortest path to a specific type of cell.
     * 
     * Pre: Receives x,y board coordinates and a type of cell
     * Post: Returns the Path from (x,y) to the furthest cell of the specified type.
     * If there's no reachable cell of that type, will return a Path of size 0.
     */
     Path bfs(int x, int y, CType type){
        const int NOT_VISITED = -2;
        const int UNREACHABLE = -1;
        int n = number_rows();
        int m = number_universe_columns();
        Path res;
        queue<Pos> q;
        vector< vector<int> > dist(n, vector<int>(m,NOT_VISITED));
        vector< vector<Pos> > prev(n, vector<Pos>(m,NOT_VISITED));
        vector<Pos> adj = {Pos(-1,0),Pos(0,1),Pos(1,0)};
        bool found = false;
        Pos pFound;
        int yaux = y;
        y = y%m;
        q.push(Pos(x,y));
        if(x>=0 and x<n and y>=0 and y<m){
            dist[x][y] = 0;

            while (not found and not q.empty()){     
                    Pos v = q.front();
                    q.pop();

                    if(within_window(v, round()+1) and cell(v).type == type){
                        if(within_window(v,round()+dist[first(v)][second(v)])){
                            found = true;
                            pFound = v;
                        }
                    }
                    
                    for(int i=0;i<adj.size();++i){
                        Pos p = v+adj[i];
                        p = Pos(first(p),(second(p)+m)%m);
                        if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED){
                            
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                        }
                    }
                    Pos p = v+Pos(-1,1);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0 
                        and dist[first(v)-1][second(v)] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(1,1);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0 
                        and dist[first(v)+1][second(v)] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(-1,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)-1][second(v)] > 0 
                        and dist[first(v)-1][second(v)+1] > 0 and dist[first(v)][second(v)+1] > 0 and dist[first(v)][second(v)+2] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(0,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(1,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)+1][second(v)] > 0 
                        and dist[first(v)+1][second(v)+1] > 0 and dist[first(v)][second(v)+1] > 0 and dist[first(v)][second(v)+2] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
            }
            if(found){
                
            Pos aux = pFound;
                while(aux!=Pos(x,y)){
                    res.push_back(aux);
                    aux = prev[first(aux)][second(aux)];
                }
                int i = 0;
                int j = res.size()-1;
                while(i<j){
                    Pos aux = res[i];
                    res[i] = res[j];
                    res[j] = aux;
                    ++i; --j;
                }
                for(int i=0;i<res.size();++i){
                    int aux = second(res[i]);
                    while(aux<yaux)aux+=m;
                    res[i] = Pos(first(res[i]),aux);
                }
            }
        }
        return res;
    }
    
    Path checkStacked(Starship s){
        int colsToLookForward = 8;
        int x = first(s.pos);
        int y = second(s.pos);
        
        const int NOT_VISITED = -2;
        const int UNREACHABLE = -1;
        int n = number_rows();
        int m = number_universe_columns();
        bool found = false;
        Pos pFound;
        Path res;
        queue<Pos> q;
        vector< vector<int> > dist(n, vector<int>(m,NOT_VISITED));
        vector< vector<Pos> > prev(n, vector<Pos>(m,NOT_VISITED));
        vector<Pos> adj = {Pos(-1,0),Pos(0,1),Pos(1,0)};
        int yaux = y;
        y = y%m;
        q.push(Pos(x,y));
        if(x>=0 and x<n and y>=0 and y<m){
            dist[x][y] = 0;
            while (not found and not q.empty()){     
                    Pos v = q.front();
                    q.pop();

                        if(within_window(v,round()+dist[first(v)][second(v)]) and second(v) == (y+colsToLookForward)%number_universe_columns()){
                            found = true;
                            pFound = v;
                        }
                    
                    for(int i=0;i<adj.size();++i){
                        Pos p = v+adj[i];
                        p = Pos(first(p),(second(p)+m)%m);
                        if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED){
                            
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                        }
                    }
                    Pos p = v+Pos(-1,1);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0 
                        and dist[first(v)-1][second(v)] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(1,1);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0 
                        and dist[first(v)+1][second(v)] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(-1,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)-1][second(v)] > 0 
                        and dist[first(v)-1][second(v)+1] > 0 and dist[first(v)][second(v)+1] > 0 and dist[first(v)][second(v)+2] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(0,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)][second(v)+1] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
                    p = v+Pos(1,2);
                    p = Pos(first(p),(second(p)+m)%m);
                    if(within_window(p, round()+1) and dist[first(p)][second(p)]==NOT_VISITED and dist[first(v)+1][second(v)] > 0 
                        and dist[first(v)+1][second(v)+1] > 0 and dist[first(v)][second(v)+1] > 0 and dist[first(v)][second(v)+2] > 0){
                            if(cell(p).type != ASTEROID){
                                dist[first(p)][second(p)]=dist[first(v)][second(v)]+1;
                                prev[first(p)][second(p)] = v;
                                q.push(p);
                            }
                            else dist[first(p)][second(p)] = UNREACHABLE;
                    }
            }
            if(found){
                
            Pos aux = pFound;
                while(aux!=Pos(x,y)){
                    res.push_back(aux);
                    aux = prev[first(aux)][second(aux)];
                }
                int i = 0;
                int j = res.size()-1;
                while(i<j){
                    Pos aux = res[i];
                    res[i] = res[j];
                    res[j] = aux;
                    ++i; --j;
                }
                for(int i=0;i<res.size();++i){
                    int aux = second(res[i]);
                    while(aux<yaux)aux+=m;
                    res[i] = Pos(first(res[i]),aux);
                }
            }
        }
        return res;
    }
    
     bool bestMove(Starship s){
        vector<Dir> all_dirs = {FAST,FAST_UP,FAST_DOWN,DEFAULT,UP,DOWN,SLOW_UP,SLOW_DOWN};
        int max = 0;
        Dir bestDir = SLOW;
        for(int i=0;i<all_dirs.size();++i){
            if(isMoveAllowed(s.pos, all_dirs[i]) and not missileDanger(s.pos+all_dirs[i]) and not canCollide(s,s.pos+all_dirs[i])){
                int aux = 0;
                if(all_dirs[i]==SLOW_UP) aux += getCellValue(s.pos+SLOW_UP);
                else if(all_dirs[i]==SLOW_DOWN) aux += getCellValue(s.pos+SLOW_DOWN);
                else if(all_dirs[i]==DEFAULT) aux += getCellValue(s.pos+DEFAULT);
                else if(all_dirs[i]==UP) aux += getCellValue(s.pos+SLOW_UP) + getCellValue(s.pos+DEFAULT) + getCellValue(s.pos+UP);
                else if(all_dirs[i]==DOWN) aux += getCellValue(s.pos+SLOW_DOWN) + getCellValue(s.pos+DEFAULT) + getCellValue(s.pos+DOWN);
                else if(all_dirs[i]==FAST_UP) aux += getCellValue(s.pos+SLOW_UP) + getCellValue(s.pos+DEFAULT) 
                    + getCellValue(s.pos+UP) + getCellValue(s.pos+FAST) + getCellValue(s.pos+FAST_UP);
                else if(all_dirs[i]==FAST) aux += getCellValue(s.pos+DEFAULT) + getCellValue(s.pos+FAST);
                else if(all_dirs[i]==FAST_DOWN) aux += getCellValue(s.pos+SLOW_DOWN) + getCellValue(s.pos+DEFAULT) 
                    + getCellValue(s.pos+DOWN) + getCellValue(s.pos+FAST) + getCellValue(s.pos+FAST_DOWN);
                if(aux>max){
                    max = aux;
                    bestDir = all_dirs[i];
                }
            }
        }
        cerr << "LOOK FOR THE BEST MOVE" << endl;
        cerr << "Seems like best move is " << bestDir << " with " << max << " points. " << endl;
        if(max>2){
            return safeMove(s,s.pos+bestDir);
        }else return false;
    }
    
    int getCellValue(Pos p){
        if(within_universe(p)){
            if(cell(p).type == POINT_BONUS) return 2;
            else if(cell(p).type == MISSILE_BONUS) return 1;
        }
        return 0;
    }
    
    bool canCollide(Starship s, Pos p){
        cerr << "CANCOLLIDE++++"<<endl;
        for(int i=-1;i<=1;++i){
            for(int j=-2;j<=0;++j){
                Pos pp = Pos(first(p)+i,second(p)+j);
                if(within_universe(pp) and cell(pp).type == STARSHIP and cell(pp).sid!=s.sid){
                    cerr << "OJO!! en " << pp << " hay una nave que nos puede alcanzar!!" << endl;
                    return true;
                }
            }
        }
        cerr << "Podemos movernos a la posicion " << p << endl;
        return false;
    }
    
    bool isClear(Pos p){
        bool res = false;
        if(within_window(p, round()+1)){
            Cell c = cell(p);
            res = (c.type != ASTEROID and c.type != MISSILE and c.type != STARSHIP);
        }
        return res;
    }
    
    bool isMoveAllowed(Pos p, Dir d){
        if(d==SLOW) return isClear(p+SLOW);
        else if(d==SLOW_UP) return isClear(p+SLOW_UP);
        else if(d==SLOW_DOWN) return isClear(p+SLOW_DOWN);
        else if(d==DEFAULT) return isClear(p+DEFAULT);
        else if(d==UP) return isClear(p+SLOW_UP) and isClear(p+DEFAULT) and isClear(p+UP);
        else if(d==DOWN) return isClear(p+SLOW_DOWN) and isClear(p+DEFAULT) and isClear(p+DOWN);
        else if(d==FAST_UP) return isClear(p+SLOW_UP) and isClear(p+UP) and isClear(p+DEFAULT) and isClear(p+FAST) and isClear(p+FAST_UP);
        else if(d==FAST) return isClear(p+DEFAULT) and isClear(p+FAST);
        else if(d==FAST_DOWN) return isClear(p+SLOW_DOWN) and isClear(p+DOWN) and isClear(p+DEFAULT) and isClear(p+FAST) and isClear(p+FAST_DOWN);
        else return false;
    }
    bool missileDanger(Pos p){
        int num_cells = 4;
        ++num_cells;
        for(int i=1;i<num_cells;++i){
            int col = (second(p)+number_universe_columns()-i)%number_universe_columns();
            Pos pp = Pos(first(p),col);
            if(cell(pp).type == MISSILE or (cell(pp).type == STARSHIP and player_of(cell(pp).sid) != me())){
                for(int j=i-1;j>0;--j){
                    int c = (second(p)+number_universe_columns()-j)%number_universe_columns();
                    Pos ppp = Pos(first(p),c);
                    cerr << ppp <<",";
                    if(cell(ppp).type != EMPTY and cell(ppp).type != POINT_BONUS and cell(ppp).type != MISSILE_BONUS and not (cell(ppp).type == STARSHIP 
                        and player_of(cell(ppp).sid) == me())){
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }
    
    bool safeMove(Starship s, Pos p){
        cerr << "SAFEMOVE+++  (A ver si nos movemos a la " << p <<")" << endl;
            Dir d = p - s.pos;
            
            if(within_window(p, round()+1) and isMoveAllowed(s.pos, d) and not missileDanger(p) and not canCollide(s,p)){
                p = s.pos + d;
                cerr << "Nos movemos a " <<p << "porque es 'SAFE'" << endl;
                move(s.sid, d);
                return true;
            }
            return false;
    }
    
    bool hurryMove(Starship s, Pos p){
        cerr << "HURRYMOVE+++  (A ver si nos movemos a la " << p <<")" << endl;
            Dir d = p - s.pos;
            if(within_window(p, round()+1) and isMoveAllowed(s.pos, d) and not missileDanger(p)){
                p = s.pos + d;
                cerr << "Nos movemos a " <<p << "porque hay prisa!" << endl;
                move(s.sid, d);
                return true;
            }
            return false;
    }
    
    bool moveToBonus(Starship s, CType type){
        cerr << "MOVETOBONUS+++"<< endl;
        Path p = bfs(first(s.pos),second(s.pos), type);
        if(p.size()>0){
             bool res = false;
             res = safeMove(s, p[0]);
             if(missileDanger(s.pos) and not res) hurryMove(s,p[0]);
        } 
        return false;
    }
    
    /**
     * Search for enemies and shoot them if found.
     * Pre: It receives the starship that will attack if possible.
     * Post: Returns true if attacked, false otherwise.
     */
    bool attack(Starship s){
        cerr << "ATTACK+++" << endl;
        bool res = false;
        Pos p1 = Pos(first(s.pos),(second(s.pos)+1)%number_universe_columns());
        Pos p2 = Pos(first(s.pos),(second(s.pos)+2)%number_universe_columns());
        Pos p3 = Pos(first(s.pos),(second(s.pos)+3)%number_universe_columns());
        if(within_universe(p1) and cell(p1).type == STARSHIP and player_of(cell(p1).sid) != me()){
            shoot(s.sid);
            res = true;
        }
        
        if(within_universe(p2) and cell(p1).type == EMPTY and cell(p2).type == STARSHIP and player_of(cell(p2).sid) != me()){
            shoot(s.sid);
            res = true;
        }
        
        if(within_universe(p3) and cell(p1).type == EMPTY and cell(p2).type == EMPTY and cell(p3).type == STARSHIP and player_of(cell(p3).sid) != me()){
            shoot(s.sid);
            res = true;
        }
        
        if(not res){ //Ya que no hemos atacado vemos si nos podemos poner detras de alguna nave
            for(int i=-1;i<=1;++i){
                for(int j=1;j<=3;++j){
                    Pos p = s.pos + Pos(i,j);
                    if(within_universe(p) and cell(p).type == STARSHIP and player_of(cell(p).sid) != me()){
                        Pos pp = p - DEFAULT;
                        Dir d = pp-s.pos;
                        if(not missileDanger(pp) and isMoveAllowed(s.pos,d)) return safeMove(s,pp);
                    }
                }
            }
        }
        
        return res;
    }
    
    void idle(Starship s){
        cerr << "IDLE+++" << endl;
        vector<Dir> all_dirs = {FAST,FAST_UP,FAST_DOWN,DEFAULT,UP,DOWN,SLOW,SLOW_UP,SLOW_DOWN};
        bool done = false;
        
        for(int i=0;i<all_dirs.size() and not done;++i){
            cerr << "idle check pos " << s.pos+all_dirs[i] << endl;
            if(within_window(s.pos+all_dirs[i], round()+1) and isMoveAllowed(s.pos, all_dirs[i]) and not missileDanger(s.pos+all_dirs[i])){
               
                if(windowColumn(s)>2){
                    bool res = false;
                    res = canCollide(s, s.pos+all_dirs[i]);
                    if(not res or (res and missileDanger(s.pos))){
                        move(s.sid, all_dirs[i]);
                        done = true;
                    }
                }else{
                    move(s.sid, all_dirs[i]);
                    done = true;
                }
            }
            
        }
        cerr << "NO NOS PODEMOS MOVER pero no vamos a chocar" << endl;
        if(not done and cell(s.pos+DEFAULT).type == ASTEROID){
            cerr << "NO TENEMOS NA QUE HACER y vamos a chocar, DISPARAMOS. " << endl;
            shoot(s.sid);
        }
    }
    
    int windowColumn(Starship s){
     if(s.alive) return abs(((second(s.pos)%number_universe_columns()) - (round()%number_universe_columns())));
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
        for (Starship_Id sid = begin(me()); sid != end(me()); ++sid) {

            Starship s = starship(sid);

            if (s.alive) { // if the starship is alive and
                cerr << "NAVE (" << s.sid << ") en posicion " << s.pos << "--------------------------------" << endl;
                bool done = false;
                if(s.nb_miss>0 and not missileDanger(s.pos)) done = attack(s);
                if(not done and s.nb_miss == 0){
                    done = moveToBonus(s, MISSILE_BONUS);
                }
                if(not done){
                    done  = bestMove(s);
                    done = moveToBonus(s, POINT_BONUS);
                     if(not done and windowColumn(s)<number_window_columns()-8){
                        Path pStacked = checkStacked(s);
                        if(pStacked.size()>0){
                           /* cerr << "No se tengo nada que hacer pero no estoy atascado. Voy a seguir este camino (long:" << pStacked.size()<<"):" << endl;
                            for(int i=0;i<pStacked.size();++i){
                                cerr << pStacked[i] << ",";
                            }
                            cerr << endl;
                            done = safeMove(s, pStacked[0]);*/
                        } else shoot(s.sid);
                    }
                    if(not done) idle(s);
                }
                
            }
        }
    }    
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);

