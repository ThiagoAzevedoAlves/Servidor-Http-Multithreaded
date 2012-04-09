#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]){
	//Testa se a chamada do servidor foi executada corretamente.	
	if (argc != 2){
		cout << "\nArgumentos inválidos.\nPor favor, siga a seguinte sintaxe:\n./exe [porta]\n\n";
		exit(1);
	}

	int sock, novosock, num_char; //sock e novosock armazenam o retorno do sistema de criação e aceitação do socket,
											// num_char armazena o valor de retorno de read() e write(), 
                                 //contendo o número de caracteres lidos ou escritos.
	
	int porta = atoi(argv[1]); //a porta em que o servidor irá executar
	socklen_t cliente_len; //armazena o tamanho do endereço do cliente
	char buffer[256];
	struct sockaddr_in end_serv, end_cli;   // contém o endereço do sevidor e cliente
	sock = socket(AF_INET, SOCK_STREAM, 0); //cria um novo socket
	if (sock < 0){                          //retorna -1 no caso de falha
		cout << "Erro ao abrir socket." << endl;
	}
	bzero((char*) &end_serv, sizeof(end_serv)); //inicia a estrutura com todos os valores zero
	end_serv.sin_family = AF_INET;
	end_serv.sin_addr.s_addr = INADDR_ANY;
	end_serv.sin_port = htons(porta);
	if (bind(sock, (struct sockaddr *) &end_serv, sizeof(end_serv)) < 0){ 
		cout << "Erro ao realizar o bind." << endl;
	}
	listen(sock, 5);
}
