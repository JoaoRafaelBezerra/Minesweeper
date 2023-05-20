#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class CampoMinado
{
    public:
        bool TemBomba(int linha,int coluna);
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
        cout << i << " ";
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
        cout << "   " << i;
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
void CampoMinado::AtualizarTabuleiro(int linha, int coluna)
{
    
    if(!TemBomba(linha,coluna)){
        tabuleiro[linha][coluna] = ' ';
       }
    
   
}
int main()
{
    CampoMinado m;
    int row,column;
    m.Inicializar();
    do{
        m.MostrarTabuleiro();
        cout << "Linha: ";
        cin >> row;
        cout << endl;
        cout << "Coluna: ";
        cin >> column;
        cout << endl;
        m.AtualizarTabuleiro(row,column);
    }while(!m.TemBomba(row,column));
    return 0;
}