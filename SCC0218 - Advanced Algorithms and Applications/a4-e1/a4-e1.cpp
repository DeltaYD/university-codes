#include <stdio.h>
#include <queue>
#include <cstring>

using namespace std;

struct state{
	int digit[4];
	int depth;
    int sort;
};

//  Estrutura de Overload
struct CompareSort { 
    bool operator()(state const& p1, state const& p2) 
    { 
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1.sort > p2.sort; 
    } 
};

int moves [8][4]= { {-1, 0, 0, 0 },
					{ 1, 0, 0, 0 },
					{ 0,-1, 0, 0 },
					{ 0, 1, 0, 0 },
					{ 0, 0,-1, 0 }, 
					{ 0, 0, 1, 0 },
					{ 0, 0, 0,-1 },
					{ 0, 0, 0, 1 } };


void next_states(state s, state e, state next[8]){
	int i, j, k;
    int aux1, aux2;
	int x, y;

	for(i=0; i<8; i++){
        k = 0;
		next[i] = s;
		next[i].depth = s.depth+1;
		for(j=0; j<4; j++){
			next[i].digit[j] += moves[i][j];
			if (next[i].digit[j]<0)
				next[i].digit[j] = 9;
			if (next[i].digit[j]>9)
				next[i].digit[j] = 0;

            //  aplicando heuristica

			//	dist(X, Y) = min { X-Y, N-(X-Y-1) }
			if(next[i].digit[j] > e.digit[j]){
				x = next[i].digit[j];
				y = e.digit[j];
			} else{
				y = next[i].digit[j];
				x = e.digit[j];
			}
            aux1 = x - y;
			aux2 = 9 - (x - y - 1);

			//	escolher o menor dos dois resultados
            if(aux1 < aux2){
                k += aux1;
            } else{
                k += aux2;
            }
		}

        //  somando heuristica com distancia do inicio
        next[i].sort = k + next[i].depth;
	}

    return;
}


int equal(state s, state e){
	int i;
	for (i=0; i<4; i++)
		if (s.digit[i] != e.digit[i])
			return 0;

	return 1;
}

int bfs(state current, state final, int visited[10][10][10][10]){
	state next[8];
	int i;
    //  Troquei a fila normal por uma fila de prioridade que compara "sort"
	priority_queue<state, vector<state>, CompareSort> q;

    //  Primeira comparacao a ser observada: Se o estado atual foi visitado. Isto ja cobre caso o estado inicial seja proibido
	if (!visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]]){

        //  Marcamos nosso espaco atual como visitado
		visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]] = 1;

        //  Colocamos ele na fila de estados
		q.push(current);

        // Enquanto dada fila nao estiver vazia
		while(!q.empty()) {
            //  Determinamos nosso estado atual como o primeiro item da fila
			current = q.top();
            //  Retiramos um item da fila
			q.pop();

            //  Caso o nosso estado atual seja igual ao final, significa que chegamos ao fim do algoritmo
			if (equal(current, final)){
                //  Assim, devolvemos a profundidade em que chegamos
				return current.depth;
            }
            //  Se nao houver sucesso, obter proximos estados em largura e guardar em next
			next_states(current, final, next);
            //  Para cada iteracao, so estamos colocando um estado na fila. Caso
			for (i=0; i<8; i++)
				if (!visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]]){
					visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]] = 1;
					q.push(next[i]);
				}
		}
	}
	return -1;
}

int main (){
	int nr_testes, test, forbidden, i;
	int visited[10][10][10][10];
	state initial, final, aux;

    //  Obtemos o numero de testes que serao feitos. O procedimento sera executado para cada um deles
	scanf("%d", &nr_testes);
	for (test=0; test<nr_testes; test++){
        //  Receber configuracao inicial
		scanf("%d %d %d %d", &initial.digit[0], &initial.digit[1], &initial.digit[2], &initial.digit[3]);
        //  Receber configuracao buscada
		scanf("%d %d %d %d", &final.digit[0], &final.digit[1], &final.digit[2], &final.digit[3]);
        //  Receber quantidade de configuracoes proibidas
		scanf("%d", &forbidden);

        //  Zerar vetor de visitados (melhor que um monte de for's)
		memset(visited, 0, sizeof visited);

        //  Looping para receber as configuracoes proibidas (simplesmente marcaremos essas areas como visitadas, impedindo acesso durante iteracoes)
		for(i=0; i<forbidden; i++) {
			scanf("%d %d %d %d", &aux.digit[0], &aux.digit[1], &aux.digit[2], &aux.digit[3]);
			visited[aux.digit[0]][aux.digit[1]][aux.digit[2]][aux.digit[3]] = 1;
		}

        //  Inicializacao da profundidade do algoritmo
		initial.depth=0;

        //  Imprimir resultante da busca em largura
		printf("%d\n", bfs(initial, final, visited));
	}

    //  Fim
	return 0;
}