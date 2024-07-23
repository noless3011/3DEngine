#pragma once
// Vector2 class
class Vector2 {
public:
	// data members
	float x, y;

	// default constructor
	Vector2() : x(0), y(0) {}

	// parameterized constructor
	Vector2(float x, float y) : x(x), y(y) {}

	// copy constructor
	Vector2(const Vector2& other) : x(other.x), y(other.y) {}

	// destructor
	~Vector2() {}

	// methods
	float getLength() const {
		return sqrt(x * x + y * y); // use the Pythagorean theorem
	}

	Vector2 normalize() {
		float length = this->getLength();
		if (length != 0) {
			x /= length;
			y /= length;
		}
		return *this;
	}

	static float dot(Vector2& v1, Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y; // use the dot product formula
	}

	// operators
	Vector2& operator+=(Vector2& other) {
		const Vector2& v = dynamic_cast<Vector2&>(other); // cast the other vector to Vector2
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& operator-=(Vector2& other) {
		const Vector2& v = dynamic_cast<Vector2&>(other); // cast the other vector to Vector2
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(float scalar) {
		if (scalar != 0) {
			x /= scalar;
			y /= scalar;
		}
		return *this;
	}

	Vector2 operator+(Vector2& v) {
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(Vector2& v) {
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(float scalar) {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(float scalar) {
		if (scalar != 0) {
			return Vector2(x / scalar, y / scalar);
		}
		return Vector2();
	}

	bool operator==(Vector2& v) { // cast the other vector to Vector2
		return x == v.x && y == v.y;
	}

	bool operator!=(Vector2& other) {
		return !(*this == other);
	}
};

// Vector3 class
class Vector3 {
public:
	// data members
	float x, y, z;

	// default constructor
	Vector3() : x(0), y(0), z(0) {}

	// parameterized constructor
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	// copy constructor
	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

	// destructor
	~Vector3() {}

	// methods
	float getLength() {
		return sqrt(x * x + y * y + z * z); // use the Pythagorean theorem
	}

	Vector3 normalize() {
		float length = getLength();
		if (length != 0) {
			x /= length;
			y /= length;
			z /= length;
		}
		return *this;
	}

	static float dot(Vector3& v1, Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; // use the dot product formula
	}

	static Vector3 Cross(Vector3& v1, Vector3& v2) {
		return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	// operators
	Vector3& operator+=(Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator-=(Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator/=(float scalar) {
		if (scalar != 0) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}
		return *this;
	}

	Vector3 operator+(Vector3& v) {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3& v) {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float scalar) {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator/(float scalar) {
		if (scalar != 0) {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}
		return Vector3();
	}

	bool operator==(Vector3& v) {
		return x == v.x && y == v.y;
	}

	bool operator!=(Vector3& other) {
		return !(*this == other);
	}
};

class Vector4 {
public:
	// data members
	float x, y, z, w;

	// default constructor
	Vector4() : x(0), y(0), z(0), w(0) {}

	// parameterized constructor
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// copy constructor
	Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

	// destructor
	~Vector4() {}

	// methods
	float getLength() {
		return sqrt(x * x + y * y + z * z + w * w); // use the Pythagorean theorem
	}

	Vector4 normalize() {
		float length = getLength();
		if (length != 0) {
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}
		return *this;
	}

	static float dot(Vector4& v1, Vector4& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; // use the dot product formula
	}

	// operators
	Vector4& operator+=(Vector4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4& operator-=(Vector4& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vector4& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4& operator/=(float scalar) {
		if (scalar != 0) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
		}
		return *this;
	}

	Vector4 operator+(Vector4& v) {
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Vector4 operator-(Vector4& v) {
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector4 operator*(float scalar) {
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4 operator/(float scalar) {
		if (scalar != 0) {
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}
		return Vector4();
	}

	bool operator==(Vector4& v) {
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}

	bool operator!=(Vector4& other) {
		return !(*this == other);
	}
};
