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
// --- Estrutura de Dados -----------------------------
  struct Territorio{

   char Dono[Nome_Max];
   char Nome[Nome_Max];
   char Cor[Cor_Max];
   int Tropas;
   
};


// --- Protótipos das Funções ----------------------------
void LimparBuffer(){
    int c;
    while ((c = getchar()) !='\n' && c != EOF);
}

int AtacarTerritorio()
{
   int ForçaAtacante;
   int ForçaDefensor;
   
   ForçaAtacante = rand();
   printf("\n Força do atacante é : %d",ForçaAtacante);
   ForçaDefensor = rand();
   printf("\n Força do defensor é : %d",ForçaDefensor);

   if(ForçaAtacante > ForçaDefensor){
    return 0;
   }
   else if(ForçaAtacante < ForçaDefensor){
    return 1;
   }
   else if(ForçaAtacante == ForçaDefensor){
    return 3;
   }
}

void VerificarMissões(){

        struct Territorio Terrenos;
        int TerritoriosVerdes;
        printf("\nVerificando missões...\n");
    for (int i = 0; i < Territorio_Max;i++){

        if(Terra[i].Cor == "Verde"){
            TerritoriosVerdes++;
        }
        
      
    }
    if (TerritoriosVerdes == 0 ){
        printf("\nMissão : Destruir todos territórios verdes - Concluida\n");
    }
    else{
        printf("\nMissão : Destruir todos territórios verdes - Incompleta\n");
    }
}
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ----------------------------
int main() {

    struct Territorio *Terra;

    int (*Atacar)() = AtacarTerritorio;
    Terra = (struct Territorio*) calloc(Territorio_Max,sizeof(struct Territorio));
    
    if(Terra == NULL)
    {
        printf("Erro ao alocar memória");
        return 1;
    }

    do
    {

    // Menu Inicial -----------------------------------------------------------
    printf("========================================\n");
    printf("         Desafio War - Novato\n");
    printf("========================================\n");
    printf("---- Quantidade de Territorios : %d ----\n", Territorio_Atual);
    printf("========================================\n");

    printf("Selecione uma opção :\n");
    printf("1 - Cadastrar territórios\n");
    printf("2 - Exibir territórios\n");
    printf("3 - Atacar territórios\n");
    printf("4 - Verificar missões\n");
    printf("0 - Sair\n");

    scanf("%d",&Opcao);
    LimparBuffer();
   
    switch (Opcao)
    {
    // Cadastro ---------------------------------------------------------------
    case 1:
        if(Territorio_Atual < Territorio_Max)
    {
    printf("\n\n=======================================\n");
    printf("Cadastro de território\n");
    printf("=======================================\n");
    // Cadastrar Nome
    printf("\nDigite o nome do território %d :\n",Territorio_Atual+1);
    fgets(Terra[Territorio_Atual].Nome,Nome_Max,stdin); 
    strcpy(Terra[Territorio_Atual].Dono, Terra[Territorio_Atual].Nome);
  
    // Cadastrar Cor
    printf("\nDigite a cor do território %d :\n",Territorio_Atual+1);
    fgets(Terra[Territorio_Atual].Cor,Cor_Max,stdin);  
    // Cadastrar Tropas
    printf("\nDigite a quantidade de tropas do território %d :\n",Territorio_Atual+1);
    scanf("%d",&Terra[Territorio_Atual].Tropas);  
    LimparBuffer();
    Territorio_Atual++;
    }
        else{
        printf("\nNúmero máximo de territórios atingidos, retornando ao Menu\n");
                

    }
        break;
    case 2:
    // Exibição -----------------------------------------------------------------
       if(Territorio_Atual == 0){
        printf("Não há territórios cadastrados");
        
    }
       else{

        printf("\n\n=======================================\n");
    printf("Exibição de territórios\n");
    printf("=======================================\n");
        for (int i = 0; i < Territorio_Atual; i++)
        {
             printf("%d -------------------------------------\n", i+1);
             printf("Dono %s :\n", Terra[i].Dono);
             printf("Nome : %s",Terra[i].Nome);
             printf("Cor : %s",Terra[i].Cor);
             printf("Quantidade de tropas : %d\n",Terra[i].Tropas);
             printf("-------------------------------------\n\n");


        }

    }
       break;
    case 3:
    // Guerra ---------------------------------------------------------------------
      if (Territorio_Atual >= 2)
      {
        int Atacante = 0;
        int Defensor = 0;
       printf("\n\n=======================================\n");
       printf("Ataque de territórios!\n");
       printf("=======================================\n");
       printf("\nEscolha o Território atacante :\n");
       scanf("%d",&Atacante);
       LimparBuffer();
       printf("\nEscolha o Território defensor :\n");
       scanf("%d",&Defensor);
       LimparBuffer();

       int Vencedor = Atacar();
       // Atacante venceu ----------------------
       if(Vencedor == 0)
       {
       printf("\n\n=== O vencedor é o território : %d! ===\n",Atacante);
       printf("Reduzindo 1 tropa do perdedor...\n\n");
       Terra[Defensor-1].Tropas--;
       }
       // Defensor venceu ---------------
       else if (Vencedor == 1)
       {
        printf("\n\n=== O vencedor é o território : %d! ===\n",Defensor);
       printf("Reduzindo 1 tropa do perdedor...\n\n");
       Terra[Atacante-1].Tropas--;

       }
       // Empate -------------------------
       else
       {
        printf("\n\n=== Houve um Empate! ===\n");
        printf("Vitória pro atacante, Reduzindo 1 tropa do perdedor...\n\n");
       Terra[Defensor-1].Tropas--;
       }
       
       // Resultados -----------------------------------
       if(Terra[Atacante-1].Tropas == 0)
       {
        printf("\nAtacante perdeu suas tropas, agora pertence ao Defensor!\n");
        strcpy(Terra[Atacante-1].Dono, Terra[Defensor-1].Nome);
       }
       else if(Terra[Atacante-1].Tropas == 0)
       {
        printf("\nDefensor perdeu suas tropas, agora pertence ao Atacante!\n");
        strcpy(Terra[Defensor-1].Dono, Terra[Atacante-1].Nome);
       }
      } 
      else
      {
        printf("\nTerritórios insuficientes!\n");
      } 
      break;
      case 4:
      VerificarMissões();
      break;

    case 0:
        break;

    }
    } while (Opcao != 0);
    
    free(Terra);
    free(Atacar);
    return 0;
    

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
