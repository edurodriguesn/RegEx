# Códigos em C para Teoria da Computação

O `GeradorRegex.c` busca uma expressão regular qualquer no arquivo `entrada.txt` e imprime na tela as ocorrências, similar ao grep do Linux.
O `ComparadorRegex.c` compara o conteúdo de `entrada.txt` com uma expressão regular passada como parâmetro na execução do código.

- Uma expressão regular é um padrão ao qual o mecanismo de expressões regulares tenta corresponder no texto de entrada.
- grep: procura por padrões especificados pelo usuário dentro de arquivos de texto. Em outras palavras, você pode pesquisar por palavras ou padrões e a linha ou linhas que serão exibidas.

## Como executar
- **Caso esteja no sistema Windows é necessário executar o seguinte passo:**
1. **Baixe o MinGW**: Vá para o [site oficial do MinGW](http://www.mingw.org/), baixe e execute o instalador.

2. **Adicione o MinGW ao Path**:
   - Adicione o diretório `bin` do MinGW ao PATH do sistema:
     - Abra o Painel de Controle > Sistema > Configurações avançadas do sistema > Variáveis de ambiente.
     - Na seção "Variáveis do sistema", encontre a variável "Path" e clique em "Editar".
     - Adicione o caminho para o diretório `bin` do MinGW (por exemplo, `C:\MinGW\bin`).

- Após isso abra o terminal, caminhe até a pasta do arquivo e execute os seguintes comandos:
1. **Compilação do código**
```bash
gcc -o GeradorRegex GeradorRegex.c
```
- No Windows deve ser adicionado .exe ao nome do programa após o "-o"

2. **Execução do programa compilado**

No Linux:
```bash
./GeradorRegex
```
No Windows:
```bash
GeradorRegex.exe
```

Para executar o `ComparadorRegex.c` corretamente deve-se adicionar uma expressão regular como parâmetro na execução do programa, após ter compilado o código:  
Exemplo:
```bash
./ComparadorRegex 01*
```


