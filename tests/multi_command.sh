../bin/rshell << 'EOF'
echo hello; rm b.cpp || ls && echo done
echo hi && rm b.cpp || ls; echo bye
echo hi && exit; ls
echo bye || exit; ls && exit
EOF