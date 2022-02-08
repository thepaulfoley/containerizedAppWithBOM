#include "Msg.pb.h"
#include "mpi.h"

const int RECEIVER_RANK = 0;

void runAsReceiver(const int& rank )
{
  std::cout<<__func__<<":"<<__LINE__<<" I am a receiver"<< " | rank "<<rank<<std::endl;
}

void runAsSender(const int& rank)
{
  std::cout<<__func__<<":"<<__LINE__<<" I am a sender"<< " | rank "<<rank<<std::endl;
  containerizedapp::ping msg;
}

int main (int argc, char** argv){
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  if (rank == RECEIVER_RANK)
  {
    runAsReceiver(rank);
  }
  else
  {
    runAsSender(rank);
  }

  MPI_Finalize();

  return 0;
}
