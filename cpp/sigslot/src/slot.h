#pragma once

#include <functional>
#include "connection.h"

namespace S
{
  template <typename FN>
  class Signal;

  template <typename FN>
  class Slot
  {
    public:
      friend Signal<FN>;
      using ConnTyp = Connection<FN>;

      Slot(const ConnectionId inId, std::function<FN>& inFn) : mConnId(inId), mConnStatus(ConnectionState::STATE_CONNECTED), mFn(inFn) {}

      template <typename... Ts>
      void operator()(Ts&&... ts)
      {
        if (IsConnected())
        {
          mFn(std::forward<Ts>(ts)...);
        }
      }

      ConnectionState GetConnectionState() const 
      {
        return mConnStatus;
      }

      void Connect()
      {
        mConnStatus = ConnectionState::STATE_CONNECTED;
      }

      void DisConnect()
      {
        mConnStatus = ConnectionState::STATE_DISCONNECTED;
      }

      bool IsConnected()
      {
        return mConnStatus == ConnectionState::STATE_CONNECTED;
      }

    private:
      ConnectionId mConnId = INVALID_CONN_ID;
      ConnectionState mConnStatus = ConnectionState::STATE_INVALID;
      std::function<FN> mFn;
  };
}


