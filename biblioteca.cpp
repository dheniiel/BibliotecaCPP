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
    char area[100], titulo[150], autor[150], editora[150];
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
        cout << "=======================================================================" << endl; 
        cout << "Bem vindo a biblioteca do Dheniel." << endl;
        cout << "Selecione as opcoes no menu de acordo com seu interesse"<< endl;
        cout << "=======================================================================" << endl; 
        cout << "1 - CADASTRO\n";
        cout << "2 - ALTERACAO\n";
        cout << "3 - EXCLUIR LIVRO\n";
        cout << "4 - EMPRESTIMO\n";
        cout << "5 - DEVOLUCAO\n";
        cout << "6 - CONSULTA\n";
        cout << "7 - LIVROS PARA DISPONIVEIS PARA EMPRESTIMO\n";
        cout << "8 - LISTAGEM DE TODOS OS LIVROS\n";
        cout << "9 - SAIR\n";
        cout << "=======================================================================" << endl << endl; 
        cout << "Digite o qual opcao desejada: ";
        cin >> opcaoMenu; 
        cout << "\n";

        switch (opcaoMenu) {
            // cadastro
            case 1: 
                cout << "CADASTRO DE LIVRO: \n\n";
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
                cout << "ALTERACAO: \n\n";
                cout << "Digite o codigo do livro a ser alterado: " << endl;
                cin >> codigoConsulta;

                dadosLivros = fopen("dados_livros.txt" , "rb+");
                pos = -1;
                while (!feof(dadosLivros)){
                    fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                    pos++;
                    if (codigoConsulta == livrosDisponiveis.codigoCatalogo){
                        fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);
                        cout << "Digite a area do livro: ";
                        cin.get(area, 150);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Digite o titulo do livro: ";
                        cin.get(titulo, 150);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Digite os autores do livro: ";
                        cin.get(autor, 150);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Digite a editora do livro: ";
                        cin.get(editora, 150);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        cout << "Digite o numero de paginas do livro: ";
                        cin >> livrosDisponiveis.numeroPaginas; 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        strcpy(livrosDisponiveis.areaLivro, area);                    
                        strcpy(livrosDisponiveis.tituloLivro, titulo);                    
                        strcpy(livrosDisponiveis.autorLivro, autor);    
                        strcpy(livrosDisponiveis.editoraLivro, editora); 
                        
                        fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                        break;
                    }
                }
                fclose(dadosLivros);
                cin.ignore();
                cin.get();
                break;

            // exclusão
            case 3:
                cout << "EXCLUIR LIVRO: \n\n";
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
                cout << "Exclusao realizada com sucesso!";
                cin.ignore();
                cin.get();
                break;

            // emprestimo
            case 4:
                cout << "EMPRESTIMO: \n\n";
                cout << "Digite o codigo do livro que deseja alugar: " << endl;
                cin >> codigoConsulta;

                dadosLivros = fopen("dados_livros.txt", "rb+");
                pos = -1;
                while(!feof(dadosLivros)){
                    fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                    pos++;
                    if ((strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0) && (livrosDisponiveis.codigoCatalogo == codigoConsulta)){
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
                        break;
                    }
                }
        
                fclose(dadosLivros);
                cin.ignore();
                cin.get();
                break;
            
            // devolução
            case 5:
                cout << "DEVOLUCAO: \n\n";
                cout << "Digite o codigo do livro que deseja devolver: " << endl;
                cin >> codigoConsulta;

                while(continuar == "S" || continuar == "s"){
                    dadosLivros = fopen("dados_livros.txt", "ab+");
                    pos = -1;
                    while(!feof(dadosLivros)){
                        fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                        pos++;
                        if (livrosDisponiveis.codigoCatalogo == codigoConsulta){
                            if (strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel") == 0){
                                fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);

                                strcpy(livrosDisponiveis.emprestimoLivro.usuario, "");                    
                                strcpy(livrosDisponiveis.emprestimoLivro.dataEmprestimo, "");                    
                                strcpy(livrosDisponiveis.emprestimoLivro.dataDevolucao, "");    
                                strcpy(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel"); 

                                fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                            }
                        }
                    }
                }
                fclose(dadosLivros);
                cin.ignore();
                cin.get();
                break;

            // consulta de livros
            case 6:
                cout << "CONSULTA: \n\n";
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
            // listagem livros disponiveis para emprestimo
            case 7:
                cout << "LIVROS DISPONIVEIS PARA EMPRESTIMO: \n\n";
                cout << "Estes sao os livros presentes em nosso acervo disponiveis para emprestimo: " << endl << endl;    

                dadosLivros = fopen("dados_livros.txt" , "rb");
                fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);

                while(!feof(dadosLivros)){
                    if(strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0){
                        cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                        cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                        cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                        cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                        cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                        cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl << endl << endl;
                        fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                    }
                };
                fclose (dadosLivros);
                cin.ignore();
                cin.get();
                break;

            // listagem de livros 
            case 8:
                cout << "LISTAGEM DE TODOS OS LIVROS : \n\n";
                cout << "Estes sao os livros presentes em nosso acervo: " << endl << endl;    

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
