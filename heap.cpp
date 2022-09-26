/*
Joao Luis Chiarelotto Crema

ENUNCIADO 
    Sua tarefa será construir um heap (binário, max-heap), e criar métodos para criar a árvore e a 
partir de um array, inserir, excluir, e buscar valores na árvore. Seu objetivo é explicar o funcionamento 
dos  métodos  que  você  irá  criar.  Para  isso,  deve  buscar  em  sites  acadêmicos,  exemplos  de 
implementação de árvores heap. 
    Para  testar,  você deve usar  um  array  com,  no  mínimo, 500  itens,  gerados  randomicamente  e 
criar métodos para testar se a estrutura criada obedece a regra de criação que você determinou. 
*/

#include<iostream>
#include<math.h>
#include<random>
using namespace std;

void troca(int &x, int &y) //funcao que troca o valor de lugar caso ele nao atenda a estrutura de Max Heap
{
    int temp = x;
    x = y;
    y = temp;
}

class MaxHeap //classe da Heap
{
    public:
        int *arr; //ponteiro para o array de dados na MaxHeap
        int tamanhoHeap; //tamanho max possivel da MaxHeap
        int capacidadeHeap; //numero de elementos na MaxHeap atual

        MaxHeap(int cap) //atributos da Heap
        {
            tamanhoHeap = 0;
            capacidadeHeap = cap;
            arr = new int [cap];
        }

        void BuscaLinear(int val) //varre o array um por um
        {
            for (int i = 0; i < tamanhoHeap; i++)
            {
                if(arr[i]==val)
                {
                    cout<<"Valor encontrado";
                    return;
                }
            }
            cout<<"Valor nao encontrado";
        }

        void PrintArray() //print o array inteiro
        {
            for (int i = 0; i < tamanhoHeap; i++)
                cout<<arr[i]<<" ";
            cout<<endl;
        }

        int altura () // calcula altura da MaxHeap
        {
            return ceil(log2(tamanhoHeap+1))-1;
        }

        int pai(int i) //checa o pai do no
        {
            return(i-1)/2;
        }
        int esq(int i) //checa o valor a esquerda do no
        {
            return(2*i+1);
        }
        int dir(int i) //checa o valor a direita do no
        {
            return(2*i+2);
        }
        int GetMax() //retira o valor maior da raiz (root)
        {
            return arr[0];
        }

        void InsereValor(int k) //funcao para inserir valores e realocalos caso estejam na ordem errada
        {
            if(tamanhoHeap == capacidadeHeap)
            {
                cout<<"\nOverflow: Heap cheia";
                return;
            }
            tamanhoHeap++; //insere o valor no fim da MaxHeap
            int i = tamanhoHeap-1;
            arr[i] = k;

            while (i != 0 && arr[pai(i)]< arr[i]) // realoca para a ordem certa
            {
                troca(arr[i], arr[pai(i)]);
                i = pai(i);
            }

        }

    void MaxHeapify(int i) //reorganiza a heap se algum valor for retirado
    {
        int e = esq(i);
        int d = dir(i);
        int maior = i;
        if(e < tamanhoHeap && arr[e] > arr[maior])
            maior = e;
        if(d < tamanhoHeap && arr[d] > arr[maior])
            maior = d;
        if(maior != i)
        {
            troca(arr[i], arr[maior]); 
            //troca(&arr[i], &arr[maior]);
            MaxHeapify(maior);
        }
    }

    int ExtractMax () //retira o valor mais alto (raiz) da heap
    {
        if(tamanhoHeap<=0)
            return INT_MAX;
        if(tamanhoHeap==1)
        {
            tamanhoHeap--;
            return arr[0];
        }
        int raiz = arr[0];
        arr[0] = arr[tamanhoHeap-1];
        tamanhoHeap--;
        MaxHeapify(0);

        return raiz;
    }

    void DiminuiValor(int i, int novo)
    {
        arr[i] = novo;
        while(i != 0 && arr[pai(i)] > arr[i])
        {
            troca(arr[i], arr[pai(i)]);
            i = pai(i);
        }
    }

    void DeletaValor (int i)
    {
        DiminuiValor(i, INT_MAX);
        ExtractMax();
    }

};

int main()
{
    int s;
    s = 1000; //tamanho da heap
    MaxHeap obj(s); //cria objeto MaxHeap

    int opt, val;
    do
    {
        cout<<"Escolha uma operacao, "
        <<"Digite 0 para sair"<<endl;
        cout<<"1 - Insere 500 valores/keys/nos"<<endl;
        cout<<"2 - Buscar key/no"<<endl;
        cout<<"3 - Excluir key/no"<<endl;
        cout<<"4 - GetMax (maior valor da Heap)"<<endl;
        cout<<"5 - ExtractMax (retira o maior valor da Heap)"<<endl;
        cout<<"6 - Altura da Heap"<<endl;
        cout<<"7 - Imprime os valores da Heap"<<endl;
        cout<<"0 - Sair"<<endl;

        cin>>opt;
        switch(opt)
        {
            case 1:
                cout<<"Valores sendo inseridos: ";
                
                for (int i = 0; i < 500; i++) //inserindo valores aleatorios
                {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> dist(1,10000);
                    val = dist(gen);
                    obj.InsereValor(val);

                }
                cout<<endl;
                break;
            case 2:
                cout<<"Valor a ser buscado: ";
                cin>>val; 
                obj.BuscaLinear(val);
                cout<<endl;
                break;
            case 3:
                cout<<"Insira o index a ser excluido da Heap: ";
                cin>>val; 
                obj.DeletaValor(val);
                cout<<endl;
                break;
            case 4:
                cout<<"Valor MAX da Heap: ";
                cout<<obj.GetMax()<<endl;
                cout<<endl;
                break;
            case 5:
                cout<<"Valor MAX da Heap extraido: ";
                cout<<obj.ExtractMax()<<endl;
                cout<<endl;
                break;
            case 6:
                cout<<"Altura da Heap: ";
                cout<<obj.altura()<<endl;
                cout<<endl;
                break;
            case 7:
                cout<<"Valores da Heap: "<<endl;
                obj.PrintArray();
                cout<<endl;
                break;
            case 0:
                break;
            default:
                cout<<"Insira uma opcao valida"<<endl;
        }
    }while(opt != 0);
}
