//C++ — это мышцы. Его задача — максимально быстро стучаться в сокеты. Ему не нужно думать о форматах файлов и красивых отчетах.
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib> // добавлено для atoi

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <IP> <порт>\n";
        std::cerr << "Пример: " << argv[0] << " 127.0.0.1 80\n";
        return 1;
    }
    
    std::string target_ip = argv[1];
    int target_port = std::atoi(argv[2]); 

    struct sockaddr_in addr; //структура айпи адреса
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    
    if (inet_pton(AF_INET, target_ip.c_str(), &addr.sin_addr) <= 0) { //переводим айпи адрес в бинарный вид
        std::cerr << "Неверный IP-адрес!" << '\n';
        return 1;
    }

    std::cout << "Сканирование " << target_ip << " на порт " << target_port << "...\n";

    // Убрали цикл, теперь сканируем только заданный порт для скорости
    int client_socket = socket(AF_INET, SOCK_STREAM, 0); //создаем новый сокет
    if (client_socket >= 0) {
        addr.sin_port = htons(target_port); //в структуре обновляем номер порта 

        int connect_result = connect(client_socket, (struct sockaddr*)&addr, sizeof(addr)); //пытаемся подкл и сразу сохр рез в переменную

        if (connect_result == 0) { //если 0 - подкл установлено
            std::cout << "[+] Порт " << target_port << " ОТКРЫТ!" << '\n';
        }

        close(client_socket); //закрываем сокет, иначе блок
    }

    std::cout << "Сканирование завершено!\n";
    return 0;
}