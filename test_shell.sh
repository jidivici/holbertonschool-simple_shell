#!/bin/bash

SHELL="./a.out"
SH="/bin/sh"
PASS=0
FAIL=0

run_test() {
	TEST_NAME="$1"
	INPUT="$2"

	OUT_SHELL=$(echo "$INPUT" | $SHELL 2>&1)
	OUT_SH=$(echo "$INPUT" | $SH 2>&1)

	if [ "$OUT_SHELL" = "$OUT_SH" ]; then
		echo "PASS: $TEST_NAME"
		PASS=$((PASS + 1))
	else
		echo "FAIL: $TEST_NAME"
		echo "  Expected: $OUT_SH"
		echo "  Got:      $OUT_SHELL"
		FAIL=$((FAIL + 1))
	fi
}

run_test "ls simple" "ls"
run_test "chemin complet" "/bin/ls"
run_test "ls avec args" "ls -l /tmp"
run_test "commande inexistante" "fakecommand"
run_test "ligne vide" ""
run_test "espaces seuls" "    "
run_test "chemin complet faux" "/bin/fakecommand"
run_test "plusieurs commandes" "ls
pwd
whoami"

echo ""
echo "Résultats: $PASS passed, $FAIL failed"
