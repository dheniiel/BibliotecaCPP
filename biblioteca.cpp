#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>

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
              
    int codigoConsulta, opcaoMenu, pos;
    string continuar;
    char nome[150], dataE[5], dataD[5];

    struct emprestimo {
        char usuario[150], dataEmprestimo[5], dataDevolucao[5], sitacaoEmprestimo[20];
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

                    strcpy(livrosDisponiveis.emprestimoLivro.usuario, "");                    
                    strcpy(livrosDisponiveis.emprestimoLivro.dataEmprestimo, "");                    
                    strcpy(livrosDisponiveis.emprestimoLivro.dataDevolucao, "");    
                    strcpy(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel");                 

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

            // alteração
            case 2: 
                cout << "Digite o codigo do livro a ser alterado: " << endl;
                cin >> codigoConsulta;
                dadosLivros = fopen("dados_usuarios.txt","rb+");
                pos = -1;

                while(continuar == "S" || continuar == "s"){
                    while (!feof(dadosLivros)){
                        fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                        pos++;
                        if (codigoConsulta == livrosDisponiveis.codigoCatalogo){
                            fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);
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
                            break;
                        }
                        else {
                            cout << "Nao exite livros com este codigo. Deseja tentar novamente? S ou N " << endl; 
                            cin >> continuar; 
                        }
                    }
                    fclose(dadosLivros);
                    cout << "Deseja fazer outra alteracao? S ou N" << endl;
                    cin >> continuar; 
                }
                break;

            // exclusão
            case 3:
                cout << "Informe o codigo do livro que deseja excluir: " << endl << endl;
                cin >> codigoConsulta;

                arquivoAux = fopen("arquivo_aux.txt", "wb");
                dadosLivros = fopen("dados_livros.txt" , "rb");

                fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                while (!feof(dadosLivros)){
                    if (livrosDisponiveis.codigoCatalogo != codigoConsulta){
                        fwrite(&livrosDisponiveis, sizeof(struct livro), 1, arquivoAux);
                    }
                    fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                }
                fclose(arquivoAux);
                fclose(dadosLivros);
                remove("dados_livros.txt");
                rename("arquivo_aux.txt", "dados_livros.txt");

                break;

            // emprestimo
            case 4:
                cout << "Digite o codigo do livro que deseja alugar: " << endl;
                cin >> codigoConsulta;

                while(continuar == "S" || continuar == "s"){
                    dadosLivros = fopen("dados_livros.txt", "ab+");
                    fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                    pos = -1;

                    while(!feof(dadosLivros)){
                        if (strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0){
                            if (livrosDisponiveis.codigoCatalogo == codigoConsulta){
                                fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);

                                cout << "Digite seu nome de usuario: " << endl;
                                cin.get(nome, 150);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                cout << "Digite a data de hoje:  " << endl;
                                cin.get(dataE, 5);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                cout << "Digite a data que deseja devolver: " << endl;
                                cin.get(dataD, 5);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                strcpy(livrosDisponiveis.emprestimoLivro.usuario, nome);                    
                                strcpy(livrosDisponiveis.emprestimoLivro.dataEmprestimo, dataE);                    
                                strcpy(livrosDisponiveis.emprestimoLivro.dataDevolucao, dataD);    
                                strcpy(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel"); 

                                fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                            }
                        }
                    }
                }
                fclose(dadosLivros);
                break;
            case 5:
                break;

            // consulta de livros
            case 6:
                cout << "Digite o codigo do livro a ser consultado: " << endl;
                cin >> codigoConsulta;

                dadosLivros = fopen("dados_livros.txt" , "rb");
                fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);

                while(!feof(dadosLivros)){
                    if (codigoConsulta == livrosDisponiveis.codigoCatalogo){
                        cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                        cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                        cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                        cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                        cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                        cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                        cout << "Situacao emprestimo = "<< livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo << endl;
                    };
                    fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                };
                fclose (dadosLivros);
                cin.ignore();
                cin.get();
                break;

            case 7:
                break;

            // listagem de livros 
            case 8:
                cout << "Ola, bem vindo! \nestes sao os livros presentes em nosso acervo: " << endl << endl;    

                dadosLivros = fopen("dados_livros.txt" , "rb");
                fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);

                while(!feof(dadosLivros)){
                    cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                    cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                    cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                    cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                    cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                    cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                    cout << "Situacao de emprestimo = " << livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo << endl << endl << endl;
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
