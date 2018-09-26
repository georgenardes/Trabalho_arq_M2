#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
using namespace std;

int indice (int n, int tam) {
    return (n % tam);
}

void printar (unordered_map<int, int> cache, int tam, bool val[]) {
    cout << "Bloco\t\tValor\t\tValidade" << endl;
    for (int i = 0; i < tam; i++){
        printf("%2d   \t\t", i);
        if (val[i] == true)
            printf("%4d\t\t", cache[i]);
        else
            cout << "null \t\t";
        cout << val[i] << endl;
    }
    cout << "______________________________________________" << endl;
}

int main()
{
    unordered_map<int, int> cache;
    int tam;
    cout << "Quantos blocos tem a sua memoria:" << endl;
    cin >> tam;
    bool validade[tam];

    for (int i = 0; i < tam; i++)
        validade[i] = false;
    int n;
    do {
        system("cls");
        printar (cache, tam, validade);
        cout << "Endereco para procurar:";
        cin >> n;
        if ( n == cache[indice(n, tam)] && validade[indice(n, tam) == true])
            cout << "acerto\n";
        else {
            cout << "O endereco nao foi encontrado\n";
            cache[indice(n, tam)] = n;
            validade[indice(n, tam)] = true;
        }
        cout << "Sair?(S/N)\n";
        char aux;
        cin >> aux;
        if ( aux == 'S' || aux == 's')
            break;
        else
            continue;
    } while (true);
    return 0;
}
