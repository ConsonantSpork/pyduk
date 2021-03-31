add_library(duktape STATIC duktape.c)
set_target_properties(duktape PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  )
