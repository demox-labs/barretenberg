#pragma once
#include "barretenberg/common/wasm_export.hpp"
#include "barretenberg/ecc/curves/bn254/fr.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result);

WASM_EXPORT void bn254_sub_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result);

WASM_EXPORT void bn254_mul_fields(fr::in_buf left, fr::in_buf right, fr::out_buf result);

WASM_EXPORT void bn254_invert_field(fr::in_buf input, fr::out_buf result);

WASM_EXPORT void bn254_exp_field(fr::in_buf base, fr::in_buf exp, fr::out_buf result);

WASM_EXPORT void bn254_sqrt_field(fr::in_buf base, fr::out_buf result);

}