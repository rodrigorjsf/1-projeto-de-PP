# 1-projeto-de-PP   LOG

*Atualizaçao 21/02 : @rodrigorjsf

Fiz o upload do Principal.c que é onde fica Main() e também fiz o upload do HeaderCliente.h que são os cabeçalhos para usar no Modulo do Cliente.

Se tiver erros, podem corrigir.  

*Atualizaçao 22/02 : @rodrigorjsf

Adicionei os Modulos de Passagem e Voo no Principal.c e criei os Headers de Passagem e Voo.

Adicionei o ModCliente.c que e onde ficarão as funções e procedimentos relacionados ao Modulo do Cliente.

Os itens 5 e 6(do projeto) do Moludo do Cliente já foram feitos em ModCliente.c

*ATT 06/03 por Mateus Correia:

ModCliente.c, adicionado validar nome, telefone e email.

*Atualizaçao 08/03 : @rodrigorjsf

HeaderCliente.h :

Removi o TCliente * Cadastro() pois o cadastro será feito em CadastrarCliente().

Adicionei a biblioteca #include <ctype.h> 

Principal.c:

Coloquei a validação de CPF no Switch do ModuloCliente para que a verificação seja feita antes de entrar em algum dos procedimentos sem necessidade.

ModCLiente.c:

Adicionei os Procedimentos CadastrarCliente(), ExibirCliente() e RemoverCliente()

Alterei ValidaCPF() para que retorne 1 em caso de CPF válido e 0 para inválido.
