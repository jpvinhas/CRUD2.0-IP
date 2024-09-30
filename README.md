# Sistema de Gerenciamento de Pacientes e Atendimentos

Este projeto foi desenvolvido como parte da cadeira de **Introdução à Programação**. Trata-se de um sistema para gerenciar o cadastro de pacientes e atendimentos, armazenando os dados de maneira persistente em arquivos binários. O sistema oferece um menu interativo que permite adicionar, alterar, e visualizar informações de pacientes e seus respectivos atendimentos.

## Tecnologias Utilizadas

- **C**: Linguagem de programação utilizada para implementar o sistema.
- **Manipulação de Arquivos Binários**: Os dados de pacientes e atendimentos são salvos e carregados a partir de arquivos binários (`pacientes.bin`, `atendimentos.bin`), garantindo a persistência de dados.
- **Memória Dinâmica**: O sistema utiliza `malloc` para alocação dinâmica de memória, garantindo flexibilidade ao lidar com grandes quantidades de dados.

## Funcionalidades

- **Cadastro de Pacientes**: Permite o cadastro de novos pacientes, incluindo informações como nome, idade, etc.
- **Cadastro de Atendimentos**: Permite registrar novos atendimentos para os pacientes cadastrados.
- **Edição de Dados**: É possível alterar as informações dos pacientes e dos atendimentos.
- **Alerta de Alterações Não Salvas**: O sistema informa o usuário sobre alterações não salvas antes de sair ou executar certas operações.
- **Interface de Menu**: O sistema oferece uma interface de menu textual para facilitar a interação do usuário.

## Como Instalar e Executar

### Pré-requisitos

- **Compilador GCC** ou qualquer outro compilador compatível com a linguagem C.
- Sistema operacional compatível com a execução de arquivos binários gerados pelo compilador C.
