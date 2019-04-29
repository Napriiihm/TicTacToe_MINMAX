#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"

 
int testevaluate(){
	ttt t1={{P1,P2,0x00},{P1,0x00,P2},{P1,0x00,P2}}; //P1 gagne sur colonne	
	ttt t2={{P1,P1,P2},{P2,P2,P1},{P1,P1,P2}};		 //partie nul
	ttt t3={{P1,0x00,P2},{0x00,P2,P1},{P2,P1,0x00}};	//P2 gagne sur diago2
	ttt t4={{P1,P1,0x00},{P1,0x00,0x00},{P2,P2,P2}}; //P2 gagne sur ligne
	ttt t5={{P2,P2,P1},{P2,P1,0x00},{P1,0x00,0x00}}; //P1 gagne sur diago
	ttt t6={{P1,P1,P2},{P2,P2,P2},{P1,P1,P2}};		 //P2 gagne avec grille remplie

	int allgood=6;

	if (evaluate(t1)!=-WIN){
		printf("t1 erreur\n");
		allgood-=1;
	} 
	if (evaluate(t2)!=0){
		printf("t2 erreur\n");
		allgood-=1;
	}
	if (evaluate(t3)!=(WIN)){
		printf("t3 erreur\n");
		allgood-=1;
	}
	if (evaluate(t4)!=(WIN)){
		printf("t4 erreur\n");
		allgood-=1;
	}
	if (evaluate(t5)!=(-WIN)){
		printf("t5 erreur\n");
		allgood-=1;
	}
	if (evaluate(t6)!=(WIN)){
		printf("t6 erreur\n");
		allgood-=1;
	}
	if (allgood==6){
		printf("evaluate fonctionne pour tout les cas\n");
	}

}

/*int testnewttt(){
	ttt t0={{P1,P2,0x00},{P1,0x00,P2},{P1,0x00,0x00}};  
	ttt t1={{P1,0x00,P2},{0x00,P2,P1},{P2,0x00,0x00}};	
	ttt t2={{P1,P1,0x00},{P1,0x00,0x00},{P2,0x00,0x00}}; 
	ttt t3={{P2,P2,P1},{P2,P1,0x00},{P1,0x00,0x00}}; 

	ttt T[4];
	T[0]=newttt(t0,2,1,P2);
	T[1]=newttt(t1,2,1,P2);
	T[2]=newttt(t2,2,1,P2);
	T[3]=newttt(t3,2,1,P2);
	for (int k=0;k<4;k++){
		for (int i=0;i<NB;i++){
			for (int j=0;j<NB;j++){
				printf("%d ", T[k][i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
}*/

// evaluate for player 1 P1 (x) 
// si player 2 gagne, score = WIN 
// si player 2 perd, score = -WIN 
// si nul, score = 0 

int evaluate(ttt t){

	int ligne=0,colonne=0,diagonale=0,diagonale2=0;
	int casevide=0;

	for (int i=0;i<NB;i++){
		for (int j=0;j<NB;j++){
			ligne+=t[i][j];
			colonne+=t[j][i];
			if (t[i][j]==0x00) casevide=1;
		}
		diagonale+=t[i][i];
		diagonale2+=t[i][2-i];

		if (ligne==NB*P1 || colonne==NB*P1 || diagonale==NB*P1 || diagonale2==NB*P1){	//gagner par P1
			return -WIN;
		} else if (ligne==NB*P2 || colonne==NB*P2 || diagonale==NB*P2 || diagonale2==NB*P2){	//gagner par P2
			return WIN;
		}

		ligne=0;
		colonne=0;
	}

	if (casevide==0){	//si pas win et pas -win et qu'il n'y a pas de case vide, -> partie nul
		return 0;
	} 

	return -1; //si partie non finie
}


void affiche(ttt t)
{
	int l,c; 
	for (l=0;l<NB;l++) {
		for (c=0;c<NB;c++) {
			switch (t[l][c]) {
				case 0x00: printf("|   "); break; 
				case 0x01: printf("| x "); break; 
				case 0x10: printf("| o "); break; 
			}
		} 
		printf("|\n");
	}
	if (evaluate(t)!=-1){
		printf("score=%d\n",evaluate(t));
	}
}


int fini(ttt t) //renvoie 1 si finie
{
	if (evaluate(t)==-1){	//si partie pas finie
		return 0;
	}

	return 1;	//partie finie 
}

/*ttt newttt(ttt t, int I, int J, int joueur){
	ttt newttt;
	for (int i=0;i<NB;i++){
		for (int j=0;j<NB;j++){
			if (i==I && j==J){
				newttt[i][j]=joueur;
			} else {
				newttt[i][j]=t[i][j];
			} 
		}
	}
	return newttt;
}*/

int minimax (ttt t,int *position,int joueur)
{	
	if (fini(t)==1){ //condition d'arrêt de la recursivité de minimax, si la partie est finie
		return evaluate(t);
	}else if (joueur==P2){
		int max,first=1,Position,Minimax;
		for (int i=0;i<NB;i++){
			for (int j=0;j<NB;j++){
				if (t[i][j]==0x00){
					t[i][j]=P2;
					Minimax=minimax(t,position,P1);
					if (Minimax > max && first==0){
						//printf("b %d %d\n",minimax(t,position,P1), NB*i+j);
						max=Minimax;
						Position=NB*i+j;
						//printf("c %d\n", *position);
					}
					if (first==1){
						//printf("a %d %d\n",minimax(t,position,P1), NB*i+j);
						max=Minimax;
						Position=NB*i+j;
						first=0;
					}		
					t[i][j]=0x00;
				}
			}
		}
		*position=Position;
		return max;
	} else if (joueur==P1){
		int result=0,normalize=0;
		for(int i=0;i<NB;i++){
			for(int j=0;j<NB;j++){
				if (t[i][j]==0x00){
					t[i][j]=P1;
					result+=minimax(t,position,P2);
					t[i][j]=0x00;
					normalize+=1;
				}
			}
		}
		return result/normalize;
	}
}
	



int main() 
{	
	int val,move,joueur=P2; 

	ttt t={{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00}}; 

	testevaluate();

	while (!fini(t)) {
		affiche(t);
		if (joueur==16){
			printf("Au joueur 2 de jouer..\n");
		} else {
			printf("Au joueur 1 de jouer..\n"); 
		}
		
		if ( joueur == P1 ) { 
			do{
				do {
					printf("enter move:"); 
					scanf("%d",&move);
				} while(move<0 || move>8);	//pointe une case en dehors du tictactoe
			} while (t[move/3][move%3] != 0x00);	//la case pointer est déjà remplie 
			t[move/3][move%3]=P1;
			printf("\n");
			joueur=P2; 
		} else {
			move=-1; 
			val=minimax(t,&move,P2); 
			printf("best move %d (val=%d)\n\n",move,val); 
			if ( move != (-1) ) { 			
				t[move/3][move%3]=P2;
			}
			joueur=P1; 

		}		  
	}
	affiche(t);
	return EXIT_SUCCESS;
}




