# Plano de Testes – Atividade Baremetal (Pisca LED com dois LEDs)

**Placa:** FRDM-KL25Z
**Framework:** Zephyr 4.2 (baremetal, loop principal com `k_msleep`)
**Autor:** _(seu nome)_
**Par avaliador:** _(nome do colega)_

---

## 1. Objetivo

Verificar se o firmware controla dois LEDs da placa com os tempos especificados:

- **Versão base:** LED A alterna a cada **1000 ms** e LED B alterna a cada **500 ms**.
- **Versão desafio:** LED A alterna a cada **1000 ms** e LED B alterna a cada **350 ms**.

> **Interpretação adotada:** "piscar a cada X ms" significa **trocar de estado (ligado/desligado) a cada X ms**. Portanto, o ciclo completo (ligado + desligado) dura 2 × X.
> _(Se o professor indicar outra interpretação, ajustar os valores esperados abaixo.)_

## 2. Pré-requisitos

- [ ] Placa FRDM-KL25Z operacional e conectada por cabo USB
- [ ] Zephyr 4.2 instalado e projeto compilando sem erros
- [ ] Firmware gravado na placa
- [ ] Cronômetro (celular) ou câmera para gravar vídeo
- [ ] LEDs utilizados: LED A = `led0` e LED B = `led1` (conferir no `.dts` da placa)

## 3. Ambiente de teste

| Item | Valor |
|---|---|
| Placa | FRDM-KL25Z |
| Versão do Zephyr | 4.2 |
| Ferramenta de build | PlatformIO / west _(escolher)_ |
| Branch testada | `baremetal` |
| Commit testado | _(hash do commit)_ |

## 4. Casos de teste

### 4.1 Versão base (1 s e 500 ms)

| ID | Procedimento | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|
| T01 | Compilar o projeto | Compilação sem erros e sem warnings relevantes | | ☐ |
| T02 | Gravar o firmware e energizar a placa | Os dois LEDs começam a piscar sozinhos, sem intervenção | | ☐ |
| T03 | Cronometrar 10 trocas de estado do LED A | ≈ 10 s (tolerância ±0,5 s) | | ☐ |
| T04 | Cronometrar 10 trocas de estado do LED B | ≈ 5 s (tolerância ±0,5 s) | | ☐ |
| T05 | Observar os dois LEDs juntos por 10 s | LED B troca de estado 2 vezes para cada 1 troca do LED A | | ☐ |
| T06 | Pressionar o botão de reset | Firmware reinicia e o comportamento se repete igual | | ☐ |
| T07 | Desconectar e reconectar o USB | Comportamento idêntico ao T02 | | ☐ |
| T08 | Deixar rodando por 2 minutos | Nenhum travamento e nenhuma dessincronização visível | | ☐ |

### 4.2 Versão desafio (1 s e 350 ms)

| ID | Procedimento | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|
| T09 | Gravar a versão desafio e energizar a placa | Os dois LEDs piscam sozinhos | | ☐ |
| T10 | Cronometrar 10 trocas de estado do LED A | ≈ 10 s (±0,5 s) | | ☐ |
| T11 | Cronometrar 10 trocas de estado do LED B | ≈ 3,5 s (±0,3 s) | | ☐ |
| T12 | Observar por 7 s (mínimo múltiplo comum de 350 ms e 1000 ms é 7000 ms) | A cada 7 s os dois LEDs trocam de estado juntos (20 trocas do B e 7 do A) | | ☐ |
| T13 | Pressionar o botão de reset | Comportamento se repete igual | | ☐ |
| T14 | Deixar rodando por 2 minutos | Nenhum travamento e nenhuma dessincronização visível | | ☐ |

## 5. Como medir

1. Grave um vídeo curto (10 a 20 s) com o celular, mostrando os LEDs e um cronômetro.
2. Conte as trocas de estado em câmera lenta, se necessário.
3. Calcule o período médio: `tempo total / número de trocas`.
4. Compare com o valor esperado, respeitando a tolerância indicada.

## 6. Critérios de aceitação

- Todos os casos de teste da versão base passam (T01 a T08).
- Os casos da versão desafio passam (T09 a T14) ou o desvio é justificado e documentado.
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

- _(Anote aqui problemas encontrados, ajustes feitos e limitações, por exemplo pequena deriva de tempo por causa do `k_msleep` somado ao tempo de execução do loop.)_
