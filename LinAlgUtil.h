/*
* LinAlgUtil.h
*
*  Created on: May 4, 2018
*      Author: CBlagden
*/

#ifndef _LINALGUTIL_H_
#define _LINALGUTIL_H_

#include <vector>
#include <functional>
#include <string>

namespace lin_alg
{

	typedef unsigned int uint;
	typedef std::vector<std::vector<double>> vec_vec;
	typedef std::vector<double> vec;

	const double randomDouble();

	class Matrix
	{
	private:
		vec_vec mat;
		uint rows = 0;
		uint cols = 0;
	public:
		Matrix();
		Matrix(vec_vec &mat);
		Matrix operator+(double val) const;
		Matrix operator-(double val) const;
		Matrix operator*(double val) const;
		Matrix operator+(Matrix const &m) const;
		Matrix operator-(Matrix const &m) const;
		Matrix operator*(Matrix const &m) const;
		bool operator==(Matrix const &m) const;
		Matrix transpose() const;
		Matrix hadamardProduct(Matrix const &m) const;
		Matrix getAbs() const;
		static Matrix zeros(uint rows, uint cols);
		static Matrix identity(uint rows, uint cols);
		static Matrix random(uint rows, uint cols);
		static Matrix read(std::string filename);
		vec_vec toVec() const;
		Matrix transform(std::function<double(double)> func);
		void write(std::string filename) const;
		void set(uint i, uint j, double val);
		double get(uint i, uint j) const;
		Matrix getMatrix(uint row);
		uint getRows() const;
		uint getCols() const;
		uint size() const;
		double getSum() const;
		double getAverage() const;
		std::string toString() const;
	};

} // namespace lin_alg

#endif /* LINALGUTIL_H_ */
