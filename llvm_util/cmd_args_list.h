// Copyright (c) 2018-present The Alive2 Authors.
// Distributed under the MIT license that can be found in the LICENSE file.

#include "util/config.h"
#include "util/random.h"
#include "llvm/Support/CommandLine.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace {
llvm::cl::OptionCategory alive_cmdargs("Alive2 translation validation options");

llvm::cl::list<std::string> opt_funcs(LLVM_ARGS_PREFIX "func",
  llvm::cl::desc("Specify the name of a function to verify (without @)"),
  llvm::cl::ZeroOrMore, llvm::cl::value_desc("function name"),
  llvm::cl::cat(alive_cmdargs));

set<string> func_names;

#ifdef ARGS_SRC_TGT
llvm::cl::opt<unsigned> opt_src_unrolling_factor(LLVM_ARGS_PREFIX "src-unroll",
  llvm::cl::desc("Unrolling factor for src function (default=0)"),
  llvm::cl::init(0), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<unsigned> opt_tgt_unrolling_factor(LLVM_ARGS_PREFIX "tgt-unroll",
  llvm::cl::desc("Unrolling factor for tgt function (default=0)"),
  llvm::cl::init(0), llvm::cl::cat(alive_cmdargs));
#else
llvm::cl::opt<unsigned> opt_unrolling_factor(LLVM_ARGS_PREFIX "unroll",
  llvm::cl::desc("Unrolling factor (default=0)"),
  llvm::cl::init(0), llvm::cl::cat(alive_cmdargs));
#endif

llvm::cl::opt<bool> opt_uf_float(LLVM_ARGS_PREFIX "uf-float",
  llvm::cl::desc("Map floating point operations to uninterpreted functions (default=false)"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_disable_undef(LLVM_ARGS_PREFIX "disable-undef-input",
  llvm::cl::desc("Assume inputs are not undef (default=false)"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_disable_poison(LLVM_ARGS_PREFIX "disable-poison-input",
  llvm::cl::desc("Assume inputs are not poison (default=false)"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_error_fatal(LLVM_ARGS_PREFIX "exit-on-error",
  llvm::cl::desc("Exit on error"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_se_verbose(LLVM_ARGS_PREFIX "se-verbose",
  llvm::cl::desc("Symbolic execution verbose mode"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<unsigned> opt_smt_to(LLVM_ARGS_PREFIX "smt-to",
  llvm::cl::desc("Timeout for SMT queries (default=10000)"),
  llvm::cl::init(10000), llvm::cl::value_desc("ms"),
  llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<unsigned> opt_smt_max_mem(LLVM_ARGS_PREFIX "smt-max-mem",
  llvm::cl::desc("AMT max memory (approx)"), llvm::cl::value_desc("MB"),
  llvm::cl::init(1024), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_smt_stats(LLVM_ARGS_PREFIX "smt-stats",
  llvm::cl::desc("Show SMT statistics"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<unsigned> opt_smt_random_seed(LLVM_ARGS_PREFIX "smt-random-seed",
  llvm::cl::desc("Random seed for the SMT solver (default=0)"),
  llvm::cl::init(0), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_smt_log(LLVM_ARGS_PREFIX "smt-log",
  llvm::cl::desc("Log interactions with the SMT solver"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_smt_skip(LLVM_ARGS_PREFIX "skip-smt",
  llvm::cl::desc("Skip all SMT queries"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<string> opt_smt_bench_dir(LLVM_ARGS_PREFIX "smt-bench",
  llvm::cl::desc("Dump smtlib benchmarks"),
  llvm::cl::value_desc("directory"), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_smt_verbose(LLVM_ARGS_PREFIX "smt-verbose",
  llvm::cl::desc("SMT verbose mode"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_tactic_verbose(LLVM_ARGS_PREFIX "tactic-verbose",
  llvm::cl::desc("SMT Tactic verbose mode"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

#ifdef ARGS_REFINEMENT
llvm::cl::opt<bool> opt_always_verify(LLVM_ARGS_PREFIX "always-verify",
  llvm::cl::desc("Verify transformations even if they are syntactically equal"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));
#endif

llvm::cl::opt<bool> opt_quiet(LLVM_ARGS_PREFIX "quiet",
  llvm::cl::desc("Quiet mode"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_debug(LLVM_ARGS_PREFIX "dbg",
  llvm::cl::desc("Print debugging info"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_print_dot(LLVM_ARGS_PREFIX "dot",
  llvm::cl::desc("Print .dot files of each function"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<bool> opt_alias_stats(LLVM_ARGS_PREFIX "alias-stats",
  llvm::cl::desc("Show alias sets statistics"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

#ifdef ARGS_REFINEMENT
llvm::cl::opt<bool> opt_bidirectional(LLVM_ARGS_PREFIX "bidirectional",
  llvm::cl::desc("Run refinement check in both directions"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));
#endif

llvm::cl::opt<bool> opt_elapsed_time(LLVM_ARGS_PREFIX "time-verify",
  llvm::cl::desc("Print time taken to verify each transformation"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<string> opt_outputfile(LLVM_ARGS_PREFIX "o",
  llvm::cl::desc("Specify output filename"), llvm::cl::cat(alive_cmdargs));

ofstream out_file;
ostream *out;

llvm::cl::opt<string> opt_report_dir(LLVM_ARGS_PREFIX "report-dir",
  llvm::cl::desc("Save report to disk"), llvm::cl::value_desc("directory"),
  llvm::cl::cat(alive_cmdargs));

bool report_dir_created = false;
string report_filename;

llvm::cl::opt<bool> opt_overwrite_reports(LLVM_ARGS_PREFIX "overwrite-reports",
  llvm::cl::desc("Overwrite existing report files"),
  llvm::cl::init(false), llvm::cl::cat(alive_cmdargs));

llvm::cl::opt<unsigned> opt_max_offset_in_bits(
  LLVM_ARGS_PREFIX "max-offset-in-bits", llvm::cl::init(64),
  llvm::cl::desc("Upper bound for the maximum pointer offset in bits.  Note "
                 "that this may impact correctness, if values involved in "
                 "offset computations exceed the maximum."),
  llvm::cl::cat(alive_cmdargs));

}
