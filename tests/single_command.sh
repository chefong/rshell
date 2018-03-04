../bin/rshell << 'EOF'

echo hello
ls
ls -a
mkdir hi
rm -f hi
echo "hi"
echo goodbye
exit

EOF