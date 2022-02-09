#include "Msg.pb.h"
#include "mpi.h"
#include <string>

const int RECEIVER_RANK = 0;
std::string sendString;


void runAsReceiver(const int& rank, const int& numReceivers )
{
  std::cout<<__func__<<":"<<__LINE__<<" I am a receiver"<< " | rank "<<rank<<std::endl;
  for(int i=0; i <numReceivers+1; i++)
  {
    //Only receive messages from ranks that are not the receiver
    if (i==RECEIVER_RANK)
    {
      continue;
    }
    int msgSizeBytes;
    MPI_Status status;
    //1st receive the size of the serialized protobuf
    MPI_Recv(
      &msgSizeBytes,//Buffer 
      1, //count 
      MPI_INT,//datatype
      i, //source, 
      MPI_ANY_TAG, //tag, 
      MPI_COMM_WORLD,// communicatora 
      &status //MPI_Status
      );
    std::cout<<__func__<<":"<<__LINE__<<" serialized msgSizeBytes = "<<msgSizeBytes<< " | rank "<<rank<<std::endl; 
    //Now receive the serialized protobuf
    char* recBuf  = new char(msgSizeBytes);
    MPI_Recv(
      recBuf,//Buffer 
      msgSizeBytes, //count
      MPI_BYTE, //Data type
      i, //source, 
      MPI_ANY_TAG,  //tag, 
      MPI_COMM_WORLD, //communicator, 
      &status //MPI_Status
      );
    // Convert serialized protobuf back into protobuf message
    containerizedapp::ping msg;
    msg.ParseFromString(recBuf);
    std::cout<<__func__<<":"<<__LINE__<<" received message from "
    <<" rank "<<i<< " and msg.rank = "<<msg.rank()<<" | rank "<<rank<<std::endl;

    delete [] recBuf;
  }
}

void runAsSender(const int& rank)
{
  std::cout<<__func__<<":"<<__LINE__<<" I am a sender"<< " | rank "<<rank<<std::endl;
  containerizedapp::ping msg;
  msg.set_rank(rank);
  msg.SerializeToString(&sendString);
  int msgSizeBytes=sendString.length();
  std::cout<<__func__<<":"<<__LINE__<<" serialized msgSizeBytes = "<<msgSizeBytes<< " | rank "<<rank<<std::endl;
  //1st send the size of the serialized protobuf
  int retVal = MPI_Send(
      &msgSizeBytes, //Buffer
      1, //Count
      MPI_INT, //Data type
      RECEIVER_RANK,//Desttination
      rank, //Tag
      MPI_COMM_WORLD //Communicator 
  );
  //Now send the serialized protobuf
  retVal = MPI_Send(
      sendString.c_str(), //Buffer
      msgSizeBytes, //Count
      MPI_BYTE, //Data type
      RECEIVER_RANK,//Desttination
      rank, //Tag
      MPI_COMM_WORLD //Communicator 
  );

}

int main (int argc, char** argv){
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  int numRanks, numReceivers;
  MPI_Comm_size (MPI_COMM_WORLD, &numRanks); 
  numReceivers=numRanks-1;
  if (rank == RECEIVER_RANK)
  {
    runAsReceiver(rank, numReceivers);
  }
  else
  {
    runAsSender(rank);
  }

  MPI_Finalize();

  return 0;
}
