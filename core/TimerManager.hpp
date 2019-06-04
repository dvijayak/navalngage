#ifndef TimerManager_hpp
#define TimerManager_hpp

#include <functional>
#include <memory>

class TimerManagerImpl;

class TimerManager
{
public:
   ~TimerManager ();

   static TimerManager & Instance ();

   using TimeoutHandler = std::function<void (void)>;
   /// One-shot timer.
   /// Returns a unique ID that can be used to cancel a running timer.
   int StartTimer (float period, TimeoutHandler const& handler);
   void CancelTimer (int const id);

   /// Wraps the provided handler so that it is C-API-friendly.
   /// Code that processes the timeout can access the handler member
   /// through a pointer to the (usually heap-allocated) wrapper.
   /// (Courtesy of https://stackoverflow.com/a/47063656)
   /// NOTE: Code that processes the timeout is responsible for freeing it!!!
   struct Timeout
   {
      TimeoutHandler handler;
   };

private:
   TimerManager ();
   static TimerManager * s_pInstance;

   std::unique_ptr<TimerManagerImpl> m_pImpl;
};

#endif