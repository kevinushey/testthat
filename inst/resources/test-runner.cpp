#define CATCH_CONFIG_RUNNER
#include <tests/testthat.h>

namespace tests {

// Catch::Session is a singleton object, so make sure it's only ever
// constructed once.
Catch::Session& session()
{
  static Catch::Session instance;
  return instance;
}

bool run()
{
  return session().run() == 0;
}

} // namespace tests

#ifdef WARN
# undef WARN
#endif

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

extern "C" SEXP run_tests(SEXP reporterSEXP) {
  bool success = tests::run();
  return Rf_ScalarLogical(success);
}
