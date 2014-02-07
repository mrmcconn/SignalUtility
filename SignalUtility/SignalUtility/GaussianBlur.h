// GaussianBlur.h

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

using namespace System;

namespace GaussianBlur {
	// Object representation of Gaussian vectors.
	public ref class NoiseReducerVector
	{
	private:
		// Full dimension of the vector.
		int _dimension;
		// Vector fields.
		array<double, 1>^ _fields;
		// Sigma value for the Gaussian distribution.
		double _stdDev;
		// Method for populating vector fields using a Gaussian distribution.
		void populateVector();
	public:
		// Overloading the array operator for readability.
		property double Fields[int]
		{
			double get(int index)
			{
				return _fields[index];
			}
		}
		// Permits looping on the indices of the vector without unintended consequences.
		property int Size
		{
			int get()
			{
				return _dimension;
			}
		}
		// Basic constructor.
		NoiseReducerVector()
		{
			_dimension = 3;
			populateVector();
		};
		// Constructor which guarantees an odd number of elements (important for centering.)
		NoiseReducerVector(int LeftRightSpan)
		{
			_dimension = Math::Max(2 * LeftRightSpan + 1, 3);
			populateVector();
		};
		// Mutator to permit changes in vector dimension.
		void ResetSpan(int NewSpan)
		{
			_dimension = Math::Max(2 * NewSpan + 1, 3);
			populateVector();
		};
	};

	// Object representation of the signal/sample that will undergo noise reduction.
	public ref class Sample
	{
	private:
		// Number of elements in the sample.
		long _size;
		// A list of points to store sample data.
		array<double, 2> ^ _points;
		// Cache for the last Gaussian vector used for smoothing; prevents unnecessary computation.
		int _lastUsedVectorSize;
		// Private Method: dotProductSegment
		// Returns: double
		// Assumes: _points has been populated
		// Computes the dot product of a Gaussian vector and a segment y-values in _points,
		// returns the raw y-value if not enough points surround location to compute
		// a dot product.
		double dotProductSegment(long location, NoiseReducerVector^ smoothingVector)
		{
			int rightSpan = (smoothingVector->Size - 1) / 2;
			if (!(location + rightSpan < _size) || (location < rightSpan))
			{
				// Default behavior to prevent out of bounds errors.
				return _points[location, 1];
			}

			double outVal = 0.0;
			int start = location - rightSpan;
			for (int i = 0; i < smoothingVector->Size; i++)
			{
				outVal += (smoothingVector->Fields[i] * _points[start + i, 1]);
			}

			return outVal;
		}

	public:
		// Constructor.
		Sample()
		{
			_size = 100;
			_points = gcnew array<double, 2>(_size, 3);
			_lastUsedVectorSize = 0;
		}

		// Constructor with a specifiable size.
		Sample(long Size)
		{
			_size = 100;
			if (_size >= 1)
			{
				_size = Size;
			}
			_points = gcnew array<double, 2>(_size, 3);
			_lastUsedVectorSize = 0;
		}

		// Mutator for _size and dependent members.
		void Reset(long NewSize)
		{
			_size = NewSize;
			_lastUsedVectorSize = 0;
			_points = gcnew array<double, 2>(_size, 3);
		}

		// Property for _size.
		property long Size
		{
			long get()
			{
				return _size;
			}
		}

		// Specifies that _points[Location] is the ordered pair (XValue, YValue).
		void SetPoint(long Location, double XValue, double YValue)
		{
			if (!(Location < _size))
			{
				return;
			}
			_points[Location, 0] = XValue;
			_points[Location, 1] = YValue;
		}
		
		// Sets the x-value of _points[Location]
		void SetX(long Location, double XValue)
		{
			if (!(Location < _size))
			{
				return;
			}
			_points[Location, 0] = XValue;
		}
		
		// Sets the y-value of _points[Location]
		void SetY(long Location, double YValue)
		{
			if (!(Location < _size))
			{
				return;
			}
			_points[Location, 1] = YValue;
		}

		// Returns the x-value of _points[Location]
		double PointX(long Location)
		{
			if (!(Location < _size))
			{
				return 0.0;
			}
			return _points[Location, 0];
		}

		// Returns the y-value of _points[Location]
		double PointY(long Location)
		{
			if (!(Location < _size))
			{
				return 0.0;
			}
			return _points[Location, 1];
		}

		// Returns the y-value of _points[Location] subjected to Gaussian blur.
		double SmoothedPointY(long Location)
		{
			if (_lastUsedVectorSize == 0)
			{
				return _points[Location, 1];
			}

			return _points[Location, 2];
		}

		// Public Method: SmoothSample
		// Returns: Void
		// Assumes: _points has been populated with raw sample data.
		// Uses SmoothingVector to perform a Gaussian blur on _points;
		// points too near the beginning or end of the array for a dot
		// product (without wrapping the array,) are unchanged.
		void SmoothSample(NoiseReducerVector^ SmoothingVector)
		{
			if (_lastUsedVectorSize == SmoothingVector->Size)
			{
				return;
			}
			int span = (SmoothingVector->Size - 1) / 2;
			_lastUsedVectorSize = SmoothingVector->Size;
			for (int i = 0; i < _size; i++)
			{
				_points[i, 2] = dotProductSegment(i, SmoothingVector);
			}
		}

		// Returns true if a Gaussian blur has been performed, false otherwise.
		bool WasSmoothed()
		{
			return (_lastUsedVectorSize != 0);
		}
	};
	// Private Method: populateVector
	// Returns: Void
	// Assumes: _dimension is non-zero.
	// Populates _fields[x] with G(x - (_dimension - 1) / 2), where G(y) is
	// the Gaussian distribution function evaluated at y with sigma = _stdDev
	// and mu = 0;
	void NoiseReducerVector::populateVector()
	{
		_stdDev = (double)_dimension / 12.0;
		_fields = gcnew array<double,1>(_dimension);

		int span = (_dimension - 1) / 2;
		double linePoint;
		for (int i = 0; i < _dimension; i++)
		{
			linePoint = (double)(i - span);
			// Explicit multiplication was chosen over a power function to improve readability.
			_fields[i] = exp(-(linePoint * linePoint) / (2 * _stdDev * _stdDev)) / (_stdDev * sqrt(2 * M_PI));
		}
	}
}


