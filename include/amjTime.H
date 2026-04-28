#ifndef _AMJTIME_H_
#define _AMJTIME_H_

#include <stdint.h>
#include <time.h>

class amjTime{
public:
  amjTime(){};
  amjTime(int16_t yr, uint8_t mo, uint8_t dy, uint8_t hr, uint8_t mn,
	  uint8_t se, int32_t ns):_yr(yr),_mo(mo),_dy(dy),_hr(hr),_mn(mn),
				  _se(se),_ns(ns){updateTimespec();};
  ~amjTime(){};
  const amjTime &now();
  const struct timespec &toTimespec() const { return _ts; } // s and ns
  amjTime &fromTimespec(const struct timespec &); // s and ns
  amjTime operator+(double s) const;
  double operator-(const amjTime &) const;
  amjTime &operator+=(double); // seconds
  int size() const {return sizeof(uint16_t)+5*sizeof(uint8_t)+sizeof(int32_t);};
  int write(uint8_t *) const ;
  int read(const uint8_t *);
  int16_t yr() const {return _yr;}
  uint8_t mo() const {return _mo;}
  uint8_t dy() const {return _dy;}
  uint8_t hr() const {return _hr;}
  uint8_t mn() const {return _mn;}
  uint8_t se() const {return _se;}
  int32_t ns() const {return _ns;}
  static amjTime Now();
private:
  int16_t _yr;
  uint8_t _mo,_dy,_hr,_mn,_se;
  int32_t _ns;
  struct timespec _ts;
  void updateTimespec();
};



#endif
