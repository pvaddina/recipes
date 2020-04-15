#pragma once

#include <vector>
#include <algorithm>

#include "connection.h"
#include "slot.h"

namespace S
{
  template<typename FN>
  class Signal
  {
    public:
      using SlotTyp = Slot<FN>;
      using ConnTyp = Connection<FN>;

      Signal() 
        : mConnIdCounter(INVALID_CONN_ID)
      {
      }

      ConnTyp Connect(std::function<FN> f)
      {
        mSlots.emplace_back(new SlotTyp(++mConnIdCounter, f));
        return ConnTyp(mSlots.back());
      }

      bool Disconnect(FN f)
      {
        bool slotDisconnected = false;
        auto foundSlot = std::find_if(mSlots.begin(), mSlots.end(), [&](const std::shared_ptr<SlotTyp>& s) -> bool {
            return f == s->mFn;
        });

        if (foundSlot != mSlots.end())
        {
          slotDisconnected = true;
          mSlots.erase(foundSlot);
        }
        return slotDisconnected;
      }

      template <typename... Ts>
      void operator()(Ts&&... ts)
      {
        for (auto& f : mSlots)
        {
          (*f)(ts...);
        }
      }

    private:
      std::list<std::shared_ptr<SlotTyp>> mSlots;
      ConnectionId mConnIdCounter;
  };
}


