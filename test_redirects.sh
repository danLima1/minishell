#!/bin/bash

# Script de teste para redirecionamentos no minishell
# Execute: bash test_redirects.sh

echo "=================================="
echo "TESTES DE REDIRECIONAMENTO"
echo "=================================="
echo ""

# Cores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

test_count=0
pass_count=0

# Função de teste
run_test() {
    test_count=$((test_count + 1))
    echo -e "${YELLOW}Teste $test_count: $1${NC}"
    echo "$2"
    echo ""
}

echo "=================================="
echo "TESTE 1: Redirecionamento de entrada (<)"
echo "=================================="
echo "Este é um teste de redirecionamento de entrada" > test_input.txt
echo "Execute no minishell:"
echo "  cat < test_input.txt"
echo "Resultado esperado: Este é um teste de redirecionamento de entrada"
echo ""
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 2: Redirecionamento de saída (>)"
echo "=================================="
echo "Execute no minishell:"
echo "  echo 'Hello World' > test_output.txt"
echo "  cat test_output.txt"
echo "Resultado esperado: Hello World"
echo ""
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 3: Redirecionamento append (>>)"
echo "=================================="
echo "Execute no minishell:"
echo "  echo 'Linha 1' > test_append.txt"
echo "  echo 'Linha 2' >> test_append.txt"
echo "  echo 'Linha 3' >> test_append.txt"
echo "  cat test_append.txt"
echo "Resultado esperado:"
echo "  Linha 1"
echo "  Linha 2"
echo "  Linha 3"
echo ""
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 4: HEREDOC (<<) - Básico"
echo "=================================="
echo "Execute no minishell:"
echo "  cat << EOF"
echo "  linha 1"
echo "  linha 2"
echo "  linha 3"
echo "  EOF"
echo ""
echo "Resultado esperado:"
echo "  linha 1"
echo "  linha 2"
echo "  linha 3"
echo ""
echo "IMPORTANTE: Verifique se o prompt é '> ' durante input"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 5: HEREDOC com variáveis"
echo "=================================="
echo "Execute no minishell:"
echo '  cat << END'
echo '  Usuario: $USER'
echo '  Path: $PATH'
echo '  END'
echo ""
echo "Resultado esperado: expansão das variáveis"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 6: HEREDOC com redirecionamento de saída"
echo "=================================="
echo "Execute no minishell:"
echo "  cat << EOF > heredoc_output.txt"
echo "  teste linha 1"
echo "  teste linha 2"
echo "  EOF"
echo "  cat heredoc_output.txt"
echo ""
echo "Resultado esperado: conteúdo gravado no arquivo"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 7: HEREDOC em pipeline"
echo "=================================="
echo "Execute no minishell:"
echo "  cat << EOF | grep 'test'"
echo "  other line"
echo "  test line"
echo "  another test"
echo "  normal line"
echo "  EOF"
echo ""
echo "Resultado esperado:"
echo "  test line"
echo "  another test"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 8: HEREDOC - EOF via Ctrl+D"
echo "=================================="
echo "Execute no minishell:"
echo "  cat << EOF"
echo "  linha 1"
echo "  [pressione Ctrl+D aqui - NÃO digite EOF]"
echo ""
echo "Resultado esperado:"
echo "  minishell: warning: here-document delimited by EOF"
echo "  linha 1"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 9: Múltiplos redirecionamentos"
echo "=================================="
echo "Execute no minishell:"
echo "  cat < test_input.txt > test_multi.txt"
echo "  cat test_multi.txt"
echo ""
echo "Resultado esperado: conteúdo copiado de um arquivo para outro"
echo "Pressione ENTER para continuar..."
read

echo "=================================="
echo "TESTE 10: HEREDOC com wc"
echo "=================================="
echo "Execute no minishell:"
echo "  wc -l << EOF"
echo "  linha 1"
echo "  linha 2"
echo "  linha 3"
echo "  linha 4"
echo "  EOF"
echo ""
echo "Resultado esperado: 4"
echo "Pressione ENTER para continuar..."
read

echo ""
echo "=================================="
echo "TESTES CONCLUÍDOS!"
echo "=================================="
echo ""
echo "Limpando arquivos de teste..."
rm -f test_input.txt test_output.txt test_append.txt heredoc_output.txt test_multi.txt
echo "Arquivos removidos."
echo ""
echo "Para verificar memory leaks, execute:"
echo "  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=suppression/rline.supp ./minishell"

