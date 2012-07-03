/**
 * Thrift server for leveldb
 * @author Dhruba Borthakur (dhruba@gmail.com)
 * Copyright 2012 Facebook
 */

#include <signal.h>
#include <DB.h>
#include <protocol/TBinaryProtocol.h>
#include <server/TSimpleServer.h>
#include <server/TConnectionContext.h>
#include <transport/TServerSocket.h>
#include <transport/TBufferTransports.h>
#include <leveldb_types.h>
#include "openhandles.h"

#include "leveldb/db.h"
#include "leveldb/write_batch.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace  Tleveldb;
using boost::shared_ptr;

extern "C" void startServer(int port);
extern "C" void stopServer(int port);

static int port = 9090;

void signal_handler(int sig) {
  switch (sig) {
  case SIGINT:
    fprintf(stderr, "Received SIGINT, stopping leveldb server");
    stopServer(port);
    break;
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, signal_handler);
  startServer(port);
  return 0;
}

