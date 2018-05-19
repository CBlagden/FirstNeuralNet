#include "LinAlgUtil.h"
#include <assert.h>
#include <iostream>

typedef unsigned int uint;
typedef std::vector<std::vector<double>> vec_vec;

vec_vec vec({ { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 },{ 10, 11, 12 } });
lin_alg::Matrix mat(vec);

const int NUM_ROWS = 4;
const int NUM_COLS = 3;

static void checkRowDimen()
{
	assert(mat.getRows() == NUM_ROWS);
	std::cout << "checkRowDimen passed" << std::endl;
}

static void checkColDimen()
{
	assert(mat.getCols() == NUM_COLS);
	std::cout << "checkColDimen passed" << std::endl;
}

static void checkEquality()
{
	lin_alg::Matrix copy = mat;
	assert(copy == mat);
	std::cout << "checkEquality passed" << std::endl;
}

static void checkScalarAdd()
{
	lin_alg::Matrix new_mat = mat + 1;
	vec_vec vec_sol(
		{ { 2, 3, 4 },{ 5, 6, 7 },{ 8, 9, 10 },{ 11, 12, 13 } });
	lin_alg::Matrix solution(vec_sol);
	assert(new_mat == solution);
	std::cout << "checkScalarAdd passed" << std::endl;
}

static void checkScalarMinus()
{
	lin_alg::Matrix new_mat = mat - 1;
	vec_vec vec_sol({ { 0, 1, 2 },{ 3, 4, 5 },{ 6, 7, 8 },{ 9, 10, 11 } });
	lin_alg::Matrix solution(vec_sol);
	assert(new_mat == solution);
	std::cout << "checkScalarMinus passed" << std::endl;
}

static void checkScalarTimes()
{
	lin_alg::Matrix new_mat = mat * 2;
	vec_vec vec_sol({ { 2, 4, 6 },{ 8, 10, 12 },{ 14, 16, 18 },{ 20, 22, 24 } });
	lin_alg::Matrix solution(vec_sol);
	assert(new_mat == solution);
	std::cout << "checkScalarTimes passed" << std::endl;
}

static void checkMatrixAdd()
{
	lin_alg::Matrix new_mat = mat + mat;
	vec_vec vec_sol({ { 2, 4, 6 },{ 8, 10, 12 },{ 14, 16, 18 },{ 20, 22, 24 } });
	lin_alg::Matrix solution(vec_sol);
	assert(new_mat == solution);
	std::cout << "checkMatrixAdd passed" << std::endl;
}

static void checkMatrixMinus()
{
	lin_alg::Matrix new_mat = mat - mat;
	vec_vec vec_sol({ { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } });
	lin_alg::Matrix solution(vec_sol);
	assert(new_mat == solution);
	std::cout << "checkMatrixMinus passed" << std::endl;
}

static void checkMatrixTranspose()
{
	lin_alg::Matrix new_mat = mat.transpose();
	assert(
		mat.getRows() == new_mat.getCols() && mat.getCols() == new_mat.getRows());
	std::cout << "checkMatrixAdd passed" << std::endl;
}

static void checkMatrixTimes()
{
	lin_alg::Matrix transpose = mat.transpose();
	lin_alg::Matrix new_mat = mat * transpose;
	vec_vec vec_sol({ { 14, 32, 50, 68 },{ 32, 77, 122, 167 },{ 50, 122, 194, 266 },{ 68, 167, 266, 365 } });
	lin_alg::Matrix solution(vec_sol);
	assert(solution == new_mat);
	std::cout << "checkMatrixTimes passed" << std::endl;
}

static void checkZeroes()
{
	lin_alg::Matrix zeroes = lin_alg::Matrix::zeros(2, 2);
	vec_vec vec_sol({ { 0, 0 },{ 0, 0 } });
	lin_alg::Matrix solution(vec_sol);
	assert(zeroes == solution);
	std::cout << "checkZeroes passed" << std::endl;
}

static void checkIdentity()
{
	lin_alg::Matrix identity = lin_alg::Matrix::identity(2, 2);
	vec_vec vec_sol({ { 1, 0 },{ 0, 1 } });
	lin_alg::Matrix solution(vec_sol);
	assert(identity == solution);
	std::cout << "checkIdentity passed" << std::endl;
}

static void checkTransform()
{
	vec_vec test_vec({ { 2, 2, 2 },
		{ 2, 2, 2 } });
	lin_alg::Matrix test(test_vec);

	vec_vec sol_vec({ { 4, 4, 4 },
		{ 4, 4, 4 } });
	lin_alg::Matrix solution(sol_vec);

	test = test.transform([](float x) {
		return x * x;
	});
	assert(test == solution);
	std::cout << "checkTransform passed" << std::endl;
}

static void checkHadamardProduct()
{
	vec_vec test_sol({ { 1, 4, 9 },
		{ 16, 25, 36 },
		{ 49, 64, 81 },
		{ 100, 121, 144 } });
	lin_alg::Matrix solution(test_sol);
	lin_alg::Matrix test = mat.hadamardProduct(mat);
	assert(test == solution);
	std::cout << "checkHadamardProduct passed" << std::endl;
}

static void checkSum()
{
	double sum = mat.getSum();
	const double solution = 12 * 13 / 2;
	assert(abs(sum - solution) < 1e-6);
	std::cout << "checkSum passed" << std::endl;
}

static void checkAverage()
{
	double average = mat.getAverage();
	const double solution = 12 * 13 / 2.0 / 12.0;
	assert(abs(average - solution) < 1e-6);
	std::cout << "checkAverage passed" << std::endl;
}

static void checkAbs()
{
	vec_vec test_vec({ { -1, -1 },
		{ 1, 1 } });
	lin_alg::Matrix test(test_vec);

	vec_vec sol_vec({ { 1, 1 },
		{ 1, 1 } });
	lin_alg::Matrix solution(sol_vec);
	lin_alg::Matrix absolute = test.getAbs();
	assert(absolute == solution);
	std::cout << "checkAbs passed" << std::endl;
}

void test()
{
	std::cout << "Testing LinAlgUtil..." << std::endl;

	checkRowDimen();
	checkColDimen();
	checkEquality();

	checkScalarAdd();
	checkScalarMinus();
	checkScalarTimes();

	checkMatrixAdd();
	checkMatrixMinus();
	checkMatrixTranspose();
	checkMatrixTimes();

	checkZeroes();
	checkIdentity();
	checkTransform();
	checkHadamardProduct();

	checkSum();
	checkAverage();
	checkAbs();

	std::cout << "All Tests passed!" << std::endl;
	std::cout << "\n";

}
