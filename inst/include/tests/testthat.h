#ifndef TESTTHAT_HPP
#define TESTTHAT_HPP

#define CATCH_CONFIG_PREFIX_ALL
#define CATCH_CONFIG_NOSTDOUT

#include "vendor/catch.h"

extern "C" void Rprintf(const char*, ...);
extern "C" void R_FlushConsole();

namespace testthat {

class r_streambuf : public std::streambuf {
public:

  r_streambuf() {}

protected:

  virtual std::streamsize xsputn(const char* s, std::streamsize n) {
    Rprintf("%.*s", n, s);
    return n;
  }

  virtual int overflow(int c = EOF) {
    if (c != EOF) Rprintf("%.1s", &c);
    return c;
  }

  virtual int sync() {
    R_FlushConsole();
    return 0;
  }

};

class r_ostream : public std::ostream {

public:

  r_ostream() :
    std::ostream(new r_streambuf), pBuffer(static_cast<r_streambuf*>(rdbuf()))
  {}

private:
  r_streambuf* pBuffer;

};

} // namespace testthat

namespace Catch {

inline std::ostream& cout()
{
  static testthat::r_ostream instance;
  return instance;
}

inline std::ostream& cerr()
{
  static testthat::r_ostream instance;
  return instance;
}

} // namespace Catch

#define context(__X__, ...) CATCH_TEST_CASE(__X__ " | " __FILE__)
#define test_that CATCH_SECTION
#define expect_true CATCH_CHECK
#define expect_false CATCH_CHECK_FALSE

#endif

