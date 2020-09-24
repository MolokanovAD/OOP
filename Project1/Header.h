namespace Pr1 {
	// структура для задания строки матрицы
	struct list {
		int i;
		int val;
		list* next;
	};
	struct Line {
		int index;
		int size; // количество элементов в строке
		int req;
		list* a;
		Line* next;// массив элементов
	};

	// шаблон функций ввода одного значения
	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}

	// прототипы функций
	int limited_insert(int& num, const char* msg1, const char* msg, int from, int to);
	Line* line_search_index(Line* first, int i, char& c);
	Line* line_search_req(Line* first, int i, char& c);
	list* elem_search(Line* l, int j);
	list* elem_insert(Line* l, list* ptr, int j, int val);
	Line* line_insert(Line*& ptr, int i, int n, char c);
	int element_input(Line* l, int j);
	Line* input(int&, int&); // ввод матрицы
	void index_fix(Line* res, int m);
	void output(const char* msg, Line* a, int m, int n); // вывод матрицы
	void erase(Line*& a); // освобождение занятой памяти
	int Check(int a); // проверка чётности всех цифр числа
	Line* new_matrix(Line* base,int m, int n); // создание результирующей матрицы
}
