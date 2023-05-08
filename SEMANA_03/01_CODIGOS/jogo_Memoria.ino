
#include <Arduino.h>
#define LED_BUILTIN 2

//variaveis
int game[10] = {};
int botoes[4] = {17, 5, 18, 19};
int leds[4] = {15, 16, 0, 4};
int n_rodadas = 0;
int prox = 0;
bool game_over = false;
int reset = 26;

//função que randomiza dentre 4 numeros aleatorios e incrementa a lista o numero aleatorio ao game
void partidaRandom() {
  int sorteio = random(4);
  game[n_rodadas] = sorteio;
  n_rodadas = n_rodadas + 1;
}

//seleciona um o numero da lisata game e o acende e apaga a cada rodada aleatoria
void selecionaLed() {
  for (int i = 0; i < n_rodadas; i++) {
    digitalWrite(leds[game[i]], HIGH);
    delay(500);
    digitalWrite(leds[game[i]], LOW);
    delay(100);
  }
}

//seleciona cada led e acende para um efeito visual de perda do game
void lostGame() {
  for (int i = 0; i <= 3; i++) {
  digitalWrite(leds[i], HIGH);
  delay(100);
  digitalWrite(leds[i], LOW);
 }
  
}

//Criamos uma condição onde a cada botão apertado referente a cada led, faz com que o mesmo led acende
void actionSelect() {
  int acao = 0;
  for (int i = 0; i < n_rodadas; i++) {
    bool apertaB = false;
    while (!apertaB) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == LOW) {
          acao = i;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          apertaB = true;
        }
      }
    }
//Criamos uma condição se o botão apertado não for o referente a aquele led, chama a função de perda de game, e quebra o ciclo de novas rodadas.
    if (game[prox] != acao) {
      lostGame();   
      game_over = true;
      break;
    }
    prox = prox + 1;
  }
  prox = 0;
}




void setup() {
  // Leds
   pinMode(15, OUTPUT);
   pinMode(16, OUTPUT);
   pinMode(0, OUTPUT);
   pinMode(4, OUTPUT);
  // Botões
   pinMode(17 , INPUT_PULLUP);
   pinMode(5 , INPUT_PULLUP);
   pinMode(18 , INPUT_PULLUP);
   pinMode(19 , INPUT_PULLUP);
   pinMode(26 , INPUT_PULLUP);
 //Led LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  //Acende o LED
  digitalWrite(LED_BUILTIN, HIGH);

  // Aguarda 1 segundo
  delay(300);

  // Apaga o LED
  digitalWrite(LED_BUILTIN, LOW);

  // Aguarda 1 segundo
  delay(300);
  
//Chamamos as funções existentes para um loop
  partidaRandom();
  selecionaLed();
  actionSelect();

 //logica para que, se a partida for perdida, tenha um efeito visual constante e que caso o botão de reset for apertado ele reinicia o game
  if (game_over == true) {
    while(true){
      digitalWrite(15,HIGH);
      digitalWrite(16,HIGH);
      digitalWrite(0,HIGH);
      digitalWrite(4,HIGH);
      delay(500);
      digitalWrite(15,LOW);
      digitalWrite(16,LOW);
      digitalWrite(0,LOW);
      digitalWrite(4,LOW);
      delay(500);
      if (digitalRead(reset) == LOW){
        break;
      }
    }
    game[10] = {};
    n_rodadas = 0;
    prox = 0;
    game_over = false;
  }
  delay(1000);
}
