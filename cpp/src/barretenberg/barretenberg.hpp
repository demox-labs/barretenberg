#pragma once

// External Barretenberg C++ API
#include "common/container.hpp"
#include "common/map.hpp"
#include "common/mem.hpp"
#include "common/serialize.hpp"
#include "common/streams.hpp"
#include "common/throw_or_abort.hpp"
#include "crypto/blake2s/blake2s.hpp"
#include "crypto/blake3s/blake3s.hpp"
#include "crypto/ecdsa/ecdsa.hpp"
#include "crypto/generators/generator_data.hpp"
#include "crypto/keccak/keccak.hpp"
#include "crypto/pedersen_commitment/pedersen.hpp"
#include "crypto/pedersen_hash/pedersen.hpp"
#include "crypto/schnorr/schnorr.hpp"
#include "crypto/sha256/sha256.hpp"
#include "ecc/curves/bn254/fq.hpp"
#include "ecc/curves/bn254/fr.hpp"
#include "ecc/curves/bn254/g1.hpp"
#include "ecc/curves/grumpkin/grumpkin.hpp"
#include "numeric/random/engine.hpp"
#include "numeric/uint256/uint256.hpp"
#include "plonk/proof_system/types/proof.hpp"
#include "plonk/proof_system/verification_key/verification_key.hpp"
#include "proof_system/circuit_builder/turbo_circuit_builder.hpp"
#include "proof_system/circuit_builder/ultra_circuit_builder.hpp"
#include "proof_system/types/circuit_type.hpp"
// TODO(https://github.com/AztecProtocol/barretenberg/issues/491):
//     consider helper header(s) for serialization and other non-stdlib includes
//         - possibly: common, serialize, srs, transcript
#include "serialize/cbind.hpp"
#include "serialize/cbind_fwd.hpp"
#include "serialize/msgpack.hpp"
#include "serialize/test_helper.hpp"
#include "srs/global_crs.hpp"
#include "stdlib/commitment/pedersen/pedersen.hpp"
#include "stdlib/commitment/pedersen/pedersen_plookup.hpp"
#include "stdlib/encryption/ecdsa/ecdsa.hpp"
#include "stdlib/encryption/schnorr/schnorr.hpp"
#include "stdlib/hash/blake2s/blake2s.hpp"
#include "stdlib/hash/blake3s/blake3s.hpp"
#include "stdlib/hash/pedersen/pedersen.hpp"
#include "stdlib/merkle_tree/hash.hpp"
#include "stdlib/merkle_tree/membership.hpp"
#include "stdlib/merkle_tree/memory_store.hpp"
#include "stdlib/merkle_tree/memory_tree.hpp"
#include "stdlib/merkle_tree/merkle_tree.hpp"
// TODO(https://github.com/AztecProtocol/aztec-packages/issues/728):
//     Consider moving nullifier tree logic out of barretenberg into aztec repo
#include "stdlib/merkle_tree/nullifier_tree/nullifier_leaf.hpp"
#include "stdlib/merkle_tree/nullifier_tree/nullifier_memory_tree.hpp"
#include "stdlib/merkle_tree/nullifier_tree/nullifier_tree.hpp"
#include "stdlib/primitives/address/address.hpp"
#include "stdlib/primitives/bigfield/bigfield.hpp"
#include "stdlib/primitives/biggroup/biggroup.hpp"
#include "stdlib/primitives/bit_array/bit_array.hpp"
#include "stdlib/primitives/bool/bool.hpp"
#include "stdlib/primitives/byte_array/byte_array.hpp"
#include "stdlib/primitives/curves/bn254.hpp"
#include "stdlib/primitives/field/array.hpp"
#include "stdlib/primitives/field/field.hpp"
#include "stdlib/primitives/group/group.hpp"
#include "stdlib/primitives/packed_byte_array/packed_byte_array.hpp"
#include "stdlib/primitives/point/point.hpp"
#include "stdlib/primitives/uint/uint.hpp"
#include "stdlib/primitives/witness/witness.hpp"
#include "stdlib/recursion/aggregation_state/aggregation_state.hpp"
#include "stdlib/recursion/aggregation_state/native_aggregation_state.hpp"
#include "stdlib/recursion/verification_key/verification_key.hpp"
#include "stdlib/recursion/verifier/program_settings.hpp"
#include "stdlib/recursion/verifier/verifier.hpp"
#include "transcript/manifest.hpp"
