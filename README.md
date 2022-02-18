# containerizedAppWithBOM
Simple C++ application demonstrating containerizing an application needing a BOM consisting of several different tools. The application will make use of the following software as part of its BOM:
- MPI
- Google protocol buffers

## Description
- Application will launch N processes with one process waiting to receive a protobuf message. Each process will log when they send their protobuf to the receiver and the receiver will log a message each time it receives a protobuf and when it has received all protobufs and can exit.

