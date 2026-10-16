# Plano de Testes – Atividade Threads (Pisca LED com dois LEDs)

**Placa:** FRDM-KL25Z
**Framework:** Zephyr 4.2 (uma thread por LED, criadas com `K_THREAD_DEFINE`)
**Autor:** Kenny Tan Mei
**Par avaliador:** Não definido ainda

---

## 1. Objetivo

Verificar se o firmware controla dois LEDs da placa, cada um por uma thread independente, com os tempos especificados:

- **Versão base:** LED A alterna a cada **1000 ms** (thread A) e LED B alterna a cada **500 ms** (thread B).
- **Versão desafio:** LED A alterna a cada **1000 ms** e LED B alterna a cada **350 ms**.

> **Interpretação adotada:** "piscar a cada X ms" significa **trocar de estado (ligado/desligado) a cada X ms**. Portanto, o ciclo completo (ligado + desligado) dura 2 × X.
> _(Se o professor indicar outra interpretação, ajustar os valores esperados abaixo.)_

## 2. Pré-requisitos

- [ ] Placa FRDM-KL25Z operacional e conectada por cabo USB
- [ ] Zephyr 4.2 instalado e projeto compilando com `SUCCESS`
- [ ] Firmware gravado na placa
- [ ] Cronômetro (celular) ou câmera para gravar vídeo
- [ ] LEDs utilizados: LED A = `led0` e LED B = `led1` _(ajustar se usou outros aliases)_

## 3. Ambiente de teste

| Item | Valor |
|---|---|
| Placa | FRDM-KL25Z |
| Versão do Zephyr | 4.2 |
| Ferramenta de build | PlatformIO |
| Branch testada | `threads` |
| Commit testado | _(hash do commit)_ |

## 4. Casos de teste

### 4.1 Versão base (1 s e 500 ms)

| ID | Procedimento | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|
| T01 | Compilar o projeto | Compilação com `SUCCESS` e sem erros | | ☐ |
| T02 | Gravar o firmware e energizar a placa | As duas threads iniciam sozinhas e os dois LEDs começam a piscar sem intervenção | | ☐ |
| T03 | Cronometrar 10 trocas de estado do LED A | ≈ 10 s (tolerância ±0,5 s) | | ☐ |
| T04 | Cronometrar 10 trocas de estado do LED B | ≈ 5 s (tolerância ±0,5 s) | | ☐ |
| T05 | Observar os dois LEDs juntos por 10 s | LED B troca de estado 2 vezes para cada 1 troca do LED A | | ☐ |
| T06 | Verificar independência das threads | O ritmo de um LED não altera o ritmo do outro; os tempos de T03 e T04 se mantêm com os dois ativos | | ☐ |
| T07 | Pressionar o botão de reset | Firmware reinicia e as duas threads voltam a funcionar igual | | ☐ |
| T08 | Desconectar e reconectar o USB | Comportamento idêntico ao T02 | | ☐ |
| T09 | Deixar rodando por 2 minutos | Nenhum travamento, nenhum LED parado e nenhuma dessincronização visível | | ☐ |

### 4.2 Versão desafio (1 s e 350 ms)

| ID | Procedimento | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|
| T10 | Alterar o período da thread B para 350 ms, recompilar e gravar | Compilação com `SUCCESS` e gravação sem erros | | ☐ |
| T11 | Energizar a placa e observar | Os dois LEDs piscam sozinhos | | ☐ |
| T12 | Cronometrar 10 trocas de estado do LED A | ≈ 10 s (±0,5 s) | | ☐ |
| T13 | Cronometrar 10 trocas de estado do LED B | ≈ 3,5 s (±0,3 s) | | ☐ |
| T14 | Observar por 7 s (múltiplo comum de 350 ms e 1000 ms) | Em 7 s ocorrem 7 trocas do LED A e 20 trocas do LED B; ao fim, os dois trocam de estado juntos | | ☐ |
| T15 | Pressionar o botão de reset | Comportamento se repete igual | | ☐ |
| T16 | Deixar rodando por 2 minutos | Nenhum travamento e nenhuma dessincronização visível | | ☐ |

### 4.3 Testes específicos de threads

| ID | Procedimento | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|
| T17 | Comentar (desativar) a thread B e gravar | Só o LED A pisca a cada 1 s; o LED B permanece apagado | | ☐ |
| T18 | Comentar (desativar) a thread A e gravar | Só o LED B pisca no seu período; o LED A permanece apagado | | ☐ |
| T19 | Reativar as duas threads e gravar | Os dois LEDs voltam a piscar nos tempos corretos | | ☐ |

> Os testes T17 a T19 mostram que cada LED depende apenas da sua própria thread. Ao final, restaurar o código para a versão a ser entregue.

## 5. Como medir

1. Grave um vídeo curto (10 a 20 s) com o celular, mostrando os LEDs e um cronômetro.
2. Conte as trocas de estado em câmera lenta, se necessário.
3. Calcule o período médio: `tempo total / número de trocas`.
4. Compare com o valor esperado, respeitando a tolerância indicada.

## 6. Critérios de aceitação

- Todos os casos da versão base passam (T01 a T09).
- Os casos da versão desafio passam (T10 a T16) ou o desvio é justificado e documentado.
- Os testes específicos de threads (T17 a T19) confirmam a independência das threads.
- Os desvios de tempo ficam dentro da tolerância definida.

## 7. Registro da validação pelo par

_(Preenchido pelo colega que avalia o Pull Request)_

| Item | Registro |
|---|---|
| Data da validação | |
| Avaliador | |
| Placa / ambiente usado | |
| Testes executados | |
| Como foi medido (cronômetro, vídeo etc.) | |
| Resultado geral | ☐ Aprovado   ☐ Aprovado com ressalvas   ☐ Reprovado |
| Sugestões / issues abertas | |

## 8. Observações

- _(Anote aqui problemas encontrados, ajustes feitos e limitações. Por exemplo: pequena deriva de tempo porque `k_msleep` dorme *pelo menos* o tempo pedido e o escalonador pode atrasar o despertar da thread.)_
