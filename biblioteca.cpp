#include <iostream>
#include <cmath>
#include <time.h>
#include <limits>
#include <cstdio>

using namespace std;

int main(){
    FILE *dadosUsuarios;
    int i = 0;
    struct emprestimo {
        int dataEmprestimo, dataDevolucao;
        string usuario;
    } emprestimoLivro;
    struct livro {
        int codigoCatalogo, numeroPaginas;
        string areaLivro, tituloLivro, autorLivro, editoraLivro;
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
        
        cout << "Digite o qual opcao desejada: ";
        cin >> opcaoMenu; 
        // cadastro
        switch (opcaoMenu) {
            case 1: 
                for (i = 0; i < 5; i++) {
                    cout << "Digite a codigo de catalogacao: ";
                    cin >> livrosDisponiveis.codigoCatalogo;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Digite a area do livro: ";
                    cin >> livrosDisponiveis.areaLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Digite o titulo do livro: ";
                    cin >> livrosDisponiveis.tituloLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Digite os autores do livro: ";
                    getline (cin, livrosDisponiveis.autorLivro);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Digite a editora do livro: ";
                    cin >> livrosDisponiveis.editoraLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Digite o numero de paginas do livro: ";
                    cin >>livrosDisponiveis.numeroPaginas; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    fopen("dados_usuarios.txt", "ab");
                    if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosUsuarios) == 1){
                        cout << "Registro gravado com sucesso";
                        cin.get();
                    }
                    else {
                        cout << "Erro ao gravar registro!" << endl;
                        cin.get(); 
                    }
                    fclose(dadosUsuarios);
                }

            case 2: //emprestimo
                for (i = 0;  i < 10; i++) {
                    cout << "Digite o código do livro: ";
                    cin >> livrosDisponiveis.codigoCatalogo;    
                    
                    cout << "Digite a data que deseja pegar o livro emprestado: ";
                    // getline (cin, livrosDisponiveis.emprestimoLivro.dataEmprestimo);

                    cout << "Digite seu nome de usuario:";
                    cin >> livrosDisponiveis.emprestimoLivro.usuario;
                        
                    // devolucao
                    cout << "Digite o codigo do livro a ser devolvido: ";
                    cin >> livrosDisponiveis.codigoCatalogo;

                    livrosDisponiveis.emprestimoLivro.dataEmprestimo = 0;
                    livrosDisponiveis.emprestimoLivro.dataDevolucao = 0;
                };
            case 3:
            //consulta de livro

                cout << "Digite o codigo do livro: ";
                cin >> livrosDisponiveis.codigoCatalogo;

            // livros disponíveis
        }
    }
}