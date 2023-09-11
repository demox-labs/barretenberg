#pragma once
#include "barretenberg/common/wasm_export.hpp"
#include "barretenberg/ecc/curves/bn254/fq.hpp"
#include "barretenberg/ecc/curves/bn254/g1.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result);

WASM_EXPORT void bn254_sub_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result);

WASM_EXPORT void bn254_mul_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result);

WASM_EXPORT void bn254_invert_field(fq::in_buf input, fq::out_buf result);

WASM_EXPORT void bn254_exp_field(fq::in_buf base, fq::in_buf exp, fq::out_buf result);

WASM_EXPORT void bn254_sqrt_field(fq::in_buf base, fq::out_buf result);

WASM_EXPORT void bn254_random_point(g1::affine_element::out_buf result);

WASM_EXPORT void bn254_add_points(fq::in_buf p1_x, fq::in_buf p1_y, fq::in_buf p2_x, fq::in_buf p2_y, fq::out_buf result);

WASM_EXPORT void bn254_double_point(fq::in_buf p1_x, fq::in_buf p1_y, fq::out_buf x, fq::out_buf z);
}