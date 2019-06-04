#include "TimerManager.hpp"

#include <SDL2/SDL.h>

#include "global.hpp"

TimerManager * TimerManager::s_pInstance = 0;

TimerManager & TimerManager::Instance ()
{
   if (!s_pInstance)
   {
      s_pInstance = new TimerManager();
   }
   return *s_pInstance;
}

TimerManager::~TimerManager ()
{}

struct TimerManagerImpl
{
   int StartTimer (float period, TimerManager::TimeoutHandler const& handler)
   {
      TimerManager::Timeout * wrapper = new TimerManager::Timeout;
      wrapper->handler = handler;
      return SDL_AddTimer((Uint32)period, SDL_oneshot_timeout_wrapper, static_cast<void *>(wrapper));
   }

   void CancelTimer (int const id)
   {
      SDL_RemoveTimer(id);
   }

private:
   static Uint32 s_timeoutEventId;

   static Uint32 SDL_oneshot_timeout_wrapper (Uint32 interval, void * actualHandlerInfo)
   {
      // SDL timers elapse on a worker thread. To avoid having to handle concurrency
      // issues, we push this event to the main event queue so that it is processed
      // on the main thread

      SDL_UserEvent userevent;
      userevent.type = s_timeoutEventId;
      userevent.code = 0; // TODO: Should be set to an application-wide unique value to signify that this is a timeout event
      userevent.data1 = actualHandlerInfo;
      userevent.data2 = 0; // unused

      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user = userevent;
      SDL_PushEvent(&event);

      return 0; // one-shot
   }
};
Uint32 TimerManagerImpl::s_timeoutEventId = SDL_RegisterEvents(1);

int TimerManager::StartTimer (float period, TimeoutHandler const& handler)
{
   return m_pImpl->StartTimer(period, handler);
}

void TimerManager::CancelTimer (int const id)
{
   m_pImpl->CancelTimer(id);
}

TimerManager::TimerManager ()
   : m_pImpl(new TimerManagerImpl())
{}
