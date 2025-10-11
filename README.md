# PSI-Microcontroladores2-Aula01

Atividade prática inicial da aula 1 da disciplina Microcontroladores 2 (PSI).

### Atividade Baremetal (implementação individual, validação em dupla)
- [ ] Crie uma branch chamada baremetal
- [ ] Compile e execute o exemplo de piscar led baremetal na placa Freedom com o Zephyr versão 4.2 (vide [https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/2-pisca-led-simples](https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/1-exemplo-pisca-led-rtos/atualizao-para-o-zephyr-42)). Dica: Utilize por enquanto somente o led da placa
- [ ] Faça alterações no código para controlar dois leds: um led deve piscar a cada segundo, e o segundo led deve piscar a cada meio segundo
- [ ] Desafio: tente fazer com que o primeiro led pisque a cada segundo, e o segundo led pisque a cada 350 ms
- [ ] Crie um planejamento de testes para verificação do correto funcionamento, detalhando quais são os resultados esperados
- [ ] Abra uma Pull Request
- [ ] Seu par irá avaliar a Pull Request: adicionar sugestões em issues ou na discussão do PR (ATENÇÃO: o par deve tentar executar os testes propostos, e mesmo em caso de tudo funcionar, registrar em comentários como a validação foi realizada)
- [ ] Após as pendências serem resolvidas, seu par irá validar as melhorias e aceitar a PR

### Atividade Threads (implementação individual, validação em dupla)
- Objetivo do programa: 
    Fazer o led vermelho piscar a cada 350ms e o verde a cada 1s.
  
- Descricao do codigo:
    O codigo funciona por meio de um contador e um loop infinito, desencadeado a cada 50ms. A cada ciclo, se incrementa o contador. Quando o resto da divisao do contador por 7 e' igual a 0 (counter%7 == 0), acionamos o led vermelho, e quando o resto da divisao do contador por 20 e' 0, acionamos o verde. Quando o contador chega em 139, resetamos o seu valor para 0 ao inves de aumentar por 1.
