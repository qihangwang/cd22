#pragma once

#include <cmath>
#include <cstdint>
#include <vector>
#include <utility>

#define INITGUID
#include <Windows.h>

#include <ioctl.h>
#include <ifc_ldev.h>

#include <DAQ.h>

class LCardDaqTest;

namespace ros { namespace dc { namespace lcard {

// ��������� ����� �-����, ������������ ��� ��������� ������� ��� (����������� � ������������ ��������)
struct AdcRateParams
{
    double_t FClock;
    uint32_t FClock_MinDiv;
    uint32_t FClock_MaxDiv;
    uint16_t IKD_MinKoeff;
    uint16_t IKD_MaxKoeff;
    uint32_t IrqStep_Min;
    uint32_t IrqStep_Max;
};

// ����� ���/���/��� �� �-���� (����� lcomp)
class LCardDaq : public DAQ
{
    friend class ::LCardDaqTest;

public:
    LCardDaq() = default;

    ~LCardDaq() override;

    uint32_t GetBoardType() const { return board_type_; }

    char GetRevision() const { return _revision; }

    // DAQ

    tl::expected<void, std::error_code> Init(size_t slot_num) override;

    tl::expected<void, std::error_code> Deinit() override;

    tl::expected<void, std::error_code> TtlEnable(bool enable) override;

    tl::expected<void, std::error_code> TtlOut(uint16_t value) override;

    tl::expected<void, std::error_code> TtlOut_SetPin(uint16_t value) override;

    tl::expected<void, std::error_code> TtlOut_ClrPin(uint16_t value) override;

    tl::expected<uint16_t, std::error_code> TtlIn() override;

    tl::expected<void, std::error_code> AdcRead(double_t& reg_freq, size_t points_count, const _Channels& channels,
            int16_t* values, const std::function<FiniteAdcReadCallback>& callback, const std::atomic_bool& cancel_token) override;

    tl::expected<void, std::error_code> AdcRead(double_t& reg_freq, const _Channels& channels,
            const std::function<InfiniteAdcReadCallback>& callback, const std::chrono::milliseconds& callback_interval,
            const std::atomic_bool& cancel_token) override;

private:
#if INTPTR_MAX == INT64_MAX
    const char* const LCompName{"lcomp64.dll"};
#else
    const char* const LCompName{"lcomp.dll"};
#endif
    // �������� ��� �������� ���������� ��������� ������ ��� ������
    const std::chrono::milliseconds AdcFillDelay{1};
    // �������� ��������� ������ ����� callback ��� ������ finite AdcRead
    const std::chrono::milliseconds FiniteAdcReadCallbackInterval{100};

    tl::expected<void, std::error_code> NonVirtualDeinit();

    static const char* DetectBiosName(ULONG board_type);

    static char DetectRevision(ULONG board_type, const PLATA_DESCR_U2& plata_descr);

    static AdcRateParams DetectAdcRateParams(ULONG board_type, const PLATA_DESCR_U2& plata_descr);

    tl::expected<void, std::error_code> PrepareAdc(double_t& reg_freq, const _Channels& channels,
            const std::chrono::milliseconds& tick_interval, size_t& half_buffer, void** data, ULONG** sync);

    struct RateParams
    {
        uint32_t FClock_Div;
        uint16_t IKD_Koeff;
    };

    // ��������� ��������� ��� ��������� ������� ����������� ��� ����������� ������������ ������� � ����� � �������
    // channelRate ����� ������� (��������)
    // ����� ������� ___GetRate �� ������� UsbE_dll_v2.
    static RateParams SelectRate(const AdcRateParams& rateParams, double_t channelRate, size_t channelCount, double_t eps);

    struct AdcBufferParams
    {
        ULONG FIFO;
        ULONG IrqStep;
        ULONG Pages;
    };

    // ��������� ��������� ������ (������������ ��������� � ���) ����� �������, ��� �������� ������ ������� ��
    // tick_interval ��, ������ IrqStep ������ 32, ���������� Pages �� ����� 16 � ������ �������� ������ ������ �����
    // �������
    // ��� ������� ���������� �������� Pages ������� ����� sync ���������� ����� � � ��� callback ���������� ������������.
    static AdcBufferParams SelectAdcBuffer(const AdcRateParams& rateParams, double_t channelRate, size_t channelCount,
            const std::chrono::milliseconds& tick_interval);

    HINSTANCE lcomp_handle_{nullptr};
    IDaqLDevice* device_{nullptr};
    ULONG board_type_{NONE};
    char _revision{'\0'};
    AdcRateParams adc_rate_params_{};

    uint16_t ttl_out_value{0};
};

}}}
