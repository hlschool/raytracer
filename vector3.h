#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

class Vector3 {
  public:
    Vector3() { };
    Vector3(float x, float y, float z) { d[0] = x; d[1] = y; d[2] = z; }
    Vector3(const Vector3 &v)
      { d[0] = v.d[0]; d[1] = v.d[1]; d[2] = v.d[2]; }

    float x() const { return d[0]; }
    float y() const { return d[1]; }
    float z() const { return d[2]; }

    float operator[](int i) const { return d[i]; }
    
    float length() const
      { return sqrt(d[0]*d[0] + d[1]*d[1] + d[2]*d[2]); }
    void normalize() {
      float temp = length();
      if (temp == 0.0)
        return;	// 0 length vector
      // multiply by 1/magnitude
      temp = 1 / temp;
      d[0] *= temp;
      d[1] *= temp;
      d[2] *= temp;
    }

    /////////////////////////////////////////////////////////
    // Overloaded operators
    /////////////////////////////////////////////////////////
  
    Vector3 operator+(const Vector3 &op2) const {   // vector addition
      return Vector3(d[0] + op2.d[0], d[1] + op2.d[1], d[2] + op2.d[2]);
    }
    Vector3 operator-(const Vector3 &op2) const {   // vector subtraction
      return Vector3(d[0] - op2.d[0], d[1] - op2.d[1], d[2] - op2.d[2]);
    }
    Vector3 operator-() const {                    // unary minus
      return Vector3(-d[0], -d[1], -d[2]);
    }
    Vector3 operator*(float s) const {            // scalar multiplication
      return Vector3(d[0] * s, d[1] * s, d[2] * s);
    }
    void operator*=(float s) {
      d[0] *= s;
      d[1] *= s;
      d[2] *= s;
    }
    Vector3 operator/(float s) const {            // scalar division
      return Vector3(d[0] / s, d[1] / s, d[2] / s);
    }
    float operator*(const Vector3 &op2) const {   // dot product
      return d[0] * op2.d[0] + d[1] * op2.d[1] + d[2] * op2.d[2];
    }
    Vector3 operator^(const Vector3 &op2) const {   // cross product
      return Vector3(d[1] * op2.d[2] - d[2] * op2.d[1], d[2] * op2.d[0] - d[0] * op2.d[2],
                    d[0] * op2.d[1] - d[1] * op2.d[0]);
    }
    bool operator==(const Vector3 &op2) const {
      return (d[0] == op2.d[0] && d[1] == op2.d[1] && d[2] == op2.d[2]);
    }
    bool operator!=(const Vector3 &op2) const {
      return (d[0] != op2.d[0] || d[1] != op2.d[1] || d[2] != op2.d[2]);
    }
    bool operator<(const Vector3 &op2) const {
      return (d[0] < op2.d[0] && d[1] < op2.d[1] && d[2] < op2.d[2]);
    }
    bool operator<=(const Vector3 &op2) const {
      return (d[0] <= op2.d[0] && d[1] <= op2.d[1] && d[2] <= op2.d[2]);
    }
    void rotate_x(float angle) {
		float temp_x = d[0];
		float temp_y = (d[1] * cos(angle)) - (d[2] * sin(angle));
		float temp_z = (d[1] * sin(angle)) + (d[2] * cos(angle));
		d[0] = temp_x;
		d[1] = temp_y;
		d[2] = temp_z;
	}
	void rotate_y(float angle) {
		float temp_x = (d[0] * cos(angle)) + (d[2] * sin(angle));
		float temp_y = d[1];
		float temp_z = -(d[0] * sin(angle)) + (d[2] * cos(angle));
		d[0] = temp_x;
		d[1] = temp_y;
		d[2] = temp_z;
	}
	void rotate_z(float angle) {
		float temp_x = (d[0] * cos(angle)) - (d[1] * sin(angle));
		float temp_y = (d[0] * sin(angle)) + (d[1] * cos(angle));
		float temp_z = d[2];
		d[0] = temp_x;
		d[1] = temp_y;
		d[2] = temp_z;
	}
  
  private:
    float d[3];
};

#endif // _VECTOR3_H_
