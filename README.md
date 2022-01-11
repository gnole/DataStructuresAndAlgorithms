# Алгоритмы и структуры данных
## Введение 
В данном репозитории представлены решения (не всех) задач по курсу "Алгоритмы и структуры данных".
3 курс осенний семестр 2021 год. 

## Задачи 
* Модуль 1
    * [Сумма (С++)](1module/sum/main.cpp). [Условие](#Задача-про-сумму).
        Считываем минус.
    * [Стек (C++)](1module/stack/main.cpp). [Условие](#Задача-про-стек).
        Бывают неправильные команды и всяческие отступления от формата ввода.
    * [Очередь (C++)](1module/gueue/main.cpp). [Условие](#Задача-про-очередь). 
        Круговая Очередь. Ввод/вывод через файл. 
* Модуль 3
    * [Фильтр Блума (C++)](3module/bloom_filter/main.cpp). [Условие](#Фильтр-Блума).
        Операнды для вычисления хэш-функции стоит брать по модулю M. Бывают неправильные команды и всяческие отступления от формата ввода.
    * [Задача о рюкзаке (C++)](3module/knapsack/main.cpp). [Условие](#Рюкзак).
        Динамическое программирование. НОД от весов. Парсинг строк. 
    * [Сумасшедший богач (C++)](3module/greedy/main.cpp). [Условие](#Сумасшедший-богач).
   
        

## Условия задач Модуль 1

### Задача про сумму 
На стандартном потоке ввода задаётся последовательность целых чисел.
Каждое число последовательности не меньше -200 000 000 и не больше 200 000 000.
На стандартный поток вывода напечатайте сумму этих чисел.
Особое внимание хочу обратить на ввод.
### Задача про стек
Реализуйте стек, используя только массив.
Память под очередь должна быть выделена не более одного раза, при вызове команды `"set_size"`.

#### Формат входных данных
На стандартном потоке ввода задаётся последовательность команд. Пустые строки игнорируются.
Первая строка всегда содержит `"set_size N"`, где `N` - максимальный размер стека, целое число.
Каждая последующая строка содержит ровно одну команду: `push X`, `pop` или `print`, где `X` - произвольная строка без пробелов.

#### Формат результата
Команда print выводит содержимое стека (снизу вверх) одной строкой, значения разделяются пробелами. Если стек пуст, то выводится `"empty"`.
В случае переполнения стека выводится `"overflow"`.
Команда pop выводит элемент или `"underflow"`, если стек пуст.
Память под стек должна быть выделена не более одного раза, при вызове команды `"set_size"`.
В любой непонятной ситуации результатом работы любой команды будет "error".
Результат работы программы выводится в стандартный поток вывода.

### Задача про очередь
Это как задача про стек, только про очередь.
Реализуйте очередь, используя только массив.
Ввод и вывод данных осуществляется через файлы. Имена входного и выходного файлов задаются через аргументы командной строки (первый и второй соответственно).

#### Формат входных данных
Во входном файле задаётся последовательность команд. Пустые строки игнорируются.
Первая строка всегда содержит `"set_size N"`, где `N` - максимальный размер очереди, целое число.
Каждая последующая строка содержит ровно одну команду: `push X`, `pop` или `print`, где `X` - произвольная строка без пробелов.

#### Формат результата
Команда print выводит содержимое очередь (от головы к хвосту) одной строкой, значения разделяются пробелами. Если очередь пуста, то выводится `"empty"`.
В случае переполнения очереди выводится `"overflow"`.
Команда pop выводит элемент или `"underflow"`, если очередь пуста.
Память под очередь должна быть выделена не более одного раза, при вызове команды `"set_size"`.
В любой непонятной ситуации результатом работы любой команды будет `"error"`.

## Условия задач Модуль 3

### Фильтр Блума
Реализуйте фильтр Блума, позволяющий дать быстрый, но вероятностный ответ, присутствует ли объект в коллекции.
Реализация самой структуры данных должна быть инкапуслирована, т.е. не зависеть от форматов входных/выходных данных и непосредственно ввода/вывода.
Реализация битового массива также должна быть инкапсулирована. Массив битов должен быть эффективно расположен в памяти.
Параметрами структуры данных являются `n` - приблизительное количество элементов (целое), P - вероятность ложноположительного ответа.
Размер структуры, `m`, вычисляется как -`n log2 P / ln 2`, а количество хэш-функций - как -`log2 P`. Оба значения округляются до ближайшего целого.
В качестве семейства функций используйте семейство хэш-функций вида
```
hi(x) = (((i + 1)*x + pi+1) mod M) mod m,
```
где - `x` - ключ, `i` - номер хэш-функции, `pi` - i-тое по счету простое число, а `M` - 31ое число Мерсенна.

#### Формат входных данных
На стандартном потоке ввода задаётся последовательность команд. Пустые строки игнорируются.
Первая строка содержит команду вида `set n P`.
Каждая последующая строка содержит ровно одну команду: `add K`, `search K` или `print`, где `K` - неотрицательное число (64 бита вам хватит), ключ.

#### Формат результата
Команда set инициализирует структуру и выводит вычисленные параметры в формате "m k".
Команда add добавляет в структуру ключ K.
Команда `search` выводит либо "1", если элемент возможно присутствует в структуре, либо "0", если он там отсутствует.
Команда `print` выводит внутреннее состояние струтуры - последовательность из 0 и 1, не разделенную пробелами.
В любой непонятной ситуации результатом работы любой команды будет `"error"`.
Результат работы программы выводится в стандартный поток вывода.

### Рюкзак
Решите задачу о рюкзаке методом динамического программирования. Алгоритм должен быть инкапсулирован.

#### Формат входных данных
Данные подаются на стандартный поток ввода. Пустые строки игнорируются.
Первая строка содержит целое неотрицательное число — максимальную массу предметов, которую выдержит рюкзак.
Каждая последующая содержит два целых неотрицательных числа: массу предмета и его стоимость.

#### Формат результата
Первая строка содержит два числа: суммарную массу предметов и их суммарную стоимость.
В последующих строках записаны номера предметов, которые были помещены в рюкзак, в порядке возрастания номера.
Результат работы программы выводится в стандартный поток вывода.
В любой непонятной ситуации результатом работы любой команды будет "error".

### Сумасшедший богач
Один сумасшедший богач на старости лет впал в маразм и стал еще более сумасшедшим. Он решил отдать половину своих богатств тому, кто выиграет в математической игре.

Правила игры: изначально каждый игрок начинает с нулевой суммой. Он может либо получить у богача 1 миллион сантиков, либо отдать ему 1 миллион сантиков, либо получить от богача ту же сумму, которая есть у него сейчас.
Выигрывает тот, кто за минимальное количество действий наберет сумму, равную половине состояния богача.
На беду других игроков, нашелся человек, который что-то слышал про жадные алгоритмы и двоичную систему счисления (возможно это вы).

#### Формат входных данных
В стандартном потоке записано единственное натуральное число - размер половины состояния богача (в миллионах).

#### Формат результата
Каждая строка выхода содержит ровно одну операцию (`inc`, `dec` или `dbl`) из кратчайшей последовательности действий для победы.
Результат работы программы выводится в стандартный поток вывода.




