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
        void MostrarTabuleiroBomba();
        void Inicializar();
        void AtualizarTabuleiro(int linha, int coluna);
        void Marcar(int linha, int coluna);
        int marcado[9][9];
    private:
        char tabuleiro[9][9];
        int bomba[8][2];
};
void CampoMinado::Inicializar()
{
    // inicializa o tabuleiro e a matriz de marcações
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            tabuleiro[i][j] = '-';
            marcado[i][j] = 0;
        }
    }
    // inicializa as bombas em posicoes aleatorias
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
            if(marcado[i][j]){
                cout << "[F] ";
            } else if(tabuleiro[i][j] == 'B'){
                cout << "[-] ";
            } else {
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
void CampoMinado::MostrarTabuleiroBomba(){
    for(int i = 0; i < 9; i++){
        cout << i + 1 << " ";
        for(int j = 0; j < 9; j++){
            if (tabuleiro[i][j] == 'B') {
                cout << "[-] ";
            } else if (marcado[i][j]) {
                cout << "[F] ";
            } else {
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
            if (i >= 0 && i < 9 && j >= 0 && j < 9 && tabuleiro[i][j] == '-' && !marcado[i][j]) {
                AtualizarTabuleiro(i, j);
            }
        }
    }
}
void CampoMinado::Marcar(int linha, int coluna)
{
    marcado[linha][coluna] = !marcado[linha][coluna];
}

int main()
{
    CampoMinado m;
    int row,column;
    m.Inicializar();
    string resposta;
    bool jogando = true;
    do{
        m.MostrarTabuleiro();
        cout << endl;
        cout << "Linha: ";
        cin >> row;
        row -= 1; 
        cout << endl;
        cout << "Coluna: ";
        cin >> column;
        column -= 1;
        cout << endl;
        if(m.TemBomba(row,column)){
            m.MostrarTabuleiroBomba();
            cout << "Voce perdeu!" << endl;
            cout << "Deseja jogar novamente?(sim/nao): ";
            cin >> resposta;
            if(resposta == "sim"){
                m.TemBomba(row,column) == false;
                m.Inicializar();
                cout << endl;
            }
        } else if (m.marcado[row][column]) {
            cout << "A célula " << row + 1 << "," << column + 1 << " está marcada com uma bandeira." << endl;
        } else {
            m.AtualizarTabuleiro(row, column);
            cout << "Deseja marcar/desmarcar a célula com uma bandeira? (sim/nao):";
            cin >> resposta;
            if(resposta == "sim") {
                m.Marcar(row, column);
            }
            cout << endl;
        }
    } while(!m.TemBomba(row,column));
    
    return 0;
}
