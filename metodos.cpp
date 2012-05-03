#include "servidor.h"
#include <string>

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

			//avisa sobre erro
			if (erro){
				montaCabecalho(protocolo, codigo, descricao, mensagem, socket, tipo,1);
			}
			else{
			
				//aqui forma o caminho para o arquivo desejado
				truk = this->dir + truk;
				
				//aqui verifica qual metodo que foi pedido
				if (m == 0){
					HEAD(truk, socket);
				}
				else{
					GET(truk, socket);
				}
			}
		}
	}
	
	//aqui fecha o socket
	close (c_socket);
	return 0;
}

int verificaProtocolo(string &protocolo){
	if (protocol == "HTTP/1.1"){
		return 1;
	}
	return 0;
}

int verificaMetodo(string &metodo){
	if (metodo == "HEAD"){
		return 1;
	}
	if (metodo == "GET"){
		return 2;
	}
	return -1;
}

void montaCabecalho(string protocolo,string codigo, string descricao, string mensagem, int socket, string type, int erro){
	
	string cabecalho;
	time_t hora;
   char data[50];
   hora=time(NULL);
   strftime(data, sizeof(data), "%a, %d/%m/%Y %H:%M:%S", gmtime(&hora));
	
	cabecalho=protocolo;
	cabecalho+=" ";
	cabecalho+=codigo;
	cabecalho+=" ";
	cabecalho+=descricao;
	cabecalho+="\nConnection: close\nDate: ";
	cabecalho+=data;
	cabecalho+=" \nServer: Servidor-Http-Multithreaded";
	cabecalho+="\nAllow: GET, HEAD";
	cabecalho+="\nContent-Type: ";
	cabecalho+=type;
	cabecalho+="\n";
	send(socket, cabecalho.data(), cabecalho.size(),0);
	cout << cabecalho;
	
	
	if(erro){
		cabecalho.clear();
		
		cabecalho="\n\n<HTML>\n<HEAD>\n<title>";
        cabecalho+=codigo;
        cabecalho+=" ";
        cabecalho+=descricao;
        cabecalho+="</titulo>\n</HEAD>\n<BODY>\n<H4>";
        cabecalho+=codigo;
        cabecalho+=" ";
        cabecalho+=descricao;
        cabecalho+="</H4>\n";
        cabecalho+=mensagem;
        cabecalho+="\n</BODY>\n</HTML>\n";
        send(socket, cabecalho.data(), cabecalho.size(),0);
        cout << cabecalho;		
	}
	
}

void GET(string arquivo, int socket){
	
	ifstream in(arquivo.data());
	string dados;
	char ficheiro[1000];
	
	if(!in){
		string type=pegaExtensao(arquivo);
		if(type==NULL){
			cout << "\nErro Extensão Inesistente";
			close(socket);
			exit(0);
		}
		
		montaCabecalho(protocolo,"404","Not Found","Ficheiro não Encontrado",socket,type,1);
		close(socket);
		exit(0);
	}
	else{
		string type=pegaExtensao(arquivo);
		if(type==NULL){
			cout << "\nErro Extensão Inesistente";
			close(socket);
			exit(0);
		}
		
		montaCabecalho(protocolo,"200","OK","Página Carregada",socket,type,0);
		in.getline(ficheiro,1000,'\n');
		dados.clear();
	
		while(in){
			dados.clear();
			dados=ficheiro;
			write(socket,dados.data(),dados.size());
			in.getline(ficheiro,1000,'\n');
			//cout << "\n" << dados;
		}
	}
	in.close();
}
	
void HEAD(string arquivo, int socket){
	
	ifstream in(arquivo.data());
	
	if(!in){
		string type=pegaExtensao(arquivo);
		if(type==NULL){
			cout << "\nErro Extensão Inesistente";
			close(socket);
			exit(0);
		}
		
		montaCabecalho(protocolo,"404","Not Found","Ficheiro não Encontrado",socket,type,0);
	}
	else{
		string type=pegaExtensao(arquivo);
		if(type==NULL){
			cout << "\nErro Extensão Inesistente";
			close(socket);
			exit(0);
		}
		
		montaCabecalho(protocolo,"200","OK","Página Carregada",socket,type,0);
	}
	in.close();
}

string pegaExtensao(string &arquivo){
	string extensao;
	extensao=strrchr(arquivo.data(),'.');
	if((extensao==".html") || (extensao==".htm"))return "text/html";
	else if(extensao==".css") return "text/css";
	else if(extensao==".php") return "text/php";
	else if((extensao==".jpeg") || (extensao==".jpg"))return "image/jpeg";
	else if(extensao==".gif")return "image/gif";
	else if(extensao==".png")return "image/png";
	else if(extensao==".mp3") return "audio/mpeg";
	else if(extensao==".wav") return "audio/wav";
	else if(extensao==".au") return "audio/basic";
	else if((extensao==".mpeg") || (extensao==".mpg")) return "video/mpeg";
	else if(extensao==".avi") return "video/x-msvideo";
	else return "";
}
