 Sistema de Gerenciamento de Senhas de Atendimento Clínico

 Objetivo do Projeto

O Gerenciamento de senhas foi feito com linguagem c para organizar filas preferenciais e de acordo com a cor da pulseira do hospital ( de acordo com o caso do cliente )

O sistema permite cadastrar pacientes, identificar automaticamente suas prioridades de atendimento, gerar senhas sequenciais e controlar a ordem das chamadas, garantindo que os pacientes sejam atendidos conforme as categorias estabelecidas.

Funcionalidades

O sistema possui as seguintes funcionalidades:

Cadastro de pacientes.
Registro de gênero e idade.
Identificação de gestantes e lactantes.
Identificação de pessoas com necessidades especiais.
Identificação de pessoas com condição de obesidade.
Classificação automática dos pacientes.
Geração de senhas sequenciais.
Filas independentes por categoria.
Consulta da próxima senha.
Chamada de pacientes.
Finalização de atendimentos.
Painel textual com as senhas aguardando.
Contagem de pacientes por categoria.
 Categorias de Atendimento

O sistema trabalha com três categorias:

 Normal (N)

Pacientes que não apresentam nenhuma das condições de prioridade estabelecidas.

Exemplos:

N001
N002
N003
Preferencial (P)
Pacientes que se enquadram em pelo menos uma das seguintes condições:

Gestantes.
Lactantes.
Pessoas com necessidades especiais.
Pessoas com condição de obesidade.
Mulheres com 60 anos ou mais.
Homens com 65 anos ou mais.

Exemplos:

P001
P002
P003
 Urgente (U)

Pacientes com idade superior a 80 anos.

Exemplos:

U001
U002
U003

Ordem de prioridade:

Urgente.
Preferencial.
Normal.

A categoria urgente possui prioridade sobre as demais, seguida da preferencial e, por último, da normal.

Essas regras são exclusivamente didáticas para a atividade e não substituem avaliação clínica ou classificação médica de risco.


 Modularização do Programa

O programa foi organizado em funções com responsabilidades específicas, mantendo todo o código-fonte em um único arquivo chamado main.c.
