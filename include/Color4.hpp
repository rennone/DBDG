#ifndef DBDG_COLOR4_H
#define DBDG_COLOR4_H

#include <iostream> // "<<" のオーバーロード用
namespace DBDG
{
  class Color4
  {
  public:
    float r, g, b, a;
  	
    Color4()
      :r(0),g(0),b(0),a(1)
    {		
    }
	
    Color4(const float &r,const float &g,const float &b)
      :r(r),g(g),b(b),a(1)
    {
    }
  
    Color4(const float &r,const float &g,const float &b, const float &a)
      :r(r),g(g),b(b),a(a)
    {
    }
	
    Color4(const Color4 &other)
      :r(other.r), g(other.g), b(other.b), a(other.a)
    {
    }
	
    Color4& set(const float &r, const float &g, const float &b, const float &a)
    {
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    
      return *this;
    }
	
    Color4& set(const Color4 &other)
    {
      this->r = other.r;
      this->g = other.g;
      this->b = other.b;
      this->a = other.a;
    
      return *this;
    }
	
    Color4& add(const float &r, const float &g, const float &b, const float &a)
    {
      this->r += r;
      this->g += g;
      this->b += b;
      this->a += a;
    
      return *this;
    }
	
    Color4& add(const Color4 &other)
    {
      this->r += other.r;
      this->g += other.g;
      this->b += other.b;
      this->a += other.a;
    
      return *this;
    }
	
    Color4& sub(const float &r, const float &g, const float &b, const float &a)
    {
      this->r -= r;
      this->g -= g;
      this->b -= b;
      this->a -= a;
    
      return *this;
    }
	
    Color4& sub(const Color4 &other){
      this->r -= other.r;
      this->g -= other.g;
      this->b -= other.b;
      this->a -= other.a;
    
      return *this;
    }
	
    Color4& mul(const float &scalar)
    {
      this->r *= scalar;
      this->g *= scalar;
      this->b *= scalar;
      this->a *= scalar;
      return *this;
    }
	
    Color4& operator=(const Color4 &other)
    {
      this->r = other.r;
      this->g = other.g;
      this->b = other.b;
      this->a = other.a;

      return *this;
    }

    Color4& operator-=(const Color4 &other)
    {
      this->r -= other.r;
      this->g -= other.g;
      this->b -= other.b;
      this->a -= other.a;
    
      return *this;
    }

    Color4& operator+=(const Color4 &other)
    {
      this->r += other.r;
      this->g += other.g;
      this->b += other.b;
      this->a += other.a;
    
      return *this;
    }

    Color4& operator*=(const float &scalar)
    {
      this->r *= scalar;
      this->g *= scalar;
      this->b *= scalar;
      this->a *= scalar;
    
      return *this;
    }

    Color4 operator+() const
    {
      return *this;
    }

    Color4 operator-() const
    {
      return Color4(-r, -g, -b, -a);
    }

    Color4 operator+(const Color4 &rhs) const
    {
      return Color4(this->r+rhs.r, this->g+rhs.g, this->b+rhs.b, this->a+rhs.a);
    }

    Color4 operator-(const Color4 &rhs) const
    {
      return Color4(this->r-rhs.r, this->g-rhs.g, this->b-rhs.b, this->a-rhs.a);
    }

    Color4 operator*(const float &k) const
    {
      return Color4(this->r*k, this->g*k, this->b*k, this->a*k);
    }

    friend Color4 operator*(const float &k, const Color4 &rhs)
    {
      return Color4(rhs.r*k, rhs.g*k, rhs.b*k, rhs.a*k);
    }

    Color4 operator/(const float &k) const
    {
      return Color4(this->r/k, this->g/k, this->b/k, this->a/k);
    }

    friend std::ostream& operator<<(std::ostream &s, const Color4 &rhs)
    {
      return s << "(" << rhs.r << "," << rhs.g << "," << rhs.b << "," << rhs.a << ")" << std::endl;
    }
  };
}
#endif
