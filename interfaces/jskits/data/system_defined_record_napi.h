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

#ifndef UDMF_SYSTEM_DEFINED_RECORD_NAPI_H
#define UDMF_SYSTEM_DEFINED_RECORD_NAPI_H

#include <memory>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace UDMF {
struct ContextBase;
class UnifiedRecord;
class SystemDefinedRecord;
class SystemDefinedRecordNapi {
public:
    static napi_value Constructor(napi_env env);
    static void NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out);
    static napi_value GetDetails(napi_env env, napi_callback_info info);
    static napi_value SetDetails(napi_env env, napi_callback_info info);
    std::shared_ptr<SystemDefinedRecord> value_;

private:
    static napi_value New(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void *data, void *hint);
    static SystemDefinedRecordNapi *GetSystemDefinedRecord(
        napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt);
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_SYSTEM_DEFINED_RECORD_NAPI_H