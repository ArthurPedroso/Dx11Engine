#pragma once

#include <vector>

namespace Matrices
{
	class Matrix
	{
	private:
		std::vector<float> m_data;
		int m_numOfRows;
		int m_numOfColumns;
		int m_size;

	public:

		Matrix(int _rows, int _columns);
		Matrix(std::vector<float>& _data);

		float* GetData();
		float GetElement(int _line, int _column);
		float GetElement(int _elementIndex);
		int GetNumOfRows();
		int GetNumOfColumns();
		int GetSize();
		void SetElement(int _line, int _column, float _newValue);
		void SetElement(int _elementIndex, float _newValue);

		Matrix operator*(Matrix& _secondMatrix);
		Matrix operator-(Matrix& _secondMatrix);
		Matrix operator+(Matrix& _secondMatrix);
	};
	class Matrix4x4 : public Matrix
	{
	public:
		Matrix4x4() : Matrix(4, 4) 
		{
			SetElement(0, 0, 1.0f);
			SetElement(1, 1, 1.0f);
			SetElement(2, 2, 1.0f);
			SetElement(3, 3, 1.0f);
		}

		Matrix4x4 operator*(Matrix4x4& _secondMatrix);
		Matrix4x4 operator-(Matrix4x4& _secondMatrix);
		Matrix4x4 operator+(Matrix4x4& _secondMatrix);
	};
	class Matrix3x3 : public Matrix
	{
	public:
		Matrix3x3() : Matrix(3, 3) { }
	};
}