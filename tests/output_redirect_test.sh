../bin/rshell << 'EOF'

echo hello > test1.txt
echo hi > test2.txt
echo hi > test1.txt # should overwrite test1.txt with "hi"
ls > test3.txt
ls -a > test4.txt
echo hello and goodbye > test5.txt
wc < test1.txt > out.txt # out.txt should contain wc stuff in out.txt

rm test1.txt
rm test2.txt
rm test3.txt
rm test4.txt
rm out.txt

exit

EOF