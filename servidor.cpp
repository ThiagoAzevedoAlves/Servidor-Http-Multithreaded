#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int main(int argc, char *argv[]){
	//Testa se a chamada do servidor foi executada corretamente.	
	if (argc != 3){
		cout << "\nArgumentos inválidos.\nPor favor, siga a seguinte sintaxe:\n./exe [diretorio] [porta]\n\n";
		exit(1);
	}

	int sock, novosock, num_char; //sock e novosock armazenam o retorno do sistema de criação e aceitação do socket,
											// num_char armazena o valor de retorno de read() e write(), 
                                 //contendo o número de caracteres lidos ou escritos.
	
	int porta = atoi(argv[2]); //a porta em que o servidor irá executar
	socklen_t cliente_len; //armazena o tamanho do endereço do cliente
	char buffer[256], dir[256];
	strcpy(dir, argv[1]);	
	struct sockaddr_in end_serv, end_cli;   // contém o endereço do sevidor e cliente
	sock = socket(AF_INET, SOCK_STREAM, 0); //cria um novo socket
	if (sock < 0){                          //retorna -1 no caso de falha
		cout << "Erro ao abrir socket." << endl;
	}
	bzero((char*) &end_serv, sizeof(end_serv)); //inicia a estrutura com todos os valores zero
	end_serv.sin_family = AF_INET;
	end_serv.sin_addr.s_addr = INADDR_ANY;
	end_serv.sin_port = htons(porta);
	if (bind(sock, (struct sockaddr *) &end_serv, sizeof(end_serv)) < 0){ //realiza o bind testando se não há erros. 
		cout << "Erro ao realizar o bind." << endl;
	}
	listen(sock, 5);
	cout << "Executando Servidor HTTP..." << endl;
	cout << "Porta: " << porta << endl;
	cout << "Diretorio: " << dir << endl;
	while(true){
		if ((novosock = accept(sock, (struct sockaddr *)&end_cli, (socklen_t*)&cliente_len)) == -1){
			cout << "Conexao não estabelecida." << endl;
			exit(1);
		}else{
			cout << "Conexao estabelecida." << endl;
		}
		pthread_t thread;
		pthread_create(&thread, NULL, &conectar, (void*)novosock);
	}
}

void comunicar(int socket){
	bool b, erro;
	int i, len;
	char mensagem[TAM+1];
	string metodo, truk, resto, protocolo, tipo, tprotocolo, codigo, descrição, msg;
	vector<string> linhas;
	istringstream buffer;
	
	//trata os pedidos	

	b = true;
	for(i=0 ; ; i++){
		if (recv(socket, mensagem, TAM, 0) == -1){
			cout << "Erro ao realizar o recieve." << endl;
			exit(1);
		}
		linhas.push_back(msg);
		if (mensagem[0] == '\r'){
			b = false;
			linhas.pop_back();
			break;
		}
		mensagem[0] = '\0';
	}

	//aqui verifica os erros e executa os pedidos 
	len = linhas.size();
	for (i = 0; i < len; i++){
		buffer.clear();
		protocolo.clear();
		truk.clear();
		resto.clear(); 
		metodo.clear();		

		strcpy(mensagem, linhas[i].data());
		
		buffer.str(linhas[i].c_str());
		buffer.getline(msg, MSG_TAM, '\n');
		buffer.str(msg);
		
		buffer >> metodo;
		buffer >> truk;
		buffer >> protocolo;
		buffer >> resto;
		tprotocolo = "HTTP/1.1";
		tipo = "text/html";
		erro = 1;

		//aqui verifica se foi digitada uma linha em branco pelo cliente entre os pedidos
		if (!metodo.empty()){
			if ((!resto.empty()) || (protocolo.empty()) || (truk.empty())){
				codigo = "400";
				descricao = "BAD REQUEST";
				msg= "Seu navegador mandou um pedido que o Servidor não conseguiu entender.";
			}
			else if (verificaProtocolo(protocolo) == 0){
				codigo = "505";
				descricao = "HTTP Version Not Supported";
				mensagem = "O Servidor não suporta a versão do protocolo HTTP que é utilizado na mensagem.";
			}
			else if (verificaMethod(metodo) == -1 ){
				m = verificaMethod(metodo);				
				codigo = "405";
				descricao = "Method Not Allowed";
				mensagem = "O metodo " + method + " não esta apto na URL " + truk + " .";
			}else{
				erro = 0;
			}
			
			//aqui forma o caminho para o arquivo desejado
			truk = this->dir + truk;
			
			//aqui verifica qual metodo que foi pedido
			if (m == 0){
				HEAD(truk, c_socket);
			}
			else{
				GET(truk, c_socket);
			}
		}
	}
	
	//aqui fecha o socket
	close (c_socket);
	return 0;
}

static void *conectar(void *sock){ //Esse metodo foi feito para auxiliar na criação das threads
			struct sock *socket;
			socket = (struct sock*)sock;
			return comunicar(socket->new_socket);
}

int Servidor::verificaProtocolo(string &protocolo){
	if (protocol == "HTTP/1.1"){
		return 1;
	}
	return 0;
}

int Servidor::verificaMetodo(string &metodo){
	if (metodo == "HEAD"){
		return 1;
	}
	if (metodo == "GET"){
		return 2;
	}
	return -1;
}
