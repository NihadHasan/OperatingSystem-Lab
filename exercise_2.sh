
#!/bin/bash

file="todo.txt"

case "$1" in
    add)
        echo "[ ] $2" >> "$file"
        echo "Task added!"
        ;;
    list)
        if [ -f "$file" ]; then
            nl -w1 -s'. ' "$file"
        else
            echo "No tasks found."
        fi
        ;;
    done)
        if [ -f "$file" ]; then
            sed -i "${2}s/\[ \]/[x]/" "$file"
            echo "Nice job!"
        else
            echo "No tasks found."
        fi
        ;;
    clear)
        > "$file"
        echo "Todo list cleared"
        ;;
    search)
        if [ -f "$file" ]; then
            grep -i -- "$2" "$file"
        fi
        ;;
    *)
        echo "Usage: ./todo.sh {add|list|done|clear|search}"
        ;;
esac
