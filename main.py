#Python — это мозг. Он уже перехватывает вывод от C++, анализирует его и принимает решения.

import subprocess

server_path = "./main" #путь к скомпилированному серверу

print("Запуск сканера...")

process = subprocess.Popen( #popen позволяет запускать процесс и сразу возвращает управление пайтон скрипту
    [server_path, "127.0.0.1", "8080"], #сканируем порт Docker-контейнера
    stdout=subprocess.PIPE, #pipe перенаправляет поток вывода программы в память пайтон, а не терминал
    stderr=subprocess.PIPE,
    text=True #сразу декодируем вывод в строку
)

# Ждем завершения процесса и получаем вывод
output, errors = process.communicate()

if errors:
    print(f"Ошибка при запуске: {errors}")

print("Вывод сканера:\n", output)

# Анализируем вывод и ищем открытые порты
found_ports = []
for line in output.split('\n'):
    if "[+] Порт" in line and "ОТКРЫТ" in line:
        parts = line.split()
        if len(parts) >= 3:
            found_ports.append(int(parts[2]))

if found_ports:
    print(f"Найдено открытых портов: {len(found_ports)}")

    with open("scan_report.txt", "w", encoding="utf-8") as report: 
        report.write("===== Отчет сканирования =====\n") 
        report.write(f"Цель: 127.0.0.1\n")
        report.write(f"Найдено портов: {len(found_ports)}\n\n")
        
        for port in found_ports:
            report.write(f"[+] Порт {port} ОТКРЫТ\n")
            
    print("📄 Отчет сохранен в scan_report.txt")
else:
    print("Открытых портов не найдено.")