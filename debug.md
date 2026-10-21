# Recursos do Debug

Temos vários recursos para o debug como, por exemplo:
- printk/Logging Module: Útil para rastrear o fluxo de execução, checar valores de variáveis em tempo de execução e identificar em qual trecho o código falhou.

- Thread Analyzer: Permite identificar gargalos de desempenho, vazamentos de memória de pilha ou threads que estão consumindo mais recursos do que o esperado.

- GDB via JTAG/SWD (West Debug): Permite pausar a execução (breakpoints), inspecionar registradores do microcontrolador, analisar a memória RAM e rodar o código passo a passo.

# Debug vs Testes

Ambas as práticas fazem parte do ciclo de garantia de qualidade de software, mas elas possuem objetivos e momentos de aplicações diferentes.

- Testes: Validar se o sistema atende aos requisitos e identificar a presença de defeitos.

- Debugging: Localizar a causa raiz de um defeito conhecido e aplicar a correção.

As duas práticas são complementares. Sem os Testes, não dá pra saber se ou quando o sistema falha. Sem o Debug, você terá dificuldade em descobrir onde e por que a falha ocorreu.