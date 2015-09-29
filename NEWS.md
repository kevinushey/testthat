# testthat 0.10.0.9000

* New `expect_silent()` ensures that code produces no output, messages,
  or warnings (#261).

* `expect_output()`, `expect_message()`, `expect_warning()`, and
  `expect_error()` now accept `NA` as the second argument to indicate that
  output, messages, warnings, and errors should be absent (#219).

* Praise gets more diverse thanks to the praise package, and you'll now
  get random encouragment if your tests don't pass.

* testthat no longer muffles warning messages. If you don't want to see them 
  in your output, you need to explicitly quiet them, or use an expectation that 
  captures them (e.g. `expect_warning()`). (#254)

* Use tests in `inst/tests` is formally deprecated. Please move them into
  `tests/testthat` instead (#231).

* `expect_match()` now encodes the match, as well as the output, in the 
  expectation message (#232).

* `expect_is()` gives better failure message when testing multiple inheritance,
  e.g. `expect_is(1:10, c("glm", "lm"))` (#293).

* Corrected argument order in `compare.numeric()` (#294).

* `comparison()` constructure now checks its arguments are the correct type and
  length. This bugs a bug where tests failed with an error like "values must be 
  length 1, but FUN(X[[1]]) result is length 2" (#279).

* Added `skip_on_os()`, to skip tests on specified operating systems
  (@kevinushey).

* Skip test that depends on `devtools` if it is not installed (#247, @krlmlr)

* Added `skip_on_appveyor()` to skip tests on Appveyor (@lmullen).

* `compare()` shows detailed output of differences for character vectors of
  different length (#274, @krlmlr).

* Detailed output from `expect_equal()` doesn't confuse expected and actual
  values anymore (#274, @krlmlr).

# testthat 0.10.0

* Failure locations are now formated as R error locations.

* The [Catch](https://github.com/philsquared/Catch) unit
  testing library can now be used for unit testing of C++
  files. You can place C++ files within the `tests/testthat/cpp`
  folder named as `test-*.cpp`, and `test_dir()` and friends
  will automatically compile and run tested examples. See
  `system.file(package = "testthat", "resources", "test-example.cpp")`
  for a sample file using `Catch` and `testthat`.

* Deprecated `library_if_available()` has been removed.

* test (`test_dir()`, `test_file()`, `test_package()`, `test_check()`) functions 
  now return a `testthat_results` object that contains all results, and can be 
  printed or converted to data frame.

* `test_dir()`, `test_package()`, and `test_check()` have an added `...`
  argument that allows filtering of test files using, e.g., Perl-style regular
  expressions,or `fixed` character filtering. Arguments in `...` are passed to
  `grepl()` (@leeper).

* `test_check()` uses a new reporter specifically designed for `R CMD check`.
  It displays a summary at the end of the tests, designed to be <13 lines long
  so test failures in `R CMD check` display something more useful. This will
  hopefully stop BDR from calling testthat a "test obfuscation suite" (#201).

* `compare()` is now documented and exported. Added a numeric method so when
  long numeric vectors don't match you'll see some examples of where the
  problem is (#177). The line spacing in `compare.character()` was
  tweaked.

* `skip_if_not_installed()` skips tests if a package isn't installed (#192).

* `expect_that(a, equals(b))` style of testing has been soft-deprecated.
  It will keep working, but it's no longer demonstrated any where, and new
  expectations will only be available in `expect_equal(a, b)` style. (#172)

* Once again, testthat suppresses messages and warnings in tests (#189)

* New `test_examples()` lets you run package examples as tests. Each example
  counts as one expectation and it succeeds if the code runs without errors
  (#204).

* New `succeed()` expectation always succeeds.

* `skip_on_travis()` allows you to skip tests when run on Travis CI.
  (Thanks to @mllg)

* `colourise()` was removed. (Colour is still supported, via the `crayon` 
  package.)

* Mocks can now access values local to the call of `with_mock` (#193, @krlmlr).

* All equality expectations are now documented together (#173); all
  matching expectations are also documented together.

# testthat 0.9.1

* Bump R version dependency

# testthat 0.9

## New features

* BDD: testhat now comes with an initial behaviour driven development (BDD)
  interface. The language is similiar to RSpec for Ruby or Mocha for JavaScript.
  BDD tests read like sentences, so they should make it easier to understand
  the specification of a function. See `?describe()` for further information
  and examples.

* It's now possible to `skip()` a test with an informative message - this is
  useful when tests are only available under certain conditions, as when
  not on CRAN, or when an internet connection is available (#141).

* `skip_on_cran()` allows you to skip tests when run on CRAN. To take advantage
  of this code, you'll need either to use devtools, or run
  `Sys.setenv(NOT_CRAN = "true"))`

* Simple mocking: `with_mock()` makes it easy to temporarily replace
  functions defined in packages. This is useful for testing code that relies
  on functions that are slow, have unintended side effects or access resources
  that may not be available when testing (#159, @krlmlr).

* A new expectation, `expect_equal_to_reference()` has been added. It
  tests for equality to a reference value stored in a file (#148, @jonclayden).

## Minor improvements and bug fixes

* `auto_test_package()` works once more, and now uses `devtools::load_all()`
  for higher fidelity loading (#138, #151).

* Bug in `compare.character()` fixed, as reported by Georgi Boshnakov.

* `colourise()` now uses option `testthat.use_colours` (default: `TRUE`). If it
  is `FALSE`, output is not colourised (#153, @mbojan).

* `is_identical_to()` only calls `all.equal()` to generate an informative
  error message if the two objects are not identical (#165).

* `safe_digest()` uses a better strategy, and returns NA for directories
  (#138, #146).

* Random praise is renabled by default (again!) (#164).

* Teamcity reporter now correctly escapes output messages (#150, @windelinckx).
  It also uses nested suites to include test names.

## Deprecated functions

* `library_if_available()` has been deprecated.

# testthat 0.8.1

* Better default environment for `test_check()` and `test_package()` which
  allows S4 class creation in tests

* `compare.character()` no longer fails when one value is missing.

# testthat 0.8

testthat 0.8 comes with a new recommended structure for storing your tests. To
better meet CRAN recommended practices, testthat now recommend that you to put
your tests in `tests/testthat`, instead of `inst/tests` (this makes it
possible for users to choose whether or not to install tests). With this
new structure, you'll need to use `test_check()` instead of `test_packages()`
in the test file (usually `tests/testthat.R`) that runs all testthat unit
tests.

The other big improvement to usability comes from @kforner, who contributed
code to allow the default results (i.e. those produced by `SummaryReporter`)
to include source references so you can see exactly where failures occured.

## New reporters

* `MultiReporter`, which combines several reporters into one.
  (Thanks to @kforner)

* `ListReporter`, which captures all test results with their file,
  context, test and elapsed time. `test_dir`, `test_file`, `test_package` and
  `test_check` now use the `ListReporter` to invisibly  return a summary of
  the tests as a data frame. (Thanks to @kforner)

* `TeamCityReporter` to produce output compatible with the TeamCity
  continuous integration environment. (Thanks to @windelinckx)

* `SilentReporter` so that  `testthat` can test calls to `test_that`.
  (Thanks to @craigcitro, #83)

## New expectations

* `expect_null()` and `is_null` to check if an object is NULL (#78)

* `expect_named()` and `has_names()` to check the names of a vector (#79)

* `expect_more_than()`, `is_more_than()`, `expect_less_than()`,
  `is_less_than()` to check values above or below a threshold.
  (#77, thanks to @jknowles)

## Minor improvements and bug fixes

* `expect_that()` (and thus all `expect_*` functions) now invisibly return
  the expectation result, and stops if info or label arguments have
  length > 1 (thanks to @kforner)

* fixed two bugs with source_dir(): it did not look for the source scripts
  at the right place, and it did not use its `chdir` argument.

* When using `expect_equal()` to compare strings, the default output for
  failure provides a lot more information, which should hopefully help make
  finding string mismatches easier.

* `SummaryReporter` has a `max_reports` option to limit the number of detailed
  failure reports to show. (Thanks to @crowding)

* Tracebacks will now also contain information about where the functions came
  from (where that information is available).

* `matches` and `expect_match` now pass additional arguments on to `grepl` so
  that you can use `fixed = TRUE`, `perl = TRUE` or `ignore.case = TRUE` to
  control details of the match. `expect_match` now correctly fails to match
  NULL. (#100)

* `expect_output`, `expect_message`, `expect_warning` and `expect_error`
  also pass ... on to `grepl`, so that you can use  `fixed = TRUE`,
  `perl = TRUE` or `ignore.case = TRUE`

* Removed `stringr` and `evaluate` dependencies.

* The `not()` function makes it possible to negate tests. For example,
  `expect_that(f(), not(throws_error()))` asserts that `f()` does not
  throw an error.

* Make `dir_state` less race-y. (Thanks to @craigcitro, #80)

* `auto_test` now pays attention to its 'reporter' argument (Thanks to @crowding, #81)

* `get_reporter()`, `set_reporter()` and `with_reporter()` are now
  exported (#102)


# testthat 0.7.1

* Ignore attributes in `is_true` and `is_false` (#49)

* `make_expectation` works for more types of input (#52)

* Now works better with evaluate 0.4.3.

* new `fail()` function always forces a failure in a test. Suggested by
  Richie Cotton (#47)

* Added `TapReporter` to produce output compatible with the "test anything
  protocol". Contributed by Dan Keshet.

* Fixed where `auto_test` would identify the wrong files as having changed.
  (Thanks to Peter Meilstrup)

# testthat 0.7

* `SummaryReporter`: still return informative messages even if no tests
  defined (just bare expectations). (Fixes #31)

* Improvements to reference classes (Thanks to John Chambers)

* Bug fixes for when nothing was generated in `gives_warning` /
  `shows_message`. (Thanks to Bernd Bischl)

* New `make_expectation` function to programmatically generate an equality
  expectation. (Fixes #24)

* `SummaryReporter`: You don't get praise until you have some tests.

* Depend on `methods` rather than requiring it so that testthat works when run
  from `Rscript`

* `auto_test` now normalises paths to enable better identification of file
  changes, and fixes bug in instantiating new reporter object.

# testthat 0.6

* All `mutatr` classes have been replaced with ReferenceClasses.

* Better documentation for short-hand expectations.

* `test_dir` and `test_package` gain new `filter` argument which allows you to
   restrict which tests are run.

# testthat 0.5

* bare expectations now correctly throw errors again

# testthat 0.4

* autotest correctly loads code and executes tests in same environment

* contexts are never closed before they are opened, and always closed at the
  end of file

* fixed small bug in `test_dir` where each test was not given its own
  environment

* all `expect_*` short cut functions gain a label argument, thanks to Steve
  Lianoglou

# testthat 0.3

* all expectations now have a shortcut form, so instead of
     expect_that(a, is_identical_to(b))
  you can do
     expect_identical(a, b)

* new shows_message and gives_warning expectations to test warnings and
  messages

* expect_that, equals, is_identical_to and is_equivalent to now have
  additional label argument which allows you to control the appearance of the
  text used for the expected object (for expect_that) and actual object (for
  all other functions) in failure messages. This is useful when you have loops
  that run tests as otherwise all the variable names are identical, and it's
  difficult to tell which iteration caused the failure.

* executing bare tests gives nicer output

* all expectations now give more information on failure to make it easier to
  track down the problem.

* test_file and test_dir now run in code in separate environment to avoid
  pollution of global environment. They also temporary change the working
  directory so tests can use relative paths.

* test_package makes it easier to run all tests in an installed package. Code
  run in this manner has access to non-exported functions and objects. If any
  errors or failures occur, test_package will throw an error, making it
  suitable for use with R CMD check.

# testthat 0.2

* colourise also works in screen terminal

* equals expectation provides more information about failure

* expect_that has extra info argument to allow you to pass in any extra
  information you'd like included in the message - this is very helpful if
  you're using a loop to run tests

* is_equivalent_to: new expectation that tests for equality ignoring
  attributes

* library_if_available now works! (thanks to report and fix from Felix
  Andrews)

* specify larger width and join pieces back together whenever deparse used
  (thanks to report and fix from Felix Andrews)

* test_dir now looks for any files starting with test (not test- as before)
