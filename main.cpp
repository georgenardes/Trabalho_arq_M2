#include <unordered_map>
#include <vector>
#include <ctype.h>
#include <iostream>
//#include <windows.h>
#include <math.h>
#include <unistd.h>

using namespace std;
#define ENDERECO 32
#define PALAVRA 4
//#define INT_MAX INTMAX_MAX

struct bloco
{
    int tag;
    int tempo;
    bool val;
};

int indice (int n, int tam)
{
    return (n % tam);
}

void printar (unordered_map<int, bloco> cache[],int grau_asso, int qtd_bloco, int tempo)
{
    system("cls");
    //system("clear");
    for (int i = 0; i < grau_asso; i++)
    {
        cout << "Bloco\tValor\tValidade\tTempo";
        for (int j = 0; j < qtd_bloco; j++)
        {
            printf("\n%2d   \t", j);
            printf("%4d\t", cache[i][j].tag);
            cout << cache[i][j].val << "\t\t";
            cout << cache[i][j].tempo;
        }
        cout << "\t\tTempo atual: " << tempo <<endl;
        cout << "---------------------------------" << endl;
    }
}

int num_exp(int  n)
{
    int exp = 1;
    int base = 2;
    while ( (pow (base, exp)) < n)
        exp++;
    return  exp;
}
int getch ()
{
    cin.ignore();
    return  cin.get();
}

int main()
{
    int qtd_bloco = 0;
    int grau_asso = 0;
    int custo_bit = 0;
    int tempo = 1;

    do
    {

        cout << "Quantos blocos tem a sua memoria: ";
        cin >> qtd_bloco;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Digite um numero por favor\n";
            cin >> qtd_bloco;
        }
    }
    while (qtd_bloco <= 0);

    do
    {
        cout << "Qual o grau de associatividade: ";
        cin >> grau_asso;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Digite um numero por favor\n";
            cin >> grau_asso;
        }
    }
    while (grau_asso <= 0 || qtd_bloco%grau_asso != 0.0 );

    /* Quantidade de bloco passa a ser quantidade de bloco por via */
    qtd_bloco = qtd_bloco/grau_asso;

    /* Usado tabela hash por ser mais facil de associar com uma memoria cache *
     * Cache é a variavel usada como uma memoria cache real */
    unordered_map<int, bloco> cache[grau_asso];

    /* Zera todos os tempos iniciais */
    for ( int i = 0; i < grau_asso; i++)
        for ( int j = 0; j < qtd_bloco; j++)
            cache[i][j].tempo = 0;

    /* Mostra a formula do custo de tag */
    cout << grau_asso << " * ";
    cout << pow (2, num_exp(qtd_bloco)) << " * (";
    cout << ENDERECO << " - (";
    cout << num_exp(qtd_bloco) << " + ";
    cout << num_exp(PALAVRA) << " + 2))\n\n";

    /* Faz o calculo do custo em bit para as tags */
    custo_bit = grau_asso * pow (2, num_exp(qtd_bloco)) * ( ENDERECO - num_exp(qtd_bloco) - num_exp(PALAVRA) - 2)  ;
    cout << "Custo em bits = "<<custo_bit << endl;
    cout << "enter para prosseguir ";
    getch();

    system("cls");
    //system("clear");
    do
    {
        /* Chamada de função para mostrar o estado da cache */
        printar (cache, grau_asso, qtd_bloco, tempo);

        char op;
        cout << "Digite 'p' para procurar um endereco ou 'i' para invalidar um bloco: ";
        cin >> op;

        if (op == 'p')
        {
            int endereco;
            int mais_antigo = 99999;
            int memo_to_change = 0;
            bool encontrado = false;

            do
            {
                cout << "Endereco para procurar:";
                cin >> endereco;
                while (cin.fail())
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "Digite um numero por favor\n";
                    cin >> endereco;
                }
            }
            while (endereco <= 0);

            /* Dado o endereço para pesquisar, é iniciado a busca na cache *
             * analisando a tag somente dos blocos com bit de validade em 1*/
            for ( int i = 0; i < grau_asso; i++)
            {
                if ( cache[i][indice(endereco, qtd_bloco)].val == true )
                {
                    /* Dos blocos validos, é coletado o índice do bloco com maior tempo de
                     * espera e salvo na variavel memo_to_change*/
                    if ( mais_antigo > cache[i][indice(endereco, qtd_bloco)].tempo )
                    {
                        mais_antigo = cache[i][indice(endereco, qtd_bloco)].tempo;
                        memo_to_change = i;
                    }
                    /* Se a tag de algum bloco for igual ao endereço que esta sendo procurado
                     * obtem-se um 'hit'. Em seguida atualizado o tempo e finalizada a busca */
                    if ( endereco == cache[i][indice(endereco, qtd_bloco)].tag )
                    {
                        cout << "Acerto\n";
                        cache[i][indice(endereco, qtd_bloco)].tempo = tempo;
                        encontrado = true;
                        break;
                    }
                }
            }
            /* Se o endereço não for encontrado na primeira varredura,
             * inicia-se uma segunda varredura em busca do primeiro bloco com
             * bit de validade em 0 */
            if ( encontrado == false )
            {
                for ( int i = 0; i < grau_asso; i++)
                {
                    if ( cache[i][indice(endereco, qtd_bloco)].val == false )
                    {
                        cout << "Dado invalido \n";
                        cache[i][indice(endereco, qtd_bloco)].tag = endereco;
                        cache[i][indice(endereco, qtd_bloco)].tempo = tempo;
                        cache[i][indice(endereco, qtd_bloco)].val = true;
                        encontrado = true;
                        break;
                    }
                }

            }
            /* Caso o endereço seja encontrado em nenhuma das verificações anteriores
             * é então substituido o bloco mais antigo na cache */
            if ( encontrado == false )
            {
                cout << "O endereco nao foi encontrado\n";
                cache[memo_to_change][indice(endereco, qtd_bloco)].tag = endereco;
                cache[memo_to_change][indice(endereco, qtd_bloco)].tempo = tempo;
                cache[memo_to_change][indice(endereco, qtd_bloco)].val = true;
            }
            //Sleep (750);
            sleep(3);
            tempo++;
        }
        else if (op == 'i')
        {
            int num_bloco = -1;
            int num_via = -1;
            cout << "Escolha o bloco: ";
            cin >> num_bloco;
            cout << "Escolha a via: ";
            cin >> num_via;
            cache[num_via][indice(num_bloco, qtd_bloco)].val = false;
        }
        else
        {
            system("cls");
            //system("clear");
        }
    }
    while (true);

    return 0;
}
