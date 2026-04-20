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
 
    # Replace shell names for comparison
    NORM_SHELL=$(echo "$OUT_SHELL" | sed "s|$SHELL|SHELL|g")
    NORM_SH=$(echo "$OUT_SH" | sed "s|$SH|SHELL|g")
 
    if [ "$NORM_SHELL" = "$NORM_SH" ]; then
        echo "PASS: $TEST_NAME"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $TEST_NAME"
        echo "  hsh:    $OUT_SHELL"
        echo "  /bin/sh: $OUT_SH"
        FAIL=$((FAIL + 1))
    fi
}
 
run_status_test() {
    TEST_NAME="$1"
    INPUT="$2"
 
    STATUS_SHELL=$(echo "$INPUT" | $SHELL 2>/dev/null; echo $?)
    STATUS_SH=$(echo "$INPUT" | $SH 2>/dev/null; echo $?)
 
    if [ "$STATUS_SHELL" = "$STATUS_SH" ]; then
        echo "PASS: $TEST_NAME"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $TEST_NAME"
        echo "  hsh exit:    $STATUS_SHELL"
        echo "  /bin/sh exit: $STATUS_SH"
        FAIL=$((FAIL + 1))
    fi
}
 
echo "=== OUTPUT TESTS ==="
run_test "ls simple" "ls"
run_test "chemin complet" "/bin/ls"
run_test "ls avec args" "ls -l /tmp"
run_test "commande inexistante" "fakecommand"
run_test "chemin complet faux" "/bin/fakecommand"
run_test "ligne vide" ""
run_test "espaces seuls" "   "
run_test "plusieurs commandes" "/bin/ls
/bin/pwd"
run_test "commande fausse puis vraie" "fake
/bin/ls"
run_test "vraie puis fausse" "/bin/ls
fake"
run_test "deux fausses" "fake1
fake2"
 
echo ""
echo "=== EXIT STATUS TESTS ==="
run_status_test "status ls" "/bin/ls"
run_status_test "status fake" "fakecommand"
run_status_test "status chemin faux" "/bin/fakecommand"
run_status_test "status ligne vide" ""
run_status_test "status ls puis fake" "/bin/ls
fake"
run_status_test "status fake puis ls" "fake
/bin/ls"
 
echo ""
echo "=== RESULTATS ==="
echo "$PASS passed, $FAIL failed"
