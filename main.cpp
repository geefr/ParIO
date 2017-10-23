
#include "pario.h"

#include <iostream>
#include <chrono>
#include <thread>

int main(void)
{

  ParIOPort port( 0 );
  if( !port.is_open() )
  {
    std::cerr << "Failed to open parallel port" << std::endl;
    return 1;
  }

  for( unsigned int i{0}; i < 10; ++i )
  {
    port.write( 0xFF );
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    port.write( 0x00 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
  }

  return 0;
}
