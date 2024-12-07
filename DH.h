#ifndef DH_H
#define DH_H

#include "basic_func.h"
#include "calc_operations.h"

/**
 * @brief Finds a generator g for the given prime p and subgroup order q.
 *
 * @details The h, g satisfies the conditions:
 *          - h is in the range [2, p-2]
 *          - g ≠ 1 mod p
 *          This function uses the formula g = h^((p-1)/q) mod p where h is a randomly chosen value.
 *          
 * @param[out] g Pointer to the generator bigint** to be computed.
 * @param[in] p Prime modulus bigint**.
 * @param[in] q Subgroup order bigint**.
 * @return Success or failure status.
 *
 */
msg bi_dh_find_generator_g(OUT bigint** g, IN bigint** p, IN bigint** q);

/**
 * @brief Generates a private key for Diffie-Hellman key exchange.
 *
 * @details The key satisfies the conditions:
 *          - key is in the range [2, p-1]
 * 
 * @param[out] key Pointer to store the generated private key.
 * @param[in] q A prime number used as a modulus for the private key generation.
 * @return Status of the key generation (success or failure).
 */
msg bi_dh_private_key_gen(OUT bigint** key, IN bigint** q);

/**
 * @brief Generates a public key for Diffie-Hellman key exchange.
 *
 * @param[out] gA Pointer to store the generated public key.
 * @param[in] g Generator used for the key exchange.
 * @param[in] key Private key used to generate the public key.
 * @param[in] p Prime modulus for the key exchange.
 * @return Status of the public key generation (success or failure).
 */
msg bi_dh_public_key_gen(OUT bigint** gA, IN bigint** g, IN bigint** key, IN bigint** p);

/**
 * @brief Generates a shared session key for Diffie-Hellman key exchange.
 *
 * @param[out] gAB Pointer to store the generated session key.
 * @param[in] gB The other party's public key.
 * @param[in] key The private key of the current party.
 * @param[in] p Prime modulus for the key exchange.
 * @return Status of the session key generation (success or failure).
 */
msg bi_dh_session_key_gen(OUT bigint** gAB, IN bigint** gB, IN bigint** key, IN bigint** p);

#endif  // DH_H
