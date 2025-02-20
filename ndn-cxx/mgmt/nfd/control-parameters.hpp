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

#ifndef NDN_CXX_MGMT_NFD_CONTROL_PARAMETERS_HPP
#define NDN_CXX_MGMT_NFD_CONTROL_PARAMETERS_HPP

#include "ndn-cxx/name.hpp"
#include "ndn-cxx/encoding/nfd-constants.hpp"
#include "ndn-cxx/mgmt/control-parameters-base.hpp"
#include "ndn-cxx/util/time.hpp"

#include <array>
#include <bitset>

namespace ndn::nfd {

/**
 * \ingroup management
 */
enum ControlParameterField {
  CONTROL_PARAMETER_NAME,
  CONTROL_PARAMETER_FACE_ID,
  CONTROL_PARAMETER_URI,
  CONTROL_PARAMETER_LOCAL_URI,
  CONTROL_PARAMETER_ORIGIN,
  CONTROL_PARAMETER_COST,
  CONTROL_PARAMETER_CAPACITY,
  CONTROL_PARAMETER_COUNT,
  CONTROL_PARAMETER_FLAGS,
  CONTROL_PARAMETER_MASK,
  CONTROL_PARAMETER_STRATEGY,
  CONTROL_PARAMETER_EXPIRATION_PERIOD,
  CONTROL_PARAMETER_FACE_PERSISTENCY,
  CONTROL_PARAMETER_BASE_CONGESTION_MARKING_INTERVAL,
  CONTROL_PARAMETER_DEFAULT_CONGESTION_THRESHOLD,
  CONTROL_PARAMETER_MTU,
  CONTROL_PARAMETER_UBOUND,
};

inline constexpr std::array CONTROL_PARAMETER_FIELD = {
  "Name"sv,
  "FaceId"sv,
  "Uri"sv,
  "LocalUri"sv,
  "Origin"sv,
  "Cost"sv,
  "Capacity"sv,
  "Count"sv,
  "Flags"sv,
  "Mask"sv,
  "Strategy"sv,
  "ExpirationPeriod"sv,
  "FacePersistency"sv,
  "BaseCongestionMarkingInterval"sv,
  "DefaultCongestionThreshold"sv,
  "Mtu"sv,
};

/**
 * \ingroup management
 * \brief Represents parameters in a ControlCommand request or response.
 * \sa https://redmine.named-data.net/projects/nfd/wiki/ControlCommand#ControlParameters
 * \details This type is copyable because it's an abstraction of a TLV type.
 */
class ControlParameters : public mgmt::ControlParametersBase
{
public:
  class Error : public tlv::Error
  {
  public:
    using tlv::Error::Error;
  };

  ControlParameters();

  explicit
  ControlParameters(const Block& block);

  template<encoding::Tag TAG>
  size_t
  wireEncode(EncodingImpl<TAG>& encoder) const;

  Block
  wireEncode() const final;

  void
  wireDecode(const Block& wire) final;

public: // getters & setters
  bool
  hasName() const
  {
    return m_hasFields[CONTROL_PARAMETER_NAME];
  }

  const Name&
  getName() const
  {
    BOOST_ASSERT(this->hasName());
    return m_name;
  }

  ControlParameters&
  setName(const Name& name)
  {
    m_wire.reset();
    m_name = name;
    m_hasFields.set(CONTROL_PARAMETER_NAME);
    return *this;
  }

  ControlParameters&
  unsetName()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_NAME);
    return *this;
  }

  bool
  hasFaceId() const
  {
    return m_hasFields[CONTROL_PARAMETER_FACE_ID];
  }

  uint64_t
  getFaceId() const
  {
    BOOST_ASSERT(this->hasFaceId());
    return m_faceId;
  }

  ControlParameters&
  setFaceId(uint64_t faceId)
  {
    m_wire.reset();
    m_faceId = faceId;
    m_hasFields.set(CONTROL_PARAMETER_FACE_ID);
    return *this;
  }

  ControlParameters&
  unsetFaceId()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_FACE_ID);
    return *this;
  }

  bool
  hasUri() const
  {
    return m_hasFields[CONTROL_PARAMETER_URI];
  }

  const std::string&
  getUri() const
  {
    BOOST_ASSERT(this->hasUri());
    return m_uri;
  }

  ControlParameters&
  setUri(const std::string& uri)
  {
    m_wire.reset();
    m_uri = uri;
    m_hasFields.set(CONTROL_PARAMETER_URI);
    return *this;
  }

  ControlParameters&
  unsetUri()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_URI);
    return *this;
  }

  bool
  hasLocalUri() const
  {
    return m_hasFields[CONTROL_PARAMETER_LOCAL_URI];
  }

  const std::string&
  getLocalUri() const
  {
    BOOST_ASSERT(this->hasLocalUri());
    return m_localUri;
  }

  ControlParameters&
  setLocalUri(const std::string& localUri)
  {
    m_wire.reset();
    m_localUri = localUri;
    m_hasFields.set(CONTROL_PARAMETER_LOCAL_URI);
    return *this;
  }

  ControlParameters&
  unsetLocalUri()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_LOCAL_URI);
    return *this;
  }

  bool
  hasOrigin() const
  {
    return m_hasFields[CONTROL_PARAMETER_ORIGIN];
  }

  RouteOrigin
  getOrigin() const
  {
    BOOST_ASSERT(this->hasOrigin());
    return m_origin;
  }

  ControlParameters&
  setOrigin(RouteOrigin origin)
  {
    m_wire.reset();
    m_origin = origin;
    m_hasFields.set(CONTROL_PARAMETER_ORIGIN);
    return *this;
  }

  ControlParameters&
  unsetOrigin()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_ORIGIN);
    return *this;
  }

  bool
  hasCost() const
  {
    return m_hasFields[CONTROL_PARAMETER_COST];
  }

  uint64_t
  getCost() const
  {
    BOOST_ASSERT(this->hasCost());
    return m_cost;
  }

  ControlParameters&
  setCost(uint64_t cost)
  {
    m_wire.reset();
    m_cost = cost;
    m_hasFields.set(CONTROL_PARAMETER_COST);
    return *this;
  }

  ControlParameters&
  unsetCost()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_COST);
    return *this;
  }

  bool
  hasCapacity() const
  {
    return m_hasFields[CONTROL_PARAMETER_CAPACITY];
  }

  uint64_t
  getCapacity() const
  {
    BOOST_ASSERT(this->hasCapacity());
    return m_capacity;
  }

  ControlParameters&
  setCapacity(uint64_t capacity)
  {
    m_wire.reset();
    m_capacity = capacity;
    m_hasFields.set(CONTROL_PARAMETER_CAPACITY);
    return *this;
  }

  ControlParameters&
  unsetCapacity()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_CAPACITY);
    return *this;
  }

  bool
  hasCount() const
  {
    return m_hasFields[CONTROL_PARAMETER_COUNT];
  }

  uint64_t
  getCount() const
  {
    BOOST_ASSERT(this->hasCount());
    return m_count;
  }

  ControlParameters&
  setCount(uint64_t count)
  {
    m_wire.reset();
    m_count = count;
    m_hasFields.set(CONTROL_PARAMETER_COUNT);
    return *this;
  }

  ControlParameters&
  unsetCount()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_COUNT);
    return *this;
  }

  bool
  hasFlags() const
  {
    return m_hasFields[CONTROL_PARAMETER_FLAGS];
  }

  uint64_t
  getFlags() const
  {
    BOOST_ASSERT(this->hasFlags());
    return m_flags;
  }

  ControlParameters&
  setFlags(uint64_t flags)
  {
    m_wire.reset();
    m_flags = flags;
    m_hasFields.set(CONTROL_PARAMETER_FLAGS);
    return *this;
  }

  ControlParameters&
  unsetFlags()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_FLAGS);
    return *this;
  }

  bool
  hasMask() const
  {
    return m_hasFields[CONTROL_PARAMETER_MASK];
  }

  uint64_t
  getMask() const
  {
    BOOST_ASSERT(this->hasMask());
    return m_mask;
  }

  ControlParameters&
  setMask(uint64_t mask)
  {
    m_wire.reset();
    m_mask = mask;
    m_hasFields.set(CONTROL_PARAMETER_MASK);
    return *this;
  }

  ControlParameters&
  unsetMask()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_MASK);
    return *this;
  }

  bool
  hasStrategy() const
  {
    return m_hasFields[CONTROL_PARAMETER_STRATEGY];
  }

  const Name&
  getStrategy() const
  {
    BOOST_ASSERT(this->hasStrategy());
    return m_strategy;
  }

  ControlParameters&
  setStrategy(const Name& strategy)
  {
    m_wire.reset();
    m_strategy = strategy;
    m_hasFields.set(CONTROL_PARAMETER_STRATEGY);
    return *this;
  }

  ControlParameters&
  unsetStrategy()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_STRATEGY);
    return *this;
  }

  bool
  hasExpirationPeriod() const
  {
    return m_hasFields[CONTROL_PARAMETER_EXPIRATION_PERIOD];
  }

  const time::milliseconds&
  getExpirationPeriod() const
  {
    BOOST_ASSERT(this->hasExpirationPeriod());
    return m_expirationPeriod;
  }

  ControlParameters&
  setExpirationPeriod(const time::milliseconds& expirationPeriod)
  {
    m_wire.reset();
    m_expirationPeriod = expirationPeriod;
    m_hasFields.set(CONTROL_PARAMETER_EXPIRATION_PERIOD);
    return *this;
  }

  ControlParameters&
  unsetExpirationPeriod()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_EXPIRATION_PERIOD);
    return *this;
  }

  bool
  hasFacePersistency() const
  {
    return m_hasFields[CONTROL_PARAMETER_FACE_PERSISTENCY];
  }

  FacePersistency
  getFacePersistency() const
  {
    BOOST_ASSERT(this->hasFacePersistency());
    return m_facePersistency;
  }

  ControlParameters&
  setFacePersistency(FacePersistency persistency)
  {
    m_wire.reset();
    m_facePersistency = persistency;
    m_hasFields.set(CONTROL_PARAMETER_FACE_PERSISTENCY);
    return *this;
  }

  ControlParameters&
  unsetFacePersistency()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_FACE_PERSISTENCY);
    return *this;
  }

  bool
  hasBaseCongestionMarkingInterval() const
  {
    return m_hasFields[CONTROL_PARAMETER_BASE_CONGESTION_MARKING_INTERVAL];
  }

  time::nanoseconds
  getBaseCongestionMarkingInterval() const
  {
    BOOST_ASSERT(this->hasBaseCongestionMarkingInterval());
    return m_baseCongestionMarkingInterval;
  }

  ControlParameters&
  setBaseCongestionMarkingInterval(time::nanoseconds interval)
  {
    m_wire.reset();
    m_baseCongestionMarkingInterval = interval;
    m_hasFields.set(CONTROL_PARAMETER_BASE_CONGESTION_MARKING_INTERVAL);
    return *this;
  }

  ControlParameters&
  unsetBaseCongestionMarkingInterval()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_BASE_CONGESTION_MARKING_INTERVAL);
    return *this;
  }

  bool
  hasDefaultCongestionThreshold() const
  {
    return m_hasFields[CONTROL_PARAMETER_DEFAULT_CONGESTION_THRESHOLD];
  }

  /** \brief Get default congestion threshold (measured in bytes).
   */
  uint64_t
  getDefaultCongestionThreshold() const
  {
    BOOST_ASSERT(this->hasDefaultCongestionThreshold());
    return m_defaultCongestionThreshold;
  }

  /** \brief Set default congestion threshold (measured in bytes).
   */
  ControlParameters&
  setDefaultCongestionThreshold(uint64_t threshold)
  {
    m_wire.reset();
    m_defaultCongestionThreshold = threshold;
    m_hasFields.set(CONTROL_PARAMETER_DEFAULT_CONGESTION_THRESHOLD);
    return *this;
  }

  ControlParameters&
  unsetDefaultCongestionThreshold()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_DEFAULT_CONGESTION_THRESHOLD);
    return *this;
  }

  bool
  hasMtu() const
  {
    return m_hasFields[CONTROL_PARAMETER_MTU];
  }

  /** \brief Get MTU (measured in bytes).
   *
   *  This value is capped at MAX_NDN_PACKET_SIZE, even if the MTU of the face is unlimited.
   */
  uint64_t
  getMtu() const
  {
    BOOST_ASSERT(this->hasMtu());
    return m_mtu;
  }

  /** \brief Set MTU (measured in bytes).
   *
   *  This value is capped at MAX_NDN_PACKET_SIZE, even if the MTU of the face is unlimited.
   */
  ControlParameters&
  setMtu(uint64_t mtu)
  {
    m_wire.reset();
    m_mtu = mtu;
    m_hasFields.set(CONTROL_PARAMETER_MTU);
    return *this;
  }

  ControlParameters&
  unsetMtu()
  {
    m_wire.reset();
    m_hasFields.reset(CONTROL_PARAMETER_MTU);
    return *this;
  }

  auto
  getPresentFields() const noexcept
  {
    return m_hasFields;
  }

public: // Flags and Mask helpers
  /**
   * \return whether bit is enabled in Mask
   * \param bit bit position within range [0, 64) (least significant bit is 0)
   */
  bool
  hasFlagBit(size_t bit) const;

  /**
   * \return bit at a position in Flags
   * \param bit bit position within range [0, 64) (least significant bit is 0)
   */
  bool
  getFlagBit(size_t bit) const;

  /**
   * \brief Set a bit in Flags.
   * \param bit bit position within range [0, 64) (least significant bit is 0)
   * \param value new value in Flags
   * \param wantMask if true, enable the bit in Mask
   */
  ControlParameters&
  setFlagBit(size_t bit, bool value, bool wantMask = true);

  /**
   * \brief Disable a bit in Mask.
   * \param bit bit position within range [0, 64) (least significant bit is 0)
   * \post If all bits are disabled, Flags and Mask fields are deleted.
   */
  ControlParameters&
  unsetFlagBit(size_t bit);

private:
  std::bitset<CONTROL_PARAMETER_UBOUND> m_hasFields;

  Name                m_name;
  uint64_t            m_faceId;
  std::string         m_uri;
  std::string         m_localUri;
  RouteOrigin         m_origin;
  uint64_t            m_cost;
  uint64_t            m_capacity;
  uint64_t            m_count;
  uint64_t            m_flags;
  uint64_t            m_mask;
  Name                m_strategy;
  time::milliseconds  m_expirationPeriod;
  FacePersistency     m_facePersistency;
  time::nanoseconds   m_baseCongestionMarkingInterval;
  uint64_t            m_defaultCongestionThreshold;
  uint64_t            m_mtu;

  mutable Block m_wire;
};

NDN_CXX_DECLARE_WIRE_ENCODE_INSTANTIATIONS(ControlParameters);

std::ostream&
operator<<(std::ostream& os, const ControlParameters& parameters);

} // namespace ndn::nfd

#endif // NDN_CXX_MGMT_NFD_CONTROL_PARAMETERS_HPP
