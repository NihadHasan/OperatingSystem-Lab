
#!/bin/bash

read -p "Enter username: " username
read -s -p "Enter password: " password
echo

if grep -Fxq "$username $password" userdata.txt; then
    echo "Welcome, $username!"
else
    echo "Error: Invalid username or password!"
fi
