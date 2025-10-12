Esse código é a implementação baremetal
 Abra o Visual Code, ou qualquer outro IDE com suporte ao RTOS Zephyr, importe o código, de upload e observe que os LEDs azul e verde estarão piscando simultaneamente, porém com delays diferentes, um com 350ms e outro com 1000ms
# PSI-Microcontroladores2-Aula01

Atividade prática inicial da aula 1 da disciplina Microcontroladores 2 (PSI).

Registre sua evolução utilizando os checklists abaixo por meio de commits com mensagens descritivas:

### Setup (individual)
- [x] Possuo VSCode instalado
- [x] Possuo MCUXpresso instalado
- [x] Possuo PlatformIO instalado
- [x] Possuo cabo USB compatível com Placa Freedom
- [x] Possuo Placa Freedom operacional
- [x] Possuo Zephyr atualizado para versão 4.2

Materiais para consulta: https://frdm-kl25z-com-zephyr-rtos.super.site/instalao, https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/1-exemplo-pisca-led-rtos/atualizao-para-o-zephyr-42

### Atividade Baremetal (implementação individual, validação em dupla)
- [x] Crie uma branch chamada baremetal
- [x] Compile e execute o exemplo de piscar led baremetal na placa Freedom com o Zephyr versão 4.2 (vide [https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/2-pisca-led-simples](https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/1-exemplo-pisca-led-rtos/atualizao-para-o-zephyr-42)). Dica: Utilize por enquanto somente o led da placa
- [x] Faça alterações no código para controlar dois leds: um led deve piscar a cada segundo, e o segundo led deve piscar a cada meio segundo
- [x] Desafio: tente fazer com que o primeiro led pisque a cada segundo, e o segundo led pisque a cada 350 ms
- [x] Crie um planejamento de testes para verificação do correto funcionamento, detalhando quais são os resultados esperados
- [x] Abra uma Pull Request
- [x] Seu par irá avaliar a Pull Request: adicionar sugestões em issues ou na discussão do PR (ATENÇÃO: o par deve tentar executar os testes propostos, e mesmo em caso de tudo funcionar, registrar em comentários como a validação foi realizada)
- [x] Após as pendências serem resolvidas, seu par irá validar as melhorias e aceitar a PR

