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

#include "udmf_client_fuzzer.h"

#include <unistd.h>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

#include "udmf_client.h"
#include "text.h"
#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "file.h"
#include "image.h"
#include "video.h"
#include "system_defined_record.h"
#include "system_defined_form.h"
#include "system_defined_appitem.h"
#include "system_defined_pixelmap.h"

using namespace OHOS;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;

namespace OHOS {
void SetHapToken()
{
    HapInfoParams info = {
        .userID = 100,
        .bundleName = "ohos.test.demo",
        .instIndex = 0,
        .appIDDesc = "ohos.test.demo"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo",
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
                .label = "label",
                .labelId = 1,
                .description = "test",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.test",
                .isGeneral = true,
                .resDeviceID = {"local"},
                .grantStatus = {PermissionState::PERMISSION_GRANTED},
                .grantFlags = {1}
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void SetUpTestCase()
{
    SetHapToken();
}

void TearDown()
{
}

void SetNativeToken()
{
    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 0,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = nullptr,
        .acls = nullptr,
        .processName = "msdp_sa",
        .aplStr = "system_core",
    };
    auto tokenId = GetAccessTokenId(&infoInstance);
    SetSelfTokenID(tokenId);
    AccessTokenKit::ReloadNativeTokenInfo();
}

void SetDataTextFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    UnifiedData unifiedData;
    CustomOption option = {.intention = Intention::UD_INTENTION_BUTT};
    Text text;
    UDDetails details;
    details.insert({skey, svalue});
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    unifiedData.AddRecord(record);
    std::string key;
    UdmfClient::GetInstance().SetData(option, unifiedData, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataPlainTextFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    PlainText plainText1;
    UDDetails details1;
    details1.insert({skey, svalue});
    plainText1.SetDetails(details1);
    plainText1.SetContent(svalue + "content");
    plainText1.SetAbstract(svalue + "abstract");
    plainText1.GetContent();
    plainText1.GetAbstract();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<PlainText>(plainText1);
    data1.AddRecord(record1);
    std::string key;
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataHtmlFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    Html html1;
    UDDetails details1;
    details1.insert({skey, svalue});
    html1.SetDetails(details1);
    html1.SetHtmlContent(svalue + "htmlcontent");
    html1.SetPlainContent(svalue + "plainContent");
    html1.GetHtmlContent();
    html1.GetPlainContent();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Html>(html1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataLinkFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    Link link1;
    UDDetails details1;
    details1.insert({skey, svalue});
    link1.SetDetails(details1);
    link1.SetUrl(svalue + "url");
    link1.SetDescription(svalue + "description");
    link1.GetUrl();
    link1.GetDescription();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Link>(link1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataFileFuzz(const uint8_t *data, size_t size)
{
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    File file1;
    file1.SetUri(svalue + "uri");
    file1.SetRemoteUri(svalue + "remoteUri");
    file1.GetUri();
    file1.GetRemoteUri();
    file1.GetSize();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<File>(file1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataImageFuzz(const uint8_t *data, size_t size)
{
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    Image image1;
    image1.SetUri(svalue + "uri");
    image1.SetRemoteUri(svalue + "remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Image>(image1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataVideoFuzz(const uint8_t *data, size_t size)
{
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    Video video1;
    video1.SetUri(svalue + "uri");
    video1.SetRemoteUri(svalue + "remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Video>(video1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedRecordFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    SystemDefinedRecord systemDefinedRecord1;
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedRecord1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedRecord>(systemDefinedRecord1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedFormFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    SystemDefinedForm systemDefinedForm1;
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedForm1.SetDetails(details1);
    auto formId = 123;
    systemDefinedForm1.SetFormId(formId);
    systemDefinedForm1.SetFormName(svalue + "formName");
    systemDefinedForm1.SetModule(svalue + "module");
    systemDefinedForm1.SetAbilityName(svalue + "abilityName");
    systemDefinedForm1.SetBundleName(svalue + "bundleName");
    systemDefinedForm1.GetFormId();
    systemDefinedForm1.GetFormName();
    systemDefinedForm1.GetBundleName();
    systemDefinedForm1.GetAbilityName();
    systemDefinedForm1.GetModule();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedForm>(systemDefinedForm1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedAppItemFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    SystemDefinedAppItem systemDefinedAppItem1;
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedAppItem1.SetDetails(details1);
    systemDefinedAppItem1.SetAppId(svalue + "appId");
    systemDefinedAppItem1.SetAppName(svalue + "appName");
    systemDefinedAppItem1.SetAppIconId(svalue + "appIconId");
    systemDefinedAppItem1.SetAppLabelId(svalue + "appLabelId");
    systemDefinedAppItem1.SetBundleName(svalue + "bundleName");
    systemDefinedAppItem1.SetAbilityName(svalue + "abilityName");
    systemDefinedAppItem1.GetAppId();
    systemDefinedAppItem1.GetAppName();
    systemDefinedAppItem1.GetBundleName();
    systemDefinedAppItem1.GetAbilityName();
    systemDefinedAppItem1.GetAppIconId();
    systemDefinedAppItem1.GetAppLabelId();
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedAppItem>(systemDefinedAppItem1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedPixelMapFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedPixelMap1.SetDetails(details1);
    std::vector<uint8_t> rawData1 = {1, 2, 3, 4, 5};
    systemDefinedPixelMap1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedPixelMap>(systemDefinedPixelMap1);
    data1.AddRecord(record1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void GetSummaryFuzz(const uint8_t *data, size_t size)
{
    std::string skey(data, data + size);
    std::string svalue(data, data + size);
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData UData;
    std::string key;

    UDDetails details;
    details.insert({skey, svalue});

    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text);
    UData.AddRecord(record1);

    PlainText plainText;
    plainText.SetDetails(details);
    plainText.SetContent(svalue + "content");
    plainText.SetAbstract(svalue + "abstract");
    std::shared_ptr<UnifiedRecord> record2 = std::make_shared<PlainText>(plainText);
    UData.AddRecord(record2);

    File file;
    file.SetUri(svalue + "uri");
    file.SetRemoteUri(svalue + "remoteUri");
    std::shared_ptr<UnifiedRecord> record3 = std::make_shared<File>(file);
    UData.AddRecord(record3);

    Image image;
    image.SetUri(svalue + "uri");
    image.SetRemoteUri(svalue + "remoteUri");
    std::shared_ptr<UnifiedRecord> record4 = std::make_shared<Image>(image);
    UData.AddRecord(record4);

    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record5 = std::make_shared<SystemDefinedRecord>(systemDefinedRecord);
    UData.AddRecord(record5);

    SystemDefinedForm systemDefinedForm;
    systemDefinedForm.SetDetails(details);
    auto formId = 123;
    systemDefinedForm.SetFormId(formId);
    systemDefinedForm.SetFormName(svalue + "formName");
    systemDefinedForm.SetModule(svalue + "module");
    systemDefinedForm.SetAbilityName(svalue + "abilityName");
    systemDefinedForm.SetBundleName(svalue + "bundleName");
    std::shared_ptr<UnifiedRecord> record6 = std::make_shared<SystemDefinedForm>(systemDefinedForm);
    UData.AddRecord(record6);

    UdmfClient::GetInstance().SetData(option1, UData, key);

    QueryOption option2 = {.key = key};
    Summary summary;
    UdmfClient::GetInstance().GetSummary(option2, summary);
    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    OHOS::SetUpTestCase();
    OHOS::SetDataFileFuzz(data, size);
    OHOS::SetDataHtmlFuzz(data, size);
    OHOS::SetDataImageFuzz(data, size);
    OHOS::SetDataLinkFuzz(data, size);
    OHOS::SetDataPlainTextFuzz(data, size);
    OHOS::SetDataSystemDefinedAppItemFuzz(data, size);
    OHOS::SetDataSystemDefinedFormFuzz(data, size);
    OHOS::SetDataSystemDefinedPixelMapFuzz(data, size);
    OHOS::SetDataSystemDefinedRecordFuzz(data, size);
    OHOS::SetDataTextFuzz(data, size);
    OHOS::SetDataVideoFuzz(data, size);
    OHOS::GetSummaryFuzz(data, size);
    OHOS::TearDown();
    return 0;
}