#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <windows.h>
using namespace std;

struct bloco
{
    int tag;
    int tempo;
    bool val;
};

int indice (int n, int tam) {
    return (n % tam);
}

void printar (unordered_map<int, bloco> cache[],int qtd_memoria, int tam) {
    system("cls");
    for (int i = 0; i < qtd_memoria; i++){
        cout << "Bloco\tValor\tValidade" << endl;
        for (int j = 0; j < tam; j++){
            printf("%2d   \t", j);
            if ( cache[i][j].val == true)
                printf("%4d\t", cache[i][j].tag);
            else
                cout << "null \t";
            cout << cache[i][j].val << endl;
        }
        cout << "______________________________" << endl;
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

    unordered_map<int, bloco> cache[qtd_memoria];
    int endereco;
    int tempo = 0;
    system("cls");
    do {
        printar (cache, qtd_memoria, tam);

        cout << "Endereco para procurar:";
        cin >> endereco;
        int mais_antigo = 99999;
        int memo_to_change;
        bool encontrado = false;
        for ( int i = 0; i < qtd_memoria; i++){
            if ( mais_antigo > cache[i][indice(endereco, tam)].tempo ){
                mais_antigo =cache[i][indice(endereco, tam)].tempo;
                memo_to_change = i;
            }
            if ( endereco == cache[i][indice(endereco, tam)].tag ) {
                if ( cache[i][indice(endereco, tam)].val == true ){
                    cache[i][indice(endereco, tam)].tempo = tempo;
                    cout << "Acerto\n";
                    encontrado = true;
                }
                else
                    cout << "Vencido\n";
            }
        }
        if ( encontrado == false ) {
            cout << "O endereco nao foi encontrado\n";
            cache[memo_to_change][indice(endereco, tam)].tag = endereco;
            cache[memo_to_change][indice(endereco, tam)].tempo = tempo;
            cache[memo_to_change][indice(endereco, tam)].val = true;
        }
        Sleep (750);
        tempo++;
    } while (true);
    return 0;
}
