# Caso de Teste 1: Validação de Inicialização (Boot & Hardware)

- Objetivo: Garantir que o sistema inicializa os pinos sem falhas e sem travar.
- Procedimento: Conectar a placa ao PC via UART e monitorar a saída do terminal serial.
- Resultado Esperado:A mensagem "Hardware inicializado!" deve ser impressa na UART.O código deve rodar sem gerar mensagens de erro de GPIO ou travamento de pilha.

# Caso de Teste 2: Verificação Visual de Independência e Frequência 

- Objetivo: Validar o correto comportamento temporal e concorrência das duas threads.
- Procedimento: Observar os LEDs em execução contínua por no mínimo 30 segundos.
- Resultado Esperado:O LED 1 deve alternar seu estado mais rápido que o LED 0.O LED 0 pisca com um intervalo de inversão de 1000 ms.O LED 1 pisca com um intervalo de inversão de 350 ms.Nenhuma thread deve bloquear o ciclo da outra.