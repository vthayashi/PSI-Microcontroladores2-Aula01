# PSI-Microcontroladores2-Aula01

Esse código é a implementação SEM threads.

### Como testar

1) Abra o Visual Code, ou qualquer outro IDE com suporte ao RTOS Zephyr
2) Importe o código desejado (com thread ou sem thread)
3) Faça a build para a sua placa-alvo (em meu caso, KL25Z)
4) Seja feliz :)


### Resultados observados até então:

Sem threads A coisa fica muito difícil. Sincronizar as tarefas é uma verdadeira tortura, portanto, simplesmente desisti.

Com threads MUITO mais fácil. As coisas funcionam em um sincronismo invejável, e é muito fácil alterar o comportamento do sistema, como por exemplo editar os períodos dos LEDs.

Threads FTW.

DISCLAIMER: NÃO SOU RESPONSÁVEL POR NENHUM EVENTO DE EXPLOSÃO TERMONUCLEAR INESPERADA PROVOCADA POR ESTE CÓDIGO. USE COM RESPONSABILIDADE, EVITE CATÁSTROFES TERMONUCLEARES.
