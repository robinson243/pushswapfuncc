#!/bin/bash

# Testeur pour push_swap
# Usage: ./test.sh

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Fonctions
run_test() {
    echo -e "${YELLOW}Test: $1${NC}"
    eval $2
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
    else
        echo -e "${RED}✗ FAIL${NC}"
    fi
    echo
}

# 1. Compilation
echo -e "${YELLOW}1. Compilation...${NC}"
make re
if [ $? -ne 0 ]; then
    echo -e "${RED}Erreur de compilation${NC}"
    exit 1
fi
echo -e "${GREEN}Compilation réussie ✓${NC}\n"

# 2. Tests d'arguments invalides
run_test "Aucun argument" "./push_swap"
run_test "Argument vide" "./push_swap \"\""
run_test "Caractères non numériques" "./push_swap 1 2 a 3"
run_test "Doublons" "./push_swap 1 2 3 1"
run_test "Débordement INT_MAX" "./push_swap 1 2147483648 3"
run_test "Débordement INT_MIN" "./push_swap 1 -2147483649 3"

# 3. Tests valides
run_test "Déjà trié" "./push_swap 1 2 3 4 5"
run_test "Deux éléments triés" "./push_swap 1 2"
run_test "Deux éléments inversés" "./push_swap 2 1"
run_test "Trois éléments (déjà trié)" "./push_swap 1 2 3"
run_test "Trois éléments (inversé)" "./push_swap 3 2 1"
run_test "Trois éléments (cas A)" "./push_swap 1 3 2"
run_test "Trois éléments (cas B)" "./push_swap 2 1 3"
run_test "Trois éléments (cas C)" "./push_swap 2 3 1"
run_test "Cinq éléments" "./push_swap 5 4 3 2 1"
run_test "Cinq éléments aléatoires" "./push_swap 10 -5 8 0 3"

# 4. Test de performance
echo -e "${YELLOW}4. Tests de performance${NC}"
echo "100 éléments:"
./push_swap `seq 1 100 | sort -R` | wc -l
echo "500 éléments:"
./push_swap `seq 1 500 | sort -R` | wc -l

# 5. Test avec checker (si disponible)
if [ -f "checker_Mac" ]; then
    echo -e "\n${YELLOW}5. Validation avec checker${NC}"
    echo "Petite pile:"
    ./push_swap 2 1 3 | ./checker_Mac 2 1 3
    echo "Grande pile:"
    ./push_swap `seq 1 5 | sort -R` | ./checker_Mac `seq 1 5 | sort -R`
fi

echo -e "\n${GREEN}Tous les tests sont terminés ✓${NC}"