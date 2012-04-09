#include <iostream>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

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
	struct sockaddr_in end_serv, end_cli; // contém o endereço do sevidor e cliente
	cout << porta << endl;
}
