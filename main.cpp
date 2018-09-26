#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <windows.h>

using namespace std;

int indice (int n, int tam) {
    return (n % tam);
}

void printar (unordered_map<int, int> cache[],int qtd_memoria, int tam, bool val[]) {
    for (int i = 0; i < qtd_memoria; i++){
        cout << "Bloco\t\tValor\t\tValidade" << endl;
        for (int j = 0; j < tam; j++){
            printf("%2d   \t\t", j);
            if (val[j] == true)
                printf("%4d\t\t", cache[i][j]);
            else
                cout << "null \t\t";
            cout << val[j] << endl;
        }
        cout << "______________________________________________" << endl;
    }
}

int main()
{
    int tam;
    int qtd_memoria;
    cout << "Quantos blocos tem a sua memoria: ";
    cin >> tam;
    cout << "Quantas memorias voce tem: ";
    cin >> qtd_memoria;
    bool validade[tam];
    unordered_map<int, int> cache[qtd_memoria];

    for (int i = 0; i < tam; i++)
        validade[i] = false;
    int n;
    do {
        system("cls");

        printar (cache, qtd_memoria, tam, validade);

        cout << "Endereco para procurar:";
        cin >> n;
        for ( int i = 0; i < qtd_memoria; i++){
            if ( n == cache[i][indice(n, tam)] && validade[indice(n, tam) == true])
                cout << "acerto\n";
            else {
                cout << "O endereco nao foi encontrado\n";
                cache[i][indice(n, tam)] = n;
                validade[indice(n, tam)] = true;
            }
        }

//        cout << "Sair?(S/N)\n";
//        char aux;
//        cin >> aux;
//        if ( aux == 'S' || aux == 's')
//            break;
//        else
            //continue;
        Sleep (750);
    } while (true);
    return 0;
}
