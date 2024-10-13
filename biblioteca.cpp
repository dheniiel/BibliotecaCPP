#include <iostream>
#include <limits>
#include <cstdio>

using namespace std;

int main(){
    FILE *dadosLivros;
    FILE *arquivoAux;

    dadosLivros = fopen("dados_livros.txt", "ab");
    if (dadosLivros == NULL){
        dadosLivros = fopen("dados_livros.txt", "wb");
        cout << "Erro ao abrir o arquivo";
    }
    else {
        fclose(dadosLivros);
    }

    arquivoAux = fopen("arquivo_aux.txt", "ab");
    if (arquivoAux == NULL){
        arquivoAux = fopen("arquivo_aux.txt", "wb");
        cout << "Erro ao abrir o arquivo";
    }
    else {
        fclose(arquivoAux);
    }
              
    int codigoConsulta, opcaoMenu;
    string continuar;

    struct emprestimo {
        char usuario[150], dataEmprestimo[150], dataDevolucao[150];
    };
    struct emprestimo emprestimoLivro;
    struct livro {
        int codigoCatalogo, numeroPaginas;
        char  areaLivro[100], tituloLivro[150], autorLivro[150], editoraLivro[150];
        struct emprestimo emprestimoLivro;
    };
    struct livro livrosDisponiveis;

    do{
        cout << "Digite o qual opcao desejada: ";
        cin >> opcaoMenu; 
        switch (opcaoMenu) {
            // cadastro
            case 1: 
                cout << "Deseja cadastrar um livro? S ou N" << endl;
                cin >> continuar;

                while(continuar == "S" || continuar == "s"){
                    dadosLivros = fopen("dados_livros.txt", "ab+");
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

                    
                    if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros) == 1){
                        cout << "Registro gravado com sucesso";
                        cin.get();
                    }
                    else {
                        cout << "Erro ao gravar registro!" << endl;
                        cin.get(); 
                    }
                    fclose(dadosLivros);

                    cout << "Deseja cadastrar outro livro?" << endl;
                    cin >> continuar;
                }
                break;
            // alteracao
            case 2: 
                cout << "Digite o codigo do livro a ser alterado: " << endl;
                cin >> codigoConsulta;

                while(!feof(dadosLivros)){
                    while (continuar == "S" || continuar == "s")
                        dadosLivros = fopen("dados_usuarios.txt" , "ab+");
                        if (codigoConsulta == livrosDisponiveis.codigoCatalogo){
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

                            if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros) == 1){
                                cout << "Registro atualizado com sucesso";
                                cin.get();
                            }
                            else {
                                cout << "Erro ao atualizar registro!" << endl;
                                cin.get(); 
                            }
                            fclose(dadosLivros);

                            cout << "Deseja fazer outra alteracao? S ou N" << endl;
                            cin >> continuar; 
                        }
                        else {
                            cout << "Nao exite livros com este codigo. Deseja tentar novamente? S ou N " << endl; 
                            cin >> continuar; 
                        }
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                cout << "Digite o codigo do livro a ser consultado: " << endl;
                cin >> codigoConsulta;

                while(continuar == "S" || continuar == "s")
                    while(!feof(dadosLivros)){
                        if (codigoConsulta == livrosDisponiveis.codigoCatalogo){
                            dadosLivros = fopen("dados_livros.txt" , "rb");
                            fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                            cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                            cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                            cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                            cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                            cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                            cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                            cout << "Situacao emprestimo "<< livrosDisponiveis.emprestimoLivro.usuario << endl;
                        };
                        fclose (dadosLivros);
                        cin.ignore();
                        cin.get();
                        };
                break;
            case 7:
                break;
            case 8:
                dadosLivros = fopen("dados_livros.txt" , "rb");
                fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                while(!feof(dadosLivros)){
                    cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                    cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                    cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                    cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                    cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                    cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl << endl;
                    fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                };
                fclose (dadosLivros);
                cin.ignore();
                cin.get();
                break;
        };
        cout << "\e[2J" << "\e[0;0H";
    } while(opcaoMenu != 9);
}