#include <iostream>
#include "Header.h"

using namespace Pr1;
int main() {
	Line* arr = nullptr, * res = nullptr;; // �������� ������ � ������ �� �������� �������������� �������
	int m, n; // ���������� ����� � ��������
	arr = input(m, n); // ���� �������
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output("Sourced matrix", arr, m, n);
	std::cout << std::endl;
	res = new_matrix(arr,m, n);
	output("Result matrix", res, m, n);
	std::cout << std::endl;
	erase(arr);// ������������ ������
	erase(res);
	return 0;
}