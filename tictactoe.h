#define NB 3

#define INFINITY 10000
#define WIN 1000 

#define P1 0x01 	// x
#define P2 0x10		// o 

typedef int ttt[NB][NB]; 

int testevaluate();
int evaluate(ttt t);
void affiche(ttt t);
int fini(ttt t);
int** newttt(ttt t, int I, int J, int joueur);
int minimax (ttt t,int *position,int joueur);
int main();
