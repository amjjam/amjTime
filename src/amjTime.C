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
  updateTimespec();
  return size();
}

const amjTime &amjTime::now(){
  clock_gettime(CLOCK_REALTIME,&_ts);
  return fromTimespec(_ts);
}

amjTime &amjTime::fromTimespec(const struct timespec &t){
  struct tm utc;
  gmtime_r(&t.tv_sec,&utc);
  _yr=utc.tm_year+1900;
  _mo=utc.tm_mon+1;
  _dy=utc.tm_mday;
  _hr=utc.tm_hour;
  _mn=utc.tm_min;
  _se=utc.tm_sec;
  _ns=t.tv_nsec;
  _ts=t;
  return *this;
}

amjTime amjTime::operator+(double s) const {
  amjTime t = *this;
  t += s;
  return t;
}

double amjTime::operator-(const amjTime &tm) const{
  return (_ts.tv_sec-tm._ts.tv_sec+(double)(_ts.tv_nsec-tm._ts.tv_nsec)/1e9);
}

amjTime &amjTime::operator+=(double s){
  long is=(long)s;
  _ts.tv_sec+=is;
  _ts.tv_nsec+=(long)((s-is)*1e9);
  if(_ts.tv_nsec>=1000000000L){
    _ts.tv_sec++;
    _ts.tv_nsec-=1000000000L;
  }
  else if(_ts.tv_nsec<0){
    _ts.tv_sec--;
    _ts.tv_nsec+=1000000000L;
  }
  return fromTimespec(_ts);
}

amjTime amjTime::Now(){
  amjTime t;
  t.now();
  return t;
}

void amjTime::updateTimespec(){
  struct tm tmp = {};
  tmp.tm_year = _yr - 1900;
  tmp.tm_mon  = _mo - 1;
  tmp.tm_mday = _dy;
  tmp.tm_hour = _hr;
  tmp.tm_min  = _mn;
  tmp.tm_sec  = _se;

  _ts.tv_sec  = timegm(&tmp);
  _ts.tv_nsec = _ns;
}
