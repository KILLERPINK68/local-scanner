#Bash — это кнопка пуска. Его задача — просто скомпилировать и запустить.
#!/bin/bash

echo "🔨 Компиляция C++ сканера..."
g++ main.cpp -o main

echo "Запуск Python..."
python3 main.py

echo "Готово! Проверь файл scan_report.txt"