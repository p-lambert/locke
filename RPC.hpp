#pragma once

namespace locke {

namespace RPC {

enum Type {
  Unknown,
  AppendEntry,
  AppendEntryResponse,
  RequestVote,
  RequestVoteResponse
};

}

}
