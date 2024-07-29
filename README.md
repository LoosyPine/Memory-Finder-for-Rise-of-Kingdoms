# Memory-Finder-for-Rise-of-Kingdoms
WinAPI. RAM read and search.
Программа вытаскивает из памяти данные об игроках в Rise of Kingdoms.
# Принцип работы:
Программа работает в области памяти, выделенной системой под процесс игры.
Данные об игроках преположительно хранятся в формате JSON и загружаются в памяти при открытии вклади с лидербордом.
Растояние между адресами нужных данных не имеет постоянной разницы, но был выявлен диапазон в котором могут хранится эти данные.
Отталкиваясь от адреса топ 1 игрока программа побитово считывает данные из памяти в поисках нужной закономерности(названия элемента JSON структуры, которая каждый раз повторяется).
Как только закономерность была найдена, включается цикл который из всего "мусора" находит нужное значение.
Так как лидерборд имеет упорядоченный вид, то следующее значение должно быть меньше предыдущего и при этом быть максимальным на этом диапазоне поиска.
Подобным образом находятся вся 1000 лучших игроков.
# P.S.
Для толчка в поиске нужен адрес топ 1 игрока в рейтинге. Его можно получить из CheatEngine(Сделать поиск по значению).
Это можно реализовать в самой программе через WinAPI.
# Tutorial(ENG)
# 1
Download and install CheatEngine(https://www.cheatengine.org/downloads.php)
# 2
Run CheatEngine and select game procces(*.exe)
# 3
Select "Type of serach" on exact value and "Type of value" select on 8 bytes
# 4
Open in the game "rating on personal murders" and write on paper top 1 player score
# 5
Open CheatEngine and write top 1 player score in value search field, click "Search" P.S. You need write score of top 1 player in filed(line 60): unsigned long long prev = HIM SCORE + 1;
# 6
You may find several values, if you don't go into details, it's easier to just sort them out.
# 7
Copy the memory address of the found value and paste in my programm(in filed "unsigned long long adress = YOUR ADDRESS;")
# 8(final)
Run programm:)
