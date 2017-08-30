#include<windows.h>
#include<stdio.h>
#include<conio.h>


#define i 20   // quantia de linhas
#define j 60    // quantia de colunas


int veloc, op = 2;


void desenha(int x, int y) {
	//Parte da biblioteca windows.h
	//Funcao para desenhar na tela com utilizacao de coordenadas x e z (como um plano cartesiano)
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y}); // x=j (sao colunas) e y=i (sao as linhas)
}

void desenha_parede() //desenha as paredes
{
    int z; // variavel auxiliar para desenhar

    for (z = 0; z < j; z++) // desenha parede de cima horizontal
    {
        desenha(z, 0);
        printf("_");
        Sleep(1);
    }
    for (z = 1; z <= i; z++) // desenha parede da direita vertical
    {
        desenha(j, z);
        printf("|");
        Sleep(1);
    }
    
    for (z = j; z > 0  ; z--) // desenha parede de baixo horizontal
    {
        desenha(z, i);
        printf("_");
        Sleep(1);
    }
    for (z = i; z >= 0; z--) // desenha parede da esquerda vertical
    {
        desenha(0, z);
        printf("|");
        Sleep(1);
    }
}

void bem_vindo() {
	//variaveis para receber a tecla digitada pelo usuario e para auxiliar na selecao de dificuldade
    int tecla, dif = 0;
    desenha(15, 5);
    printf("==SNAKE GAME==");
    desenha(15, 7);
    printf("MENU");
    desenha(15, 9);
    printf("Selecione uma das opcoes");
    desenha(15, 11);
    printf("<ENTER> Iniciar \t<ESC> Instrucoes \t<ESPACO> Dificuldade ");
	//Loop que executa ao menos uma vez
    do {
    	//Recebe a tecla do usuario e nao a mostra ao mesmo
        tecla = getch();
        //Verifica qual tecla foi pressionada
        if (tecla == 27) {
            instrucoes();
            system("cls");
            desenha(15, 5);
            printf("<ENTER> Iniciar \t <ESPACO> Dificuldade");
            tecla = getch();
        }
        else if (tecla == 32) {
        	//Recebe o retorno do metodo dificuldade e o coloca na velocidade
            veloc = dificuldade();
            dif = 1;
            desenha(15, 5);
            printf("Pressione ENTER tecla para iniciar para comecar");
            tecla = getch();
        }
        //Verifica se a variavel dificulade esta zero
       	if (dif == 0){
       	 	//Coloca velociade como 200
	     	veloc = 200;
		}
		//Limpa a tela
        system("cls");
    } while (tecla != 13 && tecla != 27 && tecla != 32); //Enquanto a tecka eh diferente de ESC ENTER e ESPACO repete o loop
}

void instrucoes() {
	//Limpa a tela 
    system("cls");
    desenha(15, 3);
    printf("Use as setas para controlar a cobrinha:");
    desenha(15, 5);
    printf("Seta para cima move a cobra para cima");
    desenha(15, 6);
    printf("Seta para baixo move a cobra para baixo");
    desenha(15, 7);
    printf("Seta para direita move a cobra para direita");
    desenha(15, 8);
    printf("Seta para esquerda move a cobra para esquerda ");
    desenha(15, 9);
    printf("Coma os alimentos para crescer saudavel e evoluir");
    desenha(15, 10);
    printf("Nao cruze os obstaculos ou morrera");
    desenha(15, 11);
    printf("Use a tecla ESC para finalizar a qualquer momento ");
    desenha(15 , 12);
    printf("Aperte qualquer tecla para continuar");
    //Pausa o jogo ate que alguma outra tecla seja precionada
    system("pause");
}
//Metodo que retorna o tipo inteiro que sera a velocidade da cobra
int dificuldade() {
	//Variavel para retornar o nivel selecionado
    int nivel_dif = 0;
    //Loop que executa ao menos uma vez
    do {
    	//Limpa a tela
        system("cls");
        desenha(15, 5);
        printf("Escolha o Nivel de Dificuldade: ");
        desenha(15, 8);
        printf("<1> FACIL \t <2> MEDIA \t <3> DIFICIL \t <4> HARDCORE \t <5> Impossivel");
        scanf("%d", &op);
        //Divide 300 pela opcao digitada para colocar na velocidade da cobra
        nivel_dif = 300 / op;
    } while (op < 1 || op > 5); // Se a opcao nao entrar nos criterios repete o LOOP
    system("cls");
    //Retorna a dificuldade para recuperar posteriormente
    return (nivel_dif);
}
//Metodo do desenvolvimento do jogo
void snakeGame() {
    //d= direcao/ x= auxiliar/ t= variavel de controle do tamanho da cobra/ 
	//level= nivel k= controle do nivel/ pontos= pontuacao/ veloc= controle sleep/ resp= resposta para continuar
    int d = 2, x, t = 1, pontos = 0, level = 1, k = 10, resp;
    // cx= tamanho da cobra na horizontal // cy= tamanho da cobra na vertical
    //Ja inicializa a cobra na posicao definida
    int cx[300] = {8}, cy[300] = {8};
	int ax, ay, ox, oy,ox2, oy2,ox3, oy3,ox4, oy4;
    
    int tecla = 32;
    // tecla para receber o botao pressionado
    srand(time(NULL)); // cria o alimento e o obstaculo em posicao aleatoria, inicializa
    ax = (rand() % (j - 1)) + 1; //Soma 1 no final para que nao apareca na mesma linha das barreiras
    ay = (rand() % (i - 1)) + 1;
    ox = (rand() % (j - 1)) + 1;
    oy = (rand() % (i - 1)) + 1;
    ox2 = (rand() % (j - 1)) + 1;
    oy2= (rand() % (i - 1)) + 1;
    ox3 = (rand() % (j - 1)) + 1;
    oy3 = (rand() % (i - 1)) + 1;
    ox4 = (rand() % (j - 1) + 1);
   	oy4 = (rand() % (i - 1) + 1);
   
	//Se tecla ESC apertada finaliza o jogo se nao roda desenvolvimento do mesmo
    while (tecla != 27) // desenvolvimento do jogo
    {
        while (tecla != 27 && !(kbhit())) { //Equanto a tecla for diferente de ESC e  nao estiver sendo pressionado nenhuma tecla o jogo inicia
            //For para remover uma posicao da cobra a cada andada 
			for (x = t; x > 0; x--) {
               cx[x] = cx[x - 1]; //Tira um na horizontal e na vertical
               cy[x] = cy[x - 1];
        	}
        	desenha(cx[t], cy[t]); //Desenha um espaco em branco na posicao que a cobra passou
            printf(" ");
            //Verifica a tecla pressionada para movela
            if (d == 0 ){
				cx[0]--; //esquerda
            }else if (d == 1) {
				cy[0]--; //cima
			}else if (d == 2){
				cx[0]++; //direita
			}else if (d == 3){
				cy[0]++; //baixo
			}
			//Desenha a cobra com suas posicoes 
            desenha(cx[0], cy[0]);
            printf("O");
            //Desenha o alimento em sua posicao aleatoria
            desenha(ax, ay);
            printf("*");
            //Desenha o obstaculo em suas posicoes
            if(op != 5){
				desenha(ox, oy);
	            printf("X");
	            desenha(ox2, oy2);
	            printf("X");
	            desenha(ox3, oy3);
	            printf("X");
	            desenha(ox4, oy4);
	            printf("X");
            }
            
            if (ax == cx[0] && ay == cy[0]) { //Verifica se a cabeca da cobra esta na mesma posicao do alimento em X e Y
                t++; //Se verdade aumenta um no tamannho de t e quando ele for desenhar um espaco em branco desenhara em 2 posicoes atras
               	//Faz um beep quando come o alimento
                Beep(200,150);
                //Coloca outro alimento em outra posicao aleatoria
                desenha(ox4, oy4);
                printf(" ");
				ax = (rand() % (j - 1) + 1); 
                ay = (rand() % (i - 1) + 1);
                ox4 = (rand() % (j - 1) + 1);
   		 		oy4 = (rand() % (i - 1) + 1);
			    //Cada alimento comido aparece um obstaculo novo no campo
   		 		if(op != 5){		
					desenha(ox4,oy4);
   		 			printf("X");
   		 		}
                //Aumenta o contador de pontos 
                pontos++;
            }
      		//Desenha pontuacao     
            desenha(20, i + 2);
            printf("Pontuacao= %d", pontos);
            //da uma pausa a partir da velocidade definada no metodo de dificuldade
            Sleep(veloc);
            desenha(10, i + 4);
            printf("dificuldade: %d", op);
            //Mostra a velocidade da cobra
			desenha(30, i + 4);
            printf("%d", veloc);
            //for para acompanhar crescemento da cobra com passar das posicoes
            for (x = 1; x < t; x++) {
            	//Verifica se a cobra na posicao 0 esta na mesma posicao de alguma parte do seu corpo 
                if (cx[0] == cx[x] && cy[0] == cy[x]){
               		//Emite beep
					Beep(750,600);
            		Beep(600,600);
               		Beep(450,1200);
					tecla = 27;
				}
            }
			//Verifica se a cobra na posicao 0 esta na mesma posicao  de algum obstaculo
            if ((ox == cx[0] && oy == cy[0]) || (ox2 ==cx[0] && oy2 == cy[0]) || (ox3 ==cx[0] && oy3 == cy[0])|| (ox4 ==cx[0] && oy4 == cy[0])){
            	//Emite beep
				Beep(750,600);
            	Beep(600,600);
                Beep(450,1200);
				tecla = 27;//Se verdadeiro termina o jogo
			}
			//Verifica se aa cobra na posicao 0 esta na mesma posicao de alguma parede
            if (cy[0] == 0 || cy[0] == i || cx[0] == 0 || cx[0] == j){
            	//Emite beep
				Beep(750,600);
            	Beep(600,600);
                Beep(450,1200);
				tecla = 27; //Se estiver termina o jogo
			}
        }
        if (tecla != 27){ //Se a tecla for diferente de ESC recebe  a tecla pressionada pelo usuario
			tecla = getch();
		}
		if(tecla == 98 && op == 4){
			desenha(6, 11);
            printf("IT'S GONNA BE LEGEN");	
			desenha(6, 13);
            printf("WAIT FOR IT");
          	desenha(6, 15);
            printf("DARY");
		}
        if (tecla == 75){ //Se for igual a 75 (seta esquerda)
			d = 0; //Variavel de direcao move para esquerda
		}
        if (tecla == 72){ //Se igual a 72 (seta cima)
			d = 1;//Variavel de direcao move para cima
		}
        if (tecla == 77){//Se igual a 77 (seta direita)
			d = 2;//Variavel de direcao move para direita
		}
        if (tecla == 80){//Se igual a 80 (seta baixo)
			d = 3;//Variavel de direcao move para baixo
		}
    }
    system("cls");
	desenha(35, i + 10);
    printf("Pontos = %d", pontos);
    system("pause");
    do {
    	desenha(1, 1);
        printf("Deseja comecar denovo? <1>SIM <2>Nao \n"); //reinicia o jogo
        scanf("%d", &resp);
    } while (resp != 1 && resp != 2);
    system("cls");
    if (resp == 1){// se 1 pressinado, ele retorna ao main e comecaa o jogo de novo
        main();
    } else {
    	desenha(1, 1);
        printf("FIM DE JOGO"); // se o 2 pressionado, ele finaliza o jogo
    }
}
void main() {
    bem_vindo(); // tela inicial
    desenha_parede(); // desenha o quadro do campo
    snakeGame(); //jogo
}
