//===- All.h --------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// C+++ main header file, includes all C+++ features.
//
//===----------------------------------------------------------------------===//

#ifndef CPLUSPLUSPLUS_ALL_H
#define CPLUSPLUSPLUS_ALL_H

#include "CPlusPlusPlus.h"
#include "Features.h"

#ifdef CPLUSPLUSPLUS_ENABLE_BETTER_RANDOM
#include "Random.h"
#endif

#ifdef CPLUSPLUSPLUS_ENABLE_HIGH_LEVEL_DATA_STRUCTURES
#include "DataStructures.h"
#endif

#ifdef CPLUSPLUSPLUS_ENABLE_CONTROL_FLOW_ENHANCEMENTS
#include "ControlFlow.h"
#endif

#ifdef CPLUSPLUSPLUS_ENABLE_CONTAINER_ENHANCEMENTS
#include "Container.h"
#endif

#ifdef CPLUSPLUSPLUS_ENABLE_OOP_ENHANCEMENTS
#include "OOP.h"
#endif

#endif // CPLUSPLUSPLUS_ALL_H
