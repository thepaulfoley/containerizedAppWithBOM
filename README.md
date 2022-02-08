# containerizedAppWithBOM
Simple C++ application demonstrating containerizing an application needing a BOM consisting of several different tools. The implication will make use of the following software as part of its BOM:
- MPI
- log4cxx
- Googgle protocol buffers

## Description
- Application will launch N processes with one process waiting to receive  a protobuf message. Each process will log when they send their proto-buff to the receiver and the receiver will login message each time they receive a proto-buff and when they have received all protobuf and can exit.

