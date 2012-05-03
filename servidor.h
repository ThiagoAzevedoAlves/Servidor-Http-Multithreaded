
//SERIVIDOR HTTP 1.1 DESENVOLVIDO POR THIAGO AZEVEDO E BRUNO IOST//

#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

using namespace std;

void conectar(void *sockk);
void *comunicar(int socket);
int verificaMetodo(string &metodo);
int verificaProtocolo(string &protocolo);
void montaCabecalho(string &protocolo, string &codigo, string &descricao, string &mensagem, int &socket, string &type, int erro);
void HEAD(string &arquivo, int socket);
void GET(string &arquivo, int socket);
string pegaExtensao(string &arquivo);

#endif // SERVIDOR_H
