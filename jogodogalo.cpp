#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <windows.h>

using namespace std;
struct jogador
{
    string nome;
    string simbolo;
    int ganhos;
    int perdas;
    int empates;
    int partidas;
    bool vez = false;
};
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //mudanca de cor das letras
jogador j1, j2;
string tabuleiro[3][3];
int contador=0;
int coluna, linha, partida =0;
fstream ficheiro;

string lerNomeJogadores();
void iniciarJogo();
void menu(int op);
void menuPartida (int opcao);
void inicioFicheiro();
void mostrartabuleiro();
void inserirTabuleiro();
void verificaganhador();
void vencedorx();
void vencedorO();
void inicializarVetor();
void inicializarJogo();
void atribuirSimbolo();
int verificarCampo();
void iniciarPartida();
void maisPartida();
void mostrarResultado();
void inserirFicheiro();
void listarFicheiro();
void pesquisarFicheiro();
void apagarFicheiro();
void verificarJogo();

main()
{		
	inicializarVetor();
	iniciarJogo();
}
void inicializarVetor(){//inicializando o tabuleiro para depois verificar na funcao insere tabuleiro
	for (int i=0;i<3;i++)
	{
		for (int k=0; k<3;k++){			
		    tabuleiro[i][k] = "";			
		}	
	}
}
void inicializarJogo(){//inicializando os jogadores todos
	j1.nome = "\0";
	j1.simbolo ="\0";
	j1.ganhos =0;
	j1.perdas =0;
	j1.empates=0;
	j1.partidas=0;
	j1.vez=false;	
	
	j2.nome = "\0";
	j2.simbolo ="\0";
	j2.ganhos =0;
	j2.perdas =0;
	j2.empates=0;
	j2.partidas=0;
	j2.vez=false;
	
	partida =0;
	inicializarVetor();
	contador =0;//zera o contador
	iniciarPartida();
}
void iniciarJogo(){
	int op=0;
	do {
		  system ("CLS");
		  SetConsoleTextAttribute(hConsole, 2);
		  cout << "\n______________________BEM VINDO AO JOGO DO GALO______________________\n\n\n";
		  SetConsoleTextAttribute(hConsole, 15);
		  cout<<"\t\t\tO que deseja realizar \n";
		  cout<<"\t\t1. Jogar\n";
		  cout<<"\t\t2. Partidas\n";
		  cout<<"\t\t0. Sair\n";
		  cout<<"\t\tDigite sua opcao: ";		 
		  op = verificarCampo();
	 	  menu(op);
	   	  system ("CLS");
	}while (op != 0);
}
void menu(int op){		
	    switch(op){
		case 0: cout <<"\t\tAte breve";
				exit(0);
		break;
		case 1: verificarJogo();
		break;
		case 2: inicioFicheiro();
		break;
	}		
}
void verificarJogo(){//inicializando os jogadores todos
	int op;
	if(partida > 0){
		cout<<"\t\tExiste uma partida em andamento. Deseja continuar? [1]SIM [0]NAO: ";
		cin >> op;
		while(cin.fail() || op != 0  && op != 1)
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tCampo invalido, digite novamente: ";
         cin >> op;
        }	
		if(op==1){
			iniciarPartida();
		}else{
			inicializarJogo();
		}
	}else{
		inicializarJogo();
	}		
}
void iniciarPartida(){	
	partida++;		
	if(partida == 1){
		cout << "\n\t\tDigite o nome do primeiro jogador (MAIS DE 3 CARATERES):";
		j1.nome = lerNomeJogadores();
		atribuirSimbolo();	
		cout << "\t\tDigite o nome do segundo jogador (MAIS DE 3 CARATERES):";
		j2.nome = lerNomeJogadores();	
		j1.vez = true;	
	}else {
		system ("CLS");		
		inicializarVetor();
		contador =0;//zera o contador	
	}					
	mostrartabuleiro();		
}
string lerNomeJogadores(){	
	string nome;			
	cin.ignore();
	getline( cin, nome);
	while(nome.length() < 3){		
		cout << "\t\tDigite o novamente o nome: ";
		getline( cin,nome );	
	}  
	return nome;  		    	  
}
void atribuirSimbolo(){
	cout << "\t\tDigite simbolo desejado [X | O] (Maiusculas): ";
	cin >> j1.simbolo;
    while(cin.fail() || j1.simbolo.length() != 1 || j1.simbolo !="X" && j1.simbolo !="O")
	   {
	     cin.clear();
	     cin.ignore();
	     cout << "\t\tOpcao invalida, digite novamente: ";
	     cin >> j1.simbolo;
	    }
	if(j1.simbolo == "X"){//verifica qual simbolo o primeiro jogador escolheu pra atribuir o outro ao segundo jogador
		j2.simbolo = "O";
	}else{
		j2.simbolo = "X";
	}	
}

void mostrartabuleiro(){
	system ("CLS");
	cout<<"\t\tPartida N: "<<partida<< "\n";
	cout << "\n\t\tPrimeiro jogador (a) "<<j1.nome << "= "<<j1.simbolo<<endl;
    cout << "\t\tSegundo jogador (a) "<<j2.nome << "= "<<j2.simbolo<<"\n"<<endl;
	int l,c;
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\t\t   0  1  2\n";
	for (l=0;l<3;l++)
	{		
		cout << "\t\t" << l;	
		for (c=0; c<3;c++){
			if (c ==0 ){
				if(tabuleiro[l][c].length() == 0){
					cout << "   ";
				}else{
					cout << " "<<tabuleiro[l][c]<<" ";
				}
			}else{
				if(tabuleiro[l][c].length() == 0){
					cout << "|   ";
				}else{
					cout << "| "<<tabuleiro[l][c]<<" ";
				}
				
			}			
		}
		cout << "\n"; 
		if(l!=2){
			cout << "\t\t  ----------";	
			cout << "\n"; 
		}			
	}
	SetConsoleTextAttribute(hConsole, 15);	
	verificaganhador();
	inserirTabuleiro();
}
void inserirTabuleiro(){
	do{//loop para inserir dados no tabuleiro
		if(j1.vez){
			cout<<"\n\t\tVez do jogador (a): "<<j1.nome;
		}else{
			cout<<"\n\t\tVez do jogador  (a): "<<j2.nome;
		}	
		cout<<"\n\t\tDigite a linha: ";	
		linha = verificarCampo();
		cout<<"\t\tDigite a coluna: ";
		coluna= verificarCampo();		
		if (tabuleiro[linha][coluna].length()==0){//insere o simbolo caso a posicao selecionada esteja vazia
			if(j1.vez){
				tabuleiro[linha][coluna]=j1.simbolo;
			}else{
				tabuleiro[linha][coluna]=j2.simbolo;					
			}	
			j1.vez = !j1.vez;
			j2.vez=  !j2.vez;							
			contador++;	//o contador soma mais 1 todas as vezes que é inserido um dado no tabuleiro
		}else{
			cout<<"\t\tEscolha uma posicao vazia\n";
			getch();
		}
		
		mostrartabuleiro(); //Mostra como o tabuleiro fica preenchido a cada jogada
	} while(contador<9);	//o ciclo sai quando ja foi preenchido os 9 lugares dentro do tabuleiro
	
}
int verificarCampo(){
	int n;
	cin >> n;
    while(cin.fail()|| n > 2 || n <0 )
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tCampo invalido, digite novamente: ";
         cin >> n;
        }	
	return n;
}

void verificaganhador(){//verifica quem foi o vencedor da partida
	
	if (tabuleiro[0][0]=="X"&&tabuleiro[0][1]=="X"&&tabuleiro[0][2]=="X"){	//verifica se o X é vencedor
		vencedorx();
	}else if(tabuleiro[1][0]=="X"&&tabuleiro[1][1]=="X"&&tabuleiro[1][2]=="X"){
		vencedorx();
	}else if(tabuleiro[2][0]=="X"&&tabuleiro[2][1]=="X"&&tabuleiro[2][2]=="X"){
		vencedorx();
	}else if(tabuleiro[0][0]=="X"&&tabuleiro[1][1]=="X"&&tabuleiro[2][2]=="X"){
		vencedorx();
    }else if(tabuleiro[0][2]=="X"&&tabuleiro[1][1]=="X"&&tabuleiro[2][0]=="X"){
		vencedorx();
    }else if(tabuleiro[0][0]=="X"&&tabuleiro[1][0]=="X"&&tabuleiro[2][0]=="X"){
		vencedorx();
    }else if(tabuleiro[0][1]=="X"&&tabuleiro[1][1]=="X"&&tabuleiro[2][1]=="X"){
		vencedorx();
    }else if(tabuleiro[0][2]=="X"&&tabuleiro[1][2]=="X"&&tabuleiro[2][2]=="X"){
		vencedorx();
    }else if(tabuleiro[0][0]=="O"&&tabuleiro[0][1]=="O"&&tabuleiro[0][2]=="O"){   //verifica se o O é vencedor
		vencedorO();
	}else if(tabuleiro[1][0]=="O"&&tabuleiro[1][1]=="O"&&tabuleiro[1][2]=="O"){
		vencedorO();
	}else if(tabuleiro[2][0]=="O"&&tabuleiro[2][1]=="O"&&tabuleiro[2][2]=="O"){
		vencedorO();
	}else if(tabuleiro[0][0]=="O"&&tabuleiro[1][1]=="O"&&tabuleiro[2][2]=="O"){
		vencedorO();
    }else if(tabuleiro[0][2]=="O"&&tabuleiro[1][1]=="O"&&tabuleiro[2][0]=="O"){
		vencedorO();
    }else if(tabuleiro[0][0]=="O"&&tabuleiro[1][0]=="O"&&tabuleiro[2][0]=="O"){
		vencedorO();
    }else if(tabuleiro[0][1]=="O"&&tabuleiro[1][1]=="O"&&tabuleiro[2][1]=="O"){
		vencedorO();
    }else if(tabuleiro[0][2]=="O"&&tabuleiro[1][2]=="O"&&tabuleiro[2][2]=="O"){
		vencedorO();
    }else{
    	if (contador>=9){
    		cout <<"\n\t\tNao houve vencedores!";
    		j1.partidas++;
    		j2.partidas++;
    		j1.empates++;
    		j2.empates++;
    		mostrarResultado();
				
		}
	}	
}
void vencedorx(){
	if(j1.simbolo == "X"){
		cout << "\n\t\tO jogador (a) " << j1.nome <<" venceu! Parabens! ";
		j1.partidas++;
		j1.ganhos++;
		j2.partidas++;
		j2.perdas++;
	}else{
		cout << "\n\t\tO jogador (a) " << j2.nome <<" venceu! Parabens! ";
		j2.partidas++,
		j2.ganhos++;
		j1.partidas++;
		j1.perdas++;
	}	
	mostrarResultado();	
}

void vencedorO(){
	if(j1.simbolo == "O"){
		cout << "\n\t\tO jogador (a) " << j1.nome <<" venceu! Parabens! "<<endl;
		j1.partidas++;
		j1.ganhos++;
		j2.partidas++;
		j2.perdas++;
	}else{
		cout << "\n\t\tO jogador (a) " << j2.nome <<" venceu! Parabens! "<<endl;
		j2.partidas++,
		j2.ganhos++;
		j1.partidas++;
		j1.perdas++;
	}	
	mostrarResultado();
}
void mostrarResultado(){
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\n\t\tRESULTADO\n"<<endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout <<"\t\t"<< j1.nome << "\n\t\tGanhou: " << j1.ganhos << "\n\t\tPerdeu: " << j1.perdas << "\n\t\tEmpates: " << j1.empates<<"\n\t\tPartidas: " << j1.partidas<<endl;
	cout <<"\n\t\t" << j2.nome << "\n\t\tGanhou: " << j2.ganhos << "\n\t\tPerdeu: " << j2.perdas << "\n\t\tEmpates: " << j2.empates<<"\n\t\tPartidas: " << j2.partidas<<endl;
	maisPartida();
}
void maisPartida(){//perguntar se deseje realizar mais uma partida voltando assim pro ciclo. Caso nao, ele ele volta o menu
	int op;
	cout << "\n\t\tDeseja jogar mais uma partida? [1] SIM [0] VOLTAR: ";
	cin >> op;
	while(cin.fail() || op != 0  && op != 1)
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tCampo invalido, digite novamente: ";
         cin >> op;
        }	
	if(op==1){
		iniciarPartida();
	}else{
		iniciarJogo();
	}
}
/********************************************************************************/
//FICHEIROS
void inicioFicheiro(){
	int op;
	do {
		  system ("CLS");
		  SetConsoleTextAttribute(hConsole, 2);
		  cout << "______________________PARTIDAS______________________\n\n\n";
		  SetConsoleTextAttribute(hConsole, 15);
		  cout<<"\t\tO que deseja realizar \n";
		  cout<<"\t\t1. Inserir\n";
		  cout<<"\t\t2. Listar\n";
		  cout<<"\t\t3. Apagar\n";
		  cout<<"\t\t4. Pesquisar\n";
		  cout<<"\t\t0. Sair\n";
		  cout<<"\t\tDigite sua opcao: ";
		  cin >> op;
		  while(cin.fail()|| op > 4 || op < 0)	{
		     cin.clear();
		     cin.ignore();
		     cout << "\t\tOpcao invalida, digite novamente: ";
	     	 cin >> op;
	      }
	 	  menuPartida(op);
	   	  system ("CLS");
	}while (op != 0);
}
void menuPartida (int opcao){
	switch(opcao){
	 	case 1: 
			    inserirFicheiro();
		break;
		case 2: 
			    listarFicheiro();
		break;
		case 3: 
				apagarFicheiro();
		break;		
		case 4: 
		  		pesquisarFicheiro(); 
		break;
		case 0: 
		break;
	}
}
void inserirFicheiro(){//inserir no ficheiro a partida atual
	int op;
	cout << "\n\t\tDeseja adicionar a partida nos ficheiros? [1] SIM [0] VOLTAR: ";
	do{
		cin >> op;
	}while(op != 0  && op != 1);
	if(op == 1){
		if(j1.partidas == 0){//so adiciono no ficheeiro se houver partidas, se nao nao sera adicionado
			cout << "\n\t\tNao ha partidas para adicionar"<<endl;
			getch();//para manter no ecran
		}else{
			ficheiro.open("partidas.txt",ios::app);//escrita sem sobrepor, no fim
			ficheiro << j1.nome << " Ganhou: " << j1.ganhos << " Perdeu: " << j1.perdas << " Empates: " << j1.empates<<" Partidas: " << j1.partidas<<endl;
			ficheiro << j2.nome << " Ganhou: " << j2.ganhos << " Perdeu: " << j2.perdas << " Empates: " << j2.empates<<" Partidas: " << j2.partidas<<endl;	
			ficheiro.close();
			cout << "\n\t\tPartida adicionada"<<endl;
		}			
	}else{
		inicioFicheiro();
	}	
}
void listarFicheiro(){
	string linha;
	ficheiro.open("partidas.txt",ios::in);
	cout<< "\n\t\tPartidas no ficheiro\n" <<endl;
	if (ficheiro.is_open()){
		while(getline(ficheiro,linha)){
			cout <<"\t\t"<< linha <<endl;
		}
		
	}else{
		cout<< "\t\tAinda nao existe nenhuma partida salva";
		getch();

	}
	ficheiro.close();
	getch();
}
void pesquisarFicheiro(){
	bool flag = false;
	string nome;
	string linha;
	ficheiro.open("partidas.txt",ios::in);
	cout<< "\t\tQual nome de jogador deseja pesquisar?[Atencao: Verifique maiusculas e minusculas -MAIS DE 3 CARATERES-]"<<endl;
	cout<< "\t\tNome: ";
	nome = lerNomeJogadores();
   	if (ficheiro.is_open()){//abrir ficheiro
		while(getline(ficheiro,linha)){//usar o find para encontrar
			if(linha.find(nome) != string::npos){
				cout<< "\n\t\tPartidas encontradas" << endl;
			 	cout << "\t\t"<< linha <<endl;
			 	flag = true;
			}
		}
		
		if(!flag){
			cout<< "\t\tNome inexistente, verifica se digitou corretamente!" << endl;		
			getch();								
		}
	}else{
		cout<< "\t\tAinda nao existe nenhuma partida salva";
	}	
	ficheiro.close();
	getch();
}
void apagarFicheiro(){
	bool flag = false;
	string nome = "";
	string linha;
	fstream ficheiroAux;
	ficheiro.open("partidas.txt",ios::in);
	cout<< "\t\tQual jogador deseja apagar? Digite o nome do jogador [ATENCAO, ISSO AFETARA TODOS OS NOMES CORRESPONDENTES -MAIS DE 3 CARATERES-]\n"<<endl;
	cout<< "\t\tNome: ";
	nome = lerNomeJogadores();
   	if (ficheiro.is_open()){//abrir ficheiro   		
		while(getline(ficheiro,linha)){
			if(linha.find(nome) != string::npos){
			 	flag=true;
			}
		}
	    if (flag==true){
	    	ficheiroAux.open("auxiliar.txt",ios::app);//so criar o ficheiero auxiliar se o ficheiro for possivel ser aberto, e se realmente o nome inserido existe
			ficheiro.clear();
			ficheiro.seekp(0, ios::beg);
			while(getline(ficheiro,linha)){//mandar cada linha para variavel linha
				if(linha.find(nome) == string::npos){//se o nome digitado for diferente, escreve no ficheiro aux, se for igual nao faz nada, dessa forma, ele nao escreve
			 		ficheiroAux << linha << endl;
				}
			}
			cout<< "\t\tPartida apagada com sucesso!";
				ficheiro.close();
				ficheiroAux.close();
				remove("partidas.txt");//removo ficheiro anterior
				rename("auxiliar.txt", "partidas.txt");//renomeio o auxiliar para o nome do arquivo original
		}else{
			cout<< "\t\tNome inexistente, verifica se digitou corretamente!" << endl;		
			getch();								
		}
	}else{
		cout<< "\t\tAinda nao existe nenhuma partida salva";
	}	
	ficheiro.close();
	ficheiroAux.close();
	getch();
}


