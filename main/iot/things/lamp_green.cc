#include "iot/thing.h"
#include "board.h"
#include "audio_codec.h"

#include <driver/gpio.h>
#include <esp_log.h>

#define TAG "Lamp_Green"

namespace iot {

// 这里仅定义 Lamp_Green 的属性和方法，不包含具体的实现
class Lamp_Green : public Thing {
private:
    gpio_num_t gpio_num_ = GPIO_NUM_17;
    bool Power_Green_ = false;

    void InitializeGpio() {
        gpio_config_t config = {
            .pin_bit_mask = (1ULL << gpio_num_),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
        ESP_ERROR_CHECK(gpio_config(&config));
        gpio_set_level(gpio_num_, 0);
    }

public:
// Lamp_Green :后台历史对话里显示的指令
// 一个测试用的灯: 这是什么设备，什么用途之类
// 灯是否打开: 相同或类似的说法，就会触发此操作
    Lamp_Green() : Thing("Lamp_Green", "一个绿色的氛围灯"), Power_Green_(false) {
        InitializeGpio();

        // 定义设备的属性
        properties_.AddBooleanProperty("Power_Green", "氛围灯是否打开", [this]() -> bool {
            return Power_Green_;
        });

        // 定义设备可以被远程执行的指令
        methods_.AddMethod("TurnOn", "打开绿灯", ParameterList(), [this](const ParameterList& parameters) {
            Power_Green_ = true;
            gpio_set_level(gpio_num_, 1);
        });

        methods_.AddMethod("TurnOff", "关闭绿灯", ParameterList(), [this](const ParameterList& parameters) {
            Power_Green_ = false;
            gpio_set_level(gpio_num_, 0);
        });
    }
};

} // namespace iot

DECLARE_THING(Lamp_Green);
