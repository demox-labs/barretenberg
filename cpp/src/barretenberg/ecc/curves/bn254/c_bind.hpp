#pragma once
#include "barretenberg/common/wasm_export.hpp"
#include "barretenberg/ecc/curves/bn254/fr.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result);
}