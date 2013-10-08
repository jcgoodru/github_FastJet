#include<iostream>
#include<fstream>
#include<numeric>
#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<time.h>
using namespace std;



int main ( int argc , char *argv[] ){


/*
Currently, I'm assuming FJ will take a command-line argument.
This argument is argv[1], aka, the number of cores you're using.
*/

  if( argc == 1 ){
    int numcores = 1;
  }else{
    int numcores = argv[1];
  }




/*
This is where I'm putting threaded code for now...
Later, I'll either leave all the parallelizible
sections in here, to be run when called by the
main FJ part, or I'll put them in FJ itself.

I'm thinking:
[ pretend the following  code is located in the      ]
[ primary parts of FastJet (ClusterSequence, etc...) ]

EITHER send the flow of control to 
       this document, concurrency.hh:

   if (parallelize? = true){
     [execute threaded version, by sending the flow]
     [of control to this file.  Once the threaded  ]
     [code is done, return flow of control to the  ]
     [part of FastJet that enabled this section    ]
   }else{
     [execute the currently existing, single       ]
     [core implementation of FastJet               ]
   }

OR leave the flow of control in the
   FastJet file I pulled it from:

   if (parallelize? = true){
     [execute threaded version, which is located   ]
     [within the FastJet documents themselves      ]
   }else{
     [execute the currently existing, single       ]
     [core implementation of FastJet               ]
   }






The second implementation is easiest for me, but it
would require "clogging" the files with extra code
(which isn't necessarily a bad thing).  Nonetheless,
the code itself needs to be written, the only
difference here is the location of the concurrent
models.
*/
	
00291   vector<Tile>::const_iterator tile;
00292   for (tile = _tiles.begin(); tile != _tiles.end(); tile++) {
00293     // first do it on this tile

tile, jetA??, jetB??

00294     for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {
00295       for (jetB = tile->head; jetB != jetA; jetB = jetB->next) {
00296         double dist = _bj_dist(jetA,jetB);
00297         if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
00298         if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
00299       }
00300     }
00301     // then do it for RH tiles
00302     for (Tile ** RTile = tile->RH_tiles; RTile != tile->end_tiles; RTile++) {
00303       for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {
00304         for (jetB = (*RTile)->head; jetB != NULL; jetB = jetB->next) {
00305           double dist = _bj_dist(jetA,jetB);
00306           if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
00307           if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
00308         }
00309       }
00310     }
00311   }



//  TGROUP.create_thread(boost::bind(&TILING_292_300::compute,&ThreadedTile));

class TILING_292_311 {
  public :
    //TILING_292_311(unsigned int N) : NNdist(N) {}
    //double & operator[] (unsigned int j) {return NNdist[j];}
    void _292_300_(tile){
      for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {
       for (jetB = tile->head; jetB != jetA; jetB = jetB->next) {
         double dist = _bj_dist(jetA,jetB);
         if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
         if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
       }
      }
  //  void _302_310_(arguments referring to tile){

    //  for (Tile ** RTile = tile->RH_tiles; RTile != tile->end_tiles; RTile++) {
      //  for (jetA = tile->head; jetA != NULL; jetA = jetA->next) {
        //  for (jetB = (*RTile)->head; jetB != NULL; jetB = jetB->next) {
          //  double dist = _bj_dist(jetA,jetB);
            //if (dist < jetA->NN_dist) {jetA->NN_dist = dist; jetA->NN = jetB;}
            //if (dist < jetB->NN_dist) {jetB->NN_dist = dist; jetB->NN = jetA;}
   //       }
    //    }
     // }
    }
    protected : 
      //std::vector<double> NNdist;
};





/*this is w/o a locking mechanism, this simply
  creates a thread for every tile.  This is
  written under the assumption that each thread
  will execute whenever a core is free   */
boost::thread_group ThreadGROUP;
vector<Tile>::const_iterator ThreadedTile;
ThreadedTile = _tiles.begin();
while( ThreadedTile != _tiles.end() ){
  ThreadGROUP.create_thread(boost::bind(&TILING_292_311::_292_300_,&ThreadedTile));
  ThreadedTile++;
}
ThreadGROUP.join_all();





// with a locking mechanism (under construction)
int bool locked[numcores];
boost::thread_group ThreadGROUP;
vector<Tile>::const_iterator ThreadedTile;
ThreadedTile = _tiles.begin();

for ( int i = 0 ; i < numcores ; i++ ){
  ThreadGROUP.create_thread(/*ThreadedTile and other arguments*/)
  locked[i] = true;
  ThreadedTile++;
}







return 69;}
