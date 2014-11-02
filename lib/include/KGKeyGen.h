/*
 * KeyGen is a key- and password generator.
 * Copyright (C) 2014  offa
 * 
 * This file is part of KeyGen.
 *
 * KeyGen is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KeyGen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KeyGen.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        KGKeyGen.h
 * 
 * @version     0.1
 * @author      offa
 * @date        21.10.2014
 * 
 * Key- and password generator. For the cryptography <i>OpenSSL</i> is used.
 * Please consult the <i>OpenSSL</i> documentation for futher details.
 * 
 * @attention
 * Make sure <b><i>all</i> key buffer</b> are <b><i>always</i> cleaned</b> - 
 * <i>always</i> and <i>under all circumstances</i>!
 * 
 * @see
 * <a href=https://www.openssl.org/>OpenSSL</a>, 
 * <a href=http://wiki.openssl.org/index.php/Main_Page/>OpenSSL Wiki</a>
 */

#ifndef KEYGEN_H
#define	KEYGEN_H

#ifdef	__cplusplus
extern "C"
{
#endif
    
/** Minimum key length. */
#define KEY_MIN_LENGTH          8
    
    
    /**
     * Key output format.
     */
    enum Format
    {
        ASCII,  ///< Ascii
        ASCII_BLANKS    ///< Ascii including blanks
    };
    
    /**
     * Error codes returned by the key generator.
     */
    typedef enum 
    {
        KG_ERR_SUCCESS = 0,    ///< Success / No error
        KG_ERR_GENERAL,        ///< General error
        KG_ERR_ILL_ARGUMENT,   ///< Illegal argument
        KG_ERR_SECURITY,       ///< Security error
        KG_ERR_UNKNOWN         ///< Unknown error
    } KeyGenError;
    
    
    /** An unsigned byte. */
    typedef unsigned char UByte;
    
    
    /**
     * Generates a new key of the given length.
     * 
     * Each buffer containing keys must be cleaned using
     * <code>keygen_cleanBuffer()</code>.
     * 
     * If this function does return an error, <code>buffer</code> remains
     * untouched; all internal buffers are cleaned by this function. On
     * success,the caller is responsible for cleaning <code>buffer</code> using
     * <code>keygen_cleanBuffer()</code>.
     * 
     * Key lengths less than <code>KEY_MIN_LENGTH</code> are not allowed! If a
     * smaller key length is given, this will always return
     * <code>KG_ERR_ILL_ARGUMENT</code> immediately - without generating a key.
     * 
     * The buffer must not be <code>NULL</code> - this will return
     * <code>KG_ERR_ILL_ARGUMENT</code> immediately too.
     * 
     * @attention
     * After usage, <b>any key buffer must be cleaned using
     * <code>keygen_cleanBuffer()</code>!</b>
     * 
     * @warning
     * The caller is responsible for cleaning the buffer!
     * 
     * @remark
     * This function is <code>NULL</code>-safe. However providing
     * <code>NULL</code> will return an error without changes. This also applies
     * for <code>length</code> less than <code>1</code>.
     * 
     * @param buffer        Buffer to store the key
     * @param length        Key length (>= <code>KEY_MIN_LENGTH</code>)
     * @param format        Output format
     * @return              Returns <code>KG_ERR_SUCCESS</code> on success or
     *                      an error code
     */
    KeyGenError keygen_createKey(UByte* buffer, const unsigned int length, enum Format format);
    
    
    /**
     * Cleans the buffer <code>buffer</code>. This is done from the beginning
     * of <code>buffer</code> to the full length of <code>length</code>.
     * 
     * The buffer is <code>NULL</code> or the key length of <code>0</code> will
     * immediately return.
     * 
     * @attention
     * After usage, <b>any key buffer must be cleaned using
     * <code>keygen_cleanBuffer()</code>!</b>
     * 
     * @warning
     * The caller is responsible for cleaning the buffer!
     * 
     * @remark
     * This function is <code>NULL</code>-safe. Providing <code>NULL</code> will
     * return without changes. This also applies for <code>length</code> less
     * than <code>1</code>.
     * 
     * @param buffer        Buffer
     * @param length        Length (size) (>= 0)
     */
    void keygen_cleanBuffer(UByte* buffer, unsigned int length);
    

#ifdef	__cplusplus
}
#endif

#endif	/* KEYGEN_H */
