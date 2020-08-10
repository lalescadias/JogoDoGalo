#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cstdio>
#include <windows.h>

using namespace std;
struct player
{
    string name;
    string symbol;
    int winnings;
    int losings;
    int ties;
    int matches;
    bool playerTurn = false;
};
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //change colour of the letter
player player1, player2;
string gameBoard[3][3];
int count=0;
int column, line, match =0;
fstream file;

string readPlayerName();
void startGame();
void menu(int op);
void selectMatchMenu (int opcao);
void showFileMenu();
void showGameBoard();
void insertGameBoard();
void checkWinner();
void winnerX();
void winnerO();
void startGameBoard();
void clearGame();
void setSymbol();
int checkField();
void startMatch();
void checkKeepPlaying();
void showResult();
void insertFile();
void listFile();
void searchFile();
void deleteFile();
void checkGame();

main()
{		
	startGameBoard();
	startGame();
}
void startGameBoard(){//start game board for check in function insertGameBoard
	for (int i=0;i<3;i++)
	{
		for (int k=0; k<3;k++){			
		    gameBoard[i][k] = "";			
		}	
	}
}
void clearGame(){
	player1.name = "\0";
	player1.symbol ="\0";
	player1.winnings =0;
	player1.losings =0;
	player1.ties=0;
	player1.matches=0;
	player1.playerTurn=false;	
	
	player2.name = "\0";
	player2.symbol ="\0";
	player2.winnings =0;
	player2.losings =0;
	player2.ties=0;
	player2.matches=0;
	player2.playerTurn=false;
	
	match =0;
	startGameBoard();
	count =0;//clear count
	startMatch();
}
void startGame(){
	int op=0;
	do {
		  system ("CLS");
		  SetConsoleTextAttribute(hConsole, 2);
		  cout << "\n______________________TIC TAC TOE______________________\n\n\n";
		  SetConsoleTextAttribute(hConsole, 15);
		  cout<<"\t\t\t What do you want to do? \n";
		  cout<<"\t\t1. Play\n";
		  cout<<"\t\t2. Matches\n";
		  cout<<"\t\t0. Exit\n";
		  cout<<"\t\tChoose your option: ";		 
		  op = checkField();
	 	  menu(op);
	   	  system ("CLS");
	}while (op != 0);
}
void menu(int op){		
	    switch(op){
		case 0: cout <<"\t\tGood Bye";
				exit(0);
		break; 
		case 1: checkGame();
		break;
		case 2: showFileMenu();
		break;
	}		
}
void checkGame(){//ckeck if there is a game in progress
	int op;
	if(match > 0){
		cout<<"\t\tThere is a match in progress. Do you wish to continue? [1]YES [0] NO: ";
		cin >> op;
		while(cin.fail() || op != 0  && op != 1)
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tInvalid field. Type again: ";
         cin >> op;
        }	
		if(op==1){
			startMatch();
		}else{
			clearGame();
		}
	}else{
		clearGame();
	}		
}
void startMatch(){	
	match++;		
	if(match == 1){
		cout << "\n\t\tEnter the name of the first player. [More than 3 characters]:";
		player1.name = readPlayerName();
		setSymbol();	
		cout << "\t\tEnter the name of the second player. [More than 3 characters]:";
		player2.name = readPlayerName();	
		player1.playerTurn = true;	
	}else {
		system ("CLS");		
		startGameBoard();
		count =0;//clear count	
	}					
	showGameBoard();		
}
string readPlayerName(){	
	string name;			
	cin.ignore();
	getline( cin, name);
	while(name.length() < 3){		
		cout << "\t\tRetype name: ";
		getline( cin,name );	
	}  
	return name;  		    	  
}
void setSymbol(){
	cout << "\t\tEnter which symbol you want [X | O] (capital letters): ";
	cin >> player1.symbol;
    while(cin.fail() || player1.symbol.length() != 1 || player1.symbol !="X" && player1.symbol !="O")
	   {
	     cin.clear();
	     cin.ignore();
	     cout << "\t\tInvalid option. Type again: ";
	     cin >> player1.symbol;
	    }
	if(player1.symbol == "X"){//verify which symbol the first player chose, to set the symbol for the other player
		player2.symbol = "O";
	}else{
		player2.symbol = "X";
	}	
}

void showGameBoard(){
	system ("CLS");
	cout<<"\t\t Match N: "<<match<< "\n";
	cout << "\n\t\tFirst player: "<<player1.name << " = "<<player1.symbol<<endl;
    cout << "\t\tSecond player: "<<player2.name << " = "<<player2.symbol<<"\n"<<endl;
	int l,c;
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\t\t   0  1  2\n";
	for (l=0;l<3;l++)
	{		
		cout << "\t\t" << l;	
		for (c=0; c<3;c++){
			if (c ==0 ){
				if(gameBoard[l][c].length() == 0){
					cout << "   ";
				}else{
					cout << " "<<gameBoard[l][c]<<" ";
				}
			}else{
				if(gameBoard[l][c].length() == 0){
					cout << "|   ";
				}else{
					cout << "| "<<gameBoard[l][c]<<" ";
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
	checkWinner();
	insertGameBoard();
}
void insertGameBoard(){
	do{//loop for insert data into the gameBoard
		if(player1.playerTurn){
			cout<<"\n\t\tPlayer's turn: "<<player1.name;
		}else{
			cout<<"\n\t\tPlayer's turn: "<<player2.name;
		}	
		cout<<"\n\t\tEnter a line: ";	
		line = checkField();
		cout<<"\t\tEnter a column: ";
		column= checkField();		
		if (gameBoard[line][column].length()==0){//insert symbol if the position is empty
			if(player1.playerTurn){
				gameBoard[line][column]=player1.symbol;
			}else{
				gameBoard[line][column]=player2.symbol;					
			}	
			player1.playerTurn = !player1.playerTurn;
			player2.playerTurn=  !player2.playerTurn;							
			count++;//the count add 1 everytime the player insert to the gameBoard
		}else{
			cout<<"\t\tChoose an empty field\n";
			getch();
		}
		
		showGameBoard();//show the gameBoard after each turn
	} while(count<9);	//the loop stop if all fields are filled
	
}
int checkField(){
	int n;
	cin >> n;
    while(cin.fail()|| n > 2 || n <0 )
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tInvalid field. Type again: ";
         cin >> n;
        }	
	return n;
}

void checkWinner(){//check who is the winner
	
	if (gameBoard[0][0]=="X"&&gameBoard[0][1]=="X"&&gameBoard[0][2]=="X"){	//check X
		winnerX();
	}else if(gameBoard[1][0]=="X"&&gameBoard[1][1]=="X"&&gameBoard[1][2]=="X"){
		winnerX();
	}else if(gameBoard[2][0]=="X"&&gameBoard[2][1]=="X"&&gameBoard[2][2]=="X"){
		winnerX();
	}else if(gameBoard[0][0]=="X"&&gameBoard[1][1]=="X"&&gameBoard[2][2]=="X"){
		winnerX();
    }else if(gameBoard[0][2]=="X"&&gameBoard[1][1]=="X"&&gameBoard[2][0]=="X"){
		winnerX();
    }else if(gameBoard[0][0]=="X"&&gameBoard[1][0]=="X"&&gameBoard[2][0]=="X"){
		winnerX();
    }else if(gameBoard[0][1]=="X"&&gameBoard[1][1]=="X"&&gameBoard[2][1]=="X"){
		winnerX();
    }else if(gameBoard[0][2]=="X"&&gameBoard[1][2]=="X"&&gameBoard[2][2]=="X"){
		winnerX();
    }else if(gameBoard[0][0]=="O"&&gameBoard[0][1]=="O"&&gameBoard[0][2]=="O"){   //check O
		winnerO();
	}else if(gameBoard[1][0]=="O"&&gameBoard[1][1]=="O"&&gameBoard[1][2]=="O"){
		winnerO();
	}else if(gameBoard[2][0]=="O"&&gameBoard[2][1]=="O"&&gameBoard[2][2]=="O"){
		winnerO();
	}else if(gameBoard[0][0]=="O"&&gameBoard[1][1]=="O"&&gameBoard[2][2]=="O"){
		winnerO();
    }else if(gameBoard[0][2]=="O"&&gameBoard[1][1]=="O"&&gameBoard[2][0]=="O"){
		winnerO();
    }else if(gameBoard[0][0]=="O"&&gameBoard[1][0]=="O"&&gameBoard[2][0]=="O"){
		winnerO();
    }else if(gameBoard[0][1]=="O"&&gameBoard[1][1]=="O"&&gameBoard[2][1]=="O"){
		winnerO();
    }else if(gameBoard[0][2]=="O"&&gameBoard[1][2]=="O"&&gameBoard[2][2]=="O"){
		winnerO();
    }else{
    	if (count>=9){
    		cout <<"\n\t\tThere were no winners!";
    		player1.matches++;
    		player2.matches++;
    		player1.ties++;
    		player2.ties++;
    		showResult();
				
		}
	}	
}
void winnerX(){
	if(player1.symbol == "X"){
		cout << "\n\t\tThe player " << player1.name <<" win! Congratulations! ";
		player1.matches++;
		player1.winnings++;
		player2.matches++;
		player2.losings++;
	}else{
		cout << "\n\t\tThe player  " << player2.name <<" win! Congratulations! ";
		player2.matches++,
		player2.winnings++;
		player1.matches++;
		player1.losings++;
	}	
	showResult();	
}

void winnerO(){
	if(player1.symbol == "O"){
		cout << "\n\t\tThe player " << player1.name <<" win! Congratulations! "<<endl;
		player1.matches++;
		player1.winnings++;
		player2.matches++;
		player2.losings++;
	}else{
		cout << "\n\t\tThe player " << player2.name <<" win! Congratulations! "<<endl;
		player2.matches++,
		player2.winnings++;
		player1.matches++;
		player1.losings++;
	}	
	showResult();
}
void showResult(){
	SetConsoleTextAttribute(hConsole, 2);
	cout << "\n\t\tMatch result\n"<<endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout <<"\t\t"<< player1.name << "\n\t\tWinnings: " << player1.winnings << "\n\t\tLosings: " << player1.losings << "\n\t\tTies: " << player1.ties<<"\n\t\tMatches: " << player1.matches<<endl;
	cout <<"\n\t\t" << player2.name << "\n\t\tWinnings: " << player2.winnings << "\n\t\tLosings: " << player2.losings << "\n\t\tTies: " << player2.ties<<"\n\t\tMatches: " << player2.matches<<endl;
	checkKeepPlaying();
}
void checkKeepPlaying(){//perguntar se deseje realizar mais uma match voltando assim pro ciclo. Caso nao, ele ele volta o menu
	int op;
	cout << "\n\t\tWant to play again? [1] Yes [0] Back to menu: ";
	cin >> op;
	while(cin.fail() || op != 0  && op != 1)
       {
         cin.clear();
         cin.ignore();
         cout << "\t\tInvalid field. Type again: ";
         cin >> op;
        }	
	if(op==1){
		startMatch();
	}else{
		startGame();
	}
}
/********************************************************************************/
//FILES
void showFileMenu(){
	int op;
	do {
		  system ("CLS");
		  SetConsoleTextAttribute(hConsole, 2);
		  cout << "______________________MATCHES______________________\n\n\n";
		  SetConsoleTextAttribute(hConsole, 15);
		  cout<<"\t\tWhat do you want to do? \n";
		  cout<<"\t\t1. Insert\n";
		  cout<<"\t\t2. List\n";
		  cout<<"\t\t3. Delete\n";
		  cout<<"\t\t4. Search\n";
		  cout<<"\t\t0. Back to menu\n";
		  cout<<"\t\tChoose your option: ";
		  cin >> op;
		  while(cin.fail()|| op > 4 || op < 0)	{
		     cin.clear();
		     cin.ignore();
		     cout << "\t\tInvalid field. Type again: ";
	     	 cin >> op;
	      }
	 	  selectMatchMenu(op);
	   	  system ("CLS");
	}while (op != 0);
}
void selectMatchMenu (int opcao){
	switch(opcao){
	 	case 1: 
			    insertFile();
		break;
		case 2: 
			    listFile();
		break;
		case 3: 
				deleteFile();
		break;		
		case 4: 
		  		searchFile(); 
		break;
		case 0: 
		break;
	}
}
void insertFile(){
	int op;
	cout << "\n\t\tDo you want to add the match to the files? [1] YES [0] Back to menu: ";
	do{
		cin >> op;
	}while(op != 0  && op != 1);
	if(op == 1){
		if(player1.matches == 0){//just add in file if there are matches, else show the message
			cout << "\n\t\tThere are no matches to add"<<endl;
			getch();
		}else{
			file.open("matches.txt",ios::app);
			file << player1.name << " Winnings: " << player1.winnings << " Losings: " << player1.losings << " Ties: " << player1.ties<<" Matches: " << player1.matches<<endl;
			file << player2.name << " Winnings: " << player2.winnings << " Losings: " << player2.losings << " Ties: " << player2.ties<<" Matches: " << player2.matches<<endl;	
			file.close();
			cout << "\n\t\tMatch added"<<endl;
		}			
	}else{
		showFileMenu();
	}	
}
void listFile(){
	string line;
	file.open("matches.txt",ios::in);
	cout<< "\n\t\tMatches in the file\n" <<endl;
	if (file.is_open()){
		while(getline(file,line)){
			cout <<"\t\t"<< line <<endl;
		}
		
	}else{
		cout<< "\t\tThere is no match added";
		getch();

	}
	file.close();
	getch();
}
void searchFile(){
	bool flag = false;
	string name;
	string line;
	file.open("matches.txt",ios::in);
	cout<< "\t\tWhat player name do you want to search for?[Attention to upper and lower case. More than 3 characters]"<<endl;
	cout<< "\t\tNome: ";
	name = readPlayerName();
   	if (file.is_open()){//open file
		while(getline(file,line)){//use method 'find' to search for a word
			if(line.find(name) != string::npos){
				cout<< "\n\t\tMatches found" << endl;
			 	cout << "\t\t"<< line <<endl;
			 	flag = true;
			}
		}
		
		if(!flag){
			cout<< "\t\tName not found. Make sure you typed correctly!" << endl;		
			getch();								
		}
	}else{
		cout<< "\t\tThere is no match added";
	}	
	file.close();
	getch();
}
void deleteFile(){
	bool flag = false;
	string name = "";
	string line;
	fstream ficheiroAux;
	file.open("matches.txt",ios::in);
	cout<< "\t\tWhich player do you want to delete? Enter the name of the player [Attention: Please note this affects all matching names.More than 3 characters]\n"<<endl;
	cout<< "\t\tName: ";
	name = readPlayerName();
   	if (file.is_open()){//open file   		
		while(getline(file,line)){
			if(line.find(name) != string::npos){
			 	flag=true;
			}
		}
	    if (flag==true){
	    	ficheiroAux.open("aux.txt",ios::app);//just create aux.txt if the file was opened and found the name
			file.clear();
			file.seekp(0, ios::beg);
			while(getline(file,line)){//get line of the file
				if(line.find(name) == string::npos){//if the name was diferent then write in the file aux.txt, else do nothing
			 		ficheiroAux << line << endl;
				}
			}
			cout<< "\t\tMatch deleted successfully!";
				file.close();
				ficheiroAux.close();
				remove("matches.txt");//delete previous file
				rename("aux.txt", "matches.txt");//rename the file aux.txt to the original name
		}else{
			cout<< "\t\tName not found. Make sure you typed correctly!" << endl;		
			getch();								
		}
	}else{
		cout<< "\t\tThere is no match added";
	}	
	file.close();
	ficheiroAux.close();
	getch();
}


