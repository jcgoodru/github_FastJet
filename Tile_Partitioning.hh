#include<iostream>
#include<math.h>
using namespace std;

//INPUT THESE ARGUMENTS: ieta, iphi, numcores, the tile list



/*
HOW TILING WORKS: the particle field is broken up into
regions (tiles) which are arranged on a grid.  The grid
is basically a matrix, where iphi represents the rows
and ieta the columns (both ieta and iphi are integers).


The current (single core) FastJet implementation compares
every tile with its 4 Right Hand tiles.
  LRR
  L-R  (these are the LH/RH tiles)
  LLR
The multicore implementation (aka this one) subdivides
the grid into groups of tiles, then each group is sent
to a thread to execute concurrently.  The purpose behind
the partitioning of tiles is to help ensure that no two
threads access the same tile simultaneously.

This implementation works like this:
**the partitions are initially sized based on the number
  of cores.  For instance, if there are 12 cores, then
  there will be 12 partitions (4 on the long side, 3 on the short)
**there will never be less partitions than cores, but
  sometimes more partitions than cores.
**the partitions are then resized based on the number
  of rows and columns on the actual grid (iphi/ieta).
  Example: if there are 15 partitions horizontally but
  ieta is only 12 columns, then the 15 partitions will
  be reduced to 6.
**These maximum distances are based on the assumption 
  that 2 columns is the minimum ieta distance to (help)
  assure two tiles won't access the same tile.
  Like, if two tiles are horizontally adjacent, then the
  RH tile of the left guy will be the other tile (and
  locks/idling will be needed). (for iphi, min dist = 3)
**lastly, the four-level forloop assigns the tiles to
  their proper partition.  This works by scanning the
  regular grid (left to right, then down a row...) and
  storing the vectors somewhere (probably within 
  a vector of vectors), and sending them to threads to
  run concurrently.
*/






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
    TGROUP.create_thread("insert arguments and the 'vector of vectors' here");
  }
