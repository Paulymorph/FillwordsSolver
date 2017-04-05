//
// Created by Paul Danilin on 05/04/2017.
//

#ifndef FILLWORDSSOLVER_UTILITIES_H
#define FILLWORDSSOLVER_UTILITIES_H

/**
 * Hashes the wide char into an int with the modulus.
 * @param c the char to hash
 * @param modulus the modulus of the hash
 * @return the found hash
 */
int hash(wchar_t c, int modulus);

#endif //FILLWORDSSOLVER_UTILITIES_H
