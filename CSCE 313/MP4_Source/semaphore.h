/*  CHANGE THIS
    File: semaphore.H

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/11

*/

#ifndef _semaphore_H_                   // include file only once
#define _semaphore_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <pthread.h>

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS   S e m a p h o r e  */
/*--------------------------------------------------------------------------*/

class Semaphore {
private:
  /* -- INTERNAL DATA STRUCTURES
     You may need to change them to fit your implementation. */

  int             value;
  pthread_mutex_t m;
  pthread_cond_t  c;

public:

  /* -- CONSTRUCTOR/DESTRUCTOR */

  Semaphore(int _val)
  {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    value = _val;
  }

  ~Semaphore()
  {
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
  }

  /* -- SEMAPHORE OPERATIONS */

  int P()  // This is the lock
  {
    int error_num;
    
    if(error_num = pthread_mutex_lock(&m) != 0)
    {
      return error_num;
    }

    while(value <= 0)
    {
      if(error_num = pthread_cond_wait(&c, &m) != 0)
      {
        return error_num;
      }
    }
    
    --value;
    
    if (error_num = pthread_mutex_unlock(&m) != 0)
    {
      return error_num;
    }

    return 0;
  }

  int V()  // This is the unlock
  {
    int error_num;
    
    if(error_num = pthread_mutex_lock(&m)!= 0)
    {
      return error_num;
    }     

    ++value;

    if(error_num = pthread_cond_broadcast(&c) != 0)
    {
      return error_num;
    }

    // This is the broadcast signal
    if(error_num = pthread_cond_unlock(&m) != 0)
    {
      return error_num;
    }
  
    return 0;
  }
};

#endif