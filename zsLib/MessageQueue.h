/*
 *  Created by Robin Raymond.
 *  Copyright 2009-2013. Robin Raymond. All rights reserved.
 *
 * This file is part of zsLib.
 *
 * zsLib is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (LGPL) as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * zsLib is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with zsLib; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 */

#pragma once

#ifndef ZSLIB_MESSAGEQUEUE_H_3b3e04ed0435a1db72915c7519694f0f
#define ZSLIB_MESSAGEQUEUE_H_3b3e04ed0435a1db72915c7519694f0f

#include <zsLib/types.h>

namespace zsLib
{
  interaction IMessageQueueMessage
  {
    virtual const char *getDelegateName() const = 0;
    virtual const char *getMethodName() const = 0;

    virtual void processMessage() = 0;
  };

  interaction IMessageQueueNotify
  {
    virtual void notifyMessagePosted() = 0;
  };

  interaction IMessageQueue
  {
    typedef size_t size_type;

    virtual void post(IMessageQueueMessagePtr message) = 0;

    virtual size_type getTotalUnprocessedMessages() const = 0;
  };
}

#include <zsLib/internal/zsLib_MessageQueue.h>

namespace zsLib
{
  class MessageQueue : public internal::MessageQueue
  {
  private:
    MessageQueue(IMessageQueueNotifyPtr notify);

  public:
    static MessageQueuePtr create(IMessageQueueNotifyPtr notify);

    virtual void post(IMessageQueueMessagePtr message);

    virtual size_type getTotalUnprocessedMessages() const;

    void process();
    void processOnlyOneMessage();
  };
}

#endif //ZSLIB_MESSAGEQUEUE_H_3b3e04ed0435a1db72915c7519694f0f
