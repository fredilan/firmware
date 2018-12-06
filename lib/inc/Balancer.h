/*
 * Copyright 2018 BrewPi B.V.
 *
 * This file is part of the BrewBlox Control Library.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "ActuatorAnalog.h"
#include "ActuatorAnalogConstrained.h"
#include <algorithm>
#include <functional>
#include <vector>

namespace AAConstraints {
template <uint8_t ID>
class Balanced;
}

template <uint8_t ID>
class Balancer {
private:
    using value_t = ActuatorAnalog::value_t;
    using Balanced = AAConstraints::Balanced<ID>;

    struct Request {
        const Balanced* requester;
        value_t requested;
        value_t granted;
    };

    const value_t available = 100;

    std::vector<Request> requesters;

public:
    Balancer() = default;
    virtual ~Balancer() = default;

    void registerEntry(const Balanced* req)
    {
        requesters.push_back(Request{req, 0, available});
    }

    void unregisterEntry(const Balanced* req)
    {
        requesters.erase(std::remove_if(requesters.begin(), requesters.end(), [req](const Request& r) { return r.requester == req; }));
    }

    value_t constrain(const Balanced* req, const value_t& val)
    {
        auto match = find_if(requesters.begin(), requesters.end(), [&req](const Request& r) {
            return r.requester == req;
        });

        if (match == requesters.end()) {
            registerEntry(req);
            match = (requesters.end() - 1);
        }

        if (match != requesters.end()) {
            match->requested = val;
            return std::min(val, match->granted);
        };
        return val;
    }

    value_t granted(const Balanced* req) const
    {
        auto match = find_if(requesters.begin(), requesters.end(), [&req](const Request& r) {
            return r.requester == req;
        });

        if (match == requesters.end()) {
            return 0;
        }

        return match->granted;
    }

    void update()
    {
        auto numActuators = requesters.size();
        if (numActuators == 0) {
            return;
        }

        auto requestedTotal = value_t(0);
        for (const auto& a : requesters) {
            requestedTotal += a.requested;
        }
        auto budgetLeft = value_t(0);
        if (available > requestedTotal) {
            budgetLeft = available - requestedTotal;
            requestedTotal = available;
        }
        auto budgetLeftPerActuator = budgetLeft / numActuators;

        safe_elastic_fixed_point<10, 21, int32_t>
            scale = cnl::quotient<safe_elastic_fixed_point<21, 21, int64_t>>(available, requestedTotal);

        for (auto& a : requesters) {
            a.granted = a.requested * scale;
            a.granted += budgetLeftPerActuator;
        }
    }

    const std::vector<Request>& clients() const
    {
        return requesters;
    };
};

namespace AAConstraints {

template <uint8_t ID>
class Balanced : public Base {
private:
    const std::function<std::shared_ptr<Balancer<ID>>()> m_balancer;

public:
    explicit Balanced(
        std::function<std::shared_ptr<Balancer<ID>>()>&& balancer)
        : m_balancer(balancer)
    {
    }

    Balanced(const Balanced&) = delete;
    Balanced& operator=(const Balanced&) = delete;
    Balanced(Balanced&&) = default;
    Balanced& operator=(Balanced&&) = default;

    ~Balanced()
    {
        if (auto balancerPtr = m_balancer()) {
            balancerPtr->unregisterEntry(this);
        }
    }

    virtual value_t constrain(const value_t& val) const override final
    {
        if (auto balancerPtr = m_balancer()) {
            return balancerPtr->constrain(this, val);
        }
        return val;
    }

    virtual uint8_t id() const
    {
        return ID;
    }

    value_t granted() const
    {
        if (auto balancerPtr = m_balancer()) {
            return balancerPtr->granted(this);
        }
        return 0;
    }
    virtual uint8_t order() const override final
    {
        return 2;
    }
};
}