#pragma once

#include <memory>

namespace S
{
  using ConnectionId = int;
  static const ConnectionId INVALID_CONN_ID = 0;

  enum class ConnectionState
  {
    STATE_CONNECTED,
    STATE_DISCONNECTED,
    STATE_INVALID
  };

  template <typename FN>
  class Slot;

  template <typename FN>
  class Connection
  {
    public:
      using SlotTyp = Slot<FN>;
      using ConnTyp = Connection<FN>;

      Connection(std::shared_ptr<SlotTyp>& pSlot) : mpSlot(pSlot) {}

      bool Disconnect() 
      {
        auto disconnSuccess = false;
        if (auto s = mpSlot.lock())
          disconnSuccess = s->Disconnect();
        return disconnSuccess;
      }

      bool Reconnect()
      {
        auto reConnSuccess = false;
        if (auto s = mpSlot.lock())
          reConnSuccess = s->Connect();
        return reConnSuccess;
      }

      ConnectionState GetState() const
      {
        ConnectionState st = ConnectionState::STATE_INVALID;
        if (auto s = mpSlot.lock())
          st = s->Reconnect();
        return st;
      }

    private:
      std::weak_ptr<SlotTyp> mpSlot;
  };
}

