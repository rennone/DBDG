#ifndef DBDG_COLOR3_H
#define DBDG_COLOR3_H

#include <iostream> // "<<" のオーバーロード用

namespace DBDG
{
  class Color3
  {
  public:
    float r, g, b;
  	
    Color3()
      :r(0),g(0),b(0)
    {		
    }
	
    Color3(const float &r,const float &g,const float &b)
      :r(r),g(g),b(b)
    {
    }  
	
    Color3(const Color3 &other)
      :r(other.r), g(other.g), b(other.b)
    {
    }
	
    Color3& set(const float &r, const float &g, const float &b)
    {
      this->r = r;
      this->g = g;
      this->b = b;
    
      return *this;
    }
	
    Color3& set(const Color3 &other)
    {
      this->r = other.r;
      this->g = other.g;
      this->b = other.b;    
    
      return *this;
    }
	
    Color3& add(const float &r, const float &g, const float &b)
    {
      this->r += r;
      this->g += g;
      this->b += b;
    
      return *this;
    }
	
    Color3& add(const Color3 &other)
    {
      this->r += other.r;
      this->g += other.g;
      this->b += other.b;
    
      return *this;
    }
	
    Color3& sub(const float &r, const float &g, const float &b)
    {
      this->r -= r;
      this->g -= g;
      this->b -= b;
    
      return *this;
    }
	
    Color3& sub(const Color3 &other){
      this->r -= other.r;
      this->g -= other.g;
      this->b -= other.b;   
    
      return *this;
    }
	
    Color3& mul(const float &scalar)
    {
      this->r *= scalar;
      this->g *= scalar;
      this->b *= scalar;

      return *this;
    }
	
    Color3& operator=(const Color3 &other)
    {
      this->r = other.r;
      this->g = other.g;
      this->b = other.b;

      return *this;
    }

    Color3& operator-=(const Color3 &other)
    {
      this->r -= other.r;
      this->g -= other.g;
      this->b -= other.b;
    
      return *this;
    }

    Color3& operator+=(const Color3 &other)
    {
      this->r += other.r;
      this->g += other.g;
      this->b += other.b;
    
      return *this;
    }

    Color3& operator*=(const float &scalar)
    {
      this->r *= scalar;
      this->g *= scalar;
      this->b *= scalar;    
    
      return *this;
    }

    Color3 operator+() const
    {
      return *this;
    }

    Color3 operator-() const
    {
      return Color3(-r, -g, -b);
    }

    Color3 operator+(const Color3 &rhs) const
    {
      return Color3(this->r+rhs.r, this->g+rhs.g, this->b+rhs.b);
    }

    Color3 operator-(const Color3 &rhs) const
    {
      return Color3(this->r-rhs.r, this->g-rhs.g, this->b-rhs.b);
    }

    Color3 operator*(const float &k) const
    {
      return Color3(this->r*k, this->g*k, this->b*k);
    }

    friend Color3 operator*(const float &k, const Color3 &rhs)
    {
      return Color3(rhs.r*k, rhs.g*k, rhs.b*k);
    }

    Color3 operator/(const float &k) const
    {
      return Color3(this->r/k, this->g/k, this->b/k);
    }

    friend std::ostream& operator<<(std::ostream &s, const Color3 &rhs)
    {
      return s << "(" << rhs.r << "," << rhs.g << "," << rhs.b << ")" << std::endl;
    }
  };
}
#endif
