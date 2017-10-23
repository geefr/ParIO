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

#include "pario.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <linux/parport.h>
#include <linux/ppdev.h>

#include <unistd.h>
#include <string>

ParIOPort::ParIOPort( const unsigned int& port )
: m_isOpen{ false }
, m_fd{ -1 }
{
  m_isOpen = open( port );
}

ParIOPort::~ParIOPort()
{
  close();
}

bool ParIOPort::is_open() const
{
  return m_isOpen;
}

bool ParIOPort::open( const unsigned int& port )
{
  if( m_isOpen )
  {
    close();
  }

  m_port.assign( "/dev/parport" );
  m_port.append( std::to_string(port) );

  // Open the dev node
  m_fd = ::open( m_port.c_str(), O_RDWR );
  if( m_fd == -1 )
  {
    perror( "open" );
    return false;
  }

  // Set the port to exclusive access
  // I seriously doubt anyone will connect
  // any printers/etc to their itg cab :)
  if( ioctl( m_fd, PPEXCL ) )
  {
    perror( "PPEXCL" );
    ::close( m_fd );
    return false;
  }

  // Claim the parallel port
  if( ioctl( m_fd, PPCLAIM ) )
  {
    perror( "PPCLAIM" );
    ::close( m_fd );
    return false;
  }

  // Set port mode
  int mode{ IEEE1284_MODE_BYTE };
  if( ioctl( m_fd, PPSETMODE, &mode ) )
  {
    perror( "PPNEGOT" );
    ioctl( m_fd, PPRELEASE );
    ::close( m_fd );
    return false;
  }

  // Set data pin direction
  int dir{ 0 };
  if( ioctl(m_fd, PPDATADIR, &dir) )
  {
    perror( "PPDATADIR" );
    ioctl( m_fd, PPRELEASE );
    ::close( m_fd );
    return false;
  }
  
  m_isOpen = true;
  return true;
}

void ParIOPort::close()
{
  if( !m_isOpen )
  {
    return;
  }

  ioctl( m_fd, PPRELEASE );
  ::close( m_fd );
  m_fd = -1;
  m_isOpen = false;
}

bool ParIOPort::write( const unsigned char& b ) const
{
  /* 
   * If we use PPSETMODE to the appropriate setting
   * we could probably use read/write for this
   * 
   * size_t toWrite{ 1 };
   * ssize_t written{ 0 };
   * written = write( m_fd, (const void*)b, toWrite );
   * return toWrite == written;
   */

  // But as we want to set the data pins directly 
  // this is easier
  if( ioctl( m_fd, PPWDATA, &b ) )
  {
    perror( "PPWDATA" );
    return false;
  }
  return true;
}

