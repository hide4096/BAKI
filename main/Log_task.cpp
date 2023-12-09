#include "include/Log_task.hpp"

Log_task::Log_task() : Base_task() {}

int Log_task::main_task_1() {
    log_print();
    std::cout << "main_task_1 : Log" << std::endl;
    return 0;
}

int Log_task::log() {
    std::cout << "log" << std::endl;
    return 0;
}

void Log_task::log_print() {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "logs");
    if (partition == NULL) {
        ESP_LOGE("log_print", "Partition error");
        return;
    }

    uint32_t mem_addr = partition->address;
    int16_t data[5];

    while(1) {
        esp_partition_read(partition, mem_addr, data, sizeof(data));
        printf("%4d,%4d,%4d,%4d,%4d\r\n", data[0], data[1], data[2], data[3], data[4]);
        mem_addr += sizeof(data);
        if (mem_addr >= partition->address + partition->size) {
            break;
        }
    }
}

