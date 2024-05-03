#include "../include/amjTime.H"

#include <cstring>

int amjTime::write(uint8_t *d) const{
  uint8_t *dd=(uint8_t *)memcpy(d,&_yr,sizeof(uint16_t))+sizeof(uint16_t);
  dd=(uint8_t *)memcpy(dd,&_mo,sizeof(uint8_t))+sizeof(uint8_t);
  dd=(uint8_t *)memcpy(dd,&_dy,sizeof(uint8_t))+sizeof(uint8_t);
  dd=(uint8_t *)memcpy(dd,&_hr,sizeof(uint8_t))+sizeof(uint8_t);
  dd=(uint8_t *)memcpy(dd,&_mn,sizeof(uint8_t))+sizeof(uint8_t);
  dd=(uint8_t *)memcpy(dd,&_se,sizeof(uint8_t))+sizeof(uint8_t);
  dd=(uint8_t *)memcpy(dd,&_ns,sizeof(int32_t))+sizeof(int32_t);
  return size();
}

int amjTime::read(const uint8_t *d){
  memcpy(&_yr,(void *)d,sizeof(uint16_t));
  uint8_t *dd=(uint8_t *)d+sizeof(uint16_t);
  memcpy(&_mo,dd,sizeof(uint8_t));
  dd+=sizeof(uint8_t);
  memcpy(&_dy,dd,sizeof(uint8_t));
  dd+=sizeof(uint8_t);
  memcpy(&_hr,dd,sizeof(uint8_t));
  dd+=sizeof(uint8_t);
  memcpy(&_mn,dd,sizeof(uint8_t));
  dd+=sizeof(uint8_t);
  memcpy(&_se,dd,sizeof(uint8_t));
  dd+=sizeof(uint8_t);
  memcpy(&_ns,dd,sizeof(int32_t));
  dd+=sizeof(int32_t);
  return size();
}

const amjTime &amjTime::now(){
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  struct tm utc;
  gmtime_r(&t.tv_sec,&utc);
  _yr=utc.tm_year+1900;
  _mo=utc.tm_mon+1;
  _dy=utc.tm_mday;
  _hr=utc.tm_hour;
  _mn=utc.tm_min;
  _se=utc.tm_sec;
  _ns=t.tv_nsec;
  return *this;
}

const struct timespec &amjTime::toTimespec(){
  struct tm tmp={_se,_mn,_hr,_dy,_yr-1900,0,0,0};
  _ts.tv_sec=mktime(&tmp);
  _ts.tv_nsec=_ns;
  return _ts;
};
