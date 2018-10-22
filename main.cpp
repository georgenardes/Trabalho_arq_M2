#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
//#include <windows.h>
#include <unistd.h>
#include <math.h>
using namespace std;
#define ENDERECO 32
#define PALAVRA 1


struct bloco {
    int tag;
    int tempo;
    bool val;
};

int indice (int n, int tam) {
    return (n % tam);
}

void printar (unordered_map<int, bloco> cache[],int grau_asso, int qtd_bloco) {
    system("cls");
    //system("clear");
    for (int i = 0; i < grau_asso; i++){
        cout << "Bloco\tValor\tValidade\tTempo" << endl;
        for (int j = 0; j < qtd_bloco; j++){
            printf("%2d   \t", j);
            if ( cache[i][j].val == true)
                printf("%4d\t", cache[i][j].tag);
            else
                cout << "null \t";
            cout << cache[i][j].val << "\t\t";
            cout << cache[i][j].tempo << endl;
        }
        cout << "---------------------------------" << endl;
    }
}

int num_exp(int  n) {
    int exp = 1;
    int base = 2;
    while ( (pow (base, exp)) < n)
        exp++;
    return  exp;
}

int main()
{
    int qtd_bloco = 0;
    int grau_asso = 0;
    int custo_bit = 0;

    cout << "Quantos blocos tem a sua memoria: ";
    cin >> qtd_bloco;
    cout << "Qual o grau de associatividade: ";
    cin >> grau_asso;

    qtd_bloco = qtd_bloco/grau_asso;

    cout << grau_asso << " * ";
    cout << qtd_bloco << " * (";
    cout << ENDERECO << " - (";
    cout << num_exp(qtd_bloco) << " + ";
    cout << num_exp(PALAVRA) << " + 2) + 1)\n\n";

    custo_bit = grau_asso * pow (2, num_exp(qtd_bloco)) * ( ENDERECO - num_exp(qtd_bloco) - num_exp(PALAVRA) - 2 + 1)  ;
    cout << "Custo em bits = "<<custo_bit << endl;
    system ("pause");
    system("cls");
    unordered_map<int, bloco> cache[grau_asso];

    for ( int i = 0; i < grau_asso; i++)
        for ( int j = 0; j < qtd_bloco; j++)
            cache[i][j].tempo = 0;

    int endereco;
    int tempo = 1;

    system("cls");

    //system("clear");
    do {
        printar (cache, grau_asso, qtd_bloco);
        cout << "Endereco para procurar:";
        cin >> endereco;
        int mais_antigo = 99999;
        int memo_to_change = 0;
        bool encontrado = false;

        for ( int i = 0; i < grau_asso; i++){
            if ( mais_antigo > cache[i][indice(endereco, qtd_bloco)].tempo ){
                mais_antigo = cache[i][indice(endereco, qtd_bloco)].tempo;
                memo_to_change = i;
            }
            if ( endereco == cache[i][indice(endereco, qtd_bloco)].tag ) {

                if ( cache[i][indice(endereco, qtd_bloco)].val == true ){
                    cache[i][indice(endereco, qtd_bloco)].tempo = tempo;
                    //color;
                    cout << "Acerto\n";
                    encontrado = true;
                    //branco
                }
                else {
                    cout << "Vencido\n";
                    cache[i][indice(endereco, qtd_bloco)].val = true;
                }
            }
        }
        if ( encontrado == false ) {
            //color
            cout << "O endereco nao foi encontrado\n";
            //branco
            cache[memo_to_change][indice(endereco, qtd_bloco)].tag = endereco;
            cache[memo_to_change][indice(endereco, qtd_bloco)].tempo = tempo;
            cache[memo_to_change][indice(endereco, qtd_bloco)].val = true;
        }
        //Sleep (750);
        sleep(1);
        tempo++;
    } while (true);

    return 0;
}
