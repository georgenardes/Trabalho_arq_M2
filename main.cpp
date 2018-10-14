#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
//#include <windows.h>
#include <unistd.h>
#include <math.h>
using namespace std;

struct bloco {
    int tag;
    int tempo;
    bool val;
};

int indice (int n, int tam) {
    return (n % tam);
}

void printar (unordered_map<int, bloco> cache[],int qtd_vias, int qtd_bloco) {
    //system("cls");
    system("clear");
    for (int i = 0; i < qtd_vias; i++){
        cout << "Bloco\tValor\tValidade" << endl;
        for (int j = 0; j < qtd_bloco; j++){
            printf("%2d   \t", j);
            if ( cache[i][j].val == true)
                printf("%4d\t", cache[i][j].tag);
            else
                cout << "null \t";
            cout << cache[i][j].val << endl;
        }
        cout << "------------------------" << endl;
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
    int qtd_vias = 0;
    int qtd_palavras = 0;
    int qtd_bit_end = 0;
    int custo_bit = 0;

    cout << "Quantos blocos tem a sua memoria: ";
    cin >> qtd_bloco;
    cout << "Quantas palavras por bloco: ";
    cin >> qtd_palavras;
    cout << "Quantas vias voce tem: ";
    cin >> qtd_vias;
    cout << "Quantos bits tem o endereco: ";
    cin >> qtd_bit_end;

    cout << qtd_vias << " * ";
    cout << qtd_bloco << " * (";
    cout << qtd_bit_end << " - (";
    cout << num_exp(qtd_bloco) << " + ";
    cout << num_exp(qtd_palavras) << " + 2) + 1)\n\n";
    custo_bit = qtd_vias * qtd_bloco * ( qtd_bit_end - num_exp(qtd_bloco) - num_exp(qtd_palavras) - 2 + 1)  ;
    cout << "Custo em bits = "<<custo_bit << endl;
    sleep(5);

    unordered_map<int, bloco> cache[qtd_vias];

    for ( int i = 0; i < qtd_vias; i++)
        for ( int j = 0; j < qtd_bloco; j++)
            cache[i][j].tempo = 0;

    int endereco;
    int tempo = 1;

    //system("cls");

    system("clear");
    do {
        printar (cache, qtd_vias, qtd_bloco);
        cout << "Endereco para procurar:";
        cin >> endereco;
        int mais_antigo = 99999;
        int memo_to_change = 0;
        bool encontrado = false;

        for ( int i = 0; i < qtd_vias; i++){
            if ( mais_antigo > cache[i][indice(endereco, qtd_bloco)].tempo ){
                mais_antigo = cache[i][indice(endereco, qtd_bloco)].tempo;
                memo_to_change = i;
            }
            if ( endereco == cache[i][indice(endereco, qtd_bloco)].tag ) {

                if ( cache[i][indice(endereco, qtd_bloco)].val == true ){
                    cache[i][indice(endereco, qtd_bloco)].tempo = tempo;
                    cout << "Acerto\n";
                    encontrado = true;
                }
                else {
                    cout << "Vencido\n";
                    cache[i][indice(endereco, qtd_bloco)].val = true;
                }
            }
        }
        if ( encontrado == false ) {
            cout << "O endereco nao foi encontrado\n";
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
