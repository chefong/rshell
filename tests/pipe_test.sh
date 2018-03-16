../bin/rshell << 'EOF'

echo hello > test.txt && echo hi >> test.txt
ls | wc -l
cat < test.txt | tr A-Z a-z | tee out.txt | tr a-z A-Z > final.txt

ls | head -3
ls | head -3 | tail -1

cat < test.txt | tr a-z A-Z > out.txt

ls | head -1 | tr a-z A-Z

rm test.txt
rm out.txt
rm final.txt

exit

EOF