#include "Matrices.h"

#include <exception>

Matrices::Matrix::Matrix(int _rows, int _columns) : m_numOfColumns(_columns), m_numOfRows(_rows), m_size(_rows* _columns), m_data(_rows * _columns, 0.0f)
{

}

/// <summary>
/// Cria uma matrix unidimensional com apenas 1 linha
/// </summary>
Matrices::Matrix::Matrix(std::vector<float>& _data) : m_numOfColumns(_data.size()), m_numOfRows(1), m_size(_data.size()), m_data(_data)
{
}

float* Matrices::Matrix::GetData()
{
	return &m_data[0];
}

float Matrices::Matrix::GetElement(int _row, int _column)
{
	if (_row >= GetNumOfRows() || _column >= GetNumOfColumns()) throw std::bad_exception();
	return m_data[(_row * GetNumOfColumns()) + _column];
}

float Matrices::Matrix::GetElement(int _elementIndex)
{
	if (_elementIndex >= GetSize()) throw std::bad_exception();
	return m_data[_elementIndex];
}

int Matrices::Matrix::GetNumOfRows()
{
	return m_numOfRows;
}

int Matrices::Matrix::GetNumOfColumns()
{
	return m_numOfColumns;
}

int Matrices::Matrix::GetSize()
{
	return m_size;
}

void Matrices::Matrix::SetElement(int _row, int _column, float _newValue)
{
	if (_row >= GetNumOfRows() || _column >= GetNumOfColumns()) throw std::bad_exception();
	m_data[(_row * GetNumOfColumns()) + _column] = _newValue;
}

void Matrices::Matrix::SetElement(int _elementIndex, float _newValue)
{
	if(_elementIndex >= GetSize()) throw std::bad_exception();
	m_data[_elementIndex] = _newValue;
}

Matrices::Matrix Matrices::Matrix::operator*(Matrix& _secondMatrix)
{
	if(this->GetNumOfColumns() != _secondMatrix.GetNumOfRows()) throw std::bad_exception();

	Matrix newMatrix(this->GetNumOfRows(), _secondMatrix.GetNumOfColumns());
	float newValue;

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newValue = 0;
		for (int j = 0; j < this->GetNumOfColumns(); j++)
		{
			newValue += this->GetElement(i / this->GetNumOfRows(), j) * _secondMatrix.GetElement(j, i % _secondMatrix.GetNumOfColumns());
		}
		newMatrix.SetElement(i, newValue);
	}

	return newMatrix;
}

Matrices::Matrix Matrices::Matrix::operator-(Matrix& _secondMatrix)
{
	if(this->GetSize() != _secondMatrix.GetSize()) throw std::bad_exception();

	Matrix newMatrix(*this);

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newMatrix.SetElement(i, newMatrix.GetElement(i) - _secondMatrix.GetElement(i));
	}

	return newMatrix;
}

Matrices::Matrix Matrices::Matrix::operator+(Matrix& _secondMatrix)
{
	if (this->GetSize() != _secondMatrix.GetSize()) throw std::bad_exception();

	Matrix newMatrix(*this);

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newMatrix.SetElement(i, newMatrix.GetElement(i) + _secondMatrix.GetElement(i));
	}

	return newMatrix;
}


//-----Matrix4x4-----//
Matrices::Matrix4x4 Matrices::Matrix4x4::operator*(Matrix4x4& _secondMatrix)
{
	if (this->GetNumOfColumns() != _secondMatrix.GetNumOfRows()) throw std::bad_exception();

	Matrix4x4 newMatrix(*this);
	float newValue;
	float x, y;

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newValue = 0;
		for (int j = 0; j < this->GetNumOfColumns(); j++)
		{
			x = this->GetElement(i / this->GetNumOfRows(), j);
			y = _secondMatrix.GetElement(j, i % _secondMatrix.GetNumOfColumns());
			newValue +=  x * y;
		}
		newMatrix.SetElement(i, newValue);
	}

	return newMatrix;
}

Matrices::Matrix4x4 Matrices::Matrix4x4::operator-(Matrix4x4& _secondMatrix)
{
	if (this->GetSize() != _secondMatrix.GetSize()) throw std::bad_exception();

	Matrix4x4 newMatrix(*this);

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newMatrix.SetElement(i, newMatrix.GetElement(i) - _secondMatrix.GetElement(i));
	}

	return newMatrix;
}

Matrices::Matrix4x4 Matrices::Matrix4x4::operator+(Matrix4x4& _secondMatrix)
{
	if (this->GetSize() != _secondMatrix.GetSize()) throw std::bad_exception();

	Matrix4x4 newMatrix(*this);

	for (int i = 0; i < newMatrix.GetSize(); i++)
	{
		newMatrix.SetElement(i, newMatrix.GetElement(i) + _secondMatrix.GetElement(i));
	}

	return newMatrix;
}
//-----Matrix4x4-----//
