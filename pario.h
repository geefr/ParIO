/* 
 * Copyright (c) 2017, Gareth Francis <gfrancis.dev@gmail.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PARIO_H
#define PARIO_H

#include <string>

/**
 * Class for accessing a parallel port
 */
class ParIOPort
{
  public:
    /**
     * Constructor
     * @param port The port to open (/dev/parportN)
     */
    ParIOPort( const unsigned int& port );
    ~ParIOPort();

    /**
     * @return true if the port is open, false otherwise
     */
    bool is_open() const;

    /**
     * (Re)Open a port
     * @param port The port to open (/dev/parportN)
     * @return true if the port was opened, false otherwise
     */
    bool open( const unsigned int& port );

    /**
     * Close the port
     */
    void close();

    /**
     * Write to the data pins
     * @param b Value to write
     * @return true if the data was written, false otherwise
     */
    bool write( const unsigned char& b ) const;

    /**
     * Read from the data pins
     * @param data Will be set to the state of the data pins
     * @return true if data was read, false otherwise
     */
    bool read( unsigned char& data ) const;

  private:
    /**
     * Data direction for parallel port
     * Direct mapping to values for PPDATADIR
     */
    enum class DataDirection : int
    {
      /// Data pins as output
      Output,
      /// Data pins as input
      Input
    };

    /**
     * Set direction of data pins
     * @param dir Direction to set
     * @return true if direction was set, false otherwise.
     */
    bool setDataDirection( const DataDirection& dir ) const;

    std::string m_port;
    bool m_isOpen;
    int m_fd;
    DataDirection m_dataDir;
};

#endif
