#define CATCH_CONFIG_RUNNER

extern "C" void exit_override(int) {}

#define exit exit_override
#include <tests/testthat.h>
#undef exit

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

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

extern "C" SEXP testthat_run_tests(SEXP reporterSEXP) {
  bool success = tests::run();
  return Rf_ScalarLogical(success);
}
