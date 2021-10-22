#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

bool consulta(int chave, int *tabela){
    ifstream consultar;
    consultar.open("arquivoAlunos.csv", ios::in);
    if(chave<0 || chave>999)
        return false;
    if(tabela[chave]!=-1){
        int x;
        char ig;
        string nome;
        consultar.seekg(tabela[chave] * 76);
        consultar >> x >> ig;
        getline(consultar, nome);

        cout << "\nMatricula: " << x << ", nome: " << nome << endl;
        consultar.close();
        return true;
    }
    return false;
}

bool insercao(int chave, int *tabela, int newMatricula, string newNome, int *ultimo){
    fstream inserir;
    inserir.open("arquivoAlunos.csv");
    if(chave<0 || chave>999)
        return false;
    if(tabela[chave]!=-1){
        int opcao;
        do{
            printf("Ha um aluno registrado com essa matricula, deseja substitui-lo? [1]-Sim | [2]-Nao: ");
            cin >> opcao;
            if(opcao == 2)
                return false;
        }while(opcao!=1);

        int i = newNome.size();
        if(i<70){
            for(int x=0; x<70-i; x++){
                newNome+=" ";
            }
        }

        string newChave = to_string(newMatricula);
        i = newChave.size();
        if(i<4){
            for(int x=0; x<4-i; x++){
                newChave+=" ";
            }
        }

        inserir.seekp(tabela[chave] * 76);
        inserir << newChave << ';' << newNome << endl;
        inserir.close();
        return true;
    }
    else{
        int i = newNome.size();
        if(i<70){
            for(int x=0; x<70-i; x++){
                newNome+=" ";
            }
        }

        string newChave = to_string(newMatricula);
        i = newChave.size();
        if(i<4){
            for(int x=0; x<4-i; x++){
                newChave+=" ";
            }
        }

        inserir.seekp(0, ios::end);
        inserir << newChave << ';' << newNome << endl;
        inserir.close();
        tabela[chave]=*ultimo;
        *ultimo+=1;
        return true;
    }
}

bool remocao(int chave, int *tabela){
    fstream remover;
    remover.open("arquivoAlunos.csv");
    if(chave<0 || chave>999)
        return false;
    if(tabela[chave]!=-1){
        remover.seekp(tabela[chave] * 76);
        for(int i=0; i<76; i++){
            remover << "\b";
        }
        tabela[chave] = -1;
        return true;
    }
    return false;
}

int main(){
    ifstream entrada;
    entrada.open("arquivoAlunos.csv", ios::in);

    int tabela[1000];
    fill(tabela, tabela+1000, -1);
    
    int chave, i=0;
    char ignorar;
    string nome;

    while(entrada >> chave >> ignorar){
        getline(entrada, nome);

        tabela[chave] = i;
        i++;
    }
    int ultimo = i;

    int opcao;
    do{
        printf("[0]-Finalizar | [1]-Consultar | [2]-Inserir | [3]-Remover: ");
        scanf("%d", &opcao);
        if(opcao == 0)
            break;
        
        if(opcao == 1){
            int key;
            printf("Insira a matricula que deseja consultar: ");
            scanf("%d", &key);

            if(!consulta(key, tabela)){
                printf("Matricula nao encontrada!\n");
            }
        }
        else if(opcao == 2){
            string name;
            int key;
            printf("Insira a matricula que deseja inserir: ");
            scanf("%d", &key);
            printf("Insira o nome que deseja inserir: ");
            cin.ignore();
            getline(cin, name);

            if(!insercao(key, tabela, key, name, &ultimo)){
                printf("Aluno nao foi inserido!\n");
            }
            else{
                printf("Aluno inserido com sucesso!\n");
            }
        }
        else if(opcao == 3){
            int key, op;
            printf("Insira a matricula que deseja remover: ");
            scanf("%d", &key);

            do{
                printf("Deseja realmente remover a matricula %d? [1]-Sim | [2]-Nao: ", key);
                scanf("%d", &op);
                if(op==2)
                    break;
                else{
                    if(!remocao(key, tabela)){
                        printf("Nao foi possivel remover a matricula!\n");
                    }
                    else{
                        printf("Matricula removida com sucesso!\n");
                    }
                }
            }while(op!=1);
        }
    }while(1);

    entrada.close();
    printf("\nPrograma Finalizado!\n");
}