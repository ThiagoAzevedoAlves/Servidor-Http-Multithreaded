#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

using namespace std;

void *comunicar(int socket);
void *conectar(void *sockk){
			struct sock *socket;
			socket=(struct sock*)sockk;
			return comunicar(socket->new_socket);
}
int verificaMetodo(string &metodo);
int verificaProtocolo(string &protocolo);
void montaCabecalho(string &protocolo, string &codigo, string &descricao, string &mensagem, int &socket, string &type, int erro);
void HEAD(string &arquivo, int socket);
void GET(string &arquivo, int socket);
string pegaExtensao(string &arquivo);

#endif // SERVIDOR_H
