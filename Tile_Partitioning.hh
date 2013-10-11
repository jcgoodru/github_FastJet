#include<iostream>
#include<math.h>
using namespace std;

//ARGUMENTS NEEDED: ieta, iphi, numcores, the tile list




/*
Initially, the number of cores will dictate how many
subsections of the tiling region to create (at least
one for each core)
*/
  int _ieta_partitions = sqrt( numcores );
  int _iphi_partitions = sqrt( numcores );
  double check = sqrt( numcores );

  if ( check != sqrt( numcores )){
    if ( ieta >= iphi ){
      _ieta_partitions = ceil( sqrt( numcores ));
      _iphi_partitions = _ieta_partitions - 1;
    } else {
      _ieta_partitions = floor( sqrt( numcores ));
      _iphi_partitions = _ieta_partitions + 1;
    }
  }



/*
Now, we need to ensure that we're not making too many
threads.  For instance, if there's 10 tiles, we don't
need 32 threads.
*/
  if ( _ieta_partitions > ceil( ( ieta / 2 ) ) ){
    _ieta_partitions = ceil( ( ieta / 2 ) );
  }
  if ( _iphi_partitions > ceil( ( iphi / 3 ) ) ){
    _iphi_partitions = ceil( ( iphi / 3 ) );
  }
/*
The 2 and 3 come from the minimum distance needed to
(somewhat) ensure that two tiles don't access the
same RH tile at the same time.
*/





  int _ieta_PT_size = ceil( ieta / _ieta_partitions )
  int _iphi_PT_size = ceil( iphi / _iphi_partitions )
/***************
I need to create an array/vector to store these tiles.
The a/v needs to be (_ieta_partitions)*(_iphi_partitions)
entries long, and each entry is a list of the tiles in
it's respective partition.
***************/
  
/*
m is a row, i is a column.  These are relative to the actual
tiled grid.  ROWS and COLS are relative to the partitioned
grid.  ROWS and COLS are used to designate which partition-
slash-thread to put the tiles in.
*/
  for ( int ROWS = 0 ; ROWS < _iphi_partitions ; ROWS++){
    for ( int COLS = 0 ; COLS < _ieta_partitions ; COLS++){
      for ( int m = 0 ; m < iphi ; m++ ){
        for ( int i = ( m * ieta + COLS * _ieta_PT_size ) ; i < (( COLS + 1 ) * _ieta_PT_size ) ; i++){

      //store these in an array or vector...or something threadable
      //"add vector<Tile>[i] into LISTOF[ROWS * _ieta_partitions + COLS]

        }
      }
    }
  }



/*
Lastly, send the new tile vector entries
(which should be lists of tiles) to various threads.
*/
  boost::thread_group TGROUP;
  for ( int i = 0 ; i < ( _ieta_partitions * _iphi_partitions ) ; i++ ){
    TGROUP.create_thread("insert arguments and the 'list of tiles' here");
  }
