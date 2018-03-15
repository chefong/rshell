../bin/rshell << 'EOF'

echo hello; rm b.cpp || ls && echo done
echo hi && rm b.cpp || ls; echo bye
echo hi && ls
echo bye || exit; ls && exit

EOF