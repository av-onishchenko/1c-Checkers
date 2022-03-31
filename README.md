Алгоритм для игры в шашки


Я пользовалась следующим правилами при написании:
1)Обычная фигура ходит только вперёд и рубит то же только вперёд.
2)Дамка может ходить назад и рубить назад, но размер хода ее не отличается(не может продвинуться больше чем на клетку)
3)Если фигура может бить, то она обязана это делать.

Мы будем пользоваться жадным алгоритмом, ходить так, чтобы съесть наибольшее число фигур игрока. Уровень сложности зависит от глубины рекурсии. Т.е на втором уровене сложности мы будем так ходить чтобы после нашего хода и любого последующего хода другого игрока разность между съеденными и потерянными фигурами была минимальная. 
Я успела начать реализацию  только первого уровня. Для реализации второго уровня необходимо для каждой позиции уже написанными мною функциями вычислять оптимальные ответ игрока и находить максимальную разность.