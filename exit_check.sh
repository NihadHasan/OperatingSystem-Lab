#!/bin/bash
read -p "Enter filename: " f

if [ -f "$f" ]; then
    echo "File exists"
else
    echo "File not found"
fi