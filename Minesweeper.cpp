#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class CampoMinado
{
    public:
        bool TemBomba(int linha,int coluna);
        bool TemBombaPerto(int linha,int coluna);
        int  ContaBomba(int linha, int coluna);
        void MostrarTabuleiro();
        void Inicializar();
        void AtualizarTabuleiro(int linha, int coluna);
    private:
        char tabuleiro[9][9];
        int bomba[8][2];
};
void CampoMinado::Inicializar()
{
    //inicializa o tabuleiro
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            tabuleiro[i][j] = '-';
        }
    }
    //inicializa as bombas em posicoes aleatorias
    srand(time(NULL));
    int count = 0;
    while (count < 8){
        int linha = rand() % 9;
        int coluna = rand() % 9;
        if(tabuleiro[linha][coluna] != 'B'){
            tabuleiro[linha][coluna] = 'B';
            bomba[count][0] = linha;
            bomba[count][1] = coluna;
            count++;
        }
    }
}
void CampoMinado::MostrarTabuleiro()
{
    for(int i = 0; i < 9; i++){
        cout << i + 1 << " ";
        for(int j = 0; j < 9; j++){
            if(tabuleiro[i][j] == 'B'){
                cout << "[-] ";
            }else{
            cout << "[" << tabuleiro[i][j] << "] ";
            }
        }
        cout << endl;
    }
    for(int i = 0; i < 9; i++){
        cout << "   " << i + 1;
    }
    cout << endl;
} 
bool CampoMinado::TemBomba(int linha,int coluna)
{
    if(tabuleiro[linha][coluna] == 'B'){
        return true;
    }
    return false;
}
bool CampoMinado::TemBombaPerto(int linha,int coluna)
{
    // Verificando apenas nas casas adjacentes
    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < 9 && j >= 0 && j < 9 && TemBomba(i, j)) {
                return true;
            }
        }
    }
    return false;
}
int CampoMinado::ContaBomba(int linha,int coluna)
{
    int b = 0;
    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < 9 && j >= 0 && j < 9 && TemBomba(i, j)) {
                b++;
            }
        }
    }
    return b;
}
void CampoMinado::AtualizarTabuleiro(int linha, int coluna)
{
    // Se a posição selecionada tiver bomba, colocá-la no tabuleiro e sair
    if(TemBomba(linha,coluna)){                                            
        tabuleiro[linha][coluna] = 'B';
        return;
    }
    
    // Contar as bombas ao redor da posição selecionada
    int bombas = ContaBomba(linha, coluna);
    
    // Se houver bombas ao redor, mostrar o número de bombas no tabuleiro e sair
    if(bombas > 0){
        tabuleiro[linha][coluna] = '0' + bombas;
        return;
    }
    
    // Se não houver bombas ao redor, mostrar a posição vazia no tabuleiro e atualizar o tabuleiro recursivamente
    tabuleiro[linha][coluna] = ' ';
    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            if (i >= 0 && i < 9 && j >= 0 && j < 9 && tabuleiro[i][j] == '-') {
                AtualizarTabuleiro(i, j);
            }
        }
    }
}
int main()
{
    CampoMinado m;
    int row,column;
    m.Inicializar();
    string resposta;
    bool jogando = true;
    while(jogando){
        m.MostrarTabuleiro();
        cout << endl;
        do{
            cout << "Linha: ";
            cin >> row;
            row -= 1; 
            cout << endl;
        }while(row<0 || row>9 );
        do{
            cout << "Coluna: ";
            cin >> column;
            column -= 1;
            cout << endl;
        }while(column<0 || column>9 );
        if(m.TemBomba(row,column)){
            cout << "Voce perdeu!" << endl;
            cout << "Deseja reiniciar?(sim/nao)";
            cin >> resposta;
            if(resposta == "sim"){
                cout << endl;
                m.Inicializar();
            }else{
                jogando = false;
            }
        }else{
            m.AtualizarTabuleiro(row,column);
        }
    }
    
    return 0;
}