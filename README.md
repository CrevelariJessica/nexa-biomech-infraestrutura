# Projeto de Infraestrutura Computacional — NEXA Biomech

## Resumo

Planejamento completo da infraestrutura computacional para a **NEXA Biomech**, um centro privado de pesquisa e desenvolvimento de próteses robóticas de membros superiores. A estrutura adota o **Cenário B**, consistindo em um prédio único de quatro andares que abriga Administração, Engenharia/Desenvolvimento, Pesquisa/Testes e TI, totalizando 60 funcionários. A solução técnica proposta integra arquitetura de hardware, sistemas operacionais, topologia de rede segmentada e um protótipo de IoT para monitoramento térmico da sala de servidores.

## Organização do Repositório

- `01-Empresa/`: Descrição da empresa, estrutura do prédio de 4 andares, organograma, necessidades tecnológicas por departamento e distribuição dos 60 funcionários (`tabela-mestra.xlsx`).
- `02-Arquitetura/`: Levantamento por setor, perfis de hardware (Administrativo, Operacional, Engenharia/Especializado e TI), compatibilidade, dimensionamento de servidores, RAID, proteção elétrica (nobreak) e orçamento.
- `03-Sistemas-Operacionais/`: Matriz de sistemas compatíveis, catálogo de serviços de rede, diagrama de serviços, usuários, grupos de permissões, políticas de segurança, licenciamento e plano de backup.
- `04-Redes/`: Plantas baixas dos quatro andares, topologias física e lógica (Packet Tracer e Draw.io), plano de VLANs, endereçamento IPv4, dimensionamento de Wi-Fi, cabeamento e inventário de equipamentos.
- `05-IoT/`: Documentação do monitoramento térmico da sala de servidores (`descricao-do-projeto.md`), circuito com Arduino Uno (`circuito.png`), código-fonte (`codigo.ino`) e evidências dos três testes obrigatórios.
- `07-Referencias/`: Fontes de pesquisa, catálogos de fabricantes e documentações técnicas consultadas.

## Como Consultar

Inicie a leitura pela pasta `01-Empresa/` para compreender o contexto operacional e a distribuição de postos da NEXA Biomech. Em seguida, percorra as pastas de `02` a `05` na ordem numérica. Dentro de cada diretório, os arquivos principais e planilhas demonstram as decisões técnicas, quantidades e orçamentos de forma integrada.

## Links Técnicos

- **Simulação IoT no Tinkercad:** [Monitor de Temperatura da Sala de Servidores — NEXA Biomech](https://www.tinkercad.com/things/b2jdqs66WQX-medidor-de-temperatura?sharecode=c22C3FEhAkmG6nMhoAsNOZw9SZ63KbWr5BZCC4SM0os)

## Ferramentas Utilizadas

Excel, Word, Draw.io, Cisco Packet Tracer, Tinkercad e GitHub.

## Controle e Privacidade

- **Última atualização:** 22/11/2026[cite: 1, 4]
- **Privacidade:** Este repositório público cumpre rigorosamente os requisitos de avaliação técnica e não contém nomes de integrantes, RAs, e-mails ou arquivos finais identificados.
