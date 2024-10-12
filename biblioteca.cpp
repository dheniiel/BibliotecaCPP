#include <iostream>
#include <cmath>
#include <time.h>
#include <limits>
#include <cstdio>

using namespace std;

int main(){
    FILE *dadosUsuarios;
    FILE *arquivoAux;
    int i = 0;
    int codigoAlteracao;
    
    string continuar;

    struct emprestimo {
        int dataEmprestimo, dataDevolucao;
        char usuario[150];
    } emprestimoLivro;
    struct livro {
        int codigoCatalogo, numeroPaginas;
        char  areaLivro[100], tituloLivro[150], autorLivro[150], editoraLivro[150];
        struct emprestimo emprestimoLivro;
    } livrosDisponiveis;
    int opcaoMenu;

    dadosUsuarios = fopen("dados_usuarios.txt", "ab");
    if (dadosUsuarios == NULL){
        dadosUsuarios = fopen("dados_usuarios.txt", "wb");
        cout << "Erro ao abrir o arquivo";
    }
    else {
        fclose(dadosUsuarios);
    }
    arquivoAux = fopen("dados_usuarios.txt", "ab");
    if (arquivoAux == NULL){
        arquivoAux = fopen("dados_usuarios.txt", "wb");
        cout << "Erro ao abrir o arquivo";
    }
    else {
        fclose(arquivoAux);
    }
              
    cout << "Digite o qual opcao desejada: ";
    cin >> opcaoMenu; 

    // cadastro
    switch (opcaoMenu) {
        case 1: 
            while(continuar == "S"){
                cout << "Digite a codigo de catalogacao: ";
                cin >> livrosDisponiveis.codigoCatalogo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite a area do livro: ";
                cin.get(livrosDisponiveis.areaLivro, 99);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite o titulo do livro: ";
                cin.get(livrosDisponiveis.tituloLivro, 150);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite os autores do livro: ";
                cin.get(livrosDisponiveis.autorLivro, 150);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite a editora do livro: ";
                cin.get(livrosDisponiveis.editoraLivro, 150);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Digite o numero de paginas do livro: ";
                cin >> livrosDisponiveis.numeroPaginas; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                fopen("dados_usuarios.txt", "ab+");
                if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosUsuarios) == 1){
                    cout << "Registro gravado com sucesso";
                    cin.get();
                }
                else {
                    cout << "Erro ao gravar registro!" << endl;
                    cin.get(); 
                }
                fclose(dadosUsuarios);

                cout << "Deseja cadastrar outro livro?" << endl;
                cin >> continuar;
            }
        break;
        case 2: 
            cout << "Digite o codigo do livro a ser alterado: " << endl;
            cin >> codigoAlteracao;

    };
/*
            case 2: //emprestimo
                for (i = 0;  i < 10; i++) {
                    cout << "Digite o código do livro: ";
                    cin >> livrosDisponiveis.codigoCatalogo;    
                    
                    if (livrosDisponiveis.codigoCatalogo == ){
                        
                    }

                    cout << "Digite a data que deseja pegar o livro emprestado: ";
                    // getline (cin, livrosDisponiveis.emprestimoLivro.dataEmprestimo);

                    cout << "Digite seu nome de usuario:";
                    cin >> livrosDisponiveis.emprestimoLivro.usuario;
                        
                    // devolucao
                    cout << "Digite o codigo do livro a ser devolvido: ";
                    cin >> livrosDisponiveis.codigoCatalogo;

                    livrosDisponiveis.emprestimoLivro.dataEmprestimo = 0;
                    livrosDisponiveis.emprestimoLivro.dataDevolucao = 0;
                };*/
}
    
