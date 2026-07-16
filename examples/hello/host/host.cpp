//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "edge/edge_call.h"
#include "host/keystone.h"

using namespace Keystone;

int
main(int argc, char** argv) {

  if (argc < 4) {
    std::fprintf(
        stderr,
        "Usage: %s <eapp> <runtime> <loader>\n",
        argv[0]);
    return 1;
  }

  Enclave enclave;
  Params params;

  params.setFreeMemSize(256 * 1024);
  params.setUntrustedSize(256 * 1024);

  auto result = enclave.init(argv[1], argv[2], argv[3], params);
  if (result != Error::Success) {
    std::fprintf(stderr, "Failed to initialize enclave\n");
    return 1;
  }

  enclave.registerOcallDispatch(incoming_call_dispatch);

  edge_call_init_internals(
    reinterpret_cast<uintptr_t>(enclave.getSharedBuffer()),
    enclave.getSharedBufferSize());

  std::printf("[host] Starting enclave\n");
  result = enclave.run();
  std::printf("[host] Enclave returned\n");

  return result == Error::Success ? 0 : 1;
}

//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
// #include "edge/edge_call.h"
// #include "host/keystone.h"

// using namespace Keystone;

// int
// main(int argc, char** argv) {
//   Enclave enclave;
//   Params params;

//   params.setFreeMemSize(256 * 1024);
//   params.setUntrustedSize(256 * 1024);

//   enclave.init(argv[1], argv[2], argv[3], params);

//   enclave.registerOcallDispatch(incoming_call_dispatch);
//   edge_call_init_internals(
//       (uintptr_t)enclave.getSharedBuffer(), enclave.getSharedBufferSize());

//   enclave.run();

//   return 0;
// }
