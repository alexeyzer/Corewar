rm -rf tests_cv
mkdir tests_cv
./vm_champs/corewar $1 $2 > testorig.txt
mv testorig.txt tests_cv
./corewar $1 $2 > testour.txt
mv testour.txt tests_cv
mv revtestour.txt tests_cv
diff tests_cv/testorig.txt tests_cv/testour.txt >final.log
mv final.log tests_cv
