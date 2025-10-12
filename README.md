Esse código é a implementação com threads, abra o Visual Code, ou qualquer outro IDE com suporte ao RTOS Zephyr, importe o código, de upload e observe que os LEDs azul e verde estarão piscando simultaneamente, porém com delays diferentes, um com 350ms e outro com 1000ms
### Atividade Threads (implementação individual, validação em dupla)
- [x] Crie uma branch chamada threads
- [x] Compile e execute o exemplo de piscar led com threads na placa Freedom (vide [https://github.com/platformio/platform-freescalekinetis/blob/develop/examples/zephyr-blink/src/main.c e https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/1-exemplo-pisca-led-rtos](https://frdm-kl25z-com-zephyr-rtos.super.site/tutoriais/threads-zephyr-42))
- [x] Faça alterações no código para controlar dois leds: um led deve piscar a cada segundo, e o segundo led deve piscar a cada meio segundo
- [x] Desafio: tente fazer com que o primeiro led pisque a cada segundo, e o segundo led pisque a cada 350 ms
- [x] Crie um planejamento de testes para verificação do correto funcionamento, detalhando quais são os resultados esperados
- [x] Abra uma Pull Request
- [x] Seu par irá avaliar a Pull Request: adicionar sugestões em issues ou na discussão do PR (ATENÇÃO: o par deve tentar executar os testes propostos, e mesmo em caso de tudo funcionar, registrar em comentários como a validação foi realizada)
- [x] Após as pendências serem resolvidas, seu par irá validar as melhorias e aceitar a PR

### Desafio (individual)
- [] Explore recursos de debug e faça um arquivo markdown mostrando como estes recursos podem ser úteis na identificação e correção de problemas
- [] Reflita e responda em seu arquivo markdown: qual a diferença entre os recursos de debug e testes? São abordagens complementares?