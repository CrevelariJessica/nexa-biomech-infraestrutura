# Comparação Técnica e Decisão de Arquitetura — NEXA Biomech

Este documento atende à Etapa 6 de Arquitetura e Organização de Computadores, apresentando a análise comparativa entre duas alternativas técnicas para o perfil de estação de trabalho mais crítico da empresa (`PERFIL-ENG`) e duas alternativas para o servidor principal (`SRV-NEXA-01`), avaliando desempenho, compatibilidade, custo, consumo, garantia, manutenção e expansão.

---

## 1. Comparação para Perfil Crítico: Workstation Engenharia CAD/3D (`PERFIL-ENG`)

O perfil `PERFIL-ENG` atende os **8 engenheiros mecânicos e designers** do 2º andar, responsáveis pelo desenvolvimento de próteses robóticas em SolidWorks, AutoCAD e simulações estruturais em ANSYS.

| Critério de Avaliação | Opção A (Escolhida): Workstation Montada sob Medida | Opção B: Dell Precision 3680 Tower (Pronta de Fábrica) |
| :--- | :--- | :--- |
| **Configuração Base** | Intel Core i7-14700F (20 núcleos), ASUS TUF B760M-Plus WiFi II, 64 GB DDR5, SSD NVMe 1 TB, RTX 4060 8 GB, Fonte 750W Gold + Monitor Dell U2725QE 27" 4K | Intel Core i7-14700, Placa-mãe proprietária Dell, 32 GB DDR5, SSD NVMe 512 GB, RTX 4060 8 GB, Fonte 500W Platinum + Monitor Dell U2725QE 27" 4K |
| **Desempenho (CAD/3D)** | **Superior:** 20 núcleos (8 P-cores + 12 E-cores) e **64 GB DDR5** garantem fluidez em montagens complexas e simulações simultâneas sem paginação em disco. | **Adequado:** Mesmo processador, porém os 32 GB de RAM limitam simulações de elementos finitos mais pesadas. |
| **Compatibilidade** | **Total:** Padrão aberto ATX/Micro-ATX e LGA 1700, permitindo uso de placas-mãe, memórias e fontes padrão de mercado, além de GPU com Drivers NVIDIA Studio. | **Total:** Equipamento homologado de fábrica, porém com placa-mãe, gabinete e fonte em formato proprietário Dell. |
| **Custo Unitário (8 un.)** | **R$ 19.477,78** (Total lote: **R$ 155.822,24**) | **R$ 23.950,00** (Total lote: **R$ 191.600,00**) |
| **Consumo e Térmica** | Fonte **750W 80 Plus Gold** + Water Cooler 240 mm + Gabinete Corsair 4000D Airflow (excelente dissipação e baixa temperatura sob carga contínua). | Fonte 500W Platinum + Cooler a ar compacto em chassi menor (maior aquecimento e ruído em renderizações longas). |
| **Garantia e Manutenção** | Garantia individual por componente (3 a 10 anos conforme fabricante) com reposição imediata de peças padrão no varejo nacional. | Garantia corporativa on-site de 3 anos, porém depende exclusivamente de peças proprietárias da Dell após o vencimento. |
| **Expansão Futura** | **Alta:** 2 slots DDR5 livres (até 192 GB), 1 slot M.2 NVMe adicional livre e gabinete amplo para GPUs maiores. | **Limitada:** Restrita pelo espaço interno do gabinete compacto e pela capacidade da fonte proprietária de 500W. |

### Decisão e Justificativa (`PERFIL-ENG`)
Optou-se pela **Opção A (Workstation Montada sob Medida)**. Além de gerar uma economia direta de **R$ 35.777,76** no lote de 8 estações (custo 18,7% menor), a Opção A entrega o **dobro de memória RAM (64 GB contra 32 GB)**, o **dobro de armazenamento NVMe (1 TB contra 512 GB)**, refrigeração líquida dedicada e total liberdade de manutenção e upgrade futuro com componentes padrão de mercado.

---

## 2. Comparação para Servidor Principal (`SRV-NEXA-01`)

O servidor `SRV-NEXA-01` opera na sala climatizada de TI (4º andar), hospedando via Hyper-V os serviços críticos da NEXA Biomech: Active Directory (AD DS), DNS, DHCP, Print Server, File Server (projetos CAD e firmwares), Backup Server, GitLab CE e Zabbix.

| Critério de Avaliação | Opção A (Escolhida): Dell PowerEdge T560 (Servidor Corporativo) | Opção B: Servidor Montado com Hardware Desktop (Core i9) |
| :--- | :--- | :--- |
| **Configuração Base** | Intel Xeon Silver 4410Y (12 núcleos / 24 threads), 64 GB DDR5 **ECC RDIMM**, Controladora PERC H755 Hardware RAID, 2× SSD 960 GB + 4× HDD 4 TB SAS, Dual PSU 800W | Intel Core i9-14900K (24 núcleos), Placa-mãe Z790, 64 GB DDR5 **Non-ECC**, RAID via software/chipset, 2× SSD 1 TB + 4× HDD 4 TB SATA, Fonte única 850W |
| **Desempenho e Confiabilidade** | **Projetado para operação 24/7:** Memória **ECC** detecta e corrige erros de bits automaticamente, evitando travamentos e corrupção de projetos CAD. | **Alto clock, menor estabilidade:** Memória comum (Non-ECC) não corrige falhas silenciosas de memória em operação contínua 24/7. |
| **Compatibilidade e RAID** | Controladora dedicada **Dell PERC H755** com cache protegido por bateria e baias Hot-Swap frontais para troca de discos sem desligar o servidor. | Depende de RAID por software ou chipset da placa-mãe, sem suporte nativo a discos SAS nem troca a quente (Hot-Swap). |
| **Custo Unitário (1 un.)** | **R$ 58.900,00** | **R$ 31.500,00** |
| **Consumo e Redundância** | **Dupla fonte redundante Hot-Swap (1+1) de 800W Platinum:** se uma fonte queimar, a segunda assume instantaneamente sem queda de serviço. | **Fonte única:** qualquer falha na fonte de alimentação derruba imediatamente todos os serviços e interrompe os 60 funcionários. |
| **Garantia e Manutenção** | Garantia corporativa Dell ProSupport (atendimento técnico especializado e reposição crítica) + gerenciamento remoto via **iDRAC9**. | Garantia balcão fragmentada por peça e ausência de gerenciamento remoto fora de banda (out-of-band). |
| **Expansão Futura** | Suporta até 2 processadores Xeon Scalable, até 1 TB de RAM DDR5 ECC e múltiplas baias de armazenamento corporativo. | Limitado a 1 processador desktop e máximo de 192 GB de RAM sem suporte ECC. |

### Decisão e Justificativa (`SRV-NEXA-01`)
Optou-se pela **Opção A (Dell PowerEdge T560)**. Embora o investimento inicial seja superior ao de uma máquina desktop adaptada, o servidor concentra a autenticação, os repositórios de código e os modelos 3D de toda a empresa. A presença de **memória ECC**, **controladora RAID por hardware (PERC H755)**, **fontes redundantes Hot-Swap (1+1)** e **gerenciamento remoto iDRAC9** elimina pontos únicos de falha e assegura continuidade operacional 24/7.