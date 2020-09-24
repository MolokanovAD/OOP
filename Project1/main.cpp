#include <iostream>
#include "Header.h"

using namespace Pr1;
int main() {
	Line* arr = nullptr, * res = nullptr;; // исходный массив и массив со строками результирующей матрицы
	int m, n; // количество строк и столбцов
	arr = input(m, n); // ввод матрицы
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", arr, m, n);
	std::cout << std::endl;
	res = new_matrix(arr,m, n);
	output("Result matrix", res, m, n);
	std::cout << std::endl;
	erase(arr);// освобождение памяти
	erase(res);
	return 0;
}