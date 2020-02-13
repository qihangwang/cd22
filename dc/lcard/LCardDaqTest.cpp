#include <LCardDaq.h>

#include <chrono>
#include <fstream>
#include <future>
#include <thread>

#include <catch2/catch.hpp>

#include <RosMath.h>

// ������������� � LCardDaq �����
class LCardDaqTest
{
public:
    LCardDaqTest(ros::dc::lcard::LCardDaq& daq) :
        _daq{daq}
    {}

    tl::expected<void, std::error_code> PrepareAdc(double_t& reg_freq, const ros::dc::DAQ::_Channels& channels,
            const std::chrono::milliseconds& tick_interval, size_t& half_buffer, void** data, ULONG** sync)
    {
        return _daq.PrepareAdc(reg_freq, channels, tick_interval, half_buffer, data, sync);
    }

    static ros::dc::lcard::LCardDaq::AdcBufferParams SelectAdcBuffer(const ros::dc::lcard::AdcRateParams& rateParams,
            double_t channelRate, size_t channelCount, const std::chrono::milliseconds& tick_interval)
    {
        return ros::dc::lcard::LCardDaq::SelectAdcBuffer(rateParams, channelRate, channelCount, tick_interval);
    }

private:
    ros::dc::lcard::LCardDaq& _daq;
};

// ������� ������� � ���� � ������� dsv
template <typename T>
void ExportToDsv(const std::vector<T>& values, double_t dx, const std::string& filename)
{
    std::ofstream file{filename};

    for (size_t i = 0; i < values.size(); ++i) {
        file << i * dx << ";" << values[i] << std::endl;
    }
}

static_assert(sizeof(AdcRaw_t) == sizeof(int16_t), "AdcRaw_t size is not 16 bit");

using Harmonic = std::tuple<double_t, double_t, ptrdiff_t>;

// ����� ������������ ��������� � ������� �������
Harmonic FindMaxHarmonic(const std::vector<int16_t>& values, double_t df)
{
    assert(!values.empty());
    assert(df > 0);

    const size_t points_count{values.size()};

    const auto channel_mean = Mean_AdcRaw(values.data(), static_cast<uint32_t>(points_count));

    std::vector<double_t> ampls(points_count);
    std::vector<double_t> phases(points_count);

    if (!Rfft(values.data(), ampls.data(), phases.data(), static_cast<uint32_t>(points_count), channel_mean, false)) {
        return std::make_tuple(0.0, 0.0, -1);
    }

    // ������ �������� �� �� ���� ��������, � ������ � ��� ������ ��������� (�� �����������)
    const size_t spec_points_count{points_count / 2};

    Cmplx_Ampl(ampls.data(), phases.data(), static_cast<uint32_t>(points_count), static_cast<uint32_t>(spec_points_count));

    // zero DC
    ampls[0] = 0.0;

    const auto ampls_end{ampls.begin() + spec_points_count};
    const auto max_ampl_it = std::max_element(ampls.begin(), ampls_end);
    if (max_ampl_it == ampls_end) {
        return std::make_tuple(0.0, 0.0, -1);
    }

    const auto max_ampl_index = std::distance(ampls.begin(), max_ampl_it);

    assert(max_ampl_index >= 0);
    const auto max_ampl_freq = IndexToFrequency(static_cast<uint32_t>(max_ampl_index), df);

    return std::make_tuple(*max_ampl_it, max_ampl_freq, max_ampl_index);
}

// ����� ������������ ��������� � �������, ���������� �� ������� ���������� ������ (�� ���������� ������ �� ���)
Harmonic FindMaxHarmonicInChannel(const std::vector<int16_t>& values, size_t points_count, size_t channels_count,
        size_t channel_index, double_t reg_freq)
{
    assert(values.size() >= points_count * channels_count);
    assert(points_count > 0);
    assert(channels_count > 0);
    assert(channel_index <= channels_count);
    assert(reg_freq > 0);

    std::vector<int16_t> channel_values(points_count);

    ExtractChannelFromAdcFrames(values.data(), channel_values.data(), points_count, channels_count, channel_index);

    const auto dt{1 / (reg_freq * 1000)};
    const auto df{1 / (dt * points_count)};

    //ExportToDsv(channel_values, dt, "");

    return FindMaxHarmonic(channel_values, df);
}

const double_t RefRegFreq{12.8};

const uint16_t AdcCommonGnd{1 << 5};
const ros::dc::DAQ::_Channels RefChannels{0 | AdcCommonGnd, 1 | AdcCommonGnd, 2 | AdcCommonGnd, 3 | AdcCommonGnd};

TEST_CASE("LCardDaq AdcRead", "[LCardDaq]") {
    ros::dc::lcard::LCardDaq sut;

    // Init
    const auto init_opt = sut.Init(0);

    REQUIRE(init_opt);

    SECTION("finite mode") {
        double_t reg_freq{RefRegFreq};
        const size_t points_count{1024};
        std::vector<int16_t> vals(points_count * RefChannels.size());
        std::atomic_bool cancel_token{false};

        const auto adc_read_opt = sut.AdcRead(reg_freq, points_count, RefChannels, vals.data(), nullptr, cancel_token);

        REQUIRE(adc_read_opt);
        CHECK(reg_freq == Approx(RefRegFreq).epsilon(0.02));

        const size_t test_points_count{points_count};
        const auto max_harm = FindMaxHarmonicInChannel(vals, test_points_count, RefChannels.size(), 0, reg_freq);

        REQUIRE(std::get<2>(max_harm) != -1);
        CHECK(std::get<1>(max_harm) == Approx(262).margin(1.0));
    }

    SECTION("infinite mode") {
        double_t reg_freq{RefRegFreq};
        std::atomic_bool cancel_token{false};

        size_t callback_counter{0};
        std::vector<int16_t> vals;

        auto adc_read_f = std::async(std::launch::async, [&]() {
            const auto adc_read_callback = [&](const int16_t* values, size_t values_count) {
                callback_counter++;

                vals.insert(vals.end(), values, values + values_count);
            };

            return sut.AdcRead(reg_freq, RefChannels, adc_read_callback, std::chrono::milliseconds{100}, cancel_token);
        });

        std::this_thread::sleep_for(std::chrono::seconds{3});
        cancel_token = true;

        const auto adc_read_opt = adc_read_f.get();

        REQUIRE(adc_read_opt);
        CHECK(reg_freq == Approx(RefRegFreq).epsilon(0.02));
        REQUIRE(callback_counter > 0);
        REQUIRE(vals.size() > 0);

        const size_t test_points_count{1024};
        const auto max_harm = FindMaxHarmonicInChannel(vals, test_points_count, RefChannels.size(), 0, reg_freq);

        REQUIRE(std::get<2>(max_harm) != -1);
        CHECK(std::get<1>(max_harm) == Approx(262).margin(1.0));
    }

    sut.Deinit();
}

TEST_CASE("LCardDaq PrepareAdc", "[LCardDaq]") {
    const std::chrono::milliseconds RefCallbackInterval{555};

    ros::dc::lcard::LCardDaq sut;
    LCardDaqTest sut_test{sut};

    // Init
    const auto init_opt = sut.Init(0);

    REQUIRE(init_opt);

    // PrepareAdc
    double_t reg_freq{RefRegFreq};
    size_t half_buffer{0};
    void* data{nullptr};
    ULONG* sync{nullptr};
    
    const auto prepare_adc_opt = sut_test.PrepareAdc(reg_freq, RefChannels, RefCallbackInterval, half_buffer, &data, &sync);

    REQUIRE(prepare_adc_opt);
    CHECK(reg_freq == Approx(RefRegFreq).epsilon(0.02));
    CHECK(half_buffer % RefChannels.size() == 0);
    CHECK(half_buffer / RefChannels.size() / reg_freq == Approx(RefCallbackInterval.count()).margin(30));
    CHECK(data != nullptr);
    REQUIRE(sync != nullptr);
    CHECK(*sync == 0);

    sut.Deinit();
}

TEST_CASE("LCardDaq SelectAdcBuffer", "[LCardDaq]") {
    ros::dc::lcard::AdcRateParams rateParams{};
    rateParams.IrqStep_Min = 32;
    rateParams.IrqStep_Max = 64000;
    auto channelRate = GENERATE(range(3.0, 400.0, 11.1));
    auto channelCount = GENERATE(range(1, 32, 1));
    auto tick_interval_ = GENERATE(range(100, 3000, 111));

    const std::chrono::milliseconds tick_interval{tick_interval_};
    const auto adc_buffer = LCardDaqTest::SelectAdcBuffer(rateParams, channelRate, channelCount, tick_interval);

    CHECK(adc_buffer.FIFO != 0);
    CHECK(adc_buffer.IrqStep % 32 == 0);
    const size_t half_buffer{adc_buffer.IrqStep * adc_buffer.Pages / 2};
    CHECK(half_buffer % channelCount == 0);
    CHECK(half_buffer / channelCount / channelRate == Approx(tick_interval.count()).margin(30));
}
