#include "barretenberg/common/serialize.hpp"
#include "barretenberg/ecc/curves/bn254/bn254.hpp"
#include "barretenberg/ecc/scalar_multiplication/point_table.hpp"
#include "barretenberg/ecc/scalar_multiplication/scalar_multiplication.hpp"
#include "c_bind.hpp"
#include "g1.hpp"

extern "C" {

using namespace barretenberg;

WASM_EXPORT void bn254_add_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs + rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_sub_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs - rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_mul_fields(fq::in_buf left, fq::in_buf right, fq::out_buf result)
{
    auto lhs = barretenberg::fq::serialize_from_buffer(left);
    auto rhs = barretenberg::fq::serialize_from_buffer(right);
    auto r = lhs * rhs;
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_invert_field(fq::in_buf input, fq::out_buf result)
{
    auto input_to_invert = barretenberg::fq::serialize_from_buffer(input);
    auto r = input_to_invert.invert();
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_exp_field(fq::in_buf base, fq::in_buf exp, fq::out_buf result)
{
    auto base_fr = barretenberg::fq::serialize_from_buffer(base);
    auto exp_fr = barretenberg::fq::serialize_from_buffer(exp);
    auto r = base_fr.pow(exp_fr);
    barretenberg::fq::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_sqrt_field(fq::in_buf base, fq::out_buf result)
{
    // only works if the field passed in is a square residue
    auto base_fr = barretenberg::fq::serialize_from_buffer(base);
    auto result_pair = base_fr.sqrt();
    barretenberg::fq::serialize_to_buffer(result_pair.second, result);
}

WASM_EXPORT void bn254_random_point(g1::affine_element::out_buf result)
{
    auto r = barretenberg::g1::affine_element::random_element();
    barretenberg::g1::affine_element::serialize_to_buffer(r, result);
}

WASM_EXPORT void bn254_add_points(fq::in_buf p1_x, fq::in_buf p1_y, fq::in_buf p2_x, fq::in_buf p2_y, fq::out_buf x, fq::out_buf y)
{
    auto p1_x_fq = barretenberg::fq::serialize_from_buffer(p1_x);
    auto p1_y_fq = barretenberg::fq::serialize_from_buffer(p1_y);
    auto p2_x_fq = barretenberg::fq::serialize_from_buffer(p2_x);
    auto p2_y_fq = barretenberg::fq::serialize_from_buffer(p2_y);
    g1::affine_element lhs;
    lhs.x = p1_x_fq;
    lhs.y = p1_y_fq;
    g1::affine_element rhs;
    rhs.x = p2_x_fq;
    rhs.y = p2_y_fq;
    g1::affine_element normalized = lhs + rhs;
    barretenberg::fq::serialize_to_buffer(normalized.x, x);
    barretenberg::fq::serialize_to_buffer(normalized.y, y);
}

WASM_EXPORT void bn254_double_point(fq::in_buf p1_x, fq::in_buf p1_y, fq::out_buf x, fq::out_buf y)
{
    auto p1_x_fq = barretenberg::fq::serialize_from_buffer(p1_x);
    auto p1_y_fq = barretenberg::fq::serialize_from_buffer(p1_y);
    g1::affine_element lhs;
    lhs.x = p1_x_fq;
    lhs.y = p1_y_fq;
    g1::element ext_point = g1::element(lhs);
    g1::element r = ext_point.dbl();
    auto normalized = r.normalize();
    barretenberg::fq::serialize_to_buffer(normalized.x, x);
    barretenberg::fq::serialize_to_buffer(normalized.y, y);
}

WASM_EXPORT void bn254_point_scalar(uint8_t const* point, fr::in_buf scalar, fq::out_buf x, fq::out_buf y)
{
    auto buffer_point = from_buffer<barretenberg::g1::affine_element>(point);
    g1::element ext_point = g1::element(buffer_point);
    auto scalar_base = barretenberg::fr::serialize_from_buffer(scalar);
    g1::element result = ext_point * scalar_base;
    auto normalized = result.normalize();
    barretenberg::fq::serialize_to_buffer(normalized.x, x);
    barretenberg::fq::serialize_to_buffer(normalized.y, y);
}

WASM_EXPORT void bn254_naive_msm(g1::affine_element::vec_in_buf points_data, fr::vec_in_buf scalars_data, fq::out_buf x, fq::out_buf y)
{
    auto points_vec = from_buffer<std::vector<barretenberg::g1::affine_element>>(points_data);
    auto scalars_vec = from_buffer<std::vector<fr>>(scalars_data);

    g1::element result = g1::element::zero();
    for (size_t i = 0; i < points_vec.size(); ++i) {
        g1::element ext_point = g1::element(points_vec[i]);
        auto scalar_base = scalars_vec[i];
        result += ext_point * scalar_base;
    }
    auto normalized = result.normalize();
    barretenberg::fq::serialize_to_buffer(normalized.x, x);
    barretenberg::fq::serialize_to_buffer(normalized.y, y);
}

WASM_EXPORT void bn254_pippenger(g1::affine_element::vec_in_buf points_data, fr::vec_in_buf scalars_data, fq::out_buf x, fq::out_buf y)
{
    auto points_vec = from_buffer<std::vector<barretenberg::g1::affine_element>>(points_data);
    auto scalars_vec = from_buffer<std::vector<fr>>(scalars_data);
    size_t NUM_POINTS = scalars_vec.size();
    g1::affine_element* points = (g1::affine_element*)aligned_alloc(32, sizeof(g1::affine_element) * (NUM_POINTS * 2 + 1));
    for (size_t i = 0; i < NUM_POINTS; ++i) {
        points[i] = points_vec[i];
    }
    scalar_multiplication::generate_pippenger_point_table<curve::BN254>(&points[0], &points[0], NUM_POINTS);
    scalar_multiplication::pippenger_runtime_state<curve::BN254> state(NUM_POINTS);
    g1::element result = scalar_multiplication::pippenger<curve::BN254>(
        &scalars_vec[0], &points[0], NUM_POINTS, state);
    auto normalized = result.normalize();
    aligned_free(points);
    barretenberg::fq::serialize_to_buffer(normalized.x, x);
    barretenberg::fq::serialize_to_buffer(normalized.y, y);
}
}