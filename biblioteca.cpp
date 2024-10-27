#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    cout << "\e[2J" << "\e[0;0H";
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

    struct emprestimo {
        char usuario[150], dataEmprestimo[6], dataDevolucao[6], sitacaoEmprestimo[20];
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";

        switch (opcaoMenu) {
            // cadastro
            case 1: 
                cout << "\e[2J" << "\e[0;0H";
                cout << "CADASTRO DE LIVRO: \n\n";

                continuar = "S";

                while(continuar == "S" || continuar == "s"){
                    dadosLivros = fopen("dados_livros.txt", "ab+");

                    cout << "\nDigite a codigo de catalogacao: ";
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
                        cout << "\nRegistro gravado com sucesso";
                        cin.get();
                        cout << "\e[2J" << "\e[0;0H";
                    }
                    else {
                        cout << "\nErro ao gravar registro!";
                        cin.get();
                        cout << "\e[2J" << "\e[0;0H";
                    }
            
                    fclose(dadosLivros);

                    cout << "\nDeseja cadastrar outro livro? S ou N: ";
                    cin >> continuar;
                }
                break;

            // alteração
            case 2: 
                cout << "\e[2J" << "\e[0;0H";
                cout << "ALTERACAO: \n\n";

                continuar = "S";

                while (continuar == "S" || continuar == "s"){    
                    dadosLivros = fopen("dados_livros.txt" , "rb+");
                    pos = -1;

                    cout << "Digite o codigo do livro: ";
                    cin >> codigoConsulta;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                                cout << "\e[2J" << "\e[0;0H";
                            }
                            else {
                                cout << "Erro ao atualizar registro!" << endl;
                                cin.get();
                                cout << "\e[2J" << "\e[0;0H";
                            }
                            break;
                        }
                    }
                    fclose(dadosLivros);

                    cout << "\nDeseja realizar mais uma alteracao? S ou N: ";
                    cin >> continuar; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cin.get();
                break;

            // exclusão
            case 3:
                cout << "\e[2J" << "\e[0;0H";
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
                cout << "\e[2J" << "\e[0;0H";
                cout << "EMPRESTIMO: \n\n";

                continuar = "S";

                while(continuar == "S" || continuar == "s"){
                    cout << "Digite o codigo do livro que deseja alugar: " << endl;
                    cin >> codigoConsulta;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    dadosLivros = fopen("dados_livros.txt", "rb+");
                    pos = -1;
                    while(!feof(dadosLivros)){
                        fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                        pos++;
                        if ((strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0) && (livrosDisponiveis.codigoCatalogo == codigoConsulta)){
                            fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);

                            cout << "Digite o nome do usuario: " << endl;
                            cin.get(livrosDisponiveis.emprestimoLivro.usuario, 150);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Digite a data de hoje:  " << endl;
                            cin.get(livrosDisponiveis.emprestimoLivro.dataEmprestimo, 6);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Digite a data de devolucao:  " << endl;
                            cin.get(livrosDisponiveis.emprestimoLivro.dataDevolucao, 6);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            strcpy(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel"); 

                            if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros) == 1){
                                cout << "\nEmprestimo realizado com sucesso!";
                                cin.get();
                                cout << "\e[2J" << "\e[0;0H";

                            }
                            else {
                                cout << "\nErro ao realizar emprestimo!" << endl;
                                cin.get();
                                cout << "\e[2J" << "\e[0;0H";
                            }
                            break;
                        }
                        if ((strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel") == 0) && (livrosDisponiveis.codigoCatalogo == codigoConsulta)){
                            cout << "Este livro esta indisponivel para emprestimo! \n";
                            cin.get();
                            cout << "\e[2J" << "\e[0;0H";
                            break;
                        }
                    }
                    fclose(dadosLivros);

                    cout << "\nDeseja realizar outro emprestimo? S ou N: ";
                    cin >> continuar; 
                }
                cin.ignore();
                cin.get();
                break;
            
            // devolução
            case 5:
                cout << "\e[2J" << "\e[0;0H";
                cout << "DEVOLUCAO: \n\n";

                continuar = "S";

                while (continuar == "S" || continuar == "s"){
                    cout << "Digite o codigo do livro que deseja devolver: " << endl;
                    cin >> codigoConsulta;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    dadosLivros = fopen("dados_livros.txt", "rb+");
                    pos = -1;
                    while(!feof(dadosLivros)){
                        fread(&livrosDisponiveis, sizeof(struct livro), 1 , dadosLivros);
                        pos++;
                        if ((livrosDisponiveis.codigoCatalogo == codigoConsulta)&& (strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel") == 0)){
                            fseek(dadosLivros, sizeof(struct livro)*pos, SEEK_SET);

                            strcpy(livrosDisponiveis.emprestimoLivro.usuario, "");                    
                            strcpy(livrosDisponiveis.emprestimoLivro.dataEmprestimo, "");                    
                            strcpy(livrosDisponiveis.emprestimoLivro.dataDevolucao, "");    
                            strcpy(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel"); 

                            if (fwrite(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros) == 1){
                                cout << "\nDevolucao realizada com sucesso";
                                cin.get();
                                cout << "\e[2J" << "\e[0;0H";

                            }
                            else {
                                cout << "\nErro ao realizar devolucao!" << endl;
                                cin.get();
                                cout << "\e[2J" << "\e[0;0H";
                            }
                            break;
                        }
                        else if(strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0){
                            cout << "\nFalha na devolucao, este livro ja estava disponivel para emprestimo!\n";
                            cin.get();
                            cout << "\e[2J" << "\e[0;0H";
                            break; 
                        }
                    }
                    fclose(dadosLivros);
                    cout << "\nDeseja realizar mais uma devolucao? S ou N: ";
                    cin >> continuar; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                cin.ignore();
                cin.get();
                break;

            // consulta de livros
            case 6:
                cout << "\e[2J" << "\e[0;0H";
                cout << "CONSULTA: \n\n";

                continuar = "S";

                while(continuar == "S" || continuar == "s"){
                    cout << "Digite o codigo do livro a ser consultado: " << endl;
                    cin >> codigoConsulta;

                    dadosLivros = fopen("dados_livros.txt" , "rb");
                    fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);

                    while(!feof(dadosLivros)){
                        if ((codigoConsulta == livrosDisponiveis.codigoCatalogo) && (strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Indisponivel") == 0)){
                            cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                            cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                            cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                            cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                            cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                            cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                            cout << "Situacao emprestimo = " << livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo << endl;
                            cout << "Emprestado para = " << livrosDisponiveis.emprestimoLivro.usuario << endl;
                            cout << "Data emprestimo = " << livrosDisponiveis.emprestimoLivro.dataEmprestimo << endl;
                            cout << "Data devolucao = " << livrosDisponiveis.emprestimoLivro.dataDevolucao << endl;

                            break;
                        }
                        else if ((codigoConsulta == livrosDisponiveis.codigoCatalogo) && (strcmp(livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo, "Disponivel") == 0)){
                            cout << "Codigo = " << livrosDisponiveis.codigoCatalogo << endl;
                            cout << "Area = "<< livrosDisponiveis.areaLivro << endl;
                            cout << "Titulo = " << livrosDisponiveis.tituloLivro << endl;
                            cout << "Autores = "<< livrosDisponiveis.autorLivro << endl;
                            cout << "Editora = " << livrosDisponiveis.editoraLivro << endl;
                            cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                            cout << "Situacao emprestimo = " << livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo << endl;
                        
                            break;
                        }
                        fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                    }
                    fclose (dadosLivros);

                    cout << "\nDeseja realizar mais uma consulta? S ou N: ";
                    cin >> continuar; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cin.get();
                break;

            // listagem livros disponiveis para emprestimo
            case 7:
                cout << "\e[2J" << "\e[0;0H";
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
                        cout << "Numero de paginas = "<< livrosDisponiveis.numeroPaginas << endl;
                        cout << "---------------------------------------------------" << endl;

                        fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                    }
                };
                fclose (dadosLivros);
                cin.ignore();
                cin.get();
                break;

            // listagem de livros 
            case 8:
                cout << "\e[2J" << "\e[0;0H";
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
                    cout << "Situacao de emprestimo = " << livrosDisponiveis.emprestimoLivro.sitacaoEmprestimo << endl;
                    cout << "---------------------------------------------------" << endl;
                    fread(&livrosDisponiveis, sizeof(struct livro), 1, dadosLivros);
                };
                fclose (dadosLivros);
                cin.ignore();
                cin.get();
                break;

            // sair
            case 9: 
                cout << "\nObrigado por usar nosso sistema!";
                cin.ignore();
                cin.get();
                break;

            //caso o usuario nao digite nada 
            default:
                cout << "\e[2J" << "\e[0;0H";
                cout<<"\nDigite uma opcao valida!";
                cin.ignore();
                cin.get();
                break;
        };
        cout << "\e[2J" << "\e[0;0H";
    } while(opcaoMenu != 9);
}