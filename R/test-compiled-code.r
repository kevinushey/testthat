get_active_pkg <- function(test_path) {

  ## For R CMD check; check env
  env <- Sys.getenv("R_TESTTHAT_PACKAGE", unset = "")
  if (nzchar(env))
    return(env)

  ## Otherwise, check relative to test path
  path <- normalizePath(test_path)
  parent <- dirname(path)
  while (parent != path) {
    if (file.exists(file.path(path, "DESCRIPTION"))) {
      contents <- read.dcf(file.path(path, "DESCRIPTION"), all = TRUE)
      if ("Package" %in% names(contents))
        return(contents[["Package"]])
    }

    path <- parent
    parent <- dirname(path)
  }

  ""

}

has_routine <- function(package, routine) {

  resolved <- tryCatch(
    getNativeSymbolInfo(routine, PACKAGE = package),
    error = function(e) NULL
  )

  !is.null(resolved)

}

# Returns TRUE if no tests or all tests succeeded.
test_compiled_code <- function(test_path, reporter, ...) {

  package <- get_active_pkg(test_path)
  if (!nzchar(package))
    return(TRUE)

  routine <- paste(package, "run_tests", sep = "_")
  if (!has_routine(package, routine))
    return(TRUE)

  output <- ""
  status <- 1

  tryCatch(
    output <- capture.output(status <- .Call(routine, PACAKGE = package)),
    error = function(e) {
      warning(sprintf("failed to call test entrypoint '%s'", routine))
    }
  )

  if (reporter != "silent" && nzchar(output))
    cat("\nC++ unit test results:", output[-1], sep = "\n")

  status == 0

}
