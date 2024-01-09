# frozen_string_literal: true

require "mkmf-rice"

$CPPFLAGS += " -DNDEBUG -DSIMDJSON_DISABLE_DEPRECATED_API"
$CXXFLAGS += " $(optflags)"

create_makefile "lazyjson"
