../bin/rshell << 'EOF'

echo hello > test.txt && echo hi >> test.txt # test.txt contains "hello" and "hi"

cat < test.txt # displays contents of test.txt

wc < test.txt > out.txt
cat out.txt # out.txt should contain wc stuff

cat < README.md
cat < assn4.json

rm test.txt
rm out.txt

exit

EOF