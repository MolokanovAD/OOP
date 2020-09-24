#include <iostream>
#include "Header.h"

namespace Pr1 {
	// функция ввода
	int limited_insert(int& num, const char* msg1, const char* msg, int from, int to) {
		const char* pr = "";
		std::cout << msg1;
		do {
			std::cout << pr << std::endl;
			pr = msg;
			if (getNum(num) < 0)
				return 0;
		} while (num < from || num > to);
	}
	//поиск места для новой строки по индексу
	Line* line_search_index(Line* first, int i, char& c) {
		Line* ptr = first;
		if ((!ptr) || (ptr && ptr->index > i)) {
			c = '<';
			return ptr;
		}
		if (ptr && ptr->index == i) {
			c = '=';
			return ptr;
		}
		while (ptr->next && ptr->next->index < i) {
			ptr = ptr->next;
		}
		if (ptr->next && ptr->next->index == i) {
			c = '=';
			return ptr->next;
		}
		c = '>';
		return ptr;
	}
	//поиск места для новой строки по количеству элементов, проходящих по критерию отбора
	Line* line_search_req(Line* first, int i, char& c) {
		Line* ptr = first;
		if ((!ptr) || (ptr && ptr->req > i)) {
			c = '<';
			return ptr;
		}
		if (ptr && ptr->req == i) {
			c = '>';
			return ptr;
		}
		while (ptr->next && ptr->next->req < i) {
			ptr = ptr->next;
		}
		if (ptr->next && ptr->next->req == i) {
			c = '>';
			return ptr->next;
		}
		c = '>';
		return ptr;
	}
	//вставка новой строки в матрицу
	Line* line_insert(Line*& ptr, int i, int n, char c) {
		Line* new_line;
		try {
			new_line = new Line;
		}
		catch (std::bad_alloc & ba) {
			std::cout << "Memory allocation error";
			return nullptr;
		}
		new_line->a = nullptr;
		new_line->index = i;
		new_line->size = n;
		new_line->req = 0;
		if (c == '<') {
			new_line->next = ptr;
			ptr = new_line;
		}
		if (c == '>') {
			new_line->next = ptr->next;
			ptr->next = new_line;
		}
		return new_line;
	}
	//поиск места для элемента в строке
	list* elem_search(Line* l, int j) {
		list* ptr = l->a;
		while (ptr && ptr->next && ptr->next->i < j)
			ptr = ptr->next;
		return ptr;
	}
	// вставка элемента в строку
	list* elem_insert(Line* l,list* ptr,int j,int val) {
		list* new_el;
		try {
			new_el = new list;
		}
		catch (std::bad_alloc & ba) {
			std::cout << "Memory allocation error";
			return nullptr;
		}
		new_el->val = val;
		new_el->i = j;
		if (!ptr) {
			l->a = new_el;
			new_el->next = nullptr;
			return new_el;
		}
		if (ptr->i > j) {
			new_el->next = ptr;
			l->a = new_el;
			return new_el;
		}
		if (ptr) {
			new_el->next = ptr->next;
			ptr->next = new_el;
			return new_el;
		}
	}
	//ввод значения элемента и его вставка в строку
	int element_input(Line* l, int j) {
		list* ptr = elem_search(l, j),*new_el;
		int val = 0;
		if ((ptr && ptr->next && ptr->next->i == j) || (ptr && ptr->i == j)) {
			int k;
			if (!limited_insert(k, "This element is already nonzero, press 1 to replace it and 0 to keep", "Wrong value, repeat please!", 0, 1))
				return 0;
			if (k == 1) {
				if (!limited_insert(val, "Enter element", "Wrong value, repeat please!", -2147483648, 2147483647))
					return 0;
				if (ptr->i == j) {
					if (Check(val) && !Check(ptr->val))
						l->req += 1;
					else
						if (!Check(val) && Check(ptr->val))
							l->req -= 1;
					ptr->val = val;
				}
				else {
					if (Check(val) && !Check(ptr->next->val))
						l->req += 1;
					else
						if (!Check(val) && Check(ptr->next->val))
							l->req -= 1;
					ptr->next->val = val;
				}
			}
		}
		else {
			while (!val) {
				if (!limited_insert(val, "Enter element", "Wrong value, repeat please!", -2147483648, 2147483647))
					return 0;
				if (!val)
					std::cout << "This is zero!" << std::endl;
			}
			if (Check(val))
				l->req += 1;
			if (!elem_insert(l, ptr, j, val))
				return 0;
		}
	}
	// ввод матрицы
	Line* input(int& m, int& n) {
		Line* first = nullptr;
		int flag = 1;
		if (!limited_insert(m, "Enter number of strings", "Wrong value, repeat please!", 1, 2147483647))
			return nullptr;
		if (!limited_insert(n, "Enter number of columns", "Wrong value, repeat please!", 1, 2147483647))
			return nullptr;
		std::cout << "Enter nonzero elements of the matrix" << std::endl;
		while (flag) {
			if (!limited_insert(flag, "Press 1 to enter new element; Press 0 to exit", "Wrong value, repeat please!", 0, 1)) {
				erase(first);
				return nullptr;
			}
			if (flag) {
				int i, j;
				if (!limited_insert(i, "Enter string of new element", "Wrong value, repeat please!", 1, m)) {
					erase(first);
					return nullptr;
				}
				if (!limited_insert(j, "Enter column of new element", "Wrong value, repeat please!", 1, n)) {
					erase(first);
					return nullptr;
				}
				char c;
				Line* ptr = line_search_index(first, i, c);
				if (c != '=')
					ptr = line_insert(ptr, i, n, c);
				if (!ptr) {
					erase(first);
					return nullptr;
				}
				if (c == '<')
					first = ptr;
				if (!element_input(ptr, j)) {
					erase(first);
					return nullptr;
				}
			}
		}
		if (!first)
			first = new Line{ 0,0,0,nullptr,nullptr };
		return first;
	}
	// функция вывода
	void output(const char* msg, Line* first, int m, int n) {
		std::cout << msg << std::endl;
		Line* ptr = first;
		for (int i = 1; i <= m; i++) {
			if (ptr && ptr->index == i) {
				list* p = ptr->a;
				for (int j = 1; j <= ptr->size; j++) {
					if (p && p->i == j) {
						std::cout << p->val << " ";
						p = p->next;
					}
					else
						std::cout << "0 ";
				}
				ptr = ptr->next;
			}
			else
				for (int j = 1; j <= n; j++)
					std::cout << "0 ";
			std::cout << std::endl;
		}
	}
	// функция освобождения занятой памяти
	void erase(Line*& lines)
	{
		while (lines) {
			list* ptr = lines->a;
			while (ptr) {
				list* buf = ptr;
				ptr = ptr->next;
				delete buf;
			}
			Line* buf = lines;
			lines = lines->next;
			delete buf;
		}
	}
	// проверка чётности всех цифр числа
	int Check(int a) {
		int flag = 0;
		while (a && !flag) {
			flag = a % 10 & 1;
			a /= 10;
		}
		if (flag)
			return 0;
		return 1;
	}
	// сдвиг индексов
	void index_fix(Line* res,int m) {
		int t = 0;
		Line* ptr = res;
		while (ptr) {
			ptr = ptr->next;
			t++;
		}
		ptr = res;
		t--;
		for (; t >= 0; t--) {
			ptr->index = m - t;
			ptr = ptr->next;
		}
	}
	//функция создания новой матрицы
	Line* new_matrix(Line* base, int m,int n) {
		Line* res = nullptr,*ptr = base,*new_ptr = nullptr;
		while (ptr) {
			if (ptr->req) {
				int k = 0;
				char c = 'a';
				new_ptr = line_search_req(res, ptr->req, c);
				new_ptr = line_insert(new_ptr, ptr->index, n, c);
				new_ptr->req = ptr->req;
				if (c == '<')
					res = new_ptr;
				list* p = ptr->a;
				list* lastp = nullptr;
				while (p) {
					if (Check(p->val))
						lastp = elem_insert(new_ptr, lastp, p->i - k, p->val);
					else
						k++;
					p = p->next;
				}
				new_ptr->size = n - k;
			}
			ptr = ptr->next;
		}
		index_fix(res,m);
		return res;
	}
}
