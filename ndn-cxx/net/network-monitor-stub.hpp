/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013-2025 Regents of the University of California.
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

#ifndef NDN_CXX_NET_NETWORK_MONITOR_STUB_HPP
#define NDN_CXX_NET_NETWORK_MONITOR_STUB_HPP

#include "ndn-cxx/net/network-monitor.hpp"

namespace ndn::net {

class NetworkMonitorImplStub;

/**
 * \brief A dummy NetworkMonitor for unit testing.
 */
class NetworkMonitorStub : public NetworkMonitor
{
public:
  /**
   * \brief Constructor.
   * \param capabilities The capabilities reported by getCapabilities()
   */
  explicit
  NetworkMonitorStub(uint32_t capabilities);

  /**
   * \brief Create a NetworkInterface instance.
   */
  static shared_ptr<NetworkInterface>
  makeNetworkInterface();

  /** \brief Emit the #onInterfaceAdded signal and add \p netif internally.
   *  \param netif new network interface
   *  \post getNetworkInterface(netif->getName()) == netif
   *  \post listNetworkInterfaces() contains netif
   *  \throw std::invalid_argument a network interface with the same name already exists
   */
  void
  addInterface(shared_ptr<NetworkInterface> netif);

  /** \brief Emit the #onInterfaceRemoved signal and remove \p netif internally.
   *  \param ifname network interface name
   *  \post getNetworkInterface(ifname) == nullptr
   *  \post listNetworkInterfaces() does not contains an interface with specified name
   *  \note If the specified interface name does not exist, this operation has no effect.
   */
  void
  removeInterface(const std::string& ifname);

  /** \brief Emit the #onEnumerationCompleted signal.
   *
   *  A real NetworkMonitor starts with an "enumerating" state, during which the initial
   *  information about network interfaces is collected from the OS. Upon discovering a network
   *  interface, it emits the #onInterfaceAdded signal. When the initial enumerating completes,
   *  it emits the onEnumerationCompleted signal.
   *
   *  To simulate this procedure on a newly constructed NetworkMonitorStub, the caller should
   *  invoke addInterface() once for each network interface that already exists, and then invoke
   *  emitEnumerationCompleted().
   */
  void
  emitEnumerationCompleted();

private:
  NetworkMonitorImplStub&
  getImpl();
};

} // namespace ndn::net

#endif // NDN_CXX_NET_NETWORK_MONITOR_STUB_HPP
