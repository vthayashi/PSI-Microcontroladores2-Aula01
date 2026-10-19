# Plano de Testes - Pisca LED Threads

## Ambiente de Teste
- **Placa:** FRDM-KL25Z
- **Framework:** Zephyr RTOS (via PlatformIO)
- **Abordagem:** Threads

## Objetivo
Verificar se o sistema operacional em tempo real (RTOS) consegue gerenciar duas tarefas simultâneas (piscar LEDs) de forma independente e sem bloqueios na execução.

## Casos de Teste

### Teste 1: Validação da Thread 1 (1000ms)
- **Ação:** Observar o LED principal (LED0 / Vermelho).
- [ ] **Resultado Esperado:** O LED deve alternar seu estado (ligado/desligado) exatamente a cada 1 segundo (1000 ms).

### Teste 2: Validação da Thread 2 (350ms - Desafio)
- **Ação:** Observar o segundo LED (LED1 / Verde).
- [ ] **Resultado Esperado:** O LED deve alternar seu estado de forma notavelmente mais rápida, a cada 350 ms.

### Teste 3: Validação de Concorrência (Não-bloqueio)
- **Ação:** Observar o comportamento conjunto de ambos os LEDs por pelo menos 10 segundos.
- [ ] **Resultado Esperado:** Os LEDs devem piscar de forma totalmente independente (assíncrona). Um LED não deve atrasar, pausar ou interferir no ritmo do outro, comprovando que o *Scheduler* do RTOS está alternando o contexto das threads corretamente.