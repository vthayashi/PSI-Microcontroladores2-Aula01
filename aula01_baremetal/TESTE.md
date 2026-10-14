# Planejamento de Testes: Pisca LEDs (FRDM-KL25Z)

## Definições
- "Piscar a cada X ms" = o LED **inverte o estado** a cada X ms
  (ciclo completo aceso+apagado = 2 × X).
- LED0 = período de 1000 ms. LED1 = período de 500 ms (desafio: 350 ms).
- Tolerância de medição: ±5%.

## Pré-requisitos
- Placa FRDM-KL25Z conectada por USB
- Firmware gravado (`pio run -t upload`)
- Cronômetro (ou celular gravando vídeo em câmera lenta)

## Casos de teste

| ID | Teste | Procedimento | Resultado esperado | Resultado obtido | Status |
|----|-------|--------------|--------------------|------------------|--------|
| T1 | Compilação | Rodar `pio run` | Compila sem erros | | |
| T2 | Gravação | Rodar `pio run -t upload` | Gravação concluída, placa reconhecida | | |
| T3 | Inicialização | Após gravar, observar a placa | Os dois LEDs ligam e começam a piscar | | |
| T4 | Período LED0 | Contar 10 inversões do LED0 com cronômetro | 10 inversões em ~10 s (1 s cada) | | |
| T5 | Período LED1 | Contar 10 inversões do LED1 com cronômetro | 10 inversões em ~5 s (0,5 s cada) | | |
| T6 | Proporção | Observar os dois juntos por 10 s | LED1 inverte 2x para cada 1 inversão do LED0 | | |
| T7 | Independência | Observar por 1 minuto | Um LED não atrasa nem trava o outro | | |
| T8 | Reset | Apertar o botão reset | Comportamento reinicia igual ao T3 | | |
| T9 | Estabilidade | Deixar ligado por 5 min | Sem travar e sem deriva visível | | |
| T10 | Desafio | Trocar `PERIOD_LED1_MS` para 350, recompilar, gravar | 10 inversões do LED1 em ~3,5 s | | |

## Como validar (para o avaliador)
Registrar nos comentários da PR: quais testes executou, como mediu
(cronômetro, vídeo, analisador lógico) e o resultado de cada um.