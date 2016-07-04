#include "Socket.h"
#include "thread"


using namespace Tigre;


int main(int argc, char *argv[])  {
    try {
        Socket *s = new Socket("127.0.0.1", 10001, TCP);
        s->Bind(5);
        std::cout << "Esperando Cliente\n";
        Socket *cliente = s->Accept();
        cliente->Write("Bem vindo ao servidor!");
        std::cout << "Esperando Mensagem do Cliente\n";
        int i = 0;
        while(i < 100) {
            std::cout << cliente->Read() << "\n";
            i++;
        }
    }catch (SocketException &e){
        std:cerr << e.what();
    }
}