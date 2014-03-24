#ifndef VECTOR_4_H
#define VECTOR_4_H

#include <cmath>
#include <iostream>

namespace DBDG
{
  class Vector4
  {
  public:
    static constexpr float TO_RADIANS = (1.0f/180.f)*M_PI;
    static constexpr float TO_DEGREE  = 180.0f/M_PI;
    float x, y, z,w;
  	
  Vector4()
    :x(0), y(0), z(0),w(0)
    {		
    }
	
    Vector4(const float &_x, const float &_y, const float &_z, const float &_w)
      :x(_x), y(_y), z(_z), w(_w)
    {
    }
	
    Vector4(const Vector4 &other)
    {
      this->x = other.x;
      this->y = other.y;
      this->z = other.z;
      this->w = other.w;
    }
	
    Vector4& set(const float &x, const float &y, const float &z, const float &w)
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->w = w;
      return *this;
    }
	
    Vector4& set(const Vector4 &other)
    {
      this->x = other.x;
      this->y = other.y;
      this->z = other.z;
      this->w = other.w;
      return *this;
    }
	
    Vector4& add(const float &x,const float &y, const float &z, const float &w)
    {
      this->x += x;
      this->y += y;
      this->z += z;
      this->w += w;
      return *this;
    }
	
    Vector4& add(const Vector4 &other)
    {
      this->x += other.x;
      this->y += other.y;
      this->z += other.z;
      this->w += other.w;
      return *this;
    }
	
    Vector4& sub(const float &x,const float &y, const float &z, const float &w)
    {
      this->x -= x;
      this->y -= y;
      this->z -= z;
      this->w -= w;
      return *this;
    }
	
    Vector4& sub(const Vector4 &other){
      this->x -= other.x;
      this->y -= other.y;
      this->z -= other.z;
      this->w -= other.w;
      return *this;
    }
	
    Vector4& mul(const float &scalar)
    {
      this->x *= scalar;
      this->y *= scalar;
      this->z *= scalar;
      this->w *= scalar;
      return *this;
    }
	
    float length() const
    {
      return sqrt(x*x + y*y + z*z + w*w);
    }
	
    Vector4& normalize(){
      float len = length();

      if(len != 0){
        x /= len;
        y /= len;
        z /= len;
        w /= len;
      }
      return *this;
    }

    Vector4 normalizedVector() const {
      float len = length();
      float _x=0, _y=0, _z=0, _w=0;
      if(len != 0){
        _x = x/len;
        _y = y/len;
        _z = z/len;
        _w = w/len;
      }
      return Vector4(_x,_y,_z,_w);
    }

    //距離
    float dist(const Vector4 &other) const
    {
      float distX = this->x - other.x;
      float distY = this->y - other.y;
      float distZ = this->z - other.z;
      float distW = this->w - other.w;
      return sqrt(distX*distX + distY*distY + distZ*distZ + distW*distW);
    }
	
    float dist(const float &x, const float &y, const float &z, const float &w) const
    {
      float distX = this->x - x;
      float distY = this->y - y;
      float distZ = this->z - z;
      float distW = this->w - w;
      return sqrt(distX*distX + distY*distY + distZ*distZ + distW*distW); 
    }

    float distanceTo(const Vector4 &other) const
    {
      float dist_x = other.x - this->x;
      float dist_y = other.y - this->y;
      float dist_z = other.z - this->z;
      float dist_w = other.w - this->w;
      return sqrt(dist_x*dist_x + dist_y*dist_y + dist_z*dist_z + dist_w*dist_w);
    }

    //2乗距離
    float distSquared(const Vector4 &other) const
    {
      float distX = this->x - other.x;
      float distY = this->y - other.y;
      float distZ = this->z - other.z;
      float distW = this->w - other.w;
      return distX*distX + distY*distY + distZ*distZ + distW*distW; 
    }
	
    float distSquared(const float &x, const float &y, const float &z, const float &w) const
    {
      float distX = this->x - x;
      float distY = this->y - y;
      float distZ = this->z - z;
      float distW = this->w - w;
    
      return distX*distX + distY*distY + distZ*distZ + distW*distW; 
    }

    //内積
    float dot(const Vector4 &other) const
    {
      return this->x*other.x + this->y*other.y + this->z*other.z + this->w*other.w;
    }

    /*
    //外積
    Vector4 cross(const Vector4 &other) const
    {
      return Vector4(this->y*other.z - this->z*other.y,
                     this->z*other.x - this->x*other.z,
                     this->x*other.y - this->y*other.x);
    }
    */
    /*
    //ラジアンで返る
    float angleTo(const Vector4 &other) const
    {
      float dot  = this->dot(other);
      float len1 = this->length();
      float len2 = other.length();

      //零ベクトルとの角度は0とする
      if(len1 ==0 || len2 == 0)
        return 0;

      return acos(dot/len1/len2);
    }
    */
    
    Vector4& operator=(const Vector4 &other)
      {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        this->w = other.w;
        return *this;
      }

    Vector4& operator-=(const Vector4 &other)
    {
      this->x -= other.x;
      this->y -= other.y;
      this->z -= other.z;
      this->w -= other.w;
      return *this;
    }

    Vector4& operator+=(const Vector4 &other)
    {
      this->x += other.x;
      this->y += other.y;
      this->z += other.z;
      this->w += other.w;
      return *this;
    }

    Vector4& operator*=(const float &scalar)
    {
      this->x *= scalar;
      this->y *= scalar;
      this->z *= scalar;
      this->w *= scalar;
      return *this;
    }

    Vector4 operator+() const
    {
      return *this;
    }

    Vector4 operator-() const
    {
      return Vector4(-x, -y, -z, -w);
    }

    Vector4 operator+(const Vector4 &rhs) const
    {
      return Vector4(this->x+rhs.x, this->y+rhs.y, this->z+rhs.z, this->w+rhs.w);
    }

    Vector4 operator-(const Vector4 &rhs) const
    {
      return Vector4(this->x-rhs.x, this->y-rhs.y, this->z-rhs.z, this->w-rhs.w);
    }

    Vector4 operator*(const float &k) const
    {
      return Vector4(this->x*k, this->y*k, this->z*k, this->w*k);
    }

    friend Vector4 operator*(const float &k, const Vector4 &rhs)
    {
      return Vector4(rhs.x*k, rhs.y*k, rhs.z*k, rhs.w*k);
    }

    Vector4 operator/(const float &k) const
    {
      return Vector4(this->x/k, this->y/k, this->z/k, this->w/k);
    }

    friend std::ostream& operator<<(std::ostream &s, const Vector4 &rhs)
    {
      return s << "(" << rhs.x << "," << rhs.y <<
        "," << rhs.z << "," << rhs.w << ")" << std::endl;
    }
  };
}
#endif
