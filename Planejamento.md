# PSI-Microcontroladores2-Aula01

Planejamento do Código e quais requisitos ele deve cumprir:

## Requisitos
    - Piscar o LED Verde a cada um segundo e piscar o LED azul a cada 350ms através de um sistema Baremetal;
    - O sistema deve realizar a ativação dos LEDs de maneira que a execução de um LED não interrompa a execução do outro.


### 1 Passo - Bibliotecas e definições:
    - Incluir as bibliotecas, definir as constantes (Sleep Time) e definir os endereços dos LEDs nas contantes de LED;
    - Confirmar se o LED está definido no Device Tree para depois fazer uma struct dos LEDs verde e azul.

### 2º Passo - Main (Fora do laço infinito): 
    - Definir as variáveis inteiras ret e time (Ret servirá como variável de controle do retorno do funcionamento do LED; Time servirá como variável de um temporizador utilizado no Loop);
    - Verificar se o device está pronto;
    - Configurar os dois pinos dos dois LEDs como saída ativa;
    - Após todos os procedimentos derem certo, o sistema imprime que os LEDs estão piscando, cada um mostrando sua devida porta e seu devido pino.

### 3º Passo - Main (Dentro do Laço infinito):
    - Espera 50ms em todo começo de laço
    - Adiciona 50 a variável "time" para contar o tempo
    - Toda vez que a variável "time" for múltipla de 350, o LED azul ativa. Enquanto o LED verde ativa toda vez que a variável "time" for múltipla de 1000;
    - Toda vez que a variável "time" for igual a 7000 (Mínimo múltiplo comum de 350 e 1000), a variável "time" volta para 0 para não ter problemas de overflow.
    -  Toda vez que os LEDs piscam, é impresso no terminal o LED que está piscando e o valor armazenado na variável "time" para verificar se ela está piscando de acordo com os tempos necessários
    - Toda vez que a variável "time" volta para o 0, o programa imprime uma mensagem de reset para saber se a variável está voltando normalmente.
