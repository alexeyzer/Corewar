rm -rf tests_cv
mkdir tests_cv
./vm_champs/corewar $1 $2 > testorig.txt
mv testorig.txt tests_cv
./corewar $1 $2 > testour.txt
mv testour.txt tests_cv
./vm_champs/corewar $2 $1 > revtestorig.txt
mv revtestorig.txt tests_cv
./corewar $2 $1 > revtestour.txt
mv revtestour.txt tests_cv
diff tests_cv/testorig.txt tests_cv/testour.txt >final.log
diff tests_cv/revtestorig.txt tests_cv/revtestour.txt >revfinal.log
mv final.log tests_cv
mv revfinal.log tests_cv