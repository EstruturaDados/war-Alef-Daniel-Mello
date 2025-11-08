// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================


// Bibliotecas
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

#define Territorio_Max 5
int Territorio_Atual = 0;
#define Nome_Max 50
#define Cor_Max 20
#define Tropa_Max 20
int Opcao;
// --- Estrutura de Dados --- 
struct Territorio{

   char Nome[Nome_Max];
   char Cor[Cor_Max];
   int Tropas;

};
    struct Territorio Terra[Territorio_Max];

// --- Protótipos das Funções ---
void LimparBuffer(){
    int c;
    while ((c = getchar()) !='\n' && c != EOF);
}

void Cadastrar()
{
    
    if(Territorio_Atual < Territorio_Max)
    {
    printf("\n\n=======================================\n");
    printf("Cadastro de território\n");
    printf("=======================================\n");
    // Cadastrar Nome
    printf("\nDigite o nome do território %d :\n",Territorio_Atual+1);
    fgets(Terra[Territorio_Atual].Nome,Nome_Max,stdin);  
    // Cadastrar Cor
    printf("\nDigite a cor do território %d :\n",Territorio_Atual+1);
    fgets(Terra[Territorio_Atual].Cor,Cor_Max,stdin);  
    // Cadastrar Tropas
    printf("\nDigite a quantidade de tropas do território %d :\n",Territorio_Atual+1);
    scanf("%d",&Terra[Territorio_Atual].Tropas);  
    LimparBuffer();
    Territorio_Atual++;
    printf("\n\nContinuar cadastrando?\n");
    printf("1 - Sim  /  2 - Não\n");
    int resposta = 0;
    scanf("%d",&resposta);
    LimparBuffer();
    switch (resposta)
    {
    case 1:
        Cadastrar();
    default:
        Menu();
    }
    Menu();
    }
    else{
        printf("\nNúmero máximo de territórios atingidos, retornando ao Menu\n");
        Menu();
    }
}

void Exibir(){
    
    
    printf("\n\n=======================================\n");
    printf("Exibição de territórios\n");
    printf("=======================================\n");
    if(Territorio_Atual == 0){
        printf("Não há territórios cadastrados");
        Menu();
    }
    else{
        for (int i = 0; i < Territorio_Atual; i++)
        {
             printf("%d -------------------------------------\n", i+1);
             printf("Território %d :\n", i+1);
             printf("Nome : %s",Terra[i].Nome);
             printf("Cor : %s",Terra[i].Cor);
             printf("Quantidade de tropas : %d\n",Terra[i].Tropas);
             printf("-------------------------------------\n\n");


        }
        Menu();
    }
}

void Menu(){
    Opcao = 0;
    printf("========================================\n");
    printf("         Desafio War - Novato\n");
    printf("========================================\n");
    printf("---- Quantidade de Territorios : %d ----\n", Territorio_Atual);
    printf("========================================\n");

    printf("Selecione uma opção :\n");
    printf("1 - Cadastrar territórios\n");
    printf("2 - Exibir territórios\n");
    printf("0 - Sair\n");

    scanf("%d",&Opcao);
    LimparBuffer();
    switch (Opcao)
    {
    case 1:
        Cadastrar();
    case 2:
        Exibir();
    case 0:
        printf("\nPrograma encerrado\n");
        break;
    }
}
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    Menu();

    

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
