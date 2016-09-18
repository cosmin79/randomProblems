#include <message.h>
#include <stdio.h>
#include "oops-3.h"
#include <algorithm>

#define MASTER_NODE 7
#define DONE -1

const long long INF = (1LL << 61);

int main() {
  long long N = GetN();
  long long nodes = NumberOfNodes();
  long long my_id = MyNodeId();
  long long sliceSize = N / nodes;

  long long minV = INF, maxV = -INF;

  for (long long i = my_id; i < N; i += nodes) {
    long long curr = GetNumber(i);
    minV = std::min(minV, curr);
    maxV = std::max(maxV, curr);
  }

  PutLL(MASTER_NODE, minV);
  Send(MASTER_NODE);
  PutLL(MASTER_NODE, maxV);
  Send(MASTER_NODE);

  if (my_id == MASTER_NODE) {
    for (int node = 0; node < nodes; ++node) {
      Receive(node);
      long long remoteMin = GetLL(node);
      Receive(node);
      long long remoteMax = GetLL(node);

      minV = std::min(minV, remoteMin);
      maxV = std::max(maxV, remoteMax);
    }

    printf("%lld\n", maxV - minV);
  }
  return 0;
}
