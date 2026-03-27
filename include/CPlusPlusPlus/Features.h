//===- Features.h ---------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ feature configuration header file.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_FEATURES_H
#define CPLUSPLUSPLUS_FEATURES_H

// C+++ feature configuration
// By default, all features are enabled
// Users can disable specific features by defining the corresponding macro

// Feature: let/var variable declarations
#ifndef CPLUSPLUSPLUS_DISABLE_LET_VAR
#define CPLUSPLUSPLUS_ENABLE_LET_VAR 1
#endif

// Feature: auto? optional type inference
#ifndef CPLUSPLUSPLUS_DISABLE_AUTO_OPTIONAL
#define CPLUSPLUSPLUS_ENABLE_AUTO_OPTIONAL 1
#endif

// Feature: container literal extensions
#ifndef CPLUSPLUSPLUS_DISABLE_CONTAINER_LITERALS
#define CPLUSPLUSPLUS_ENABLE_CONTAINER_LITERALS 1
#endif

// Feature: defer statement
#ifndef CPLUSPLUSPLUS_DISABLE_DEFER
#define CPLUSPLUSPLUS_ENABLE_DEFER 1
#endif

// Feature: ? error propagation operator
#ifndef CPLUSPLUSPLUS_DISABLE_ERROR_PROPAGATION
#define CPLUSPLUSPLUS_ENABLE_ERROR_PROPAGATION 1
#endif

// Feature: |> pipe operator
#ifndef CPLUSPLUSPLUS_DISABLE_PIPE_OPERATOR
#define CPLUSPLUSPLUS_ENABLE_PIPE_OPERATOR 1
#endif

// Feature: if let/while let pattern matching
#ifndef CPLUSPLUSPLUS_DISABLE_PATTERN_MATCHING
#define CPLUSPLUSPLUS_ENABLE_PATTERN_MATCHING 1
#endif

// Feature: _ default argument placeholder
#ifndef CPLUSPLUSPLUS_DISABLE_DEFAULT_ARG_PLACEHOLDER
#define CPLUSPLUSPLUS_ENABLE_DEFAULT_ARG_PLACEHOLDER 1
#endif

// Feature: @property annotation
#ifndef CPLUSPLUSPLUS_DISABLE_PROPERTY
#define CPLUSPLUSPLUS_ENABLE_PROPERTY 1
#endif

// Feature: interface keyword
#ifndef CPLUSPLUSPLUS_DISABLE_INTERFACE
#define CPLUSPLUSPLUS_ENABLE_INTERFACE 1
#endif

// Feature: multi-container parallel for loops
#ifndef CPLUSPLUSPLUS_DISABLE_PARALLEL_FOR
#define CPLUSPLUSPLUS_ENABLE_PARALLEL_FOR 1
#endif

// Feature: Better Random library
#ifndef CPLUSPLUSPLUS_DISABLE_BETTER_RANDOM
#define CPLUSPLUSPLUS_ENABLE_BETTER_RANDOM 1
#endif

// Feature: High-level data structures
#ifndef CPLUSPLUSPLUS_DISABLE_HIGH_LEVEL_DATA_STRUCTURES
#define CPLUSPLUSPLUS_ENABLE_HIGH_LEVEL_DATA_STRUCTURES 1
#endif

// Feature: String utilities
#ifndef CPLUSPLUSPLUS_DISABLE_STRING_UTILITIES
#define CPLUSPLUSPLUS_ENABLE_STRING_UTILITIES 1
#endif

// Feature: File IO utilities
#ifndef CPLUSPLUSPLUS_DISABLE_FILE_IO_UTILITIES
#define CPLUSPLUSPLUS_ENABLE_FILE_IO_UTILITIES 1
#endif

// Feature: Time utilities
#ifndef CPLUSPLUSPLUS_DISABLE_TIME_UTILITIES
#define CPLUSPLUSPLUS_ENABLE_TIME_UTILITIES 1
#endif

// Feature: Control flow enhancements
#ifndef CPLUSPLUSPLUS_DISABLE_CONTROL_FLOW_ENHANCEMENTS
#define CPLUSPLUSPLUS_ENABLE_CONTROL_FLOW_ENHANCEMENTS 1
#endif

// Feature: Container enhancements
#ifndef CPLUSPLUSPLUS_DISABLE_CONTAINER_ENHANCEMENTS
#define CPLUSPLUSPLUS_ENABLE_CONTAINER_ENHANCEMENTS 1
#endif

// Feature: OOP enhancements
#ifndef CPLUSPLUSPLUS_DISABLE_OOP_ENHANCEMENTS
#define CPLUSPLUSPLUS_ENABLE_OOP_ENHANCEMENTS 1
#endif

#endif // CPLUSPLUSPLUS_FEATURES_H
