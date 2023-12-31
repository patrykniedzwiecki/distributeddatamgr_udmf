/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
bool UnifiedDataUtils::IsValidType(int32_t value)
{
    return value >= TEXT && value < UD_BUTT;
}

bool UnifiedDataUtils::IsValidIntention(int32_t value)
{
    return value > UD_INTENTION_BASE && value < UD_INTENTION_BUTT;
}

size_t UnifiedDataUtils::GetVariantSize(UDVariant &variant)
{
    auto int32Value = std::get_if<int32_t>(&variant);
    if (int32Value != nullptr) {
        return sizeof(std::get<int32_t>(variant));
    }
    auto int64Value = std::get_if<int64_t>(&variant);
    if (int64Value != nullptr) {
        return sizeof(std::get<int64_t>(variant));
    }
    auto boolValue = std::get_if<bool>(&variant);
    if (boolValue != nullptr) {
        return sizeof(std::get<bool>(variant));
    }
    auto doubleValue = std::get_if<double>(&variant);
    if (doubleValue != nullptr) {
        return sizeof(std::get<double>(variant));
    }
    auto strValue = std::get_if<std::string>(&variant);
    if (strValue != nullptr) {
        return std::get<std::string>(variant).size();
    }
    auto vecValue = std::get_if<std::vector<uint8_t>>(&variant);
    if (vecValue != nullptr) {
        return std::get<std::vector<uint8_t>>(variant).size();
    }
    return 0;
}

size_t UnifiedDataUtils::GetDetailsSize(UDDetails &details)
{
    size_t total = 0;
    for (std::pair<std::string, UDVariant> prop : details) {
        total += prop.first.size();
        total += GetVariantSize(prop.second);
    }
    return total;
}

bool UnifiedDataUtils::IsPersist(const Intention &intention)
{
    return intention > UD_INTENTION_SYS && intention < UD_INTENTION_BUTT;
}

bool UnifiedDataUtils::IsPersist(const std::string &intention)
{
    return IsPersist(GetIntentionByString(intention));
}

Intention UnifiedDataUtils::GetIntentionByString(const std::string &intention)
{
    for (const auto &it : UD_INTENTION_MAP) {
        if (it.second == intention) {
            return static_cast<Intention>(it.first);
        }
    }
    return UD_INTENTION_BUTT;
}
} // namespace UDMF
} // namespace OHOS