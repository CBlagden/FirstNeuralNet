#include "LinAlgUtil.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

namespace lin_alg
{

	Matrix::Matrix() {}

	Matrix::Matrix(vec_vec &mat)
	{
		this->mat = mat;
		this->rows = mat.size();
		if (mat.size() > 0) {
			this->cols = mat[0].size();
		}
	}

	Matrix Matrix::operator+(double val) const
	{
		vec_vec new_mat;

		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] + val);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::operator-(double val) const
	{
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] - val);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::operator*(double val) const
	{
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] * val);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::operator+(Matrix const &m) const
	{
		if (m.getCols() != cols && m.getRows() != rows)
		{
			throw "Cannot add matrices!";
		}
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] + m.get(i, j));
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::operator-(Matrix const &m) const
	{
		if (m.getCols() != cols && m.getRows() != rows)
		{
			throw "Cannot subtract matrices!";
		}
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] - m.get(i, j));
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::operator*(Matrix const &m) const
	{
		if (cols != m.getRows())
		{
			throw "Cannot multiply matrices!";
		}
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(m.getCols());
			for (int j = 0; j < m.getCols(); j++)
			{
				double val = 0.0;
				for (int k = 0; k < cols; k++)
				{
					val += mat[i][k] * m.get(k, j);
				}
				row.push_back(val);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	bool Matrix::operator==(Matrix const &m) const
	{
		if (m.getRows() != rows || m.getCols() != cols)
		{
			return false;
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (mat[i][j] != m.get(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}

	Matrix Matrix::transpose() const
	{
		vec_vec new_mat;
		new_mat.reserve(cols);
		for (int i = 0; i < cols; i++)
		{
			vec row;
			row.reserve(rows);
			for (int j = 0; j < rows; j++)
			{
				row.push_back(mat[j][i]);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::hadamardProduct(Matrix const &m) const
	{
		if (rows != m.getRows() && cols != m.getCols())
		{
			throw "Dimensions must match for hadamard product!";
		}
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(mat[i][j] * m.get(i, j));
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::getAbs() const
	{
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				double val = fabs(mat[i][j]);
				row.push_back(val);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::zeros(uint rows, uint cols)
	{
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(0);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::identity(uint rows, uint cols)
	{
		if (rows != cols)
		{
			cols = rows;
		}
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				if (i == j)
				{
					row.push_back(1);
				}
				else
				{
					row.push_back(0);
				}
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::random(uint rows, uint cols)
	{
		srand(time(NULL));
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				const double rand = randomDouble();
				row.push_back(rand);
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	Matrix Matrix::transform(std::function<double(double)> func)
	{
		vec_vec new_mat;
		new_mat.reserve(rows);
		for (int i = 0; i < rows; i++)
		{
			vec row;
			row.reserve(cols);
			for (int j = 0; j < cols; j++)
			{
				row.push_back(func(mat[i][j]));
			}
			new_mat.push_back(row);
		}
		return new_mat;
	}

	void Matrix::write(std::string filename) const
	{
		std::ofstream writer(filename);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				writer << mat[i][j] << ",";
			}
			writer << "\n";
		}
		writer.close();
	}

	Matrix Matrix::read(std::string filename)
	{
		std::ifstream reader(filename);
		std::string line;
		vec_vec new_mat;
		while (std::getline(reader, line))
		{
			std::vector<double> row;
			int index = line.find_first_of(",");
			while (index != -1)
			{
				double val = std::stod(line.substr(0, index));
				line = line.substr(index + 1);
				index = line.find_first_of(",");
				row.push_back(val);
			}
			new_mat.push_back(row);
		}
		reader.close();
		return new_mat;
	}

	Matrix Matrix::getMatrix(uint row)
	{
		vec_vec new_mat;
		vec new_row = mat[row];
		new_mat.push_back(new_row);
		return new_mat;
	}

	vec_vec Matrix::toVec() const
	{
		return mat;
	}

	uint Matrix::getRows() const
	{
		return mat.size();
	}

	uint Matrix::getCols() const
	{
		if (mat.size() > 0) {
			return mat[0].size();
		}
		return 0;
	}

	uint Matrix::size() const
	{
		return getRows();
	}

	double Matrix::get(uint i, uint j) const
	{
		if (rows > 0 && cols > 0 && i < rows && j < cols) {
			return mat[i][j];
		}
		return 0;
	}

	void Matrix::set(uint i, uint j, double val)
	{
		mat[i][j] = val;
	}

	double Matrix::getSum() const
	{
		double sum = 0.0;
		for (int i = 0; i < getRows(); i++)
		{
			for (int j = 0; j < getCols(); j++)
			{
				sum += mat[i][j];
			}
		}
		return sum;
	}

	double Matrix::getAverage() const
	{
		return getSum() / (getRows() * getCols());
	}

	std::string Matrix::toString() const
	{
		std::string output;
		for (uint i = 0; i < getRows(); i++)
		{
			for (uint j = 0; j < getCols(); j++)
			{
				output.append(std::to_string(mat[i][j]).append(" "));
			}
			output.append("\n");
		}
		return output;
	}

	const double randomDouble()
	{
		double scale = RAND_MAX + 1.;
		double base = rand() / scale;
		double fine = rand() / scale;
		return base + fine / scale;
	}

} // namespace lin_alg
