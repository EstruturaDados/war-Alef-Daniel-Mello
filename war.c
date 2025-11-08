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

#define Territorio_Max 5
int Territorio_Atual = 0;
#define Nome_Max 50
#define Cor_Max 20
#define Tropa_Max 20
int Opcao;
int Vitorias = 0;

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

int VerificarMissões(int Verdes,int Vitorias){

        struct Territorio Terra[Territorio_Max];
        printf("\nVerificando missões...\n");
        printf("Missão 1 - Destruir todos territórios verdes.\n");
        printf("Missão 2 - Conseguir 3 vitórias.\n");

    if(Vitorias >= 3){
        printf("\nMissão : Conseguir 3 vitórias - Concluida\n");

    }
    else{
                printf("\nMissão : Conseguir 3 vitórias - Incompleta\n");

    }
    if (Verdes == 0 ){
        printf("\nMissão : Destruir todos territórios verdes - Concluida\n");
    }
    else{
        printf("\nMissão : Destruir todos territórios verdes - Incompleta\n");
    }
}

// --- Função Principal (main) ----------------------------
int main() {

    struct Territorio *Terra;

    int (*Atacar)() = AtacarTerritorio;
    int (*Missão)(int,int) = VerificarMissões;

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
       Vitorias++;
       }
       // Defensor venceu ---------------
       else if (Vencedor == 1)
       {
        printf("\n\n=== O vencedor é o território : %d! ===\n",Defensor);
       printf("Reduzindo 1 tropa do perdedor...\n\n");
       Terra[Atacante-1].Tropas--;
       Vitorias++;

       }
       // Empate -------------------------
       else
       {
        printf("\n\n=== Houve um Empate! ===\n");
        printf("Vitória pro atacante, Reduzindo 1 tropa do perdedor...\n\n");
       Terra[Defensor-1].Tropas--;
              Vitorias++;

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
        int TerritoriosVerdes = 0;

      for (int i = 0; i < Territorio_Max;i++){

        if(Terra[i].Cor == "Verde"){
            TerritoriosVerdes++;
        }
        
    
    }
      VerificarMissões(TerritoriosVerdes,Vitorias);
      break;

    case 0:
        break;

    }
    } while (Opcao != 0);
    
    free(Terra);
    free(Atacar);
    return 0;
}
