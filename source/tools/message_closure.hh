//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1993 - 2003 California Institute of Technology             //
//                                                                          //
// Read the COPYING and README files, or contact 'avida@alife.org',         //
// before continuing.  SOME RESTRICTIONS MAY APPLY TO USE OF THIS FILE.     //
//////////////////////////////////////////////////////////////////////////////

#ifndef MESSAGE_CLOSURE_HH
#define MESSAGE_CLOSURE_HH

#ifndef STRING_HH
#include "string.hh"
#endif

class cMessageType;
class cString; // aggregate
class QString;

class cMessageClosure{
private:
  cMessageType &_type;
  const char *_function;
  const char *_file;
  int _line;
  int _error;
  int _op_count;
  cString _msg;
public:
  cMessageClosure(
    cMessageType &type,
    const char *function_name,
    const char *file_name,
    int line_number
  );
  ~cMessageClosure(void);
public:
  /*
  operator<< and operator() definitions for cMessageClosure.

  Any kind of input can be placed behind the operator<<, really, but try
  to not (further) overcrowd the class...

  The operator is meant to convert its input into a string for display.
  If for example you implement
    cMessageClosure &operator<<(const myClass &instance);
  then you can write a message thus:
    DemoDebug << "this is a myClass instance: " << my_instance;
  with the result:
    "Debug [Demo] this is a myClass instance: stuff in my_instance."
  */
  cMessageClosure &operator<<(char c);
  cMessageClosure &operator<<(unsigned char c);
  cMessageClosure &operator<<(int i);
  cMessageClosure &operator<<(unsigned int i);
  cMessageClosure &operator<<(long i);
  cMessageClosure &operator<<(unsigned long i);
  cMessageClosure &operator<<(float f);
  cMessageClosure &operator<<(double f);
  cMessageClosure &operator<<(const void *p);
  cMessageClosure &operator<<(const char *s);
  cMessageClosure &operator<<(const QString &s);
  /*
  QString support is implemented outside of core of avida, in qt gui, so
  that QString can remain undefined in gui-less builds.  -- kgn
  */

  cMessageClosure &operator()(char c){ return operator<<(c); }
  cMessageClosure &operator()(unsigned char c){ return operator<<(c); }
  cMessageClosure &operator()(int i){ return operator<<(i); }
  cMessageClosure &operator()(unsigned int i){ return operator<<(i); }
  cMessageClosure &operator()(long i){ return operator<<(i); }
  cMessageClosure &operator()(unsigned long i){ return operator<<(i); }
  cMessageClosure &operator()(float f){ return operator<<(f); }
  cMessageClosure &operator()(double f){ return operator<<(f); }
  cMessageClosure &operator()(const void *p){ return operator<<(p); }
  cMessageClosure &operator()(const char *s){ return operator<<(s); }
  cMessageClosure &operator()(const QString &s){ return operator<<(s); }

  /*
  cMessageClosure::va():
  
  Support for cString-based operator<< and operator() definitions in
  cMessageClosure.  Variable argument lists are formatted and printed, a
  la printf, into a temporary buffer; the contents of this buffer are
  then appended to the cString _msg.
  */
  cMessageClosure &va(const char *fmt, ...);
private:
  void prefix(void);
};

/*
you probably don't need to change these macros...
*/

// window compatibility
#ifdef WIN32
# ifndef __PRETTY_FUNCTION__
#  define __PRETTY_FUNCTION__ "<unknown on win32>"
# endif
#endif

#define _MSG_CLOSURE_FL(x)\
  cMessageClosure(\
    x,\
    __PRETTY_FUNCTION__,\
    __FILE__,\
    __LINE__\
  )

#define _INFO_MSG(type)\
  if (Info_ ## type ## _Msg.m_is_active)\
    _MSG_CLOSURE_FL(Info_ ## type ## _Msg)

#define _DEBUG_MSG(type)\
  if (Debug_ ## type ## _Msg.m_is_active)\
    _MSG_CLOSURE_FL(Debug_ ## type ## _Msg)

#define _ERROR_MSG(type)\
  if (Error_ ## type ## _Msg.m_is_active)\
    _MSG_CLOSURE_FL(Error_ ## type ## _Msg)

#define _FATAL_MSG(type)\
  if (Fatal_ ## type ## _Msg.m_is_active)\
    _MSG_CLOSURE_FL(Fatal_ ## type ## _Msg)

#define _PLAIN_MSG(type)\
  if (type ## _Msg.m_is_active)\
    _MSG_CLOSURE_FL(type ## _Msg)

#endif
