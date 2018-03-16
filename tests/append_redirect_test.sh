../bin/rshell << 'EOF'

echo hi > test.txt
echo hello >> test.txt
ls >> test.txt
wc < test.txt >> test.txt 

echo testing >> out.txt
ls -a >> out.txt && echo END OF LIST >> out.txt

echo goodbye >> out.txt

rm test.txt
rm out.txt

exit

EOF