#!/bin/bash
# test_shell.sh - Compare ./hsh avec /bin/sh
# Utilise printf %b pour interpréter correctement \n et \t

HSH="${1:-./hsh}"
SH="/bin/sh"

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

pass=0
fail=0
failed_tests=()

# Normalise les messages d'erreur entre Mac sh et Ubuntu sh
normalize_err() {
    sed -E \
        -e 's|^[^:]+:|SHELL:|' \
        -e 's| line | |' \
        -e 's|: command not found$|: not found|' \
        -e 's|: [Ii]s a directory$|: is a directory|' \
        -e 's|: [Pp]ermission denied$|: permission denied|' \
        -e 's|: No such file or directory$|: not found|'
}

# IMPORTANT : on utilise printf %b pour interpréter \n \t correctement
# Sinon sur zsh (Mac) les \n restent littéraux et le shell reçoit "cmd\n" au lieu de "cmd<newline>"

run_test() {
    local name="$1"
    local input="$2"

    local hsh_out hsh_err hsh_code
    hsh_out=$(printf '%b' "$input" | "$HSH" 2>/tmp/hsh_err)
    hsh_code=$?
    hsh_err=$(cat /tmp/hsh_err)

    local sh_out sh_err sh_code
    sh_out=$(printf '%b' "$input" | "$SH" 2>/tmp/sh_err)
    sh_code=$?
    sh_err=$(cat /tmp/sh_err)

    local hsh_err_norm sh_err_norm
    hsh_err_norm=$(echo "$hsh_err" | normalize_err)
    sh_err_norm=$(echo "$sh_err" | normalize_err)

    if [ "$hsh_out" = "$sh_out" ] && [ "$hsh_err_norm" = "$sh_err_norm" ] && [ "$hsh_code" = "$sh_code" ]; then
        echo -e "${GREEN}PASS${NC}: $name"
        pass=$((pass + 1))
    else
        echo -e "${RED}FAIL${NC}: $name"
        fail=$((fail + 1))
        failed_tests+=("$name")
        if [ "$hsh_out" != "$sh_out" ]; then
            echo -e "  ${YELLOW}stdout diff:${NC}"
            echo "    hsh: $(echo "$hsh_out" | head -3)"
            echo "    sh:  $(echo "$sh_out" | head -3)"
        fi
        if [ "$hsh_err_norm" != "$sh_err_norm" ]; then
            echo -e "  ${YELLOW}stderr diff (normalized):${NC}"
            echo "    hsh: $hsh_err_norm"
            echo "    sh:  $sh_err_norm"
            echo -e "  ${YELLOW}stderr raw:${NC}"
            echo "    hsh: $hsh_err"
            echo "    sh:  $sh_err"
        fi
        if [ "$hsh_code" != "$sh_code" ]; then
            echo -e "  ${YELLOW}exit code:${NC} hsh=$hsh_code sh=$sh_code"
        fi
    fi
}

run_exit() {
    local name="$1"
    local input="$2"

    local hsh_code sh_code
    printf '%b' "$input" | "$HSH" >/dev/null 2>&1
    hsh_code=$?
    printf '%b' "$input" | "$SH" >/dev/null 2>&1
    sh_code=$?

    if [ "$hsh_code" = "$sh_code" ]; then
        echo -e "${GREEN}PASS${NC}: $name (exit=$hsh_code)"
        pass=$((pass + 1))
    else
        echo -e "${RED}FAIL${NC}: $name - hsh=$hsh_code sh=$sh_code"
        fail=$((fail + 1))
        failed_tests+=("$name")
    fi
}

run_stdout() {
    local name="$1"
    local input="$2"

    local hsh_out sh_out
    hsh_out=$(printf '%b' "$input" | "$HSH" 2>/dev/null)
    sh_out=$(printf '%b' "$input" | "$SH" 2>/dev/null)

    if [ "$hsh_out" = "$sh_out" ]; then
        echo -e "${GREEN}PASS${NC}: $name"
        pass=$((pass + 1))
    else
        echo -e "${RED}FAIL${NC}: $name"
        fail=$((fail + 1))
        failed_tests+=("$name")
        echo -e "  ${YELLOW}hsh:${NC} $(echo "$hsh_out" | head -3)"
        echo -e "  ${YELLOW}sh:${NC}  $(echo "$sh_out" | head -3)"
    fi
}

section() {
    echo ""
    echo -e "${BLUE}=== $1 ===${NC}"
}

if [ ! -x "$HSH" ]; then
    echo "Erreur : $HSH n'existe pas ou n'est pas executable"
    exit 1
fi

echo "Test de $HSH contre $SH"
echo "================================================"

section "COMMANDES DE BASE"
run_stdout "ls simple"               "ls\n"
run_stdout "pwd simple"              "pwd\n"
run_stdout "echo hello"              "echo hello\n"
run_stdout "echo avec args"          "echo hello world\n"
run_stdout "date"                    "date\n"

section "CHEMINS ABSOLUS"
run_stdout "/bin/ls"                 "/bin/ls\n"
run_stdout "/bin/pwd"                "/bin/pwd\n"
run_stdout "/bin/echo hello"         "/bin/echo hello\n"
run_exit   "chemin absolu valide"    "/bin/ls\n"
run_exit   "chemin absolu inexistant" "/bin/nexistepas\n"

section "CHEMINS RELATIFS"
run_exit   "chemin relatif inexistant" "./nexistepas\n"
run_exit   "chemin relatif ../"        "../nexistepas\n"
run_exit   "chemin bin/ls relatif"     "bin/ls\n"

section "LIGNES VIDES ET ESPACES"
run_test   "ligne vide"              "\n"
run_test   "plusieurs lignes vides"  "\n\n\n"
run_test   "espaces seuls"           "   \n"
run_test   "tabs seuls"              "\t\t\n"
run_test   "mix espaces/tabs"        " \t \t \n"
run_exit   "exit code ligne vide"    "\n"
run_exit   "exit code espaces"       "   \n"

section "SEPARATEURS DANS LES ARGUMENTS"
run_stdout "espaces multiples"       "echo  hello   world\n"
run_stdout "tab comme separateur"    "echo\thello\n"
run_stdout "tabs multiples"          "echo\t\thello\tworld\n"
run_stdout "mix tabs/espaces"        "echo \t hello \t world\n"
run_stdout "espaces en debut"        "   ls\n"
run_stdout "espaces en fin"          "ls   \n"

section "COMMANDES INEXISTANTES"
run_test   "commande inexistante"    "nexistepas\n"
run_exit   "exit code not found"     "nexistepas\n"
run_test   "commande bizarre"        "xyzabc123\n"

section "PERMISSIONS (exit 126 attendu)"
TMP_NOEXEC=$(mktemp)
echo "#!/bin/sh" > "$TMP_NOEXEC"
chmod 644 "$TMP_NOEXEC"
run_exit   "fichier non executable"  "$TMP_NOEXEC\n"
run_exit   "/etc/passwd"             "/etc/passwd\n"
run_exit   "repertoire /tmp"         "/tmp\n"
run_exit   "repertoire /"            "/\n"
rm -f "$TMP_NOEXEC"

section "EXIT CODES"
run_exit   "ls reussit"              "ls\n"
run_exit   "ls dossier inexistant"   "ls /dossier_qui_nexiste_pas_vraiment\n"
run_exit   "true"                    "true\n"
run_exit   "false"                   "false\n"
run_exit   "cmd absente"             "fakecmd\n"

section "COMMANDES MULTIPLES"
run_stdout "deux ls"                 "ls\nls\n"
run_stdout "ls puis pwd"             "ls\npwd\n"
run_stdout "trois commandes"         "echo a\necho b\necho c\n"
run_test   "fake puis vraie"         "fakecmd\nls\n"
run_test   "vraie puis fake"         "ls\nfakecmd\n"
run_exit   "status derniere fake"    "ls\nfakecmd\n"
run_exit   "status derniere ok"      "fakecmd\nls\n"

section "ARGUMENTS AVEC CARACTERES SPECIAUX"
run_stdout "echo avec tiret"         "echo -n hello\n"
run_stdout "ls avec option"          "ls -a /tmp\n"
run_stdout "echo chiffres"           "echo 123 456\n"

section "ENTREE SANS NEWLINE FINAL"
run_stdout "ls sans newline final"   "ls"
run_exit   "exit status sans NL"     "ls"

section "STRESS TEST PARSER"
# Construction avec printf pour avoir de vrais espaces
LONG_ARGS=$(printf "echo %s\n" "$(seq 1 50 | tr '\n' ' ')")
run_stdout "50 arguments"            "$LONG_ARGS"
LONG_ARGS2=$(printf "echo %s\n" "$(seq 1 100 | tr '\n' ' ')")
run_stdout "100 arguments"           "$LONG_ARGS2"

section "EDGE CASES"
run_test   "uniquement slash"        "/\n"
run_test   "commande avec .."        "..\n"
run_test   "commande avec ."         ".\n"

section "TESTS DIVERS"
run_stdout "head /etc/hostname"      "head /etc/hostname\n"
run_stdout "whoami"                  "whoami\n"
run_stdout "id -u"                   "id -u\n"

echo ""
echo "================================================"
echo -e "${BLUE}RESULTATS${NC}"
echo "================================================"
echo -e "${GREEN}PASS: $pass${NC}"
echo -e "${RED}FAIL: $fail${NC}"
total=$((pass + fail))
if [ $total -gt 0 ]; then
    percent=$((pass * 100 / total))
    echo "Score: $pass/$total ($percent%)"
fi

if [ $fail -gt 0 ]; then
    echo ""
    echo -e "${RED}Tests echoues:${NC}"
    for t in "${failed_tests[@]}"; do
        echo "  - $t"
    done
fi

rm -f /tmp/hsh_err /tmp/sh_err
exit $fail
