/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2024 Regents of the University of California,
 *                         Arizona Board of Regents,
 *                         Colorado State University,
 *                         University Pierre & Marie Curie, Sorbonne University,
 *                         Washington University in St. Louis,
 *                         Beijing Institute of Technology,
 *                         The University of Memphis.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#ifndef NDN_CXX_UTIL_NOTIFICATION_SUBSCRIBER_HPP
#define NDN_CXX_UTIL_NOTIFICATION_SUBSCRIBER_HPP

#include "ndn-cxx/face.hpp"
#include "ndn-cxx/util/concepts.hpp"
#include "ndn-cxx/util/scheduler.hpp"
#include "ndn-cxx/util/signal/signal.hpp"
#include "ndn-cxx/util/time.hpp"

namespace ndn::util {

class NotificationSubscriberBase : noncopyable
{
public:
  virtual
  ~NotificationSubscriberBase();

  /** \return InterestLifetime of Interests to retrieve notifications.
   *
   *  This must be greater than FreshnessPeriod of Notification Data packets,
   *  to ensure correct operation of this subscriber implementation.
   */
  time::milliseconds
  getInterestLifetime() const
  {
    return m_interestLifetime;
  }

  bool
  isRunning() const
  {
    return m_isRunning;
  }

  /** \brief Start or resume receiving notifications.
   *  \note onNotification must have at least one listener,
   *        otherwise this operation has no effect.
   */
  void
  start();

  /** \brief Stop receiving notifications.
   */
  void
  stop();

protected:
  /** \brief Construct a NotificationSubscriber.
   *  \note The subscriber is not started after construction.
   *        User should add one or more handlers to onNotification, and invoke start().
   */
  NotificationSubscriberBase(Face& face, const Name& prefix,
                             time::milliseconds interestLifetime);

private:
  /**
   * \brief Check if the subscriber is or should be stopped.
   * \retval true if the subscriber is stopped.
   */
  bool
  shouldStop();

  void
  sendInitialInterest();

  void
  sendNextInterest();

  void
  sendInterest(const Interest& interest);

  virtual bool
  hasSubscriber() const = 0;

  void
  afterReceiveData(const Data& data);

  /** \brief Decode the Data as a notification, and deliver it to subscribers.
   *  \return whether decode was successful
   */
  virtual bool
  decodeAndDeliver(const Data& data) = 0;

  void
  afterReceiveNack(const lp::Nack& nack);

  void
  afterTimeout();

  time::milliseconds
  exponentialBackoff(const lp::Nack& nack);

public:
  /// Fires when a Nack is received.
  ndn::signal::Signal<NotificationSubscriberBase, lp::Nack> onNack;

  /// Fires when no Notification is received within getInterestLifetime() period.
  ndn::signal::Signal<NotificationSubscriberBase> onTimeout;

  /// Fires when a Data packet in the notification stream cannot be decoded as a Notification.
  ndn::signal::Signal<NotificationSubscriberBase, Data> onDecodeError;

private:
  Face& m_face;
  Name m_prefix;
  uint64_t m_lastSequenceNum = std::numeric_limits<uint64_t>::max();
  uint64_t m_lastNackSequenceNum = std::numeric_limits<uint64_t>::max();
  uint64_t m_attempts = 1;
  Scheduler m_scheduler;
  scheduler::ScopedEventId m_nackEvent;
  ScopedPendingInterestHandle m_lastInterest;
  time::milliseconds m_interestLifetime;
  bool m_isRunning = false;
};

/**
 * \brief Provides the subscriber side of a Notification Stream.
 * \tparam Notification type of Notification item, appears in payload of Data packets.
 * \sa https://redmine.named-data.net/projects/nfd/wiki/Notification
 */
template<typename Notification>
class NotificationSubscriber : public NotificationSubscriberBase
{
public:
  BOOST_CONCEPT_ASSERT((boost::DefaultConstructible<Notification>));
  BOOST_CONCEPT_ASSERT((WireDecodable<Notification>));

  /** \brief Construct a NotificationSubscriber.
   *  \note The subscriber is not started after construction.
   *        User should add one or more handlers to onNotification, and invoke .start().
   */
  NotificationSubscriber(Face& face, const Name& prefix,
                         time::milliseconds interestLifetime = 1_min)
    : NotificationSubscriberBase(face, prefix, interestLifetime)
  {
  }

public:
  /**
   * \brief Fires when a Notification is received.
   * \note Removing all handlers will cause the subscriber to stop.
   */
  ndn::signal::Signal<NotificationSubscriber, Notification> onNotification;

private:
  bool
  hasSubscriber() const override
  {
    return !onNotification.isEmpty();
  }

  bool
  decodeAndDeliver(const Data& data) override
  {
    Notification notification;
    try {
      notification.wireDecode(data.getContent().blockFromValue());
    }
    catch (const tlv::Error&) {
      return false;
    }
    onNotification(notification);
    return true;
  }
};

} // namespace ndn::util

#endif // NDN_CXX_UTIL_NOTIFICATION_SUBSCRIBER_HPP
