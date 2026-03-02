# Sistema_Bancário
Desenvolvimento de um sistema financeiro de linha de comando. Implementação de lógicas e estruturas de dados para gerenciar funcionalidades completas, incluindo abertura de contas, depósitos, saques e transferências de fundos.

# 1. Organização do Projeto e Estrutura de Dados 

Para otimizar o gerenciamento das informações, foi desenvolvido um modelo centralizado denominado "Conta" (utilizando a estrutura struct). Esta unidade lógica agrupa os dados de identificação do cliente (Nome, CPF e Telefone) e os dados bancários (Número da Conta, Saldo e Agência). 

Os registros são armazenados em uma estrutura de lista estática, garantindo que o sistema possa acessar e manipular os dados de forma indexada e eficiente. 

A arquitetura do software foi projetada sob o princípio da modularização. Cada funcionalidade do sistema (saque, depósito, abertura de conta) foi isolada em funções específicas. Para assegurar a integridade e a atualização direta dos dados na memória, utilizou-se a passagem por referência (ponteiros), evitando a criação de cópias desnecessárias e otimizando o desempenho do programa principal. 

 

# 2. Validações e Regras de Negócio 

O sistema conta com um conjunto de verificações de segurança para garantir a consistência das operações: 

Prevenção de Duplicidade de CPF: Antes da finalização de um novo cadastro, o sistema realiza uma varredura completa na lista de contas. Caso o CPF informado já esteja vinculado a uma conta ativa, a operação de abertura é automaticamente bloqueada. 

Verificação de Status da Conta: Todas as operações financeiras (saques e depósitos) são condicionadas ao status da conta. O sistema impede qualquer movimentação em contas classificadas como encerradas. 

Protocolo de Encerramento: A rescisão contratual de uma conta exige que o saldo seja exatamente R$ 0,00. O sistema restringe o encerramento caso haja saldo remanescente, instruindo o usuário a realizar o saque total previamente. 

Consistência Financeira: Foram implementadas travas lógicas que impedem saques superiores ao saldo disponível e bloqueiam a inserção de valores negativos em operações de depósito. 
